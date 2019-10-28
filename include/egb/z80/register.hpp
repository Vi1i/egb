#pragma once
#include <cstdint>

namespace egb::z80 {
  class Register {
    std::uint16_t _word;

  public:
    Register();
    ~Register();

    // I do not like this layout currently
    auto SetLoByte(const std::uint8_t byte) -> void;
    auto SetHiByte(const std::uint8_t byte) -> void;
    auto SetWord(const std::uint16_t word) -> void;
    auto GetLoByte() -> std::uint8_t;
    auto GetHiByte() -> std::uint8_t;
    auto GetWord() -> std::uint16_t;
    auto Increment() -> void;
    auto Increment(int n) -> void;
    auto Decrement() -> void;
    auto Decrement(int n) -> void;
  };
}
