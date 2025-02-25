#!/usr/bin/env bash

#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

set -e

cmake . -B ./coverage -D LIBD4_BUILD_TESTS=ON -D LIBD4_COVERAGE=ON
cmake --build coverage --config Debug
ctest --output-on-failure --test-dir coverage
lcov --branch-coverage --capture -d coverage -o coverage/test.info --exclude 'test/*'
genhtml -o coverage/html coverage/test.info
open coverage/html/index.html
