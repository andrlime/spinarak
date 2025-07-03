#include <gtest/gtest.h>
#include <cpu/cpu.hpp>
#include <memory/memory.hpp>

using spinarak::memory::Memory;
using spinarak::cpu::CPU;
using spinarak::cpu::Register;
using spinarak::cpu::AtRegister;

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

TEST(LoadInstructionTest, LoadAtRegisterToRegister) {
    auto memory_ = Memory::factory();
    auto cpu_ = CPU::factory(memory_.get());

    memory_->write(0x9000, 0x34);
    cpu_->write_register<Register::BC>(0x9000);
    
    uint64_t cycles_start = cpu_->get_cycles();
    
    cpu_->ld<Register::D, AtRegister::AtBC>();
    ASSERT_EQ(cpu_->get_cycles() - cycles_start, 8);
    ASSERT_EQ(cpu_->read_register<Register::D>(), 0x34);
}

TEST(LoadInstructionTest, LoadRegisterToAtRegister) {
    auto memory_ = Memory::factory();
    auto cpu_ = CPU::factory(memory_.get());

    cpu_->write_register<Register::D>(0x12);
    cpu_->write_register<Register::BC>(0x9000);

    uint64_t cycles_start = cpu_->get_cycles();
    cpu_->ld<AtRegister::AtBC, Register::D>();
    
    ASSERT_EQ(cpu_->get_cycles() - cycles_start, 8);
    ASSERT_EQ(memory_->read(0x9000), 0x12);
}

TEST(LoadInstructionTest, Load8BitImmediateTo8BitRegister) {
    auto memory_ = Memory::factory();
    auto cpu_ = CPU::factory(memory_.get());

    byte_t imm = 0x12;

    uint64_t cycles_start = cpu_->get_cycles();
    cpu_->ld<Register::D>(imm);

    ASSERT_EQ(cpu_->get_cycles() - cycles_start, 8);
    ASSERT_EQ(cpu_->read_register<Register::D>(), imm);
}

TEST(LoadInstructionTest, Load16BitImmediateTo8BitRegister) {
    auto memory_ = Memory::factory();
    auto cpu_ = CPU::factory(memory_.get());

    word_t imm = 0x1234;

    uint64_t cycles_start = cpu_->get_cycles();
    ASSERT_THROW(cpu_->ld<Register::D>(imm), std::domain_error);
}

TEST(LoadInstructionTest, Load16BitImmediateTo16BitRegister) {
    auto memory_ = Memory::factory();
    auto cpu_ = CPU::factory(memory_.get());

    word_t imm = 0x1234;

    uint64_t cycles_start = cpu_->get_cycles();
    cpu_->ld<Register::BC>(imm);

    ASSERT_EQ(cpu_->get_cycles() - cycles_start, 12);
    ASSERT_EQ(cpu_->read_register<Register::BC>(), imm);
}
