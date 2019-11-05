#pragma once

#include <egb/z80/mmu.hpp>
#include <egb/z80/register.hpp>

#include <queue>
#include <string>

namespace egb::z80 {
  class CPU;

  class Instruction {
    CPU * _cpu;

    std::function<void()> _execute;
    std::function<void()> _unexecute;

    auto _OPLookup() -> void;

  public:
    std::vector<std::string> insHex;
    std::string insStr;

    Instruction(CPU * cpu);
    ~Instruction();

    auto Execute() -> void;
    auto Unexecute() -> void;
  };
}
