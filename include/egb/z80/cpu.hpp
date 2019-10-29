#pragma once

#include <egb/z80/mmu.hpp>
#include <egb/z80/register.hpp>

#include <cstdint>

#define RegAF 0
#define RegBC 1
#define RegDE 2
#define RegHL 3
#define RegSP 4
#define RegPC 5

namespace egb::z80 {
  class CPU {
    std::uint64_t _cycles;
    std::uint64_t _steps;
    MMU * _mmu;

  public:
    Register regs[6];
    Register prev_regs[6];
    Register rst_regs[6];

    CPU(MMU * mmu);
    ~CPU();

    auto Step() -> void;
    auto GetSteps() -> std::uint64_t;
    auto GetCycles() -> std::uint64_t;
  };
}
