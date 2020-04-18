#include "MemStack.hpp"
#include "Service/SysCfgService.hpp"

using namespace LaughCrab;

MemStack::MemStack() : m_bytes(0), m_mark(0), m_start(nullptr), m_top(nullptr) {

}

MemStack::~MemStack() {
    if (m_start) {
        Release();
    }
}

Boolean MemStack::Init() {
    Assert(g_sysCfgService != nullptr);

    m_bytes = g_sysCfgService->GetMemStackConfig().bytes;
    Size bytes = m_bytes;
    m_top = m_start = MemUtils::AlignMalloc(bytes);
    if (m_start == nullptr) {
        Log::Error("MemStack", "MemStack::Init-->no more memory.");
        std::terminate();
    }
}

void MemStack::Release() {
    MemUtils::AlignFree(m_start);
    m_start = nullptr;
    m_mark = 0;
    m_bytes = 0;
}

/// get a block
Byte *MemStack::Push(Size bytes) {
    return HasMem(bytes) ? m_top : nullptr;
}

Byte *MemStack::PushMark(Size bytes) {
    Byte *data = Push(bytes);
    if (data != nullptr) {
        SetMark(data);
    }

    return data;
}

/// return mem to last mark
void MemStack::Pop() {
    m_top -= m_mark;
}

void MemStack::PopAll() {
    m_top = m_start;
    m_mark = 0;
}

void MemStack::SetMark(Byte *data) {
    Assert(data >= m_start);
    m_mark = data - m_start;
}

MemStack::Mark MemStack::GetMark() {
    return m_mark;
}

Boolean MemStack::HasMem(Size bytes) {
    return m_top + MemUtils::GetAlignedBytes(bytes) <= m_start + m_bytes;
}

