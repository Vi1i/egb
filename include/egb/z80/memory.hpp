#pragma once

#include <cstdint>
#include <string>

namespace egb::z80 {
    // TODO: (Vi1i) Implement other memory modules or a more dynamic memory
    //              class that can be used with other modules.
  class Memory {
    // Instead of doing one "large" memory area, one could consider chunking into differrent
    // segements like bios, cartridge, etc. While this would add on work to the RB and WB
    // functions, it would allow for better segmentation for debug purposes. Since this
    // project is here for debug purposes... But, this would add some minor overhead into
    // the most called area.
    //
    std::uint8_t * _memory;

  public:
    Memory();
    ~Memory();

    auto WB(const std::uint16_t addr, const std::uint8_t bytes) -> void;
    auto RB(const std::uint16_t addr) -> std::uint8_t;
  };
}
