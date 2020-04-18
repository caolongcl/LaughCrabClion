#pragma once

#include <cstdint>

namespace LaughCrab
{
    /// base data type define
    using Boolean = bool;
    using Byte = unsigned char;
    using Char = char;
    using Integer = std::int32_t;
    using UInteger = std::uint32_t;
    using Float = float;
    using Double = double;

    using Int8 = std::int8_t;
    using Int16 = std::int16_t;
    using Int32 = std::int32_t;
    using Int64 = std::int64_t;
    using UInt8 = std::uint8_t;
    using UInt16 = std::uint16_t;
    using UInt32 = std::uint32_t;
    using UInt64 = std::uint64_t;

    using Size = std::size_t;
    using SSize = std::intptr_t;

    using Ptr = std::intptr_t;
    using PtrDiff = std::ptrdiff_t;
}
