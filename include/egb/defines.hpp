#pragma once

#include <cstdint>

namespace egb::defines {
  static const std::uint16_t MEMORY_START = 0x0000;
  static const std::uint16_t MEMORY_END = 0xFFFF;
  static const std::uint16_t BIOS_START = 0x0000;
  static const std::uint16_t BIOS_END = 0x00FF;
  static const std::uint16_t CARTRIDGE_START = 0x0000;
  static const std::uint16_t CARTRIDGE_END = 0x3FFF;
  static const std::uint16_t CARTRIDGE_HEADER_START = 0x0100;
  static const std::uint16_t CARTRIDGE_HEADER_END = 0x014F;
  static const std::uint16_t CARTRIDGE_BANKS_START = 0x4000;
  static const std::uint16_t CARTRIDGE_BANKS_END = 0x7FFF;
  static const std::uint16_t GRAPICS_RAM_START = 0x8000;
  static const std::uint16_t GRAPICS_RAM_END = 0x9FFF;
  static const std::uint16_t CARTRIDGE_EXTERNAL_START = 0xA000;
  static const std::uint16_t CARTRIDGE_EXTERNAL_END = 0xBFFF;
  static const std::uint16_t WORKING_RAM_START = 0xC000;
  static const std::uint16_t WORKING_RAM_END = 0xDFFF;
  static const std::uint16_t WORKING_RAM_SHADOW_START = 0xE000;
  static const std::uint16_t WORKING_RAM_SHADOW_END = 0xFDFF;
  static const std::uint16_t GRAPICS_SPRITE_START = 0xFE00;
  static const std::uint16_t GRAPICS_SPRITE_END = 0xFE9F;
  static const std::uint16_t MEMORY_MAPPED_IO_START = 0xFF00;
  static const std::uint16_t MEMORY_MAPPED_IO_END = 0xFF7F;
  static const std::uint16_t ZERO_PAGE_RAM_START = 0xFF80;
  static const std::uint16_t ZERO_PAGE_RAM_END = 0xFFFF;

  static const std::uint8_t BIOS_DATA[egb::defines::BIOS_END + 1] = {
      0x31, 0xFE, 0xFF, 0xAF, 0x21, 0xFF, 0x9F, 0x32, 0xCB, 0x7C, 0x20, 0xFB, 0x21, 0x26, 0xFF, 0x0E,
      0x11, 0x3E, 0x80, 0x32, 0xE2, 0x0C, 0x3E, 0xF3, 0xE2, 0x32, 0x3E, 0x77, 0x77, 0x3E, 0xFC, 0xE0,
      0x47, 0x11, 0x04, 0x01, 0x21, 0x10, 0x80, 0x1A, 0xCD, 0x95, 0x00, 0xCD, 0x96, 0x00, 0x13, 0x7B,
      0xFE, 0x34, 0x20, 0xF3, 0x11, 0xD8, 0x00, 0x06, 0x08, 0x1A, 0x13, 0x22, 0x23, 0x05, 0x20, 0xF9,
      0x3E, 0x19, 0xEA, 0x10, 0x99, 0x21, 0x2F, 0x99, 0x0E, 0x0C, 0x3D, 0x28, 0x08, 0x32, 0x0D, 0x20,
      0xF9, 0x2E, 0x0F, 0x18, 0xF3, 0x67, 0x3E, 0x64, 0x57, 0xE0, 0x42, 0x3E, 0x91, 0xE0, 0x40, 0x04,
      0x1E, 0x02, 0x0E, 0x0C, 0xF0, 0x44, 0xFE, 0x90, 0x20, 0xFA, 0x0D, 0x20, 0xF7, 0x1D, 0x20, 0xF2,
      0x0E, 0x13, 0x24, 0x7C, 0x1E, 0x83, 0xFE, 0x62, 0x28, 0x06, 0x1E, 0xC1, 0xFE, 0x64, 0x20, 0x06,
      0x7B, 0xE2, 0x0C, 0x3E, 0x87, 0xF2, 0xF0, 0x42, 0x90, 0xE0, 0x42, 0x15, 0x20, 0xD2, 0x05, 0x20,
      0x4F, 0x16, 0x20, 0x18, 0xCB, 0x4F, 0x06, 0x04, 0xC5, 0xCB, 0x11, 0x17, 0xC1, 0xCB, 0x11, 0x17,
      0x05, 0x20, 0xF5, 0x22, 0x23, 0x22, 0x23, 0xC9, 0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B,
      0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
      0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
      0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E, 0x3c, 0x42, 0xB9, 0xA5, 0xB9, 0xA5, 0x42, 0x4C,
      0x21, 0x04, 0x01, 0x11, 0xA8, 0x00, 0x1A, 0x13, 0xBE, 0x20, 0xFE, 0x23, 0x7D, 0xFE, 0x34, 0x20,
      0xF5, 0x06, 0x19, 0x78, 0x86, 0x23, 0x05, 0x20, 0xFB, 0x86, 0x20, 0xFE, 0x3E, 0x01, 0xE0, 0x50
    };
}