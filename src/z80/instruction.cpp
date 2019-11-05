#include <egb/z80/instruction.hpp>
#include <egb/z80/cpu.hpp>
#include <egb/defines.hpp>
#include <egb/utils/utils.hpp>

namespace egb::z80 {
  Instruction::Instruction(CPU * cpu) {
    _cpu = cpu;
    this->_OPLookup();
  }

  Instruction::~Instruction() {
  }

  auto Instruction::Execute() -> void {
    if(!_execute) {
      throw std::runtime_error("Instruction not implemented!");
    } else {
      _execute();
    }
  }

  auto Instruction::Unexecute() -> void {
    if(!_execute) {
      throw std::runtime_error("Instruction not implemented!");
    } else {
      _unexecute();
    }
  }

  auto Instruction::_OPLookup() -> void {
    BYTE opcode = _cpu->mmu->RB(_cpu->RegPC.w);

    switch(opcode) {
      case 0x00:
        insHex.push_back(utils::Byte(opcode));
        insStr = "NOP";

        _execute = [*this]() -> void {
          _cpu->RegPC.w += 2;
        };

        _unexecute = [*this]() -> void {
          _cpu->RegPC.w -= 2;
        };
        break;

      /**
       * ld_n_n
       *    |  n  |  n1 |
       * 0 1 * * * * * *
       *  Reg | n, n1
       *   A  | 111
       *   B  | 000
       *   C  | 001
       *   D  | 101
       *   E  | 011
       *   H  | 100
       *   L  | 101
       **/
      //case 0x7F:
      //case 0x78:
      //case 0x79:
      //case 0x7A:
      //case 0x7B:
      //case 0x7C:
      //case 0x7D:
      //case 0x40:
      //case 0x41:
      //case 0x42:
      //case 0x43:
      //case 0x44:
      //case 0x45:
      //case 0x48:
      //case 0x49:
      //case 0x4A:
      //case 0x4B:
      //case 0x4C:
      //case 0x4D:
      case 0x50:
        insHex.push_back(utils::Byte(opcode));
        insStr = "LD D, B";

        _execute = [*this]() -> void {
          _cpu->RegDE.h = _cpu->RegBC.h;
          _cpu->RegPC.w += 2;
        };
        break;
      //case 0x51:
      //case 0x52:
      //case 0x53:
      //case 0x54:
      //case 0x55:
      //case 0x58:
      //case 0x59:
      //case 0x5A:
      //case 0x5B:
      //case 0x5C:
      //case 0x5D:
      //case 0x60:
      //case 0x61:
      //case 0x62:
      //case 0x63:
      //case 0x64:
      //case 0x65:
      //case 0x68:
      //case 0x69:
      //case 0x6A:
      //case 0x6B:
      //case 0x6C:
      //case 0x6D:

      default:
        insHex.push_back(utils::Byte(opcode));
        insStr = "UNIDENTIFIED";
    }
  }
}
