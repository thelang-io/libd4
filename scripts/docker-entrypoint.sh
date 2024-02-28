#!/usr/bin/env bash

#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

set -e

if ! ctest -T memcheck --output-on-failure --test-dir build; then
  find build/Testing/Temporary -name "MemoryChecker.*.log" -exec cat {} +
  exit 1
fi
