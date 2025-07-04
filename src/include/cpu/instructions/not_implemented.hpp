#pragma once

// CPU: nop
namespace spinarak {
namespace cpu {

inline auto
CPU::not_implemented() -> void
{
    throw std::runtime_error("unimplemented opcode");
}

} // namespace cpu
} // namespace spinarak
