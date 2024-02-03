#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

cmake_minimum_required(VERSION 3.5)
project(libthe VERSION 0.1.0 LANGUAGES C)

include(GNUInstallDirs)

option(LIBTHE_BUILD_EXAMPLES "Build example programs" OFF)
option(LIBTHE_BUILD_TESTS "Build test programs" OFF)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS_PART1 "-Wall -Werror -Wextra -pedantic-errors")
set(CMAKE_C_FLAGS_PART2 "-Weverything -Wno-padded -Wno-unsafe-buffer-usage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_PART1} ${CMAKE_C_FLAGS_PART2}")

set(sources src/any.c src/bool.c src/byte.c src/char.c src/enum.c src/error.c src/number.c src/rune.c src/safe.c src/string.c)

include_directories(include)

add_library(the SHARED ${sources})
add_library(the_a STATIC ${sources})

if (MINGW OR UNIX)
  set(includedir "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
  set(libdir "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
  set(prefix "${CMAKE_INSTALL_PREFIX}")

  configure_file(libthe.pc.in libthe.pc @ONLY)
  configure_file(libthe-static.pc.in libthe-static.pc @ONLY)

  install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
  install(FILES LICENSE DESTINATION "${CMAKE_INSTALL_DOCDIR}")
  install(FILES "${PROJECT_BINARY_DIR}/libthe.pc" "${PROJECT_BINARY_DIR}/libthe-static.pc" DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
  install(TARGETS the the_a LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
endif ()
