# EGB
A basic C++ emulator for the Nintendo GameBoy.
This project currently does not get out of the BIOS yet. For a game like Tetris, minimal isntruction sets are needed.
Currently building towards ROM ONLY support, then will expand to others.

Might eventually add grahics, sound, input, etc.

## Compiling
### Requirements
* CMAKE 3 >= 3.5
* C++ >= std17
* C++ Compiler
  * GCC >= 8
  * Clang >= 7
  * MSVC >= 19.14
  * Apple Clang >= 11.0.0
* ncurses
  * This will curently limit windows, PDcurses will allow though. This will require something like an observer or MVC set up that is currently not there though.
### Building
##### General Build for Debug
```bash
cd <PROJECT_ROOT>/build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
```
##### Build with an Install Prefix
```bash
cd <PROJECT_ROOT>/build
cmake .. -DCMAKE_INSTALL_PREFIX=~/.local
make
make install
```

#### TODO
- [ ] Testing
- [ ] Integrate some type of CI/CD
- [ ] Create references
- [ ] Create list of features for support and development
- [ ] Clean up code
- [ ] Revisit poor design choices
- [ ] Write up documentation
- [ ] Create a a write up this time

#### Notes
* DO NOT DELETE THIS TIME
* Only tested on Linux.
* Should compile on Apple
  * Issues should really only be around C++17 and `<filesystem>`
