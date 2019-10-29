#include <egb/z80/cpu.hpp>
#include <egb/defines.hpp>

#include <cstdint>

namespace egb::z80 {
  CPU::CPU(MMU * mmu) {
    _cycles = 0;
    _steps = 0;
    _mmu = mmu;

    for(auto &reg : regs) {
      reg = {0x0000};
    }

    regs[RegPC].w = egb::defines::BIOS_START;
  }

  CPU::~CPU() = default;

  auto CPU::GetSteps() -> std::uint64_t {
    return _steps;
  }

  auto CPU::Step() -> void {
    std::copy(std::begin(regs), std::end(regs), std::begin(prev_regs));
    auto byte = _mmu->RB(regs[RegPC].w);
    regs[RegPC].w += 2;
    _steps++;
  }
}
