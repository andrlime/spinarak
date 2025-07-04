
#include <globals.hpp>
#include <memory/memory.hpp>
#include <types.hpp>

namespace spinarak {
namespace memory {

// blank memory
Memory::Memory()
{
    std::memset(&memory_contents_, 0, sizeof(memory_contents_));
}

Memory::Memory(std::pair<std::string, std::string> filenames)
{
    auto [bios, rom] = filenames;

    std::memset(&memory_contents_, 0, sizeof(memory_contents_));

    std::vector<byte_t> bios_buffer(0x100);
    read_file(bios_buffer, bios);

    std::vector<byte_t> rom_buffer(0x8000);
    read_file(rom_buffer, rom);

    std::memcpy(memory_contents_.bios, bios_buffer.data(), 0x100);
    std::memcpy(memory_contents_.rom_bank_00, rom_buffer.data(), 0x4000);
    std::memcpy(memory_contents_.rom_bank_01_nn, rom_buffer.data() + 0x4000, 0x4000);
}

auto
Memory::read_file(std::vector<byte_t>& buffer, std::string path) -> void
{
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) {
        throw std::runtime_error("failed to open file: " + path);
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    buffer.resize(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        throw std::runtime_error("failed to read file to buffer " + path);
    }
}

auto
Memory::read(word_t address) -> uint8_t
{
    if (address < 0x4000) {
        if (address < 0x100 && bios_active) {
            return memory_contents_.bios[address];
        }
        return memory_contents_.rom_bank_00[address];
    }
    if (address < 0x8000) {
        return memory_contents_.rom_bank_01_nn[address - 0x4000];
    }

    if (address < 0xA000) {
        return memory_contents_.vram[address - 0x8000];
    }
    if (address < 0xC000) {
        return memory_contents_.eram[address - 0xA000];
    }
    if (address < 0xD000) {
        return memory_contents_.wram0[address - 0xC000];
    }
    if (address < 0xE000) {
        auto bank = get_wram_bank();
        return memory_contents_.wram_bank[bank][address - 0xD000];
    }
    if (address < 0xFE00) {
        return read(address - 0x2000);
    }
    if (address < 0xFEA0) {
        return memory_contents_.oam[address - 0xFE00];
    }
    if (address < 0xFF00) {
        return memory_contents_.unusable[address - 0xFEA0];
    }
    if (address < 0xFF80) {
        return memory_contents_.io_registers[address - 0xFF00];
    }
    if (address < 0xFFFF) {
        return memory_contents_.hram[address - 0xFF80];
    }
    return memory_contents_.ie;
}

auto
Memory::write(word_t address, word_t value) -> void
{
    if (!!(value & 0xFF00)) {
        throw std::domain_error("attempted to write word with non-zero upper 8 bits");
    }
    if (address < 0x8000) {
        throw std::domain_error("invalid attempt to write to ROM address");
    }

    if (address < 0xA000) {
        memory_contents_.vram[address - 0x8000] = value;
        return;
    }
    if (address < 0xC000) {
        memory_contents_.eram[address - 0xA000] = value;
        return;
    }
    if (address < 0xD000) {
        memory_contents_.wram0[address - 0xC000] = value;
        return;
    }
    if (address < 0xE000) {
        auto bank = get_wram_bank();
        memory_contents_.wram_bank[bank][address - 0xD000] = value;
        return;
    }
    if (address < 0xFE00) {
        write(address - 0x2000, value);
        return;
    }
    if (address < 0xFEA0) {
        memory_contents_.oam[address - 0xFE00] = value;
        return;
    }
    if (address < 0xFF00) {
        memory_contents_.unusable[address - 0xFEA0] = value;
        return;
    }
    if (address < 0xFF80) {
        if (address == 0xFF50 && bios_active && value != 0) {
            bios_active = false;
        }
        memory_contents_.io_registers[address - 0xFF00] = value;
        return;
    }
    if (address < 0xFFFF) {
        memory_contents_.hram[address - 0xFF80] = value;
        return;
    }

    memory_contents_.ie = value;
}

} // namespace memory
} // namespace spinarak
