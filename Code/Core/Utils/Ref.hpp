#pragma once

#include "RefHelper.hpp"

#include <type_traits>

namespace LaughCrab
{
    template<typename T>
    class Ref
    {
    public:
        Ref() : m_ptr(RefHelper::InvalidPtr)
        {}

        Ref(const Ref &ref) : m_ptr(ref.m_ptr)
        {
            AddRef();
        }

        Ref &operator=(nullptr_t) noexcept
        {
            DeRef();
            if (IsRefZero())
            {
                Release();
            }
            m_ptr = RefHelper::InvalidPtr;
        }

        Ref &operator=(const Ref &ref)
        {
            if (&ref == this)
            {
                return *this;
            }

            if (m_ptr.block != nullptr)
            {
                DeRef();
            }
            m_ptr = ref.m_ptr;
            AddRef();

            return *this;
        }

        Ref(Ref &&ref) noexcept : m_ptr(ref.m_ptr)
        {
            ref.m_ptr = RefHelper::InvalidPtr;
        }

        Ref &operator=(Ref &&ref) noexcept
        {
            if (&ref == this)
            {
                return *this;
            }
            if (m_ptr.block != nullptr)
            {
                DeRef();
            }
            m_ptr = ref.m_ptr;
            ref.m_ptr = RefHelper::InvalidPtr;
            return *this;
        }

        ~Ref()
        {
            if (m_ptr.block)
            {
                DeRef();
                if (IsRefZero())
                {
                    Release();
                }
            }
        }

        //
        T *operator->() const noexcept
        {
            return reinterpret_cast<T *>(ContentPtr());
        }

        T &operator*() const noexcept
        {
            return *reinterpret_cast<T *>(ContentPtr());
        }

        UInteger UseCount() const noexcept
        {
            return RefCount();
        }

        explicit operator bool() const noexcept
        {
            return m_ptr.block != nullptr;
        }

        T *Get() const
        {
            return reinterpret_cast<T *>(ContentPtr());
        }

    private:
        explicit Ref(RawPtr &&ptr) : m_ptr(ptr)
        {
        }

        explicit Ref(const RawPtr &ptr) : m_ptr(ptr)
        {
            AddRef();
        }

        template<typename T1, typename... Args>
        friend Ref<T1> MakeRef(Args &&...args);

        template<typename T1, typename U>
        friend Ref<T1> DynamicRefCast(const Ref<U> &ref);

    private:
        UInteger &RefCount()
        {
            return *reinterpret_cast<UInteger *>(RefCountPtr());
        }

        const UInteger &RefCount() const
        {
            return *reinterpret_cast<UInteger *>(RefCountPtr());
        }

        void AddRef()
        {
            ++RefCount();
            Log::Debug("AddRef", "ref:%d", RefCount());
        }

        void DeRef()
        {
            --RefCount();
            Log::Debug("DRef", "ref:%d", RefCount());
        }

        Boolean IsRefZero()
        {
            return RefCount() == 0;
        }

        Boolean IsRefOne()
        {
            return RefCount() == 1;
        }

        void _Destroy(std::false_type)
        {
            if (m_ptr.block != nullptr)
            {
                reinterpret_cast<T *>(ContentPtr())->~T();
            }
        }

        void _Destroy(std::true_type)
        {
        }

        void Release()
        {
            using trivially = typename std::is_trivially_destructible<T>::type;
            _Destroy(trivially());
            MemHelper::Deallocate(m_ptr);
        }

        Byte *RefCountPtr() const
        {
            return m_ptr.block;
        }

        Byte *ContentPtr() const
        {
            return m_ptr.block + sizeof(UInteger);
        }

    private:
        RawPtr m_ptr;
    };

    template<typename T, typename... Args>
    inline Ref<T> MakeRef(Args &&...args)
    {
        return Ref<T>(RefHelper::Construct<T>(std::forward<Args>(args)...));
    }

    template<typename T, typename U>
    inline Ref<T> DynamicRefCast(const Ref<U> &ref)
    {
        return Ref<T>(ref.m_ptr);
    };

    // base -> derived
    template<typename Base, typename Derived, typename ...Args>
    static Ref<Base> MakeDynamicRef(Args &&... args)
    {
        return DynamicRefCast<Base>(MakeRef<Derived>(std::forward<Derived>(args)...));
    };
}
