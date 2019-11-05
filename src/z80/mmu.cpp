#include <egb/z80/mmu.hpp>

#include <cstdint>
#include <egb/z80/memory.hpp>

namespace egb::z80 {
  MMU::MMU() = default;
  MMU::~MMU() = default;

  auto MMU::WB(const WORD addr, const BYTE byte) -> void {
    _memory.WB(addr, byte);
  }

  auto MMU::WW(const WORD addr, const WORD word) -> void {
    BYTE lbyte = word & 0x00FF;
    BYTE hbyte = word >> 8;

    _memory.WB(addr, lbyte);
    _memory.WB(addr + 1, hbyte);
  }

  auto MMU::RB(const WORD addr)  -> BYTE {
    return _memory.RB(addr);
  }

  auto MMU::RW(const WORD addr)  -> WORD {
    return _memory.RB(addr) | (_memory.RB(addr + 1) << 8);
  }
}
