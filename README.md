# libd4
A library specifically designed for The programming language.

## Building and installing
To build with [CMake](https://cmake.org):

```bash
cmake . -B ./build
cmake --build build --config Debug
```

To install with [CMake](https://cmake.org):

```bash
cmake --install build
```

To build and install with [Docker](https://www.docker.com):

```bash
docker build -t libd4 .
```

## Usage
You can import specific utility with:

```c
#include <d4/macro.h>
```

With GCC/Clang:

```bash
cc main.c -o program -ld4
```

With [CMake](https://cmake.org):

```cmake
cmake_minimum_required(VERSION 3.14)

find_path(LIBD4_INCLUDE_DIR d4/macro.h)
find_library(LIBD4_LIBRARY libd4)

# ...

target_include_directories(target PUBLIC "${LIBD4_INCLUDE_DIR}")
target_link_libraries(target PUBLIC "${LIBD4_LIBRARY}")
```

With [CMake's FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html):

```cmake
cmake_minimum_required(VERSION 3.14)
include(FetchContent)

FetchContent_Declare(libd4 GIT_REPOSITORY https://github.com/thelang-io/libd4.git GIT_TAG v1.0.0)
FetchContent_MakeAvailable(libd4)

# ...

target_include_directories(target PUBLIC "${libd4_SOURCE_DIR}/include")
target_link_libraries(target PUBLIC libd4)
```

## Testing
To test your build with [CMake](https://cmake.org):

### Without Checking Memory Leaks

```bash
cmake . -B ./build -D LIBD4_BUILD_EXAMPLES=ON -D LIBD4_BUILD_TESTS=ON
cmake --build build --config Debug
ctest --output-on-failure --test-dir build
```

### With Checking Memory Leaks

```bash
cmake . -B ./build -D LIBD4_BUILD_EXAMPLES=ON -D LIBD4_BUILD_TESTS=ON -D LIBD4_SANITIZER=ON
cmake --build build --config Debug
ctest --output-on-failure --test-dir build
```

### With Docker

```bash
docker build -t libd4 .
docker run libd4
```

## Contributing
See the [guidelines for contributing](CONTRIBUTING.md).

## Version
Starting from version 1.0.0 libd4 follows [Semantic Versioning](https://semver.org) rules.

## License
libd4 is distributed under the terms of MIT License, see [LICENSE file](LICENSE) for details.
