#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)

list(APPEND LIBD4_CMAKE_FLAGS "-Walloca")
list(APPEND LIBD4_CMAKE_FLAGS "-Wbad-function-cast")
list(APPEND LIBD4_CMAKE_FLAGS "-Wcast-align")
list(APPEND LIBD4_CMAKE_FLAGS "-Wcast-qual")
list(APPEND LIBD4_CMAKE_FLAGS "-Wdate-time")
list(APPEND LIBD4_CMAKE_FLAGS "-Wdeclaration-after-statement")
list(APPEND LIBD4_CMAKE_FLAGS "-Wdeprecated")
list(APPEND LIBD4_CMAKE_FLAGS "-Wdouble-promotion")
list(APPEND LIBD4_CMAKE_FLAGS "-Wformat=2")
list(APPEND LIBD4_CMAKE_FLAGS "-Wmissing-noreturn")
list(APPEND LIBD4_CMAKE_FLAGS "-Wmissing-prototypes")
list(APPEND LIBD4_CMAKE_FLAGS "-Wpacked")
list(APPEND LIBD4_CMAKE_FLAGS "-Wpragmas")
list(APPEND LIBD4_CMAKE_FLAGS "-Wstrict-prototypes")
list(APPEND LIBD4_CMAKE_FLAGS "-Wswitch-default")
list(APPEND LIBD4_CMAKE_FLAGS "-Wswitch-enum")
list(APPEND LIBD4_CMAKE_FLAGS "-Wundef")
list(APPEND LIBD4_CMAKE_FLAGS "-Wunreachable-code")
list(APPEND LIBD4_CMAKE_FLAGS "-Wunused-macros")
list(APPEND LIBD4_CMAKE_FLAGS "-Wvla")

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND LIBD4_COVERAGE)
  list(APPEND LIBD4_CMAKE_FLAGS "-O0")
  list(APPEND LIBD4_CMAKE_FLAGS "-fcoverage-mapping")
  list(APPEND LIBD4_CMAKE_FLAGS "-fprofile-arcs")
  list(APPEND LIBD4_CMAKE_FLAGS "-fprofile-instr-generate")
  list(APPEND LIBD4_CMAKE_FLAGS "-ftest-coverage")
endif ()

list(JOIN LIBD4_CMAKE_FLAGS " " LIBD4_CMAKE_FLAGS)

if (MSVC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
else ()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -pedantic-errors ${LIBD4_CMAKE_FLAGS}")
endif ()
