#pragma once

#include <egb/defines.hpp>
#include <string>

namespace egb::utils {
    auto pWord(WORD word) -> std::string;
    auto Word(WORD word) -> std::string;
    auto pByte(BYTE byte) -> std::string;
    auto Byte(BYTE byte) -> std::string;
}
