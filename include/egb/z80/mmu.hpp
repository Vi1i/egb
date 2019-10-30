#pragma once

#include <cstdint>
#include <egb/z80/memory.hpp>

namespace egb::z80 {
  /**
   * TODO: (Vi1i) The xW functions handle endianness, for the z80 it is little endian.
   *              This means that words need to be flipped during reads and writes.
   *              Memory(LH) <-> Register(HL)
   **/
  class MMU {
    egb::z80::Memory _memory;
    bool _bios = true;

  public:
    MMU();
    ~MMU();

    auto WB(const std::uint16_t addr, const std::uint8_t byte) -> void;
    auto WW(const std::uint16_t addr, const std::uint16_t word) -> void;
    auto RB(const std::uint16_t addr) -> std::uint8_t;
    auto RW(const std::uint16_t addr) -> std::uint16_t;
 };
}
