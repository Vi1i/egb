#pragma once

#include <egb/defines.hpp>

namespace egb::z80 {
  union Register {
    WORD w;

    struct {
      BYTE h;
      BYTE l;
    };
  };
}
