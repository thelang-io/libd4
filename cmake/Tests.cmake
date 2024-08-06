#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND LIBD4_BUILD_TESTS)
  list(APPEND LIBD4_MEMCHECK_FLAGS "--error-exitcode=255")
  list(APPEND LIBD4_MEMCHECK_FLAGS "--errors-for-leak-kinds=all")
  list(APPEND LIBD4_MEMCHECK_FLAGS "--leak-check=full")
  list(APPEND LIBD4_MEMCHECK_FLAGS "--show-leak-kinds=all")
  list(APPEND LIBD4_MEMCHECK_FLAGS "--tool=memcheck")
  list(APPEND LIBD4_MEMCHECK_FLAGS "--track-origins=yes")
  list(JOIN LIBD4_MEMCHECK_FLAGS " " LIBD4_MEMCHECK_FLAGS)

  set(CTEST_MEMORYCHECK_COMMAND valgrind)
  set(MEMORYCHECK_COMMAND_OPTIONS "${LIBD4_MEMCHECK_FLAGS}")

  include(CTest)

  set(
    tests
    any
    array
    bool
    byte
    char
    crypto
    enum
    error
    fn
    globals
    map
    number
    optional
    rand
    reference
    rune
    safe
    ssl
    string
    union
  )

  foreach (test ${tests})
    add_executable(${PROJECT_NAME}-test-${test} test/${test}-test.c test/utils.c)
    target_compile_options(${PROJECT_NAME}-test-${test} PRIVATE -g)
    target_link_libraries(${PROJECT_NAME}-test-${test} PUBLIC d4)
    add_test(${test} ${PROJECT_NAME}-test-${test})
  endforeach ()
endif ()
