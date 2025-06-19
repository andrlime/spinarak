#include <cpu/cpu.hpp>

// CPU: nop
namespace spinarak {
namespace cpu {

auto
CPU::no_op() -> void
{
    DEBUG("entering NO-OP call\n");
    cycles_ += 4;
}

} // namespace cpu
} // namespace spinarak
