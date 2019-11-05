#include <egb/utils/utils.hpp>
#include <egb/defines.hpp>

#include <string>
#include <iomanip>
#include <sstream>

namespace egb::utils {
    auto pWord(WORD word) -> std::string {
      std::ostringstream oss;
      oss << "0x"<< std::setfill('0') << std::setw(4) << std::hex << std::uppercase<< (int)word;
      return oss.str();
    }

    auto Word(WORD word) -> std::string {
      std::ostringstream oss;
      oss << std::setfill('0') << std::setw(4) << std::hex << std::uppercase<< (int)word;
      return oss.str();
    }

    auto pByte(BYTE byte) -> std::string {
      std::ostringstream oss;
      oss << "0x"<< std::setfill('0') << std::setw(2) << std::hex << std::uppercase<< (int)byte;
      return oss.str();
    }

    auto Byte(BYTE byte) -> std::string {
      std::ostringstream oss;
      oss << std::setfill('0') << std::setw(2) << std::hex << std::uppercase<< (int)byte;
      return oss.str();
    }
}
