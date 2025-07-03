#pragma once

#include <globals.hpp>
#include <types.hpp>

#include <fstream>
#include <ios>
#include <stdexcept>
#include <vector>

namespace spinarak {
namespace memory {

// https://gbdev.io/pandocs/Memory_Map.html
struct memory_t {
    // BIOS stuff
    byte_t bios[0x100];

    // ROM
    byte_t rom_bank_00[0x4000];
    byte_t rom_bank_01_nn[0x4000];

    // mmaped RAM
    // NOTE: E000-FDFF mirrors C000–DDFF
    byte_t vram[0x2000];
    byte_t eram[0x2000];
    byte_t wram0[0x1000];
    byte_t wram_bank[7][0x1000];
    byte_t oam[0xA0];
    byte_t unusable[0x60]; // use prohibited
    byte_t io_registers[0x80];
    byte_t hram[0x7F];
    byte_t ie;
};

class Memory {
private:
    memory_t memory_contents_;
    bool bios_active = true;

public:
    Memory();
    Memory(std::pair<std::string, std::string> filenames);

    auto read_file(std::vector<byte_t>& buffer, std::string path) -> void;

    auto read(word_t address) -> byte_t;
    inline auto read16(word_t address) -> word_t
    {
        auto top = read(address) << 8;
        auto bottom = read(address + 1);
        return top | bottom;
    }

    // Only writes bytes
    auto write(word_t address, word_t value) -> void;
    
    // Only writes words (16 bits)
    inline auto write16(word_t address, word_t value) -> void
    {
        write(address, (value & 0xFF00) >> 8);
        write(address + 1, (value & 0x00FF));
    }

    inline auto
    get_memory_pointer() -> memory_t*
    {
        return &memory_contents_;
    }

    inline auto
    get_wram_bank() -> byte_t
    {
        byte_t bank = read(0xFF70) & 0x07;
        return (bank == 0) ? 0 : (bank - 1);
    }

    inline static auto
    factory() -> std::unique_ptr<Memory>
    {
        return std::make_unique<Memory>();
    }

    inline static auto
    factory(std::pair<std::string, std::string> filenames) -> std::unique_ptr<Memory>
    {
        return std::make_unique<Memory>(filenames);
    }
};

} // namespace memory
} // namespace spinarak
