#pragma once

#include <cpu/cpu.hpp>
#include <memory/memory.hpp>

#include <globals.h>
#include <types.h>

namespace spinarak {
namespace emulator {

class Emulator {
private:
    spinarak::cpu::CPU cpu_;
    spinarak::memory::Memory memory_
public:
    Emulator() {
    }
    ~Emulator() {
    }
}

} // namespace example
} // namespace spinarak
