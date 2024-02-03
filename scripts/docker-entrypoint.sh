#!/usr/bin/env bash

#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

set -e
cd build

if ! ctest -T memcheck --output-on-failure; then
  find Testing/Temporary -name "MemoryChecker.*.log" -exec cat {} +
  exit 1
fi
