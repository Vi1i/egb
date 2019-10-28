#include <egb/z80/cpu.hpp>
#include <egb/defines.hpp>

#include <cstdint>

#include <iostream>
#include <sstream>
#include <iomanip>
namespace egb::z80 {
  // Temporary debug processing
  // TODO: (Vi1i) Remove this at a later date.
  // TODO: (Vi1i) Look into implementing/finding a sometype of logger.
  namespace {
    auto pByte(std::uint8_t byte, std::string prefix="Byte") -> void {
      std::cout << prefix <<": 0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << (int)byte << std::endl;
    }

    auto pWord(std::uint16_t word, std::string prefix="Word") -> void {
      std::cout << prefix << ": 0x" << std::setfill('0') << std::setw(4) << std::hex << std::uppercase << (int)word << std::endl;
    }
  }

  CPU::CPU(MMU * mmu) {
    this->_mmu = mmu;
    this->_rAF.SetWord(egb::defines::BIOS_START);
    this->_cycles = 0;
  }

  CPU::~CPU() = default;

  auto CPU::Cycle() -> void {
    auto byte = this->_mmu->RB(this->_rPC.GetWord());
    pWord(this->_rPC.GetWord(), "PC");
    pByte(byte, "\tOPCODE");

    this->_rPC.Increment();

    std::ostringstream oss;
    oss << "0x" << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << (int)byte;

    switch(byte) {
      case 0x00:
        this->_NOP();
        break;

      case 0x08:
        this->_LDnnSP();
        break;

        // INCss where ss is a register pair
      //case 0x03:
      case 0x13:
      case 0x23:
      //case 0x33:
        this->_INCss(byte);
        break;

        // INCr
      //case 0x04:
      //case 0x0C:
      //case 0x14:
      //case 0x1C:
      //case 0x24:
      //case 0x2C:
      //case 0x34:
      //  this->_INCr(byte);
      //  break;

        // DECm
      case 0x05:
      //case 0x0D:
      //case 0x15:
      //case 0x1D:
      //case 0x25:
      //case 0x2D:
      //case 0x3D:
        this->_DECm(byte);
        break;

      //case 0x06:
      //case 0x0E:
      //case 0x16:
      //case 0x1E:
      //case 0x26:
      //case 0x2E:
      //case 0x3E:
      //  this->_LDrn(byte);
      //  break;

      //case 0x1A:
      //  this->_LDADE();
      //  break;

      case 0x20:
        this->_JRNZe();
        break;

      case 0x22:
        this->_LDHLIA();
        break;

      case 0x31:
        this->_LDSPnn();
        break;

      case 0xF9:
        this->_LDSPHL();
        break;

        // RST p
      //case 0xC7:
      //case 0xCF:
      //case 0xD7:
      //case 0xDF:
      //case 0xE7:
      //case 0xEF:
      //case 0xF7:
      case 0xFF:
        this->_RSTp(byte);
        break;

      //case 0xEA:
      //  this->_LDnnA();
      //  break;

      //case 0xFE:
      //  this->_CPn();
      //  break;

      default:
        throw std::runtime_error("OPCODE(" + oss.str() + ") not implemented yet!");
    }
  }

  // SP <- nn
  auto CPU::_LDSPnn() -> void { 
    this->_rSP.SetWord(this->_mmu->RW(this->_rPC.GetWord()));
    this->_rPC.Increment();
    this->_cycles += 3;
  }

  /**
   * Refer to page 158 Z80 CPU User's Manual
   * A - s
   **/
  auto CPU::_CPn() -> void {
    std::uint8_t a = _rAF.GetHiByte();
    std::uint8_t temp = this->_mmu->RB(this->_rPC.GetWord());
    auto val = a - temp;
    if(temp > a) {
      this->_rAF.SetLoByte(0x50);
    } else {
      this->_rAF.SetLoByte(0x40);
    }
    val = val & 0xFF;
    if(!val) this->_rAF.SetLoByte(this->_rAF.GetLoByte() | 0x80);
    if((this->_rAF.GetHiByte() ^ val ^ temp) & 0x10) this->_rAF.SetLoByte(this->_rAF.GetLoByte() | 0x20);

    this->_rPC.Increment();
    this->_cycles += 2;
  }

  /**
   * Refer to page 267 Z80 CPU User's Manual
   * (SP-1) <- PCH, (SP-2) <- PCL, PCH <- 0, PCL <- P
   **/
  auto CPU::_RSTp(std::uint8_t byte) -> void {
    this->_rstAF = this->_rAF;
    this->_rstBC = this->_rBC;
    this->_rstDE = this->_rDE;
    this->_rstHL = this->_rHL;
    this->_rstSP = this->_rSP;
    this->_rstPC = this->_rPC;

    this->_rSP.Decrement(2);
    this->_mmu->WW(this->_rSP.GetWord(), this->_rPC.GetWord());
    this->_rPC.SetWord(0x00FF & (byte & 0x38));
    this->_cycles += 3;
  }

