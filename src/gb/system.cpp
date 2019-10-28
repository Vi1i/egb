#include <egb/gb/system.hpp>
#include <egb/z80/mmu.hpp>
#include <egb/z80/cpu.hpp>
#include <egb/gb/cartridge.hpp>
#include <egb/defines.hpp>

#include <stdexcept>

namespace egb::gb {
  System::System() : _mmu(), _cpu(&_mmu), _cartridge(nullptr) { }

  System::~System() = default;

  // TODO: (Vi1i) Shouldn't use the hardcoded check in this function
  auto System::LoadCartridge(Cartridge *cart) -> void {
    if(cart->GetType() != 0x00) {
      throw std::runtime_error("ROM ONLY games currently supported");
    }
    this->_cartridge = cart;
  }

  auto System::Reset() -> void {
    this->_mmu = egb::z80::MMU();
    this->_cpu = egb::z80::CPU(&this->_mmu);
  }

  // TODO: (Vi1i) Look into threading here
  auto System::TurnOn() -> void {
    this->Reset();
    while(true) {
      this->_cpu.Cycle();
    }
  }
}
