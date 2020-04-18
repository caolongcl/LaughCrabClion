#pragma once

#include "MemoryService.hpp"

namespace LaughCrab
{

    class RefHelper
    {
    public:
        static constexpr RawPtr InvalidPtr = {nullptr, -1};

        template<typename T, typename... Args>
        static RawPtr Construct(Args &&...args)
        {
            RawPtr ptr = MemHelper::Allocate(sizeof(UInteger) + sizeof(T));
            if (ptr.block != nullptr)
            {
                ::new(ptr.block) UInteger(1);
                ::new(ptr.block + sizeof(UInteger)) T(std::forward<Args>(args)...);
            }
            return ptr;
        };
    };
}
