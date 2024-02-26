#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND LIBTHE_BUILD_TESTS)
  set(CTEST_MEMORYCHECK_COMMAND valgrind)
  set(MEMORYCHECK_COMMAND_OPTIONS "--error-exitcode=255 --errors-for-leak-kinds=all --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes")

  include(CTest)
  set(tests any bool byte char crypto enum error rand ssl)

  foreach (test ${tests})
    add_executable(${PROJECT_NAME}-test-${test} test/${test}-test.c)
    target_link_libraries(${PROJECT_NAME}-test-${test} PUBLIC the)
    add_test(${test} ${PROJECT_NAME}-test-${test})
  endforeach ()
endif ()
