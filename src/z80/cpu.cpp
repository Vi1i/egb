#include <egb/z80/cpu.hpp>
#include <egb/z80/register.hpp>
#include <egb/utils/utils.hpp>
#include <egb/defines.hpp>

#include <cstdint>
#include <unordered_map>

namespace egb::z80 {
  CPU::CPU(MMU * mmu) {
    _cycles = 0;
    _steps = 0;
    _mmu = mmu;

    for(auto &reg : regs) {
      reg = {0x0000};
    }

    regs[RegPC].w = egb::defines::BIOS_START;
    _instructions[0x01] = &CPU::LD_n_nn;
    _instructions[0x11] = &CPU::LD_n_nn;
    _instructions[0x21] = &CPU::LD_n_nn;
    _instructions[0x31] = &CPU::LD_n_nn;

    _instructions[0xCB] = &CPU::CBSwitcher;
    _instructions[0xCB] = &CPU::CBSwitcher;
    _instructions[0xCB] = &CPU::CBSwitcher;
    _instructions[0xCB] = &CPU::CBSwitcher;
    _instructions[0xCB] = &CPU::CBSwitcher;
    _instructions[0xCB] = &CPU::CBSwitcher;
    _instructions[0xCB] = &CPU::CBSwitcher;
    _instructions[0xCB] = &CPU::CBSwitcher;

    _instructions[0x98] = &CPU::SBC_A_s;
    _instructions[0x99] = &CPU::SBC_A_s;
    _instructions[0x9A] = &CPU::SBC_A_s;
    _instructions[0x9B] = &CPU::SBC_A_s;
    _instructions[0x9C] = &CPU::SBC_A_s;
    _instructions[0x9D] = &CPU::SBC_A_s;
    _instructions[0x9E] = &CPU::SBC_A_s;
    _instructions[0x9F] = &CPU::SBC_A_s;
    _instructions[0xDE] = &CPU::SBC_A_s;

  }

  CPU::~CPU() = default;

  auto CPU::ClearFlags() -> void {
    regs[RegAF].l = 0x00;
  }

  auto CPU::SetZFlag(bool onoff) -> void {
    auto nth(7);
    regs[RegAF].l = (regs[RegAF].l & ~(1UL << nth)) | (onoff << nth);
  }

  auto CPU::SetNFlag(bool onoff) -> void {
    auto nth(6);
    regs[RegAF].l = (regs[RegAF].l & ~(1UL << nth)) | (onoff << nth);
  }

  auto CPU::SetHFlag(bool onoff) -> void {
    auto nth(5);
    regs[RegAF].l = (regs[RegAF].l & ~(1UL << nth)) | (onoff << nth);
  }

  auto CPU::SetCFlag(bool onoff) -> void {
    auto nth(4);
    regs[RegAF].l = (regs[RegAF].l & ~(1UL << nth)) | (onoff << nth);
  }

  auto CPU::GetSteps() -> std::uint64_t {
    return _steps;
  }

  auto CPU::Step() -> void {
    std::copy(std::begin(regs), std::end(regs), std::begin(prev_regs));
    std::uint8_t byte = _mmu->RB(regs[RegPC].w);
    //regs[RegPC].w += 2;
    _steps++;
    if(_instructions.count(byte)) {
      (this->*(_instructions[byte]))();
    } else {
      throw std::runtime_error("Instruction(" + utils::pByte(byte) + ") unimplemented!");
    }
  }
}
