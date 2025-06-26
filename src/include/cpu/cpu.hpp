#pragma once

#include <cpu/register.hpp>
#include <globals.hpp>
#include <memory/memory.hpp>
#include <types.hpp>

#include <memory>

namespace spinarak {
namespace cpu {

using spinarak::memory::Memory;

union flags_t {
    struct {
        byte_t unused : 4;
        byte_t c : 1;
        byte_t h : 1;
        byte_t n : 1;
        byte_t z : 1;
    };

    byte_t f;
};

struct cpu_t {
    union {
        struct {
            flags_t f;
            byte_t a;
        };

        uint16_t af;
    };

    union {
        struct {
            byte_t c;
            byte_t b;
        };

        uint16_t bc;
    };

    union {
        struct {
            byte_t e;
            byte_t d;
        };

        uint16_t de;
    };

    union {
        struct {
            byte_t l;
            byte_t h;
        };

        uint16_t hl;
    };

    uint16_t sp;
    uint16_t pc;
};

class CPU {
private:
    uint64_t cycles_ = 0;
    cpu_t cpu_contents_;
    Memory* memory_;

    // ld register lookup table
    // horizontal order:
    //      B, C, D, E, H, L AtHL, A
    // vertical order:
    //      B D H AtHL for x0-x7
    //      C E L A for x8-xF
    static constexpr std::array<AllRegisters, 8> reg_lookup = {
        Register::B, Register::C, Register::D,      Register::E,
        Register::H, Register::L, AtRegister::AtHL, Register::A
    };

public:
    CPU(Memory* memory) : memory_(memory)
    {
        memset(&cpu_contents_, 0, sizeof(cpu_contents_));
    }

    template <Register R>
    inline auto
    write_register(byte_t value) -> void
    {
        if constexpr (R == Register::A) {
            cpu_contents_.a = value;
            return;
        }
        if constexpr (R == Register::F) {
            cpu_contents_.f.f = value;
            return;
        }
        if constexpr (R == Register::AF) {
            cpu_contents_.af = value;
            return;
        }
        if constexpr (R == Register::B) {
            cpu_contents_.b = value;
            return;
        }
        if constexpr (R == Register::C) {
            cpu_contents_.c = value;
            return;
        }
        if constexpr (R == Register::BC) {
            cpu_contents_.bc = value;
            return;
        }
        if constexpr (R == Register::D) {
            cpu_contents_.d = value;
            return;
        }
        if constexpr (R == Register::E) {
            cpu_contents_.e = value;
            return;
        }
        if constexpr (R == Register::DE) {
            cpu_contents_.de = value;
            return;
        }
        if constexpr (R == Register::H) {
            cpu_contents_.h = value;
            return;
        }
        if constexpr (R == Register::L) {
            cpu_contents_.l = value;
            return;
        }
        if constexpr (R == Register::HL) {
            cpu_contents_.hl = value;
            return;
        }
        if constexpr (R == Register::SP) {
            cpu_contents_.sp = value;
            return;
        }
        if constexpr (R == Register::PC) {
            cpu_contents_.pc = value;
            return;
        }

        throw std::runtime_error("attempted to write to unknown register");
    }

    template <Register R>
    inline auto
    read_register() -> byte_t
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

    inline auto
    get_cycles() -> uint64_t
    {
        return cycles_;
    }

    inline static auto
    factory(Memory* memory) -> std::unique_ptr<CPU>
    {
        return std::make_unique<CPU>(memory);
    }

    auto decode_and_execute(byte_t opcode) -> void;
    auto tick() -> void;

    // Instructions boilerplate starts here
    auto no_op() -> void;

    template <Register dest, Register src>
    auto ld() -> void;

    template <Register dest, AtRegister src>
    auto ld() -> void;

    template <AtRegister dest, Register src>
    auto ld() -> void;

    template <Register dest>
    auto ld(byte_t src) -> void requires Is8BitRegister<dest>;

    template <Register dest>
    auto ld(word_t src) -> void requires Is16BitRegister<dest>;

    template <Register src, WriteDirection direc>
    auto ld(byte_t dest) -> void;

    template <Register src, WriteDirection direc>
    auto ld(word_t dest) -> void;
};

} // namespace cpu
} // namespace spinarak

#include <cpu/instructions/ld.hpp>
#include <cpu/instructions/no_op.hpp>
