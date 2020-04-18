#pragma once

#include "Base.hpp"
#include "Service.hpp"
#include "MemPool.hpp"
#include "MemStack.hpp"
#include "UnCopyable.hpp"

namespace LaughCrab {
    using RawPtr = MemPool::IdPtr;

    class MemoryService : public Service {
    public:
        friend class MemHelper;

        MemoryService();

        ~MemoryService() override;

        void Start() override;

        void Stop() override;

        void Restart() override;

        Boolean Init() override;

        void Update() override;

        void DeInit() override;

    private:
        RawPtr Allocate(Integer bytes) {
            return m_memPool->Allocate(bytes);
        }

        void Deallocate(RawPtr &ptr) {
            m_memPool->Deallocate(ptr);
        }

        template<typename T, typename... Args>
        inline RawPtr &Construct(RawPtr &ptr, Args &&...args) {
            if (ptr.block != nullptr) {
                ::new(ptr.block) T(std::forward<Args>(args)...);
            }
            return ptr;
        };

        template<typename T>
        inline void Destroy(RawPtr &ptr) {
            if (ptr.block != nullptr) {
                reinterpret_cast<T *>(ptr.block)->~T();
            }
        }


    private:
        MemStack *m_memStack;
        MemPool *m_memPool;
    };

    extern MemoryService *g_memoryService;


    class MemHelper {
    public:
        static RawPtr Allocate(Integer bytes) {
            Log::Debug("MemHelper", "alloc bytes:%d", bytes);
            return g_memoryService->Allocate(bytes);
        }

        static void Deallocate(RawPtr &ptr) {
            Log::Debug("MemHelper", "dealloc index:%d", ptr.index);
            g_memoryService->Deallocate(ptr);
        }

        template<typename T, typename... Args>
        static RawPtr &Construct(RawPtr &ptr, Args &&...args) {
            return g_memoryService->Construct<T>(ptr, std::forward<Args>(args)...);
        };

        template<typename T>
        static void Destroy(RawPtr &ptr) {
            g_memoryService->Destroy<T>(ptr);
        }
    };

}