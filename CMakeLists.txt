#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

cmake_minimum_required(VERSION 3.5)

project(
  libthe
  VERSION 0.1.0
  LANGUAGES C
  DESCRIPTION "Collection of utilities for core of The programming language"
)

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

add_library(${PROJECT_NAME}_object OBJECT ${sources})
set_property(TARGET ${PROJECT_NAME}_object PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library(${PROJECT_NAME} SHARED $<TARGET_OBJECTS:${PROJECT_NAME}_object>)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::Crypto OpenSSL::SSL)

add_library(${PROJECT_NAME}_static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}_object>)
target_link_libraries(${PROJECT_NAME}_static PRIVATE OpenSSL::Crypto_a OpenSSL::SSL_a)

if (MINGW OR UNIX)
  configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)
  configure_file(${PROJECT_NAME}-static.pc.in ${PROJECT_NAME}-static.pc @ONLY)

  install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
  install(FILES LICENSE DESTINATION "${CMAKE_INSTALL_DOCDIR}")
  install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-static.pc" DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
  install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_static LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
endif ()

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND LIBTHE_BUILD_TESTS)
  set(CTEST_MEMORYCHECK_COMMAND valgrind)
  set(MEMORYCHECK_COMMAND_OPTIONS "--error-exitcode=255 --errors-for-leak-kinds=all --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes")

  include(CTest)
endif ()
