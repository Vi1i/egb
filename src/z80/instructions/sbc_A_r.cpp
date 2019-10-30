#include <egb/z80/cpu.hpp>
#include <egb/z80/register.hpp>
#include <egb/utils/utils.hpp>
#include <egb/defines.hpp>

#include <cstdint>
#include <unordered_map>

namespace egb::z80 {
  auto CPU::_SBC_A_r() -> void {
    std::uint8_t opcode = _mmu->RB(regs[RegPC].w);
    regs[RegPC].w += 2;

    std::uint8_t reg_val;
    std::uint8_t r = opcode & 0x07;
    switch(r) {
      case 0x00:
        reg_val = regs[RegBC].h;
        break;
      case 0x01:
        reg_val = regs[RegBC].l;
        break;
      case 0x02:
        reg_val = regs[RegDE].h;
        break;
      case 0x03:
        reg_val = regs[RegDE].l;
        break;
      case 0x04:
        reg_val = regs[RegAF].h;
        break;
      case 0x05:
        reg_val = regs[RegAF].l;
        break;
      case 0x06:
        throw std::runtime_error("SBc_A_r(" + utils::pByte(opcode) + "): How did you get here with this OPCODE?");
        break;
      case 0x07:
        reg_val = regs[RegAF].h;
        break;
    }

    if((reg_val + 1) == 0x00) {
      // Not sure yet
    }
    reg_val += 1;
    std::uint8_t a_val = regs[RegAF].h;

    if((a_val - reg_val) == 0) {
      this->SetZFlag(1);
    }

    this->SetNFlag(1);

    if((((a_val & 0xF) - (reg_val & 0xF)) < 0)) {
      this->SetHFlag(1);
    }

    if((a_val - reg_val) < 0) {
      this->SetCFlag(1);
    }

    regs[RegAF].h = a_val - reg_val;

    _cycles += 4;
  }

  auto CPU::_SBC_A_n() -> void { }
  auto CPU::_SBC_A_hl() -> void { }

  auto CPU::SBC_A_s() -> void {
    std::uint8_t opcode = _mmu->RB(regs[RegPC].w);

    if((opcode >= 0x98 || opcode <=0x9D) || opcode == 0x9F) {
      this->_SBC_A_r();
    } else if(opcode == 0xDE) {
      throw std::runtime_error("SBc_A_a(" + utils::pByte(opcode) + "): unimplemented!");
    } else if(opcode == 0x9E) {
      throw std::runtime_error("SBc_A_a(" + utils::pByte(opcode) + "): unimplemented!");
    } else {
      throw std::runtime_error("SBc_A_a(" + utils::pByte(opcode) + "): How did you get here with this OPCODE?");
    }
  }
}
