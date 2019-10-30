#pragma once

#include <cstdint>
#include <string>

namespace egb::utils {
    auto pWord(std::uint16_t word) -> std::string;
    auto Word(std::uint16_t word) -> std::string;
    auto pByte(std::uint8_t byte) -> std::string;
    auto Byte(std::uint8_t byte) -> std::string;
}
