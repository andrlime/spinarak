#pragma once

#include <globals.hpp>
#include <types.hpp>

#include <variant>

namespace spinarak {
namespace decoder {

enum class Load : byte_t {
    Ld02,
    Ld12,
    Ld22,
    Ld32,
    Ld70,
    Ld71,
    Ld72,
    Ld73,
    Ld74,
    Ld75,
    Ld77,
};

enum class LoadPlusMinus : byte_t {
    Normal = 0,
    Plus,
    Minus,
};

} // namespace decoder
} // namespace spinarak
