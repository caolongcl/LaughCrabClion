#pragma once

#include "TypeDef.hpp"
#include "MemUtils.hpp"
#include "DebugUtils.hpp"
#include "UnCopyable.hpp"

namespace LaughCrab
{
    class MemStack : public UnCopyable
    {
    public:
        using Mark = PtrDiff;
    public:
        MemStack();

//        MemStack(const MemStack &) = delete;

//        MemStack(MemStack &&) noexcept = delete;

//        MemStack &operator=(const MemStack &) = delete;

//        MemStack &operator=(MemStack &&) = delete;

        ~MemStack() override;

        Boolean Init();

        void Release();

        /// get a block
        Byte *Push(Size bytes);

        Byte *PushMark(Size bytes);

        /// return mem to last mark
        void Pop();

        void PopAll();

        void SetMark(Byte *data);

        Mark GetMark();

    private:
        Boolean HasMem(Size bytes);

    private:
        Size m_bytes;
        Mark m_mark;
        Byte *m_start;
        Byte *m_top;
    };
}