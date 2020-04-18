#include "MemPool.hpp"
#include "Service/SysCfgService.hpp"
#include <chrono>
#include <thread>

using namespace LaughCrab;

MemPool::MemPool() : m_normalPools(nullptr), m_reservePools{0, nullptr}, m_align(16), m_poolNum(0)
{
}

MemPool::~MemPool()
{
    if (m_normalPools != nullptr)// || m_reservePools.start != nullptr)
    {
        Release();
    }
}

// alloc the pools's memory
Boolean MemPool::Init()
{
    Assert(g_sysCfgService != nullptr);

    auto align = g_sysCfgService->GetAlign();
    auto &blockNum = g_sysCfgService->GetMemPoolConfig().blockNum;
    auto &blockBytes = g_sysCfgService->GetMemPoolConfig().blockBytes;
    auto poolsNum = SysCfgService::MemPoolConfig::POOLS_NUM;

    // normal pools handle
    m_normalPools = new PoolHeader *[poolsNum];
    if (m_normalPools == nullptr)
    {
        Log::Error("MemPool", "MemPool::Init-->no more mem for pool header.");
        std::terminate();
    }

    for (auto j = 0; j < poolsNum; ++j)
    {
        m_normalPools[j] = new PoolHeader;
        if (m_normalPools == nullptr)
        {
            Log::Error("MemPool", "MemPool::Init-->no more mem for pool header.");
            std::terminate();
        }
    }

    // alloc total pools memory
    Integer poolsSize = 0;
    for (Integer k = 0; k < poolsNum; ++k)
    {
        poolsSize += (blockBytes[k] + sizeof(UInteger)) * blockNum[k];
    }

    Byte *mem = MemUtils::AlignMalloc(poolsSize);

    if (mem == nullptr)
    {
        Log::Error("MemPool", "MemPool::Init-->no more mem for pools.");
        std::terminate();
    }

    // create normal pools
    Byte *curPool = mem;

    for (Integer i = 0; i < poolsNum; ++i)
    {
        CreatePool(m_normalPools[i], curPool, blockBytes[i], blockNum[i]);
    }

    m_align = align;
    m_poolNum = poolsNum;
}

// change pool to blocks list
void MemPool::CreatePool(PoolHeader *&header, Byte *&pool, Integer blockSize, Integer blockNum)
{
    BlockPtr *cur = nullptr;
    BlockPtr *next = reinterpret_cast<BlockPtr *>(pool);

    header->start = next;

    for (auto i = 0; i < blockNum; ++i)
    {
        cur = next;
        next = reinterpret_cast<BlockPtr *>(cur->self + blockSize);

        if (i == blockNum - 1)
        {
            cur->next = nullptr;
        }
        else
        {
            cur->next = next;
        }
    }

    header->totals = blockNum;
    header->remains = blockNum;
    header->blockBytes = blockSize;
    header->maxUseCount = 0;

    pool += blockNum * blockSize;
}

// release pools
void MemPool::Release()
{
    MemUtils::AlignFree(reinterpret_cast<Byte *>(m_normalPools[0]->start->self));

    for (auto j = 0; j < m_poolNum; ++j)
    {
        delete m_normalPools[j];
    }

    delete[] m_normalPools;

    m_normalPools = nullptr;

    // !!! current no use
//    BlockPtr *cur = m_reservePools.start;
//    BlockPtr *next = cur->next;
//    while (cur)
//    {
//        next = cur->next;
//        AlignFree(cur->self);
//        cur = next;
//    }
//
//    m_reservePools.start = nullptr;
}

// GetBlockSize() and GetPoolIndex() are  symmetrical function
inline const Integer MemPool::GetBlockSize(Integer index) const
{
    return m_normalPools[index]->blockBytes;
}

inline const Integer MemPool::GetPoolIndex(Integer bytes) const
{
    Integer i = 0;
    for (; i < m_poolNum; ++i)
    {
        if (m_normalPools[i]->blockBytes - bytes >= 0)
        {
            break;
        }
    }
    return i;
}

inline const Boolean MemPool::hasBlock(Integer index) const
{
    return m_normalPools[index]->remains > 0;
}

MemPool::IdPtr MemPool::GetBlock(Integer index)
{
    PoolHeader *pool = m_normalPools[index];
    BlockPtr *cur = pool->start;

    pool->start = cur->next;
    pool->remains -= 1;

    Integer used = pool->totals - pool->remains;
    pool->maxUseCount = used > pool->maxUseCount ? used : pool->maxUseCount;

    return IdPtr{cur->self, index};
}

MemPool::IdPtr MemPool::BorrowBlock(Integer index)
{
    IdPtr idPtr = InvalidPtr;

    // borrow mem from other normal pool
    while (index < m_poolNum)
    {
        if (hasBlock(index))
        {
            idPtr = GetBlock(index);
            break;
        }
        index++;
    }

    return idPtr;
}

// allocate and deallocate
MemPool::IdPtr MemPool::Allocate(Integer bytes)
{
    IdPtr idPtr = InvalidPtr;

    Integer index = GetPoolIndex(bytes);

    if (index < m_poolNum)
    {
        if (hasBlock(index))
        {
            idPtr = GetBlock(index);
        }
        else
        {
            idPtr = BorrowBlock(index + 1);
        }
    }

    // no more mem in normal pool
    if (idPtr.block == nullptr)
    {
        while ((idPtr.block = MemUtils::AlignMalloc(bytes)) == nullptr)
        {
            //std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        idPtr.index = m_poolNum;
    }

    return idPtr;
}

void MemPool::Deallocate(IdPtr &idPtr)
{
    if (idPtr.block == nullptr)
    {
        return;
    }

    if (idPtr.index < m_poolNum)
    {
        Log::Debug("PoolHeader", "ptr %d %d", m_normalPools, idPtr.index);
        PoolHeader *pool = m_normalPools[idPtr.index];

        BlockPtr *cur = reinterpret_cast<BlockPtr *>(idPtr.block);

        cur->next = pool->start;
        pool->start = cur;

        pool->remains += 1;
    }
    else
    {
        MemUtils::AlignFree(idPtr.block);
    }
    idPtr = InvalidPtr;
}