
#include <globals.hpp>
#include <memory/memory.hpp>
#include <types.hpp>

namespace spinarak {
namespace memory {

Memory::Memory(std::pair<std::string, std::string> filenames)
{
    auto [bios, rom] = filenames;

    std::memset(&cpu_contents_, 0, sizeof(cpu_contents_));

    std::vector<byte_t> bios_buffer(0x100);
    read_file(bios_buffer, bios);

    std::vector<byte_t> rom_buffer(0x8000);
    read_file(rom_buffer, rom);

    std::memcpy(cpu_contents_.bios, bios_buffer.data(), 0x100);
    std::memcpy(cpu_contents_.rom_bank_00, rom_buffer.data(), 0x4000);
    std::memcpy(cpu_contents_.rom_bank_01_nn, rom_buffer.data() + 0x4000, 0x4000);
}

auto
Memory::read_file(std::vector<byte_t>& buffer, std::string path) -> void
{
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) {
        throw std::runtime_error("failed to open file " + path);
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    buffer.resize(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        throw std::runtime_error("failed to read file to buffer " + path);
    }
}

auto
Memory::read(uint16_t address) -> uint8_t
{
    if (address < 0x4000) {
        if (address < 0x100 && bios_active) {
            return cpu_contents_.bios[address];
        }
        return cpu_contents_.rom_bank_00[address];
    }
    if (address < 0x8000) {
        return cpu_contents_.rom_bank_01_nn[address - 0x4000];
    }

    if (address < 0xA000) {
        return cpu_contents_.vram[address - 0x8000];
    }
    if (address < 0xC000) {
        return cpu_contents_.eram[address - 0xA000];
    }
    if (address < 0xD000) {
        return cpu_contents_.wram0[address - 0xC000];
    }
    if (address < 0xE000) {
        auto bank = get_wram_bank();
        return cpu_contents_.wram_bank[bank][address - 0xD000];
    }
    if (address < 0xFE00) {
        return read(address - 0x2000);
    }
    if (address < 0xFEA0) {
        return cpu_contents_.oam[address - 0xFE00];
    }
    if (address < 0xFF00) {
        return cpu_contents_.unusable[address - 0xFEA0];
    }
    if (address < 0xFF80) {
        return cpu_contents_.io_registers[address - 0xFF00];
    }
    if (address < 0xFFFF) {
        return cpu_contents_.hram[address - 0xFF80];
    }
    return cpu_contents_.ie;
}

auto
Memory::write(uint16_t address, uint8_t value) -> void
{
    if (address < 0x8000) {
        throw std::runtime_error("invalid attempt to write to ROM address");
    }

    if (address < 0xA000) {
        cpu_contents_.vram[address - 0x8000] = value;
        return;
    }
    if (address < 0xC000) {
        cpu_contents_.eram[address - 0xA000] = value;
        return;
    }
    if (address < 0xD000) {
        cpu_contents_.wram0[address - 0xC000] = value;
        return;
    }
    if (address < 0xE000) {
        auto bank = get_wram_bank();
        cpu_contents_.wram_bank[bank][address - 0xD000] = value;
        return;
    }
    if (address < 0xFE00) {
        write(address - 0x2000, value);
        return;
    }
    if (address < 0xFEA0) {
        cpu_contents_.oam[address - 0xFE00] = value;
        return;
    }
    if (address < 0xFF00) {
        cpu_contents_.unusable[address - 0xFEA0] = value;
        return;
    }
    if (address < 0xFF80) {
        if (address == 0xFF50 && bios_active && value != 0) {
            bios_active = false;
        }
        cpu_contents_.io_registers[address - 0xFF00] = value;
        return;
    }
    if (address < 0xFFFF) {
        cpu_contents_.hram[address - 0xFF80] = value;
        return;
    }

    cpu_contents_.ie = value;
}

} // namespace memory
} // namespace spinarak
