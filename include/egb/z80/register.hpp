#pragma once

#include <cstdint>

namespace egb::z80 {
  union Register {
    std::uint16_t w;

    //This is set this way for little-endianness
    struct {
      std::uint8_t l;
      std::uint8_t h;
    };
  };
}
