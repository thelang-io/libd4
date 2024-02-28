#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND LIBTHE_BUILD_TESTS)
  list(APPEND LIBTHE_MEMCHECK_FLAGS "--error-exitcode=255")
  list(APPEND LIBTHE_MEMCHECK_FLAGS "--errors-for-leak-kinds=all")
  list(APPEND LIBTHE_MEMCHECK_FLAGS "--leak-check=full")
  list(APPEND LIBTHE_MEMCHECK_FLAGS "--show-leak-kinds=all")
  list(APPEND LIBTHE_MEMCHECK_FLAGS "--suppressions=../valgrind.supp")
  list(APPEND LIBTHE_MEMCHECK_FLAGS "--tool=memcheck")
  list(APPEND LIBTHE_MEMCHECK_FLAGS "--track-origins=yes")
  list(JOIN LIBTHE_MEMCHECK_FLAGS " " LIBTHE_MEMCHECK_FLAGS)

  set(CTEST_MEMORYCHECK_COMMAND valgrind)
  set(MEMORYCHECK_COMMAND_OPTIONS "${LIBTHE_MEMCHECK_FLAGS}")

  include(CTest)
  set(tests any bool byte char crypto enum error number rand safe ssl)

  foreach (test ${tests})
    add_executable(${PROJECT_NAME}-test-${test} test/${test}-test.c)
    target_compile_options(${PROJECT_NAME}-test-${test} PRIVATE -g)
    target_link_libraries(${PROJECT_NAME}-test-${test} PUBLIC the)
    add_test(${test} ${PROJECT_NAME}-test-${test})
  endforeach ()
endif ()
