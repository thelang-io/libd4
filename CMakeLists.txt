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

include(cmake/openssl.cmake)
include(GNUInstallDirs)

option(LIBTHE_BUILD_EXAMPLES "Build example programs" OFF)
option(LIBTHE_BUILD_TESTS "Build test programs" OFF)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)

list(APPEND LIBTHE_CMAKE_FLAGS "-Walloca")
list(APPEND LIBTHE_CMAKE_FLAGS "-Wbad-function-cast")
list(APPEND LIBTHE_CMAKE_FLAGS "-Wcast-align")
list(APPEND LIBTHE_CMAKE_FLAGS "-Wcast-qual")
list(APPEND LIBTHE_CMAKE_FLAGS "-Wdate-time")
list(APPEND LIBTHE_CMAKE_FLAGS "-Wdeclaration-after-statement")
list(APPEND LIBTHE_CMAKE_FLAGS "-Wdeprecated")
list(APPEND LIBTHE_CMAKE_FLAGS "-Wdouble-promotion")
list(APPEND LIBTHE_CMAKE_FLAGS "-Wfloat-equal")
list(APPEND LIBTHE_CMAKE_FLAGS "-Wformat=2")
list(APPEND LIBTHE_CMAKE_FLAGS "-Wmissing-noreturn")
list(APPEND LIBTHE_CMAKE_FLAGS "-Wmissing-prototypes")
list(APPEND LIBTHE_CMAKE_FLAGS "-Wpacked")
list(APPEND LIBTHE_CMAKE_FLAGS "-Wpragmas")
list(APPEND LIBTHE_CMAKE_FLAGS "-Wstrict-prototypes")
list(APPEND LIBTHE_CMAKE_FLAGS "-Wswitch-default")
list(APPEND LIBTHE_CMAKE_FLAGS "-Wswitch-enum")
list(APPEND LIBTHE_CMAKE_FLAGS "-Wundef")
list(APPEND LIBTHE_CMAKE_FLAGS "-Wunreachable-code")
list(APPEND LIBTHE_CMAKE_FLAGS "-Wunused-macros")
list(APPEND LIBTHE_CMAKE_FLAGS "-Wvla")
list(JOIN LIBTHE_CMAKE_FLAGS " " LIBTHE_CMAKE_FLAGS)

if (MSVC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
else ()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -pedantic-errors ${LIBTHE_CMAKE_FLAGS}")
endif ()

set(sources src/any.c src/bool.c src/byte.c src/char.c src/enum.c src/error.c src/number.c src/rune.c src/safe.c src/string.c)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

if (WIN32)
  list(APPEND THE_LIBRARIES ws2_32)
  list(APPEND THE_LIBRARIES gdi32)
  list(APPEND THE_LIBRARIES advapi32)
  list(APPEND THE_LIBRARIES crypt32)
  list(APPEND THE_LIBRARIES user32)
else ()
  find_package(Threads REQUIRED)

  list(APPEND THE_LIBRARIES Threads::Threads)
  list(APPEND THE_LIBRARIES ${CMAKE_DL_LIBS})
endif ()

list(APPEND THE_LIBRARIES OpenSSL::Crypto)
list(APPEND THE_LIBRARIES OpenSSL::SSL)

add_library(the SHARED ${sources})
target_link_libraries(the PUBLIC ${THE_LIBRARIES})

if (MINGW OR UNIX)
  configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)

  install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
  install(FILES LICENSE DESTINATION "${CMAKE_INSTALL_DOCDIR}")
  install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}.pc" DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
  install(TARGETS the LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
endif ()

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND LIBTHE_BUILD_EXAMPLES)
  set(examples any bool byte char crypto enum error macro number rand safe ssl string)

  foreach (example ${examples})
    add_executable(${PROJECT_NAME}-example-${example} examples/${example}.c)
    target_link_libraries(${PROJECT_NAME}-example-${example} PRIVATE the)
  endforeach ()
endif ()

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND LIBTHE_BUILD_TESTS)
  set(CTEST_MEMORYCHECK_COMMAND valgrind)
  set(MEMORYCHECK_COMMAND_OPTIONS "--error-exitcode=255 --errors-for-leak-kinds=all --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes")

  include(CTest)
  set(tests rand)

  foreach (test ${tests})
    add_executable(${PROJECT_NAME}-test-${test} test/${test}-test.c)
    target_link_libraries(${PROJECT_NAME}-test-${test} PRIVATE the)
    add_test(${test} ${PROJECT_NAME}-test-${test})
  endforeach ()
endif ()
