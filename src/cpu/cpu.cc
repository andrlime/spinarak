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
        case 0x01: case 0x11: case 0x21: case 0x31: {
            byte_t bottom = memory_->read(cpu_contents_.pc++);
            byte_t top = memory_->read(cpu_contents_.pc++);
            auto instr_code = (opcode & 0xF0) >> 4;
            switch (instr_code) {
                case 0x0:
                    ld<Register::BC>((top << 8) | bottom);
                    break;
                case 0x1:
                    ld<Register::DE>((top << 8) | bottom);
                    break;
                case 0x2:
                    ld<Register::HL>((top << 8) | bottom);
                    break;
                case 0x3:
                    ld<Register::SP>((top << 8) | bottom);
                    break;
            }
            break;
        }
        default:
            throw std::runtime_error("unimplemented opcode");
    }
}

auto
CPU::tick() -> void
{
    byte_t opcode = memory_->read(cpu_contents_.pc++);
    decode_and_execute(opcode);
    print_state();
}

} // namespace cpu
} // namespace spinarak
