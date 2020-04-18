#pragma once

#include "Base.hpp"
#include <new>

namespace LaughCrab
{
    class MemUtils
    {
    public:
        // round up too align bytes
        template<Integer align = LAUGH_CRAB_ALIGN>
        static constexpr Integer GetAlignedBytes(Integer bytes)
        {
            return (bytes + align - 1) & (~(align - 1));
        }

        // allocate align memory
        template<Integer align = LAUGH_CRAB_ALIGN>
        static Byte *AlignMalloc(Integer size)
        {
            Byte *data = nullptr;
            Byte *start = nullptr;

            start = reinterpret_cast<Byte *>(::operator new(static_cast<Size >(size + align)));
            if (start != nullptr)
            {
                memset(start, 0, static_cast<Size >(size + align));
                data = reinterpret_cast<Byte *>((reinterpret_cast<Ptr>(start) + align - 1) & (~(align - 1)));

                if (data == start)
                {
                    data += align;
                }

                *(data - 1) = static_cast<Byte>(data - start);
            }

            return data;
        }

        // deallocate align memory
        template<Integer align = LAUGH_CRAB_ALIGN>
        static void AlignFree(Byte *data)
        {
            if (data == nullptr)
            {
                return;
            }

            Byte *start = data;
            start -= start[-1];

            ::operator delete(start);
        }

        static Integer GetExpOf2(Size number)
        {
            Integer i = 0;
            while (number != 0)
            {
                number >>= 1;
                ++i;
            }

            return i - 1;
        }
    };
}