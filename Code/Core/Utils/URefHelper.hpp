#pragma once

#include "MemoryService.hpp"

namespace LaughCrab
{

    class URefHelper
    {
    public:
        static constexpr RawPtr InvalidPtr = {nullptr, -1};

        template<typename T, typename... Args>
        static RawPtr Construct(Args &&...args)
        {
            RawPtr ptr = MemHelper::Allocate(sizeof(T));
            if (ptr.block != nullptr)
            {
                ::new(ptr.block) T(std::forward<Args>(args)...);
            }
            return ptr;
        };
    };
}
