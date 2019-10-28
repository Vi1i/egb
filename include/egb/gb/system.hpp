#pragma once

#include <egb/z80/mmu.hpp>
#include <egb/z80/cpu.hpp>
#include <egb/gb/cartridge.hpp>

namespace egb::gb {
  class System {
    egb::z80::MMU _mmu;
    egb::z80::CPU _cpu;
    Cartridge * _cartridge;

  public:
    System();
    ~System();

    auto LoadCartridge(Cartridge *cart) -> void;
    auto TurnOn() -> void;
    auto Reset() -> void;
  };
}
