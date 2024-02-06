#!/usr/bin/env bash

#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

set -e

cat > .git/hooks/pre-commit << EOF
#!/usr/bin/env bash

mkdir -p build
cmake . -B ./build -DCMAKE_BUILD_TYPE=Debug -DLIBTHE_BUILD_EXAMPLES=ON -DLIBTHE_BUILD_TESTS=ON
cmake --build build
cmake --install build
ctest --output-on-failure --test-dir build
EOF

chmod +x .git/hooks/pre-commit
