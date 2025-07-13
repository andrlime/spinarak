#pragma once

#include <cpu/decoder.hpp>
#include <cpu/register.hpp>
#include <globals.hpp>
#include <memory/memory.hpp>
#include <types.hpp>

#include <iostream>
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

        word_t af;
    };

    union {
        struct {
            byte_t c;
            byte_t b;
        };

        word_t bc;
    };

    union {
        struct {
            byte_t e;
            byte_t d;
        };

        word_t de;
    };

    union {
        struct {
            byte_t l;
            byte_t h;
        };

        word_t hl;
    };

    word_t sp;
    word_t pc;
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
    static constexpr std::array<AllRegisters, 8> reg8_lookup = {
        Register::B, Register::C, Register::D,      Register::E,
        Register::H, Register::L, AtRegister::AtHL, Register::A
    };

    static constexpr std::array<AllRegisters, 8> reg16_lookup = {
        Register::BC, Register::DE, Register::HL, Register::SP
    };

public:
    CPU(Memory* memory) : memory_(memory)
    {
        memset(&cpu_contents_, 0, sizeof(cpu_contents_));
    }

    inline auto
    print_state(std::ostream& os = std::cout) -> void
    {
        os << "=== CPU State ===\n";
        os << "AF: 0x" << std::hex << std::setw(4) << std::setfill('0')
           << static_cast<int>(cpu_contents_.af) << "\t";
        os << "A: 0x" << std::hex << std::setw(2) << std::setfill('0')
           << static_cast<int>(cpu_contents_.a) << "\t";
        os << "F: 0x" << std::hex << std::setw(2) << std::setfill('0')
           << static_cast<int>(cpu_contents_.f.f) << "\n";

        os << "BC: 0x" << std::hex << std::setw(4) << std::setfill('0')
           << static_cast<int>(cpu_contents_.bc) << "\t";
        os << "B: 0x" << std::hex << std::setw(2) << std::setfill('0')
           << static_cast<int>(cpu_contents_.b) << "\t";
        os << "C: 0x" << std::hex << std::setw(2) << std::setfill('0')
           << static_cast<int>(cpu_contents_.c) << "\n";

        os << "DE: 0x" << std::hex << std::setw(4) << std::setfill('0')
           << static_cast<int>(cpu_contents_.de) << "\t";
        os << "D: 0x" << std::hex << std::setw(2) << std::setfill('0')
           << static_cast<int>(cpu_contents_.d) << "\t";
        os << "E: 0x" << std::hex << std::setw(2) << std::setfill('0')
           << static_cast<int>(cpu_contents_.e) << "\n";

        os << "HL: 0x" << std::hex << std::setw(4) << std::setfill('0')
           << static_cast<int>(cpu_contents_.hl) << "\t";
        os << "H: 0x" << std::hex << std::setw(2) << std::setfill('0')
           << static_cast<int>(cpu_contents_.h) << "\t";
        os << "L: 0x" << std::hex << std::setw(2) << std::setfill('0')
           << static_cast<int>(cpu_contents_.l) << "\n";

        os << "SP: 0x" << std::hex << std::setw(4) << std::setfill('0')
           << static_cast<int>(cpu_contents_.sp) << "\n";
        os << "PC: 0x" << std::hex << std::setw(4) << std::setfill('0')
           << static_cast<int>(cpu_contents_.pc) << "\n";

        os << "Flags: "
           << "[Z:" << +cpu_contents_.f.z << " N:" << +cpu_contents_.f.n
           << " H:" << +cpu_contents_.f.h << " C:" << +cpu_contents_.f.c << "]\n";

        os << "Cycles: " << std::dec << cycles_ << "\n";
    }

    template <Register R>
    inline auto
    write_register(word_t value) -> void
    requires Is16BitRegister<R>
    {
        if constexpr (R == Register::AF) {
            cpu_contents_.af = value;
            return;
        }
        if constexpr (R == Register::BC) {
            cpu_contents_.bc = value;
            return;
        }
        if constexpr (R == Register::DE) {
            cpu_contents_.de = value;
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
    write_register(byte_t value) -> void
    requires Is8BitRegister<R>
    {
        if constexpr (R == Register::A) {
            cpu_contents_.a = value;
            return;
        }
        if constexpr (R == Register::F) {
            cpu_contents_.f.f = value;
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
        if constexpr (R == Register::D) {
            cpu_contents_.d = value;
            return;
        }
        if constexpr (R == Register::E) {
            cpu_contents_.e = value;
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

        throw std::runtime_error("attempted to write to unknown register");
    }

    template <Register R>
    inline auto
    read_register() -> word_t
    requires Is16BitRegister<R>
    {
        if constexpr (R == Register::AF) {
            return cpu_contents_.af;
        }
        if constexpr (R == Register::BC) {
            return cpu_contents_.bc;
        }
        if constexpr (R == Register::DE) {
            return cpu_contents_.de;
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

    template <AtRegister R>
    inline auto
    read_register() -> word_t
    requires Is16BitAtRegister<R>
    {
        if constexpr (R == AtRegister::AtAF) {
            return cpu_contents_.af;
        }
        if constexpr (R == AtRegister::AtBC) {
            return cpu_contents_.bc;
        }
        if constexpr (R == AtRegister::AtDE) {
            return cpu_contents_.de;
        }
        if constexpr (R == AtRegister::AtHL) {
            return cpu_contents_.hl;
        }
        if constexpr (R == AtRegister::AtSP) {
            return cpu_contents_.sp;
        }
        if constexpr (R == AtRegister::AtPC) {
            return cpu_contents_.pc;
        }

        throw std::runtime_error("attempted to read from unknown register");
    }

    template <Register R>
    inline auto
    read_register() -> byte_t
    requires Is8BitRegister<R>
    {
        if constexpr (R == Register::A) {
            return cpu_contents_.a;
        }
        if constexpr (R == Register::F) {
            return cpu_contents_.f.f; // flags is a bitfield, need the full value
        }
        if constexpr (R == Register::B) {
            return cpu_contents_.b;
        }
        if constexpr (R == Register::C) {
            return cpu_contents_.c;
        }
        if constexpr (R == Register::D) {
            return cpu_contents_.d;
        }
        if constexpr (R == Register::E) {
            return cpu_contents_.e;
        }
        if constexpr (R == Register::H) {
            return cpu_contents_.h;
        }
        if constexpr (R == Register::L) {
            return cpu_contents_.l;
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

    // TODO: Write decoder.hpp class and abstract this away
    // Use friend class
    auto decode_and_execute(const byte_t opcode) -> void;
    auto tick() -> void;

    // Decoder boilerplate TODO: move to decoder class
    template <Register R>
    auto ld16BitImmediate(const byte_t opcode) -> void;
    template <decoder::Load B>
    auto ldToAtRegister(const byte_t opcode) -> void;

    // Instructions boilerplate starts here
    auto no_op() -> void;
    auto not_implemented() -> void;

    // ld generic
    template <Register dest, Register src>
    auto ld() -> void;

    // load at
    template <Register dest, AtRegister src>
    auto ld() -> void
    requires Is16BitAtRegister<src>;
    template <AtRegister dest, Register src>
    auto ld() -> void
    requires Is16BitAtRegister<dest>;

    // immediate
    template <Register dest>
    auto ld(const word_t src) -> void
    requires Is8BitRegister<dest>;
    template <Register dest>
    auto ld(const word_t src) -> void
    requires Is16BitRegister<dest>;

    // load to/from literal address
    template <Register src, WriteDirection direc>
    auto ld(const byte_t dest) -> void;
    template <Register src, WriteDirection direc>
    auto ld(const word_t dest) -> void;
};

} // namespace cpu
} // namespace spinarak

#include <cpu/instructions/ld.hpp>
#include <cpu/instructions/no_op.hpp>
#include <cpu/instructions/not_implemented.hpp>
