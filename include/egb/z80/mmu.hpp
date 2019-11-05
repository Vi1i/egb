#pragma once

#include <egb/defines.hpp>
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

    auto WB(const WORD addr, const BYTE byte) -> void;
    auto WW(const WORD addr, const WORD word) -> void;
    auto RB(const WORD addr) -> BYTE;
    auto RW(const WORD addr) -> WORD;
 };
}
