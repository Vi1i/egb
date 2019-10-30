#include <egb/z80/cpu.hpp>
#include <egb/z80/register.hpp>
#include <egb/utils/utils.hpp>
#include <egb/defines.hpp>

#include <cstdint>
#include <unordered_map>

namespace egb::z80 {
  auto CPU::LD_n_nn() -> void {
    std::uint8_t opcode = _mmu->RB(regs[RegPC].w);
    regs[RegPC].w += 2;

    std::uint16_t integer = _mmu->RW(regs[RegPC].w);
    regs[RegPC].w += 4;

    std::uint8_t dd = (opcode & 0x30) >> 4;
    auto reg(0);
    switch(dd) {
      case 0x00:
        reg = RegBC;
        break;

      case 0x01:
        reg = RegDE;
        break;

      case 0x02:
        reg = RegHL;
        break;

      case 0x03:
        reg = RegSP;
        break;
    }

    regs[reg].w = integer;
    
    _cycles += 2;
  }
}
