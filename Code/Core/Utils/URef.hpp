#pragma once

#include "URefHelper.hpp"

namespace LaughCrab
{
    // unique ptr

    template<typename T>
    class URef : public UnCopyable
    {
    public:
        URef() : m_ptr(URefHelper::InvalidPtr)
        {}

        URef(nullptr_t) : m_ptr(URefHelper::InvalidPtr)
        {}

        ~URef() override
        {
            if (*this)
            {
                Destroy();
            }
        }

        URef(URef &&ref) noexcept
        {
            m_ptr = ref.Release();
        }

        URef &operator=(nullptr_t) noexcept
        {
            Destroy();
        }

        URef &operator=(URef &&ref) noexcept
        {
            Reset(ref.Release());
        }

        T *operator->() const noexcept
        {
            return reinterpret_cast<T *>(ContentPtr());
        }

        T &operator*() const noexcept
        {
            return *reinterpret_cast<T *>(ContentPtr());
        }

        explicit operator bool() const noexcept
        {
            return ContentPtr() != nullptr;
        }

        T *Get() const
        {
            return reinterpret_cast<T *>(ContentPtr());
        }

        RawPtr Release() noexcept
        {
            RawPtr ret(m_ptr);
            m_ptr = URefHelper::InvalidPtr;
            return ret;
        }

        void Reset(RawPtr &&ptr)
        {
            Destroy();
            m_ptr = ptr;
            ptr = URefHelper::InvalidPtr;
        }

    private:
        Byte *ContentPtr() const
        {
            return m_ptr.block;
        }

        void Destroy()
        {
            if (ContentPtr() != nullptr)
            {
                reinterpret_cast<T *>(ContentPtr())->~T();
            }
            MemHelper::Deallocate(m_ptr);
        }

        explicit URef(RawPtr &&ptr) : m_ptr(ptr)
        {
            ptr = URefHelper::InvalidPtr;
        }

        template<typename T1, typename... Args>
        friend URef<T1> MakeURef(Args &&...args);

        template<typename T1, typename U>
        friend URef<T1> DynamicURefCast(URef<U> &&ref);

    private:
        RawPtr m_ptr;
    };

    template<typename T, typename... Args>
    inline URef<T> MakeURef(Args &&...args)
    {
        return URef<T>(URefHelper::Construct<T>(std::forward<Args>(args)...));
    }

    template<typename T, typename U>
    inline URef<T> DynamicURefCast(URef<U> &&ref)
    {
        return URef<T>(ref.Release());
    };

    // base -> derived
    template<typename Base, typename Derived, typename ...Args>
    static URef<Base> MakeDynamicURef(Args &&... args)
    {
        return DynamicURefCast<Base>(MakeURef<Derived>(std::forward<Derived>(args)...));
    };
}
