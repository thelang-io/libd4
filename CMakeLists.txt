#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

cmake_minimum_required(VERSION 3.14)

project(
  libd4
  VERSION 0.3.0
  LANGUAGES C
  DESCRIPTION "A library specifically designed for The programming language"
)

option(LIBD4_BUILD_EXAMPLES "Build example programs" OFF)
option(LIBD4_BUILD_TESTS "Build test programs" OFF)
option(LIBD4_COVERAGE "Build programs with support for coverage" OFF)
option(LIBD4_SANITIZER "Enable address sanitizer" OFF)

include(cmake/Policies.cmake)
set_policies()

include(cmake/Flags.cmake)
include(cmake/Libraries.cmake)
include(cmake/DownloadOpenSSL.cmake)

set(
  sources
  src/any.c
  src/bool.c
  src/byte.c
  src/char.c
  src/enum.c
  src/error.c
  src/globals.c
  src/map.c
  src/number.c
  src/object.c
  src/rune.c
  src/safe.c
  src/string.c
)

add_library(d4 ${sources})
target_include_directories(d4 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(d4 PUBLIC ${LIBD4_LIBRARIES})

include(cmake/Install.cmake)
include(cmake/Examples.cmake)
include(cmake/Tests.cmake)
