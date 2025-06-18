#pragma once

#include <ios>
#include <fstream>
#include <stdexcept>
#include <vector>

#include <globals.hpp>
#include <types.hpp>

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
    memory_t cpu_contents_;
    bool bios_active = true;
public:
    Memory(std::string bios, std::string rom);

    void read_file(std::vector<byte_t> &buffer, std::string path);

    inline uint8_t get_wram_bank();

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);
};

} // namespace memory
} // namespace spinarak
