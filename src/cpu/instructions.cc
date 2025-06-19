#include <cpu/cpu.hpp>

namespace spinarak {
namespace cpu {

auto
CPU::no_op() -> void
{
    DEBUG("entering NO-OP call\n");
    cycles_ += 4;
}

auto
CPU::stop() -> void
{
    DEBUG("entering STOP call\n");
    cycles_ += 4;

    // TODO
}

} // namespace cpu
} // namespace spinarak
