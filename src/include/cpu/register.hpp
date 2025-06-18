#pragma once

#include <globals.hpp>
#include <types.hpp>

namespace spinarak {
namespace cpu {

enum class Register : byte_t {
    A, F, AF,
    B, C, BC,
    D, E, DE,
    H, L, HL,
    SP, PC
};

} // namespace example
} // namespace spinarak
