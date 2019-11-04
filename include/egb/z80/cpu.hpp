#pragma once

#include <egb/z80/mmu.hpp>
#include <egb/z80/register.hpp>

#include <cstdint>
#include <unordered_map>

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

    typedef void(z80::CPU:: * ins)();
    std::unordered_map<std::uint8_t, ins> _instructions;

    auto ClearFlags() -> void;
    auto SetZFlag(bool onoff) -> void;
    auto SetNFlag(bool onoff) -> void;
    auto SetHFlag(bool onoff) -> void;
    auto SetCFlag(bool onoff) -> void;

    auto LD_n_nn() -> void;
    auto SBC_A_s() -> void;
    auto _SBC_A_r() -> void;
    auto _SBC_A_n() -> void;
    auto _SBC_A_hl() -> void;
    auto CBSwitcher() -> void;
    auto SLA_n() -> void;
    auto _SLA_r(int target, bool hiByte) -> void;
    auto _SLA_hl() -> void;

  public:
    Register regs[6];
    Register prev_regs[6];
    Register rst_regs[6];

    CPU(MMU * mmu);
    ~CPU();

    auto Step() -> void;
    auto GetSteps() -> std::uint64_t;
    auto GetCycles() noexcept(false) -> std::uint64_t;
  };
}
