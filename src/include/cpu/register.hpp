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
enum class WriteDirection : byte_t { SrcToDest, DestToSrc };

template <Register R>
concept Is8BitRegister =
    R == Register::A || R == Register::F || R == Register::B || R == Register::C
    || R == Register::D || R == Register::E || R == Register::H || R == Register::L;

template <Register R>
concept Is16BitRegister =
    R == Register::AF || R == Register::BC || R == Register::DE || R == Register::HL
    || R == Register::SP || R == Register::PC;

template <AtRegister R>
concept Is16BitAtRegister =
    R == AtRegister::AtAF || R == AtRegister::AtBC || R == AtRegister::AtDE
    || R == AtRegister::AtHL || R == AtRegister::AtSP || R == AtRegister::AtPC;

using AllRegisters = std::variant<Register, AtRegister>;

enum class LoadDecoderBlock : byte_t {
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

} // namespace cpu
} // namespace spinarak
