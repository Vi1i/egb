#include <egb/z80/cpu.hpp>
#include <egb/z80/register.hpp>
#include <egb/utils/utils.hpp>
#include <egb/defines.hpp>

#include <cstdint>
#include <unordered_map>

namespace egb::z80 {
  /**
   * Shift n left into Carry. LSB of n set to 0.
   **/
  auto CPU::_SLA_r(int target, bool hiByte) -> void {
    std::uint8_t val;
    if(hiByte) {
      val = regs[target].h;
    } else {
      val = regs[target].l;
    }

    this->SetCFlag((val & 0x80) >> 7);
    val = val << 1;

    if(hiByte) {
      regs[target].h = val;
    } else {
      regs[target].l = val;
    }
    _cycles += 2;
  }

  auto CPU::_SLA_hl() -> void {
    std::uint8_t val = _mmu->RB(regs[RegHL].w);

    this->SetCFlag((val & 0x80) >> 7);
    val = val << 1;

    _mmu->WB(regs[RegHL].w, val);
    _cycles += 4;
  }

  auto CPU::SLA_n() -> void {
    std::uint8_t opcode = _mmu->RB(regs[RegPC].w);
    regs[RegPC].w += 2;

    std::uint8_t n = _mmu->RB(regs[RegPC].w);
    regs[RegPC].w += 2;

    std::uint8_t r = opcode & 0x07;

    std::uint8_t val;

    switch(r) {
      case 0x00:
        this->_SLA_r(RegBC, true);
        break;
      case 0x01:
        this->_SLA_r(RegBC, false);
        break;
      case 0x02:
        this->_SLA_r(RegDE, true);
        break;
      case 0x03:
        this->_SLA_r(RegDE, false);
        break;
      case 0x04:
        this->_SLA_r(RegHL, true);
        break;
      case 0x05:
        this->_SLA_r(RegHL, false);
        break;
      case 0x06:
        this->_SLA_hl();
        break;
      case 0x07:
        this->_SLA_r(RegAF, true);
        break;
    }
  }
}
