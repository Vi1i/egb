#include <egb/z80/register.hpp>

#include <cstdint>

namespace egb::z80 {
  Register::Register() {
    this->_word = 0x0000;
  }

  Register::~Register() = default;

  auto Register::SetLoByte(const std::uint8_t byte) -> void {
    this->_word = (this->_word & 0xFF00) | byte;
  }

  auto Register::SetHiByte(const std::uint8_t byte) -> void {
    this->_word = (this->_word & 0x00FF) | (byte << 8);
  }

  auto Register::SetWord(const std::uint16_t word) -> void {
    this->_word = word;
  }

  auto Register::GetLoByte() -> std::uint8_t {
    return static_cast<std::uint8_t>(this->_word & 0x00FF);
  }

  auto Register::GetHiByte() -> std::uint8_t {
    return static_cast<std::uint8_t>((this->_word & 0xFF00) >> 8);
  }

  auto Register::GetWord() -> std::uint16_t {
    return this->_word;
  }

  auto Register::Increment() -> void {
    this->_word++;
  }

  auto Register::Increment(int n) -> void {
    for(auto z = 0; z < n; ++z) {
      this->_word++;
    }
  }

  auto Register::Decrement() -> void {
    this->_word--;
  }

  auto Register::Decrement(int n) -> void {
    for(auto z = n; z > 0; --z) {
      this->_word--;
    }
  }
}
