#!/usr/bin/env bash

#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

set -e

cat > .git/hooks/pre-commit << EOF
#!/usr/bin/env bash

cmake . -B ./build -D LIBD4_BUILD_EXAMPLES=ON -D LIBD4_BUILD_TESTS=ON
cmake --build build --config Debug
cmake --install build
ctest --output-on-failure --test-dir build
EOF

chmod +x .git/hooks/pre-commit
