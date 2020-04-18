#pragma once

#include "TypeDef.hpp"
#include "Ref.hpp"

#include <memory>

namespace LaughCrab
{
    enum class GlobType
    {
        eGlobText = 0,
        eGlobBinary
    };

    class Glob : public UnCopyable, public UnMovable
    {
    public:
        Glob(GlobType type, Integer size);

        ~Glob() override;

        Byte *GetData()
        { return m_data.block; }

        const Byte *GetData() const
        { return m_data.block; }

        GlobType GetType()
        { return m_type; }

        Integer GetBytes()
        { return m_size; }

    private:
        GlobType m_type;
        Integer m_size;
        RawPtr m_data;
    };
}