#include <egb/z80/cpu.hpp>
#include <egb/z80/register.hpp>
#include <egb/utils/utils.hpp>
#include <egb/defines.hpp>

#include <cstdint>
#include <unordered_map>

namespace egb::z80 {
  auto CPU::CBSwitcher() -> void {
    std::uint8_t opcode = _mmu->RB(regs[RegPC].w);
    std::uint8_t cbOP = _mmu->RB(regs[RegPC].w + 2);
    switch(cbOP) {
      case 0x20:
      case 0x21:
      case 0x22:
      case 0x23:
      case 0x24:
      case 0x25:
      case 0x26:
      case 0x27:
        this->SLA_n();
        break;

      default:
        throw std::runtime_error("0xCB " + utils::pByte(cbOP) + "): Unimpkemented 0xCB switch!");
    }
  }
}
