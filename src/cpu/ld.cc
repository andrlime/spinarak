#include <cpu/cpu.hpp>

// CPU::ld dest, src
namespace spinarak {
namespace cpu {

template <Register dest, Register src>
auto
CPU::ld() -> void
{
    cycles_ += 4;
    write_register<dest>(read_register<src>());
}

template <Register dest, AtRegister src>
auto
CPU::ld() -> void
{
    cycles_ += 8;
    write_register<dest>(memory_->read(read_register<src>()));
}

template <AtRegister dest, Register src>
auto
CPU::ld() -> void
{
    cycles_ += 8;
    memory_->write(read_register<dest>(), read_register<src>());
}

template <Register dest>
auto
CPU::ld(byte_t src) -> void
{
    write_register<dest>(src);
}

template <Register dest>
auto
CPU::ld(word_t src) -> void
{
    // this template is only used in 16 bit word registers
    // type check for sanity
    if constexpr (dest != Register::AF && dest != Register::BC && dest != Register::DE && dest != Register::HL && dest != Register::SP && dest != Register::PC) {
        throw std::runtime_error("attempted to write a 16 bit word into a non 16 bit register");
    }

    write_register<dest>(src);
}

// because addresses are 16 bit, 8 bite addresses necessarily
// corresponds to 0xFF00 + address
template <Register src, WriteDirection direc>
auto
CPU::ld(byte_t dest) -> void
{
    cycles_ += 12;
    if constexpr (direc == WriteDirection::DestToSrc) {
        write_register<src>(memory_->read(0xFF00 + dest));
    } else { // WriteDirection::SrcToDest
        memory_->write(0xFF00 + dest, read_register<src>());
    }
}

template <Register src, WriteDirection direc>
auto
CPU::ld(word_t dest) -> void
{
    cycles_ += 16;
    if constexpr (direc == WriteDirection::DestToSrc) {
        write_register<src>(memory_->read(dest));
    } else { // WriteDirection::SrcToDest
        memory_->write(dest, read_register<src>());
    }
}

} // namespace cpu
} // namespace spinarak
