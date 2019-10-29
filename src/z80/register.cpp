#include <egb/z80/register.hpp>

#include <cstdint>

namespace egb::z80 {
  union Register {
    std::uint16_t w;
    struct {
      std::uint8_t l;
      std::uint8_t h;
    };
  };
}
