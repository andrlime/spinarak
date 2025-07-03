#include <gtest/gtest.h>
#include <memory/memory.hpp>
#include <types.hpp>

using spinarak::memory::Memory;

TEST(MemoryTest, Factory_CanCreateBlank) {
    ASSERT_NO_THROW({
        auto memory = std::make_unique<Memory>();
    });
}

TEST(MemoryTest, ReadMemory_Can) {
    auto memory = Memory::factory();
    auto memory_pointer = memory->get_memory_pointer();

    for (size_t addr = 0; addr < 0x100; addr ++) {
        memory_pointer->bios[addr] = addr;
    }
    for (size_t addr = 0; addr < 0x100; addr ++) {
        ASSERT_EQ(memory->read(addr), addr);
    }

    for (size_t addr = 0; addr < 0x100; addr ++) {
        memory_pointer->bios[addr] = addr;
    }
    for (size_t addr = 0; addr < 0x100; addr ++) {
        ASSERT_EQ(memory->read(addr), addr);
    }
}

TEST(MemoryTest, WriteMemory_Can) {
    auto memory = Memory::factory();

    for (size_t addr = 0x8000; addr <= 0xFFFF; addr ++) {
        memory->write(addr, addr & 0xFF);
    }
    for (size_t addr = 0x8000; addr <= 0xFFFF; addr ++) {
        auto fetched = memory->read(addr);
        ASSERT_EQ(fetched, addr & 0xFF);
    }
}

TEST(MemoryTest, ReadWriteMemory_16Bits) {
    auto memory = Memory::factory();

    for (size_t addr = 0x8000; addr < 0xE000; addr += 2) {
        memory->write16(addr, addr);
    }
    for (size_t addr = 0x8000; addr < 0xE000; addr += 2) {
        auto fetched = memory->read16(addr);
        ASSERT_EQ(fetched, addr);
    }
}

TEST(MemoryTest, WriteMemory_FailsOnNonByteInput) {
    auto memory = Memory::factory();

    ASSERT_THROW(memory->write(0x8000, 0x0100), std::domain_error);
    ASSERT_THROW(memory->write(0x8000, 0x0400), std::domain_error);
    ASSERT_THROW(memory->write(0x8000, 0x2000), std::domain_error);
    ASSERT_THROW(memory->write(0x8000, 0x4000), std::domain_error);
    ASSERT_THROW(memory->write(0x8000, 0x8000), std::domain_error);
    ASSERT_THROW(memory->write(0x8000, 0xF000), std::domain_error);
}

TEST(MemoryTest, FailsOnWriteToRom) {
    auto memory = Memory::factory();
    ASSERT_THROW(memory->write(0x0000, 0x12), std::domain_error);
    ASSERT_THROW(memory->write(0x1000, 0x12), std::domain_error);
}

TEST(MemoryTest, DisablesBiosSuccessfully) {
    auto memory = Memory::factory();
    auto memory_pointer = memory->get_memory_pointer();

    memory_pointer->bios[0] = 0x12;
    memory_pointer->rom_bank_00[0] = 0x34;
    ASSERT_EQ(memory->read(0x00), 0x12);

    memory->write(0xFF50, 0x01);
    ASSERT_EQ(memory->read(0x00), 0x34);
}
