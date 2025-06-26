#include <gtest/gtest.h>
#include <cpu/cpu.hpp>
#include <memory/memory.hpp>

using spinarak::memory::Memory;
using spinarak::cpu::CPU;
using spinarak::cpu::Register;

TEST(LoadInstructionTest, LoadRegisterToRegister) {
    auto memory_ = Memory::factory();
    auto cpu_ = CPU::factory(memory_.get());

    cpu_->write_register<Register::B>(0x12);
    cpu_->write_register<Register::E>(0x24);
    cpu_->write_register<Register::F>(0x16);
    
    uint64_t cycles_start = cpu_->get_cycles();
    
    cpu_->ld<Register::D, Register::B>();
    ASSERT_EQ(cpu_->get_cycles() - cycles_start, 4);
    ASSERT_EQ(cpu_->read_register<Register::D>(), 0x12);

    cpu_->ld<Register::F, Register::D>();
    ASSERT_EQ(cpu_->get_cycles() - cycles_start, 8);
    ASSERT_EQ(cpu_->read_register<Register::F>(), 0x12);

    cpu_->ld<Register::A, Register::F>();
    cpu_->ld<Register::F, Register::E>();
    ASSERT_EQ(cpu_->get_cycles() - cycles_start, 16);
    ASSERT_EQ(cpu_->read_register<Register::F>(), 0x24);
    ASSERT_EQ(cpu_->read_register<Register::A>(), 0x12);
}
