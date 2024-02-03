#!/usr/bin/env bash

#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

set -e

cat > .git/hooks/pre-commit << EOF
#!/usr/bin/env bash

mkdir -p build
cmake . -B ./build -D CMAKE_BUILD_TYPE=Debug -D LIBTHE_BUILD_EXAMPLES=ON -D LIBTHE_BUILD_TESTS=ON
cmake --build build
cmake --install build
ctest --output-on-failure --test-dir build
EOF

chmod +x .git/hooks/pre-commit
