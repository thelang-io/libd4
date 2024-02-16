#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

macro (set_policies)
  if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
  endif ()
endmacro ()
