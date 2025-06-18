#pragma once

#include <globals.hpp>
#include <types.hpp>

namespace spinarak {
namespace cpu {

using spinarak::globals;

union flags_t {
    struct {
        byte_t unused : 4;  // bits 0–3
        byte_t c : 1;       // bit 4
        byte_t h : 1;       // bit 5
        byte_t n : 1;       // bit 6
        byte_t z : 1;       // bit 7
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
    cpu_t cpu_contents_;
public:
    CPU() {
    }
    ~CPU() {
    }
};

} // namespace example
} // namespace spinarak
