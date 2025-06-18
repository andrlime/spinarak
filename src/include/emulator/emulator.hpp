#pragma once

#include <cpu/cpu.hpp>
#include <memory/memory.hpp>

#include <globals.hpp>
#include <types.hpp>

namespace spinarak {
namespace emulator {

using spinarak::cpu::CPU;
using spinarak::memory::Memory;

class Emulator {
private:
    std::unique_ptr<CPU> cpu_;
    std::unique_ptr<Memory> memory_;
public:
    inline Emulator(std::pair<std::string, std::string> filenames) :
        // cpu_(spinarak::cpu::factory()),
        memory_(Memory::factory(filenames))
        {};
};

} // namespace example
} // namespace spinarak
