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
  # UTIL stuff
  src/utils/utils.cpp

  # CLI stuff
  #src/cli.cpp

  # Z80 stuff
  src/z80/memory.cpp
  src/z80/mmu.cpp

  # I am unsure if this should stay in the z80 namespace
  # as the direct modification from the GB diffs make
  # this more of a GB perhaps?
  src/z80/instruction.cpp
  src/z80/cpu.cpp
  #src/z80/instructions/ld_n_nn.cpp
  #src/z80/instructions/sbc_A_r.cpp
  #src/z80/instructions/cb-ops.cpp
  #src/z80/instructions/sla_n.cpp

  # GameBoy stuffs
  src/gb/cartridge.cpp
  src/gb/system.cpp

  # main
  src/main.cpp
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
    ncurses
  PUBLIC
)

##############################################
# Installation instructions
# + Linux support

if(<PLATFORM_ID:Windows>)
elseif($<PLATFORM_ID:Linux>)
  include(GNUInstallDirs)
  set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/egb)
  
  install(TARGETS egb
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )
  
  install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
elseif($<PLATFORM_ID:Darwin>)
endif()
