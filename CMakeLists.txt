#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

cmake_minimum_required(VERSION 3.5)
project(libthe VERSION 0.1.0 LANGUAGES C)

include(cmake/OpenSSL.cmake)
include(GNUInstallDirs)

option(LIBTHE_BUILD_EXAMPLES "Build example programs" OFF)
option(LIBTHE_BUILD_TESTS "Build test programs" OFF)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)

if (MSVC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
else ()
  # todo find optimal flags, right now it seems too many flags
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra \
-Walloca \
-Wbad-function-cast \
-Wcast-align \
-Wcast-function-type \
-Wcast-qual \
-Wdate-time \
-Wdeclaration-after-statement \
-Wdeprecated \
-Wdouble-promotion \
-Wduplicate-decl-specifier \
-Wexpansion-to-defined \
-Wfloat-equal \
-Wformat=2 \
-Wimplicit-fallthrough \
-Wmain \
-Wmissing-noreturn \
-Wmissing-prototypes \
-Wpacked \
-Wpedantic \
-Wpointer-arith \
-Wpragmas \
-Wstrict-prototypes \
-Wswitch-default \
-Wswitch-enum \
-Wundef \
-Wunreachable-code \
-Wunused-macros \
-Wvariadic-macros \
-Wvla")
endif ()

set(sources src/any.c src/bool.c src/byte.c src/char.c src/enum.c src/error.c src/number.c src/rune.c src/safe.c src/string.c)

include_directories(include)

add_library(the SHARED ${sources})
target_link_libraries(the PRIVATE OpenSSL::Crypto OpenSSL::SSL)

add_library(the_a STATIC ${sources})
target_link_libraries(the_a PRIVATE OpenSSL::Crypto_a OpenSSL::SSL_a)

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

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND LIBDUC_BUILD_TESTS)
  set(CTEST_MEMORYCHECK_COMMAND valgrind)
  set(MEMORYCHECK_COMMAND_OPTIONS "--error-exitcode=255 --errors-for-leak-kinds=all --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes")

  include(CTest)
endif ()
