#include <cpu/cpu.hpp>

namespace spinarak {
namespace cpu {

template <Register R>
auto CPU::ld16BitImmediate(const byte_t opcode) -> void {
    const byte_t bottom = memory_->read(cpu_contents_.pc++);
    const byte_t top = memory_->read(cpu_contents_.pc++);
    const word_t word_literal = (top << 8) | bottom;
    ld<R>(word_literal);
}

template <decoder::Load B>
auto CPU::ldToAtRegister(const byte_t opcode) -> void {
    if constexpr (B == decoder::Load::Ld02) {
        constexpr Register source = Register::A;
        constexpr AtRegister destination = AtRegister::AtBC;
        ld<destination, source>();
    }
    if constexpr (B == decoder::Load::Ld12) {
        constexpr Register source = Register::A;
        constexpr AtRegister destination = AtRegister::AtDE;
        ld<destination, source>();
    }
    if constexpr (B == decoder::Load::Ld22) {
        constexpr Register source = Register::A;
        constexpr AtRegister destination = AtRegister::AtHL;
        write_register<Register::HL>(read_register<destination>() + 1);
        ld<destination, source>();
    }
    if constexpr (B == decoder::Load::Ld32) {
        constexpr Register source = Register::A;
        constexpr AtRegister destination = AtRegister::AtHL;
        write_register<Register::HL>(read_register<destination>() - 1);
        ld<destination, source>();
    }

    if constexpr (B == decoder::Load::Ld70) {
        constexpr Register source = Register::B;
        constexpr AtRegister destination = AtRegister::AtBC;
        ld<destination, source>();
    }
    if constexpr (B == decoder::Load::Ld71) {
        constexpr Register source = Register::C;
        constexpr AtRegister destination = AtRegister::AtDE;
        ld<destination, source>();
    }
    if constexpr (B == decoder::Load::Ld72) {
        constexpr Register source = Register::D;
        constexpr AtRegister destination = AtRegister::AtHL;
        ld<destination, source>();
    }
    if constexpr (B == decoder::Load::Ld73) {
        constexpr Register source = Register::E;
        constexpr AtRegister destination = AtRegister::AtHL;
        ld<destination, source>();
    }
    if constexpr (B == decoder::Load::Ld74) {
        constexpr Register source = Register::H;
        constexpr AtRegister destination = AtRegister::AtHL;
        ld<destination, source>();
    }
    if constexpr (B == decoder::Load::Ld75) {
        constexpr Register source = Register::L;
        constexpr AtRegister destination = AtRegister::AtHL;
        ld<destination, source>();
    }
    if constexpr (B == decoder::Load::Ld77) {
        constexpr Register source = Register::A;
        constexpr AtRegister destination = AtRegister::AtHL;
        ld<destination, source>();
    }
}

auto
CPU::decode_and_execute(const byte_t opcode) -> void
{
    DEBUG("running opcode 0x%x\n", opcode);
    switch (opcode) {
        case 0x00: no_op(); break;
        case 0x01: ld16BitImmediate<Register::BC>(opcode); break;
        case 0x11: ld16BitImmediate<Register::DE>(opcode); break;
        case 0x21: ld16BitImmediate<Register::HL>(opcode); break;
        case 0x31: ld16BitImmediate<Register::SP>(opcode); break;
        case 0x02: ldToAtRegister<decoder::Load::Ld02>(opcode); break;
        case 0x12: ldToAtRegister<decoder::Load::Ld12>(opcode); break;
        case 0x22: ldToAtRegister<decoder::Load::Ld22>(opcode); break;
        case 0x32: ldToAtRegister<decoder::Load::Ld32>(opcode); break;
        case 0x70: ldToAtRegister<decoder::Load::Ld70>(opcode); break;
        case 0x71: ldToAtRegister<decoder::Load::Ld71>(opcode); break;
        case 0x72: ldToAtRegister<decoder::Load::Ld72>(opcode); break;
        case 0x73: ldToAtRegister<decoder::Load::Ld73>(opcode); break;
        case 0x74: ldToAtRegister<decoder::Load::Ld74>(opcode); break;
        case 0x75: ldToAtRegister<decoder::Load::Ld75>(opcode); break;
        case 0x77: ldToAtRegister<decoder::Load::Ld77>(opcode); break;
        default: throw std::runtime_error("unimplemented opcode");
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
