#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

cmake_minimum_required(VERSION 3.14)

project(
  libthe
  VERSION 0.1.0
  LANGUAGES C
  DESCRIPTION "Collection of utilities for core of The programming language."
)

option(LIBTHE_BUILD_EXAMPLES "Build example programs" OFF)
option(LIBTHE_BUILD_TESTS "Build test programs" OFF)
option(LIBTHE_COVERAGE "Build programs with support for coverage" OFF)

include(cmake/Policies.cmake)
set_policies()

include(cmake/Flags.cmake)
include(cmake/Libraries.cmake)
include(cmake/DownloadOpenSSL.cmake)

set(
  sources
  src/any.c
  src/array.c
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
