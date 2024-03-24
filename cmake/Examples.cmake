#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND LIBTHE_BUILD_EXAMPLES)
  set(examples any array bool byte char crypto enum error fn macro number optional rand safe ssl string union)

  foreach (example ${examples})
    add_executable(${PROJECT_NAME}-example-${example} examples/${example}.c)
    target_link_libraries(${PROJECT_NAME}-example-${example} PUBLIC the)
  endforeach ()
endif ()
