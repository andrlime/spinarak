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
    inline auto write_register(byte_t value) -> void;

    template <Register R>
    inline auto read_register() -> byte_t;

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
    auto ld(byte_t src) -> void;

    template <Register dest>
    auto ld(word_t src) -> void;

    template <Register src, WriteDirection direc>
    auto ld(byte_t dest) -> void;

    template <Register src, WriteDirection direc>
    auto ld(word_t dest) -> void;
};

} // namespace cpu
} // namespace spinarak
