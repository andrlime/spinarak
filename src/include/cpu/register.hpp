#pragma once

#include <globals.hpp>
#include <types.hpp>

#include <variant>

namespace spinarak {
namespace cpu {

enum class Register : byte_t { A, F, AF, B, C, BC, D, E, DE, H, L, HL, SP, PC };
enum class AtRegister : byte_t {
    AtA,
    AtF,
    AtAF,
    AtB,
    AtC,
    AtBC,
    AtD,
    AtE,
    AtDE,
    AtH,
    AtL,
    AtHL,
    AtSP,
    AtPC
};
enum class WriteDirection : byte_t {
    SrcToDest,
    DestToSrc
};

using AllRegisters = std::variant<Register, AtRegister>;

} // namespace cpu
} // namespace spinarak
