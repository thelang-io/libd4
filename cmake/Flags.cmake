#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

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

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND LIBTHE_COVERAGE)
  list(APPEND LIBTHE_CMAKE_FLAGS "-O0")
  list(APPEND LIBTHE_CMAKE_FLAGS "-fprofile-arcs")
  list(APPEND LIBTHE_CMAKE_FLAGS "-ftest-coverage")
endif ()

list(JOIN LIBTHE_CMAKE_FLAGS " " LIBTHE_CMAKE_FLAGS)

if (MSVC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
else ()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -pedantic-errors ${LIBTHE_CMAKE_FLAGS}")
endif ()