  /**
   * This OP was modified from original Z80
   * LD (word),SP     Save SP at given address
   **/
  auto CPU::_LDnnSP() -> void {
    this->_mmu->WW(this->_mmu->RW(this->_rPC.GetWord()), this->_rSP.GetWord());
    this->_rPC.Increment();
    this->_cycles += 4;
  }

  /**
   * Refer to page 93 Z80 CPU User's Manual
   * A <- (DE)
   **/
  auto CPU::_LDADE() -> void {
    this->_rAF.SetHiByte(this->_mmu->RB(this->_rDE.GetWord()));
    this->_cycles += 2;
  }

  /**
   * Refer to page 184 Z80 CPU User's Manual
   * ss <- ss + 1
   **/
  auto CPU::_INCss(std::uint8_t byte) -> void {
    switch(byte) {
      case 0x03:
        this->_rBC.Increment();
        break;
      case 0x13:
        this->_rDE.Increment();
        break;
      case 0x23:
        this->_rHL.Increment();
        break;
      case 0x33:
        this->_rSP.Increment();
        break;
    }
    this->_cycles += 1;
  }

  /**
   * Refer to page 109 Z80 CPU User's Manual for orignal OP 0x22 -> LDnnHL
   * NOTE: In thhe GB documented changes, the same OP code really means the below function
   * LD (HLI),A       Save A at (HL) and increment HL
   **/
  auto CPU::_LDHLIA() -> void {
    this->_mmu->WB(this->_rHL.GetWord(), this->_rAF.GetHiByte());
    this->_rHL.Increment();
    this->_cycles += 2;
  }

  /**
   * Refer to page 164 Z80 CPU User's ManualS
   * m <- m <- 1
   **/
  auto CPU::_DECm(std::uint8_t byte) -> void {
    switch(byte) {
      case 0x05:
        this->_rBC.SetHiByte(this->_rBC.GetHiByte() - 1);
        this->_rBC.SetHiByte(this->_rBC.GetHiByte() & 0xFF);
        if(this->_rBC.GetHiByte()) {
          this->_rAF.SetLoByte(0x0);
        } else {
          this->_rAF.SetLoByte(0x80);
        }
        break;
      case 0x0D:
        this->_rBC.SetLoByte(this->_rBC.GetLoByte() - 1);
        this->_rBC.SetLoByte(this->_rBC.GetLoByte() & 0xFF);
        if(this->_rBC.GetLoByte()) {
          this->_rAF.SetLoByte(0x0);
        } else {
          this->_rAF.SetLoByte(0x80);
        }
        break;
      case 0x15:
        this->_rDE.SetHiByte(this->_rDE.GetHiByte() - 1);
        this->_rDE.SetHiByte(this->_rDE.GetHiByte() & 0xFF);
        if(this->_rDE.GetHiByte()) {
          this->_rAF.SetLoByte(0x0);
        } else {
          this->_rAF.SetLoByte(0x80);
        }
        break;
      case 0x1D:
        this->_rDE.SetLoByte(this->_rDE.GetLoByte() - 1);
        this->_rDE.SetLoByte(this->_rDE.GetLoByte() & 0xFF);
        if(this->_rDE.GetLoByte()) {
          this->_rAF.SetLoByte(0x0);
        } else {
          this->_rAF.SetLoByte(0x80);
        }
        break;
      case 0x25:
        this->_rHL.SetHiByte(this->_rHL.GetHiByte() - 1);
        this->_rHL.SetHiByte(this->_rHL.GetHiByte() & 0xFF);
        if(this->_rHL.GetHiByte()) {
          this->_rAF.SetLoByte(0x0);
        } else {
          this->_rAF.SetLoByte(0x80);
        }
        break;
      case 0x2D:
        this->_rHL.SetLoByte(this->_rHL.GetLoByte() - 1);
        this->_rHL.SetLoByte(this->_rHL.GetLoByte() & 0xFF);
        if(this->_rHL.GetLoByte()) {
          this->_rAF.SetLoByte(0x0);
        } else {
          this->_rAF.SetLoByte(0x80);
        }
        break;
      case 0x3D:
        this->_rAF.SetHiByte(this->_rAF.GetHiByte() - 1);
        this->_rAF.SetHiByte(this->_rAF.GetHiByte() & 0xFF);
        if(this->_rAF.GetHiByte()) {
          this->_rAF.SetLoByte(0x0);
        } else {
          this->_rAF.SetLoByte(0x80);
        }
        break;
    }
    this->_cycles += 1;
  }

