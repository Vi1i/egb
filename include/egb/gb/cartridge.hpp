#pragma once

#include <cstdint>
#include <string>

namespace egb::gb {
  class Cartridge {
    std::size_t _file_size;
    std::uint8_t _type;
    std::string _title;
    std::size_t _romSize;
    std::size_t _ramSize;
    std::uint8_t * _buffer;

    auto _Initialize() -> void;

  public:
    Cartridge(std::string filename);
    ~Cartridge();

    auto GetTitle() -> std::string;
    auto GetType() -> std::uint8_t;
    auto GetROMSize() -> std::size_t;
    auto GetRAMSize() -> std::size_t;
  };
}
