#pragma once

#include <cpu/cpu.hpp>
#include <globals.hpp>
#include <memory/memory.hpp>
#include <types.hpp>

#include <chrono>
#include <thread>

namespace spinarak {
namespace emulator {

using spinarak::cpu::CPU;
using spinarak::memory::Memory;

class Emulator {
private:
    std::unique_ptr<CPU> cpu_;
    std::unique_ptr<Memory> memory_;

public:
    inline Emulator()
    {
        memory_ = Memory::factory();
        cpu_ = CPU::factory(memory_.get());
    }

    inline Emulator(std::pair<std::string, std::string> filenames)
    {
        memory_ = Memory::factory(filenames);
        cpu_ = CPU::factory(memory_.get());
    }

    inline void
    run()
    {
        // TODO: fix condition
        while (true) {
            cpu_->tick();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
};

} // namespace emulator
} // namespace spinarak
