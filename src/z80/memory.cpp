#include <egb/z80/memory.hpp>
#include <egb/defines.hpp>

#include <cstdint>
#include <string>
#include <stdexcept>

/**
 * TODO: (Vi1i) Implement Memory specific exceptions to fine.
 **/
namespace egb::z80 {
  Memory::Memory() {
    this->_memory = new std::uint8_t[egb::defines::MEMORY_END + 1];
    for(auto z = 0; z <= egb::defines::MEMORY_END ; ++z) {
      if(z <= egb::defines::BIOS_END) {
        this->_memory[z] = egb::defines::BIOS_DATA[z];
      } else {
        this->_memory[z] = 0;
      }
    }
  }

  Memory::~Memory() {
    delete [] this->_memory;
  }

  auto Memory::WB(const std::uint16_t addr, const std::uint8_t byte) -> void {
    if(addr > egb::defines::MEMORY_END) {
      throw std::runtime_error("Invalid address " + std::to_string(addr) + " given.");
    }

    this->_memory[addr] = byte;
  }

  auto Memory::RB(const std::uint16_t addr)  -> std::uint8_t {
    if(addr > egb::defines::MEMORY_END) {
      throw std::runtime_error("Invalid address " + std::to_string(addr) + " given.");
    }

    std::uint8_t byte;

    byte = this->_memory[addr];

    return byte;
  }
}
