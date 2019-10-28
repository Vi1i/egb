#include <iostream>
#include <iomanip>
#include <cstdlib>

#include <egb/gb/cartridge.hpp>
#include <egb/gb/system.hpp>

auto main(int argc, char * argv[]) -> int {
  if(argc != 2) {
    return EXIT_FAILURE;
  }

  std::string cart_filename(argv[1]);
  egb::gb::Cartridge cart = egb::gb::Cartridge(cart_filename);
  std::cout << "   Title: " <<  cart.GetTitle() << std::endl;
  std::cout << "ROM Size: 0x" << std::setfill('0') << std::setw(2) << std::hex << (int)cart.GetROMSize() << std::endl;
  std::cout << "RAM Size: 0x" << std::setfill('0') << std::setw(2) << std::hex << (int)cart.GetRAMSize() << std::endl;
  std::cout << "    Type: 0x" << std::setfill('0') << std::setw(2) << std::hex << (int)cart.GetType() << std::endl;

  egb::gb::System gameboy = egb::gb::System();
  gameboy.LoadCartridge(&cart);
  gameboy.TurnOn();

  return EXIT_SUCCESS;
}
