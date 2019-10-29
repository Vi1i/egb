#include <egb/gb/cartridge.hpp>
#include <egb/defines.hpp>

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <exception>
#include <string>
#include <sstream>

namespace egb::gb {
  Cartridge::Cartridge(std::string filename) {
    if(!std::filesystem::exists(filename)) {
      throw std::runtime_error("File does not exist, " + filename + " not found.");
    }

    this->_file_size = std::filesystem::file_size(filename);
    std::ifstream file(filename, std::ios::binary);


    this->_buffer = new std::uint8_t[this->_file_size + 1];
    for(auto z = 0; z <= this->_file_size; ++z) {
      this->_buffer[z] = 0;
    }

    char c;
    int pos = 0;
    while(file.get(c)) {
      std::uint8_t byte = static_cast<std::uint8_t>(c);
      this->_buffer[pos] = byte;
      pos++;
    }

    file.close();

    this->_Initialize();
  }

  Cartridge::~Cartridge() {
    delete [] this->_buffer;
  }

  // TODO: (Vi1i) Currently using a lot of hardcoded positions, which should
  //       either belong in the egb::defines or should be static within the
  //       header.
  //       https://gbdev.gg8.se/wiki/articles/The_Cartridge_Header
  auto Cartridge::_Initialize() -> void {
    // Get the title
    std::ostringstream oss;
    for (int i = 0x0134; i <= 0x143; ++i) {
      oss << this->_buffer[i];
    }
    this->_title = oss.str();

    //Get the cartridge type
    this->_type = this->_buffer[0x0147];

    //Get the ROM size
    this->_romSize = static_cast<int>(this->_buffer[0x0148]);

    //Get the RAM size
    this->_ramSize = static_cast<int>(this->_buffer[0x0149]);
  }

  auto Cartridge::GetTitle() -> std::string {
    return this->_title;
  }

  auto Cartridge::GetType() -> std::uint8_t {
    return this->_type;
  }

  auto Cartridge::GetROMSize() -> std::size_t {
    return this->_romSize;
  }

  auto Cartridge::GetRAMSize() -> std::size_t {
    return this->_ramSize;
  }
}
