#!/usr/bin/env bash

#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

set -e

mkdir -p coverage
cmake . -B ./coverage -DLIBTHE_BUILD_TESTS=ON -DLIBTHE_COVERAGE=ON
cmake --build coverage --config Debug
ctest --output-on-failure --test-dir coverage
lcov --capture -d coverage -o coverage/test.info --exclude 'test/*'
genhtml -o coverage/html coverage/test.info
open coverage/html/index.html
