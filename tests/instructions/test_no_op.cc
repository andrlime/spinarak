#include <gtest/gtest.h>
#include <cpu/cpu.hpp>
#include <memory/memory.hpp>

using spinarak::memory::Memory;
using spinarak::cpu::CPU;

TEST(NoOpInstructionTest, Basic) {
    auto memory_ = Memory::factory();
    auto cpu_ = CPU::factory(memory_.get());

    uint64_t cycles_start = cpu_->get_cycles();
    cpu_->no_op();
    uint64_t cycles_end = cpu_->get_cycles();
    ASSERT_EQ(cycles_end - cycles_start, 4);
}
