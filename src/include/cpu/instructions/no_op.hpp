#pragma once

// CPU: nop
namespace spinarak {
namespace cpu {

inline auto
CPU::no_op() -> void
{
    cycles_ += 4;
}

} // namespace cpu
} // namespace spinarak
