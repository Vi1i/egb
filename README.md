# EGB
A basic C++ emulator for the Nintendo GameBoy.

## Compiling
### Requirements
* CMAKE 3 >= 3.5
* C++ >= std17
* C++ Compiler
  * GCC >= 8
  * Clang >= 7
  * MSVC >= 19.14
  * Apple Clang >= 11.0.0
### Building
##### General Build for Debug
```
cd <PROJECT_ROOT>/build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
```
##### Build with an Install Prefix
```
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
- [ ] Createa a write up this time

#### Notes
* DO NOT DELETE THIS TIME
* Only tested on Linux.