  /**
   * Refer to page 160 Z80 CPU User's ManualS
   * r <- r + 1
   **/
  auto CPU::_INCr(std::uint8_t byte) -> void {
    switch(byte) {
      case 0x04:
        this->_rBC.SetHiByte(this->_rBC.GetHiByte() + 1);
        this->_rBC.SetHiByte(this->_rBC.GetHiByte() & 0xFF);
        if(this->_rBC.GetHiByte()) {
          this->_rAF.SetLoByte(0x00);
        } else {
          this->_rAF.SetLoByte(0x80);
        }
        break;
      case 0x0C:
        this->_rBC.SetLoByte(this->_rBC.GetLoByte() + 1);
        this->_rBC.SetLoByte(this->_rBC.GetLoByte() & 0xFF);
        if(this->_rBC.GetLoByte()) {
          this->_rAF.SetLoByte(0x00);
        } else {
          this->_rAF.SetLoByte(0x80);
        }
        break;
      case 0x14:
        this->_rDE.SetHiByte(this->_rDE.GetHiByte() + 1);
        this->_rDE.SetHiByte(this->_rDE.GetHiByte() & 0xFF);
        if(this->_rDE.GetHiByte()) {
          this->_rAF.SetLoByte(0x00);
        } else {
          this->_rAF.SetLoByte(0x80);
        }
        break;
      case 0x1C:
        this->_rDE.SetLoByte(this->_rDE.GetLoByte() + 1);
        this->_rDE.SetLoByte(this->_rDE.GetLoByte() & 0xFF);
        if(this->_rDE.GetLoByte()) {
          this->_rAF.SetLoByte(0x00);
        } else {
          this->_rAF.SetLoByte(0x80);
        }
        break;
      case 0x24:
        this->_rHL.SetHiByte(this->_rHL.GetHiByte() + 1);
        this->_rHL.SetHiByte(this->_rHL.GetHiByte() & 0xFF);
        if(this->_rHL.GetHiByte()) {
          this->_rAF.SetLoByte(0x00);
        } else {
          this->_rAF.SetLoByte(0x80);
        }
        break;
      case 0x2C:
        this->_rHL.SetLoByte(this->_rHL.GetLoByte() + 1);
        this->_rHL.SetLoByte(this->_rHL.GetLoByte() & 0xFF);
        if(this->_rHL.GetLoByte()) {
          this->_rAF.SetLoByte(0x00);
        } else {
          this->_rAF.SetLoByte(0x80);
        }
        break;
      case 0x34:
        this->_rAF.SetHiByte(this->_rAF.GetHiByte() + 1);
        this->_rAF.SetHiByte(this->_rAF.GetHiByte() & 0xFF);
        if(this->_rAF.GetHiByte()) {
          this->_rAF.SetLoByte(0x00);
        } else {
          this->_rAF.SetLoByte(0x80);
        }
        break;
    }

    this->_cycles += 1;
  }

  /**
   * Refer to page 160 Z80 CPU User's ManualS
   * r <- n
   **/
  auto CPU::_LDrn(std::uint8_t byte) -> void {
    switch(byte) {
      case 0x06:
        this->_rBC.SetHiByte(this->_mmu->RB(this->_rPC.GetWord()));
        break;
      case 0x0E:
        this->_rBC.SetLoByte(this->_mmu->RB(this->_rPC.GetWord()));
        break;
      case 0x16:
        this->_rDE.SetHiByte(this->_mmu->RB(this->_rPC.GetWord()));
        break;
      case 0x1E:
        this->_rDE.SetLoByte(this->_mmu->RB(this->_rPC.GetWord()));
       break;
      case 0x26:
        this->_rHL.SetHiByte(this->_mmu->RB(this->_rPC.GetWord()));
        break;
      case 0x2E:
        this->_rHL.SetLoByte(this->_mmu->RB(this->_rPC.GetWord()));
        break;
      case 0x3E:
        this->_rAF.SetHiByte(this->_mmu->RB(this->_rPC.GetWord()));
        break;
    }
    this->_rPC.Increment();
    this->_cycles += 2;
  }

  /**
   * Refer to page 248 Z80 CPU User's Manual
   * If Z = 1, continue
   * If Z = 0, PC <- pc + e
   **/
  auto CPU::_JRNZe() -> void {
    bool dec = false;
    auto b = this->_mmu->RB(this->_rPC.GetWord());
    this->_rPC.Increment();

    if(b > 0x7F) {
      b = (-b) - 1;
      dec = true;
      pByte(b, "\tJUMP DEC");
    } else {
      pByte(b, "\tJUMP INC");
    }

    if((this->_rAF.GetLoByte() & 0x80) == 0x00) {
      if(dec) {
        this->_rPC.Decrement(b);
      } else {
        this->_rPC.Increment(b);
      }
      this->_cycles += 3;
    } else {
      this->_cycles += 2;
    }
  }

  /**
   * Refer to page 172 Z80 CPU User's Manual
   **/
  auto CPU::_NOP() -> void {
    this->_cycles += 1;
  }

  /**
   * Refer to page ??? Z80 CPU User's Manual for original OP 0xEA -> JP PE nn
   * NOTE: In thhe GB documented changes, the same OP code really means the below function
   * LD (word),A      Save A at given address
   **/
  auto CPU::_LDnnA() -> void {
    this->_mmu->WB(this->_mmu->RW(this->_rPC.GetWord()), this->_rAF.GetHiByte());
    this->_rPC.Increment();
    this->_cycles += 4;
  }

  /**
   * Refer to page 172 Z80 CPU User's Manual
   **/
  auto CPU::_LDSPHL() -> void {
    this->_rSP.SetWord(this->_rHL.GetWord());
    this->_cycles += 1;
  }
}
