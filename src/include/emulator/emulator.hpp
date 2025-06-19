#pragma once

#include <cpu/cpu.hpp>
#include <globals.hpp>
#include <memory/memory.hpp>
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
    inline Emulator(std::pair<std::string, std::string> filenames)
    {
        memory_ = Memory::factory(filenames);
        cpu_ = CPU::factory(memory_.get());
    }

    inline void
    run()
    {
        cpu_->tick();
    }
};

} // namespace emulator
} // namespace spinarak
