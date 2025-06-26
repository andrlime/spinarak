#include <cpu/cpu.hpp>

namespace spinarak {
namespace cpu {

auto
CPU::decode_and_execute(byte_t opcode) -> void
{
    DEBUG("running opcode 0x%x\n", opcode);
    switch (opcode) {
        case 0x00:
            no_op();
            break;
        default:
            throw std::runtime_error("unimplemented opcode");
    }
}

auto
CPU::tick() -> void
{
    byte_t opcode = memory_->read(cpu_contents_.pc++);
    decode_and_execute(opcode);
}

} // namespace cpu
} // namespace spinarak
