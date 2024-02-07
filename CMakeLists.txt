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

include(cmake/openssl.cmake)
include(GNUInstallDirs)

option(LIBTHE_BUILD_EXAMPLES "Build example programs" OFF)
option(LIBTHE_BUILD_TESTS "Build test programs" OFF)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)

list(APPEND THE_CMAKE_FLAGS "-Walloca")
list(APPEND THE_CMAKE_FLAGS "-Wbad-function-cast")
list(APPEND THE_CMAKE_FLAGS "-Wcast-align")
list(APPEND THE_CMAKE_FLAGS "-Wcast-qual")
list(APPEND THE_CMAKE_FLAGS "-Wdate-time")
list(APPEND THE_CMAKE_FLAGS "-Wdeclaration-after-statement")
list(APPEND THE_CMAKE_FLAGS "-Wdeprecated")
list(APPEND THE_CMAKE_FLAGS "-Wdouble-promotion")
list(APPEND THE_CMAKE_FLAGS "-Wfloat-equal")
list(APPEND THE_CMAKE_FLAGS "-Wformat=2")
list(APPEND THE_CMAKE_FLAGS "-Wmissing-noreturn")
list(APPEND THE_CMAKE_FLAGS "-Wmissing-prototypes")
list(APPEND THE_CMAKE_FLAGS "-Wpacked")
list(APPEND THE_CMAKE_FLAGS "-Wpragmas")
list(APPEND THE_CMAKE_FLAGS "-Wstrict-prototypes")
list(APPEND THE_CMAKE_FLAGS "-Wswitch-default")
list(APPEND THE_CMAKE_FLAGS "-Wswitch-enum")
list(APPEND THE_CMAKE_FLAGS "-Wundef")
list(APPEND THE_CMAKE_FLAGS "-Wunreachable-code")
list(APPEND THE_CMAKE_FLAGS "-Wunused-macros")
list(APPEND THE_CMAKE_FLAGS "-Wvla")
list(JOIN THE_CMAKE_FLAGS " " THE_CMAKE_FLAGS)

if (MSVC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
else ()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -pedantic-errors ${THE_CMAKE_FLAGS}")
endif ()

set(sources src/any.c src/bool.c src/byte.c src/char.c src/enum.c src/error.c src/number.c src/rune.c src/safe.c src/string.c)

add_library(${PROJECT_NAME}_object OBJECT ${sources})
#todo not needed?
#set_property(TARGET ${PROJECT_NAME}_object PROPERTY POSITION_INDEPENDENT_CODE 1)
target_include_directories(${PROJECT_NAME}_object PUBLIC include)
target_link_libraries(${PROJECT_NAME}_object PUBLIC OpenSSL::Crypto OpenSSL::SSL)

add_library(${PROJECT_NAME} SHARED $<TARGET_OBJECTS:${PROJECT_NAME}_object>)
add_library(${PROJECT_NAME}_static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}_object>)

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
