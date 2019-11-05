#pragma once

#include <egb/defines.hpp>
#include <string>

namespace egb::gb {
  class System;
  class Cartridge {
    friend class System;

    std::size_t _file_size;
    BYTE _type;
    std::string _title;
    std::size_t _romSize;
    std::size_t _ramSize;
    BYTE * _buffer;

    auto _Initialize() -> void;

  public:
    Cartridge(std::string filename);
    ~Cartridge();

    auto GetTitle() -> std::string;
    auto GetType() -> BYTE;
    auto GetROMSize() -> std::size_t;
    auto GetRAMSize() -> std::size_t;
  };
}
