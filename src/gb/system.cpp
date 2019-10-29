#include <egb/gb/system.hpp>
#include <egb/z80/mmu.hpp>
#include <egb/z80/cpu.hpp>
#include <egb/gb/cartridge.hpp>
#include <egb/defines.hpp>

#include <colorize/color.hpp>

#include <stdexcept>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>

namespace egb::gb {
  namespace {
    auto pWord(std::uint16_t word) -> std::string {
      std::ostringstream oss;
      oss << "0x"<< std::setfill('0') << std::setw(4) << std::hex << std::uppercase<< (int)word;
      return oss.str();
    }

    auto pByte(std::uint8_t byte) -> std::string {
      std::ostringstream oss;
      oss << "0x"<< std::setfill('0') << std::setw(2) << std::hex << std::uppercase<< (int)byte;
      return oss.str();
    }

    auto create_newwin(int height, int width, int starty, int startx) -> WINDOW * {
      WINDOW *local_win;
      local_win = newwin(height, width, starty, startx);
      box(local_win, 0 , 0);
      wrefresh(local_win);
      return local_win;
    }
  }

  System::System() : _mmu(), _cpu(&_mmu), _cartridge(nullptr) {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    getmaxyx(stdscr, _h, _w);
    refresh();
    _carWin = create_newwin(3, 75, 0, 0);
    _regWin = create_newwin(8, 36, 3, 0);
    _insWin = create_newwin(8, 36, 3, 36);
  }

  System::~System() {
    delwin(_carWin);
    delwin(_regWin);
    endwin();
  }

  // TODO: (Vi1i) Shouldn't use the hardcoded check in this function
  auto System::LoadCartridge(Cartridge *cart) -> void {
    if(cart->GetType() != 0x00) {
      throw std::runtime_error("ROM ONLY games currently supported");
    }
    _cartridge = cart;
  }

  auto System::Reset() -> void { }

  auto System::UpdateCarWindow() -> void {
    std::string title = _cartridge->GetTitle();
    std::string ramSize = pByte(_cartridge->GetRAMSize());
    std::string romSize = pByte(_cartridge->GetROMSize());
    std::string type = pByte(_cartridge->GetType());

    mvwprintw(_carWin,0,0, "(q)-To-Quit");
    mvwprintw(_carWin,0,15, "Cartridge Information");
    mvwprintw(_carWin,1,1, "Title: %s | ", title.c_str());
    wprintw(_carWin, "RAM Size: %s | ", ramSize.c_str());
    wprintw(_carWin, "ROM Size: %s | ", romSize.c_str());
    wprintw(_carWin, "Type: %s", type.c_str());
    wrefresh(_carWin);
  }

  auto System::UpdateInsWindow() -> void {
    mvwprintw(_insWin,0,15, "Registry Information");
    mvwprintw(_insWin,1,1, "OPCode: %s", pByte(_mmu.RB(_cpu.regs[RegPC].w)).c_str());
    wrefresh(_insWin);
  }
  auto System::UpdateRegWindow() -> void {
    mvwprintw(_regWin,0,0, "(s)-To-Step");
    mvwprintw(_carWin,0,15, "Registry Information");
    mvwprintw(_regWin,1,1, "PC: %s", pWord(_cpu.regs[RegPC].w).c_str());
    wprintw(_regWin, "   Hi: %s", pByte(_cpu.regs[RegPC].h).c_str());
    wprintw(_regWin, "   Lo: %s", pByte(_cpu.regs[RegPC].l).c_str());
    mvwprintw(_regWin,2,1, "SP: %s", pWord(_cpu.regs[RegSP].w).c_str());
    wprintw(_regWin, "   Hi: %s", pByte(_cpu.regs[RegSP].h).c_str());
    wprintw(_regWin, "   Lo: %s", pByte(_cpu.regs[RegSP].l).c_str());
    mvwprintw(_regWin,3,1, "AF: %s", pWord(_cpu.regs[RegAF].w).c_str());
    wprintw(_regWin, "    A: %s", pByte(_cpu.regs[RegAF].h).c_str());
    wprintw(_regWin, "    F: %s", pByte(_cpu.regs[RegAF].l).c_str());
    mvwprintw(_regWin,4,1, "BC: %s", pWord(_cpu.regs[RegBC].w).c_str());
    wprintw(_regWin, "    B: %s", pByte(_cpu.regs[RegBC].h).c_str());
    wprintw(_regWin, "    C: %s", pByte(_cpu.regs[RegBC].l).c_str());
    mvwprintw(_regWin,5,1, "DE: %s", pWord(_cpu.regs[RegDE].w).c_str());
    wprintw(_regWin, "    D: %s", pByte(_cpu.regs[RegDE].h).c_str());
    wprintw(_regWin, "    E: %s", pByte(_cpu.regs[RegDE].l).c_str());
    mvwprintw(_regWin,6,1, "HL: %s", pWord(_cpu.regs[RegHL].w).c_str());
    wprintw(_regWin, "    H: %s", pByte(_cpu.regs[RegHL].h).c_str());
    wprintw(_regWin, "    L: %s", pByte(_cpu.regs[RegHL].l).c_str());
    wrefresh(_regWin);
  }

  // TODO: (Vi1i) Look into threading here
  auto System::TurnOn() -> void {
    this->Reset();
    char ch;
    int count = 0;
    this->UpdateCarWindow();
    this->UpdateInsWindow();
    this->UpdateRegWindow();
    do {
      switch(ch) {
        case 's':
        case 'S':
          _cpu.Step();
          this->UpdateRegWindow();
          this->UpdateInsWindow();
          break;
      }
    } while((ch = getch()) != 'q');
  }
}
