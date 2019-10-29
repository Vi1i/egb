#pragma once

#include <egb/z80/mmu.hpp>
#include <egb/z80/register.hpp>

#include <cstdint>

namespace egb::z80 {
  class CPU {
    std::uint64_t _cycles;
    MMU * _mmu;

    Register _rAF;
    Register _rBC;
    Register _rDE;
    Register _rHL;
    Register _rSP;
    Register _rPC;

    Register _rstAF;
    Register _rstBC;
    Register _rstDE;
    Register _rstHL;
    Register _rstSP;
    Register _rstPC;

    auto _NOP() -> void;
    auto _LDSPnn() -> void;
    auto _CPn() -> void;
    auto _RSTp(std::uint8_t byte) -> void;
    auto _LDnnSP() -> void;
    auto _LDADE() -> void;
    auto _INCss(std::uint8_t byte) -> void;
    auto _LDHLIA() -> void;
    auto _DECm(std::uint8_t byte) -> void;
    auto _INCr(std::uint8_t byte) -> void;
    auto _LDrn(std::uint8_t byte) -> void;
    auto _JRNZe() -> void;
    auto _LDnnA() -> void;
    auto _LDSPHL() -> void;
    auto _SBCAr(std::uint8_t byte) -> void;

  public:
    CPU(MMU * mmu);
    ~CPU();

    auto Cycle() -> void;
  };
}
