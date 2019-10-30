#include <egb/z80/mmu.hpp>

#include <cstdint>
#include <egb/z80/memory.hpp>

namespace egb::z80 {
  MMU::MMU() = default;
  MMU::~MMU() = default;

  auto MMU::WB(const std::uint16_t addr, const std::uint8_t byte) -> void {
    _memory.WB(addr, byte);
  }

  auto MMU::WW(const std::uint16_t addr, const std::uint16_t word) -> void {
    std::uint8_t lbyte = word & 0x00FF;
    std::uint8_t hbyte = word >> 8;

    _memory.WB(addr, lbyte);
    _memory.WB(addr + 1, hbyte);
  }

  auto MMU::RB(const std::uint16_t addr)  -> std::uint8_t {
    return _memory.RB(addr);
  }

  auto MMU::RW(const std::uint16_t addr)  -> std::uint16_t {
    return _memory.RB(addr) | (_memory.RB(addr + 1) << 8);
  }
}
