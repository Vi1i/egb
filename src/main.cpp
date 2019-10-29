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
  egb::gb::System gameboy = egb::gb::System();
  gameboy.LoadCartridge(&cart);
  gameboy.TurnOn();

  return EXIT_SUCCESS;
}
