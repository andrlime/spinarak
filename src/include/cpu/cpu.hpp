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

public:
    CPU(Memory* memory) : memory_(memory)
    {
        memset(&cpu_contents_, 0, sizeof(cpu_contents_));
    }

    template <Register R>
    inline auto write_register(byte_t value) -> void;

    template <Register R>
    inline auto read_register() -> byte_t;

    inline static auto
    factory(Memory* memory) -> std::unique_ptr<CPU>
    {
        return std::make_unique<CPU>(memory);
    }

    auto no_op() -> void;
    auto stop() -> void;

    auto decode_and_execute(byte_t opcode) -> void;

    auto tick() -> void;
};

} // namespace cpu
} // namespace spinarak
