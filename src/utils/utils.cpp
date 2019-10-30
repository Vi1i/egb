#include <egb/utils/utils.hpp>

#include <cstdint>
#include <string>
#include <iomanip>
#include <sstream>

namespace egb::utils {
    auto pWord(std::uint16_t word) -> std::string {
      std::ostringstream oss;
      oss << "0x"<< std::setfill('0') << std::setw(4) << std::hex << std::uppercase<< (int)word;
      return oss.str();
    }

    auto Word(std::uint16_t word) -> std::string {
      std::ostringstream oss;
      oss << std::setfill('0') << std::setw(4) << std::hex << std::uppercase<< (int)word;
      return oss.str();
    }

    auto pByte(std::uint8_t byte) -> std::string {
      std::ostringstream oss;
      oss << "0x"<< std::setfill('0') << std::setw(2) << std::hex << std::uppercase<< (int)byte;
      return oss.str();
    }

    auto Byte(std::uint8_t byte) -> std::string {
      std::ostringstream oss;
      oss << std::setfill('0') << std::setw(2) << std::hex << std::uppercase<< (int)byte;
      return oss.str();
    }
}
