#pragma once

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
CPU::ld() -> void requires Is16BitAtRegister<src>
{
    cycles_ += 8;
    write_register<dest>(memory_->read(read_register<src>()));
}

template <AtRegister dest, Register src>
auto
CPU::ld() -> void requires Is16BitAtRegister<dest>
{
    cycles_ += 8;
    memory_->write(read_register<dest>(), read_register<src>());
}

// write immediate. register is ALWAYS destination here
template <Register dest>
auto
CPU::ld(word_t src) -> void requires Is8BitRegister<dest>
{
    if (!!(src & 0xFF00)) {
        throw std::domain_error("attempted to write byte with non-zero upper 8 bits to 8 bit register");
    }
    cycles_ += 8;
    write_register<dest>(src);
}

template <Register dest>
auto
CPU::ld(word_t src) -> void requires Is16BitRegister<dest>
{
    cycles_ += 12;
    write_register<dest>(src);
}

// because addresses are 16 bit, 8 bit addresses necessarily
// corresponds to 0xFF00 + address
template <Register src, WriteDirection direc>
auto
CPU::ld(byte_t dest) -> void
{
    cycles_ += 12;
    if constexpr (direc == WriteDirection::DestToSrc) {
        write_register<src>(memory_->read(0xFF00 + dest));
    }
    else { // WriteDirection::SrcToDest
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
    }
    else { // WriteDirection::SrcToDest
        memory_->write(dest, read_register<src>());
    }
}

} // namespace cpu
} // namespace spinarak
