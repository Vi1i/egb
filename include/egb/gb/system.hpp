#pragma once

#include <egb/gb/cartridge.hpp>
#include <egb/z80/mmu.hpp>
#include <egb/z80/cpu.hpp>

#include <curses.h>

namespace egb::gb {
  class System {
    egb::z80::MMU _mmu;
    egb::z80::CPU _cpu;
    Cartridge * _cartridge;

    WINDOW * _regWin;
    WINDOW * _carWin;
    WINDOW * _insWin;
    WINDOW * _spWin;
    WINDOW * _pcWin;
    int _h,_w;

  public:
    System();
    ~System();

    auto LoadCartridge(Cartridge *cart) -> void;
    auto TurnOn() -> void;
    auto Reset() -> void;
    auto UpdateCarWindow() -> void;
    auto UpdateRegWindow() -> void;
    auto UpdateInsWindow() -> void;
    auto UpdateSPWindow() -> void;
    auto UpdatePCWindow() -> void;
  };
}
