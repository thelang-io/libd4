#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

cmake_minimum_required(VERSION 3.24)

project(
  libthe
  VERSION 0.1.0
  LANGUAGES C
  DESCRIPTION "Collection of utilities for core of The programming language."
)

include(GNUInstallDirs)

option(LIBTHE_BUILD_EXAMPLES "Build example programs" OFF)
option(LIBTHE_BUILD_TESTS "Build test programs" OFF)

include(cmake/DownloadOpenSSL.cmake)
include(cmake/Flags.cmake)
include(cmake/Libraries.cmake)

set(
  sources
  src/any.c
  src/bool.c
  src/byte.c
  src/char.c
  src/enum.c
  src/error.c
  src/number.c
  src/rune.c
  src/safe.c
  src/string.c
)

add_library(the ${sources})
target_include_directories(the PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(the PUBLIC ${THE_LIBRARIES})

include(cmake/Install.cmake)
include(cmake/Examples.cmake)
include(cmake/Tests.cmake)
