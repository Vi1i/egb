#pragma once

#include <egb/defines.hpp>
#include <egb/z80/instruction.hpp>
#include <egb/z80/mmu.hpp>
#include <egb/z80/register.hpp>

#include <vector>

namespace egb::z80 {
  class CPU {
  public:
    std::vector<egb::z80::Instruction> instructions;
    std::uint64_t cycles;
    std::uint64_t steps;

    auto ClearFlags() -> void;
    auto SetZFlag(bool onoff) -> void;
    auto SetNFlag(bool onoff) -> void;
    auto SetHFlag(bool onoff) -> void;
    auto SetCFlag(bool onoff) -> void;

    MMU * mmu;
    Register RegAF;
    Register RegBC;
    Register RegDE;
    Register RegHL;
    Register RegSP;
    Register RegPC;

    CPU(MMU * mmu);
    ~CPU();

    auto Read() noexcept(false) -> void;
    auto Execute() noexcept(false) -> void;
    auto GetSteps() -> std::uint64_t;
    auto GetCycles() noexcept(false) -> std::uint64_t;
  };
}
