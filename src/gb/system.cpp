#include <egb/gb/system.hpp>
#include <egb/z80/mmu.hpp>
#include <egb/z80/cpu.hpp>
#include <egb/gb/cartridge.hpp>
#include <egb/defines.hpp>
#include <egb/utils/utils.hpp>

#include <stdexcept>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>

namespace egb::gb {
  namespace {
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
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    keypad(stdscr, true);
    getmaxyx(stdscr, _h, _w);
    refresh();
    _carWin = create_newwin(3, 75, 0, 0);
    _regWin = create_newwin(8, 36, 3, 0);
    _insWin = create_newwin(8, 39, 3, 36);
    _pcWin = create_newwin(3, 75, 11, 0);
    _spWin = create_newwin(8, 75, 14, 0);
  }

  System::~System() {
    delwin(_carWin);
    delwin(_regWin);
    delwin(_insWin);
    delwin(_pcWin);
    endwin();
  }

  // TODO: (Vi1i) Shouldn't use the hardcoded check in this function
  auto System::LoadCartridge(Cartridge *cart) -> void {
    if(cart->GetType() != 0x00) {
      throw std::runtime_error("ROM ONLY games currently supported");
    }
    _cartridge = cart;
    _cpu.RegPC.w = defines::CARTRIDGE_HEADER_START;
    for(WORD pos = defines::CARTRIDGE_HEADER_START; pos < defines::CARTRIDGE_HEADER_END; pos += 2) {
      _mmu.WB(pos, _cartridge->_buffer[pos]);
    }
  }

  auto System::Reset() -> void { }

  auto System::UpdateSPWindow() -> void {
    mvwprintw(_spWin,0,15, "Stack Counter Information");
    wrefresh(_spWin);
  }

  auto System::UpdatePCWindow() -> void {
    mvwprintw(_pcWin,0,15, "Program Counter Information");
    int posPC = _cpu.RegPC.w - (2*10);
    WORD curPC = _cpu.RegPC.w;

    for(auto col = 3; col < 72; col += 3) {
      if(posPC >= 0) {
        wmove(_pcWin, 1, col);
        if(posPC >= curPC && posPC <= curPC + _cpu.instructions.back().insHex.size()) {
          unsigned int flags = A_BOLD;
          if(posPC != curPC) {
            flags |= COLOR_PAIR(1);
          } else {
            flags |= A_UNDERLINE;
          }
          wattron(_pcWin, flags);
          wprintw(_pcWin, utils::Byte(_mmu.RB(posPC)).c_str());
          wattroff(_pcWin, flags);
        } else {
          wprintw(_pcWin, utils::Byte(_mmu.RB(posPC)).c_str());
        }
      }
      posPC += 2;
    }
    wrefresh(_pcWin);
  }

  auto System::UpdateCarWindow() -> void {
    std::string title = _cartridge->GetTitle();
    std::string ramSize = utils::pByte(_cartridge->GetRAMSize());
    std::string romSize = utils::pByte(_cartridge->GetROMSize());
    std::string type = utils::pByte(_cartridge->GetType());

    mvwprintw(_carWin,0,0, "(q)-To-Quit");
    mvwprintw(_carWin,0,15, "Cartridge Information");
    mvwprintw(_carWin,1,1, "Title: %s | ", title.c_str());
    wprintw(_carWin, "RAM Size: %s | ", ramSize.c_str());
    wprintw(_carWin, "ROM Size: %s | ", romSize.c_str());
    wprintw(_carWin, "Type: %s", type.c_str());
    wrefresh(_carWin);
  }

  auto System::UpdateInsWindow() -> void {
    mvwprintw(_insWin,0,15, "Instruction Information");
    wmove(_insWin, 1, 2);
    wprintw(_insWin,"OPCode:");
    for(const auto str : _cpu.instructions.back().insHex) {
      wprintw(_insWin, " %s", str.c_str());
    }

    mvwprintw(_insWin, 2,2, "Instruction: %s", _cpu.instructions.back().insStr.c_str());
    wrefresh(_insWin);
  }

  auto System::UpdateRegWindow() -> void {
    mvwprintw(_regWin,0,0, "(s)-To-Step");
    mvwprintw(_regWin,0,15, "Registry Information");
    mvwprintw(_regWin,1,1, "PC: %s", utils::pWord(_cpu.RegPC.w).c_str());
    wprintw(_regWin, "   Hi: %s", utils::pByte(_cpu.RegPC.h).c_str());
    wprintw(_regWin, "   Lo: %s", utils::pByte(_cpu.RegPC.l).c_str());
    mvwprintw(_regWin,2,1, "SP: %s", utils::pWord(_cpu.RegSP.w).c_str());
    wprintw(_regWin, "   Hi: %s", utils::pByte(_cpu.RegSP.h).c_str());
    wprintw(_regWin, "   Lo: %s", utils::pByte(_cpu.RegSP.l).c_str());
    mvwprintw(_regWin,3,1, "AF: %s", utils::pWord(_cpu.RegAF.w).c_str());
    wprintw(_regWin, "    A: %s", utils::pByte(_cpu.RegAF.h).c_str());
    wprintw(_regWin, "    F: %s", utils::pByte(_cpu.RegAF.l).c_str());
    mvwprintw(_regWin,4,1, "BC: %s", utils::pWord(_cpu.RegBC.w).c_str());
    wprintw(_regWin, "    B: %s", utils::pByte(_cpu.RegBC.h).c_str());
    wprintw(_regWin, "    C: %s", utils::pByte(_cpu.RegBC.l).c_str());
    mvwprintw(_regWin,5,1, "DE: %s", utils::pWord(_cpu.RegDE.w).c_str());
    wprintw(_regWin, "    D: %s", utils::pByte(_cpu.RegDE.h).c_str());
    wprintw(_regWin, "    E: %s", utils::pByte(_cpu.RegDE.l).c_str());
    mvwprintw(_regWin,6,1, "HL: %s", utils::pWord(_cpu.RegHL.w).c_str());
    wprintw(_regWin, "    H: %s", utils::pByte(_cpu.RegHL.h).c_str());
    wprintw(_regWin, "    L: %s", utils::pByte(_cpu.RegHL.l).c_str());
    wrefresh(_regWin);
  }

  // TODO: (Vi1i) Look into threading here
  auto System::TurnOn() -> void {
    this->Reset();

    try {
      _cpu.Read();
    } catch(const std::runtime_error e) {
      WINDOW * err_win = create_newwin(_h/2,_w/2, (_h/2)/2, (_w/2)/2);
      mvwprintw(err_win,1,1, "Error: %s", e.what());
      wrefresh(err_win);
    }

    char ch;
    int count = 0;
    this->UpdateCarWindow();
    this->UpdateInsWindow();
    this->UpdateRegWindow();
    this->UpdateSPWindow();
    this->UpdatePCWindow();
    do {
      switch(ch) {
        case 's':
        case 'S':
          try {
            _cpu.Execute();
            _cpu.Read();
            this->UpdateRegWindow();
            this->UpdateInsWindow();
            this->UpdateSPWindow();
            this->UpdatePCWindow();
          } catch(const std::runtime_error e) {
            WINDOW * err_win = create_newwin(_h/2,_w/2, (_h/2)/2, (_w/2)/2);
            mvwprintw(err_win,1,1, "Error: %s", e.what());
            wrefresh(err_win);
          }
          break;
      }
    } while((ch = getch()) != 'q');
  }
}
