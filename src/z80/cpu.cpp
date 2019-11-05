#include <egb/z80/cpu.hpp>
#include <egb/z80/register.hpp>
#include <egb/utils/utils.hpp>
#include <egb/defines.hpp>

#include <cstdint>
#include <unordered_map>

namespace egb::z80 {
  CPU::CPU(MMU * mmu) {
    cycles = 0;
    steps = 0;
    this->mmu = mmu;

    RegAF = {0x01B0};
    RegBC = {0x0013};
    RegDE = {0x00D8};
    RegHL = {0x014D};
    RegSP = {0xFFFE};
    RegPC = {0x0000};

   mmu->WB(0xFF05, 0x00);
   mmu->WB(0xFF06, 0x00);
   mmu->WB(0xFF07, 0x00);
   mmu->WB(0xFF10, 0x80);
   mmu->WB(0xFF11, 0xBF);
   mmu->WB(0xFF12, 0xF3);
   mmu->WB(0xFF14, 0xBF);
   mmu->WB(0xFF16, 0x3F);
   mmu->WB(0xFF17, 0x00);
   mmu->WB(0xFF19, 0xBF);
   mmu->WB(0xFF1A, 0x7F);
   mmu->WB(0xFF1B, 0xFF);
   mmu->WB(0xFF1C, 0x9F);
   mmu->WB(0xFF1E, 0xBF);
   mmu->WB(0xFF20, 0xFF);
   mmu->WB(0xFF21, 0x00);
   mmu->WB(0xFF22, 0x00);
   mmu->WB(0xFF23, 0xBF);
   mmu->WB(0xFF24, 0x77);
   mmu->WB(0xFF25, 0xF3);
   mmu->WB(0xFF26, 0xF1);
   mmu->WB(0xFF40, 0x91);
   mmu->WB(0xFF42, 0x00);
   mmu->WB(0xFF43, 0x00);
   mmu->WB(0xFF45, 0x00);
   mmu->WB(0xFF47, 0xFC);
   mmu->WB(0xFF48, 0xFF);
   mmu->WB(0xFF49, 0xFF);
   mmu->WB(0xFF4A, 0x00);
   mmu->WB(0xFF4B, 0x00);
   mmu->WB(0xFFFF, 0x00);
  }

  CPU::~CPU() = default;

  auto CPU::ClearFlags() -> void {
    RegAF.l = 0x00;
  }

  auto CPU::SetZFlag(bool onoff) -> void {
    auto nth(7);
    RegAF.l = (RegAF.l & ~(1UL << nth)) | (onoff << nth);
  }

  auto CPU::SetNFlag(bool onoff) -> void {
    auto nth(6);
    RegAF.l = (RegAF.l & ~(1UL << nth)) | (onoff << nth);
  }

  auto CPU::SetHFlag(bool onoff) -> void {
    auto nth(5);
    RegAF.l = (RegAF.l & ~(1UL << nth)) | (onoff << nth);
  }

  auto CPU::SetCFlag(bool onoff) -> void {
    auto nth(4);
    RegAF.l = (RegAF.l & ~(1UL << nth)) | (onoff << nth);
  }

  auto CPU::Read() -> void {
    instructions.push_back(Instruction(this));
  }

  auto CPU::Execute() -> void {
    instructions.back().Execute();
  }
}
