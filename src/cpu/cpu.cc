#include <cpu/cpu.hpp>

namespace spinarak {
namespace cpu {

template <Register R>
inline auto
CPU::write_register(byte_t value) -> void
{
    if constexpr (R == Register::A) {
        cpu_contents_.a = value;
    }
    if constexpr (R == Register::F) {
        cpu_contents_.f.f = value;
    }
    if constexpr (R == Register::AF) {
        cpu_contents_.af = value;
    }
    if constexpr (R == Register::B) {
        cpu_contents_.b = value;
    }
    if constexpr (R == Register::C) {
        cpu_contents_.c = value;
    }
    if constexpr (R == Register::BC) {
        cpu_contents_.bc = value;
    }
    if constexpr (R == Register::D) {
        cpu_contents_.d = value;
    }
    if constexpr (R == Register::E) {
        cpu_contents_.e = value;
    }
    if constexpr (R == Register::DE) {
        cpu_contents_.de = value;
    }
    if constexpr (R == Register::H) {
        cpu_contents_.h = value;
    }
    if constexpr (R == Register::L) {
        cpu_contents_.l = value;
    }
    if constexpr (R == Register::HL) {
        cpu_contents_.hl = value;
    }
    if constexpr (R == Register::SP) {
        cpu_contents_.sp = value;
    }
    if constexpr (R == Register::PC) {
        cpu_contents_.pc = value;
    }

    throw std::runtime_error("attempted to write to unknown register");
}

template <Register R>
inline auto
CPU::read_register() -> byte_t
{
    if constexpr (R == Register::A) {
        return cpu_contents_.a;
    }
    if constexpr (R == Register::F) {
        return cpu_contents_.f.f; // flags is a bitfield, need the full value
    }
    if constexpr (R == Register::AF) {
        return cpu_contents_.af;
    }
    if constexpr (R == Register::B) {
        return cpu_contents_.b;
    }
    if constexpr (R == Register::C) {
        return cpu_contents_.c;
    }
    if constexpr (R == Register::BC) {
        return cpu_contents_.bc;
    }
    if constexpr (R == Register::D) {
        return cpu_contents_.d;
    }
    if constexpr (R == Register::E) {
        return cpu_contents_.e;
    }
    if constexpr (R == Register::DE) {
        return cpu_contents_.de;
    }
    if constexpr (R == Register::H) {
        return cpu_contents_.h;
    }
    if constexpr (R == Register::L) {
        return cpu_contents_.l;
    }
    if constexpr (R == Register::HL) {
        return cpu_contents_.hl;
    }
    if constexpr (R == Register::SP) {
        return cpu_contents_.sp;
    }
    if constexpr (R == Register::PC) {
        return cpu_contents_.pc;
    }

    throw std::runtime_error("attempted to read from unknown register");
}

} // namespace cpu
} // namespace spinarak
