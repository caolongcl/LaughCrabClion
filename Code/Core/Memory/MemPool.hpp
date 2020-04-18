#pragma once

#include "Base.hpp"
#include "MemUtils.hpp"
#include "UnCopyable.hpp"

// TODO
// 1, handle out of memory
// 2, multi thread
namespace LaughCrab {
    class MemPool : public UnCopyable {
    public:
        struct IdPtr {
            Byte *block;
            Integer index;
        };

        using IdPtr = struct IdPtr;
        static constexpr IdPtr InvalidPtr = {nullptr, -1};
    public:
        MemPool();

        ~MemPool() override;

        Boolean Init();

        void Release();

        IdPtr Allocate(Integer bytes);

        void Deallocate(IdPtr &idPtr);

    private:
        union BlockPtr {
            union BlockPtr *next;
            Byte self[1];
        };
        using BlockPtr = union BlockPtr;

        struct PoolHeader {
            Integer totals;
            Integer remains;
            Integer maxUseCount;
            Integer blockBytes;

            BlockPtr *start;
        };
        using PoolHeader = struct PoolHeader;

        struct ReservePoolHeader {
            Size bytes;
            BlockPtr *start;
        };
        using ReservePoolHeader = struct ReservePoolHeader;

        void CreatePool(PoolHeader *&header, Byte *&pool, Integer blockSize, Integer blockNum);

        inline const Integer GetBlockSize(Integer index) const;

        inline const Integer GetPoolIndex(Integer bytes) const;

        inline const Boolean hasBlock(Integer index) const;

        IdPtr GetBlock(Integer index);

        IdPtr BorrowBlock(Integer index);


    private:
        // common mem pool
        PoolHeader **m_normalPools;

        // when normal pools empty, we can get mem from reserves pools
        ReservePoolHeader m_reservePools;

        Integer m_align;
        Integer m_poolNum;
    };
}