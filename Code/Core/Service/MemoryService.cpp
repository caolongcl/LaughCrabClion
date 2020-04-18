#include "MemoryService.hpp"

using namespace LaughCrab;

MemoryService::MemoryService() : m_memStack(nullptr), m_memPool(nullptr)
{

}

MemoryService::~MemoryService()
{

}

Boolean MemoryService::Init()
{
//    m_memStack = new MemStack();
//    Assert(m_memStack != nullptr);
//    m_memStack->Init();

    m_memPool = new MemPool();
    Assert(m_memPool != nullptr);
    m_memPool->Init();

    return true;
}

void MemoryService::Update()
{}

void MemoryService::DeInit()
{
    m_memPool->Release();
//    m_memStack->Release();
}

void MemoryService::Start()
{}

void MemoryService::Stop()
{}

void MemoryService::Restart()
{}
