cmake_minimum_required(VERSION 3.5)
project(egb VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." TRUE)
if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
       add_compile_options (-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       add_compile_options (-fcolor-diagnostics)
    endif ()
endif ()

##############################################
# Create target and set properties
add_executable(egb
  src/main.cpp

  # Z80 stuff
  src/z80/memory.cpp
  src/z80/mmu.cpp
  src/z80/register.cpp

  # I am unsure if this should stay in the z80 namespace
  # as the direct modification from the GB diffs make
  # this more of a GB perhaps?
  src/z80/cpu.cpp

  # GameBoy stuffs
  src/gb/cartridge.cpp
  src/gb/system.cpp
)

#Set target properties
target_include_directories(egb
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(egb
  PRIVATE
    $<$<PLATFORM_ID:Linux>:stdc++fs>
    $<$<PLATFORM_ID:Darwin>:${CXX_FILESYSTEM_LIBRARY}>
    $<$<PLATFORM_ID:Windows>:> 
  PUBLIC
)

##############################################
# Installation instructions
# + Linux support

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/egb)

install(TARGETS egb
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
