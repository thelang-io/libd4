# libthe
Collection of utilities for core of The programming language.
TODO test all examples from this file, along with pkg-config.

## Building and installing
To build with [CMake](https://cmake.org):
```bash
$ mkdir -p build
$ cmake . -B ./build -DCMAKE_BUILD_TYPE=Debug
$ cmake --build build
```

To install with [CMake](https://cmake.org):
```bash
$ cmake --install build
```

To build and install with [Docker](https://www.docker.com):
```bash
$ docker build -t libthe .
```

## Usage
You can import specific utility with:
```c
#include <the/macro.h>
```

With [CMake](https://cmake.org):
```cmake
cmake_minimum_required(VERSION 3.5)

find_path(LIBTHE_INCLUDE_DIR the/macro.h)
find_library(LIBTHE_LIBRARY libthe)

# ...

target_include_directories(target PUBLIC "${LIBTHE_INCLUDE_DIR}")
target_link_libraries(target PUBLIC "${LIBTHE_LIBRARY}")
```

With [CMake's FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html):
```cmake
cmake_minimum_required(VERSION 3.14)
include(FetchContent)

FetchContent_Declare(libthe GIT_REPOSITORY https://github.com/thelang-io/helpers.git GIT_TAG v1.0.0)
FetchContent_MakeAvailable(libthe)

# ...

target_include_directories(target PUBLIC "${libthe_SOURCE_DIR}/include")
target_link_libraries(target PUBLIC libthe)
```

## Testing
To test your build with [CMake](https://cmake.org):
```bash
$ cmake . -B ./build -DCMAKE_BUILD_TYPE=Debug -DLIBTHE_BUILD_EXAMPLES=ON -DLIBTHE_BUILD_TESTS=ON
$ cmake --build build
$ ctest -T memcheck --output-on-failure --test-dir build
```

To test your build with [Docker](https://www.docker.com):
```bash
$ docker run libthe
```

## Contributing
See the [guidelines for contributing](CONTRIBUTING.md).

## Version
Starting from version 1.0.0 libthe follows [Semantic Versioning](https://semver.org) rules.

## License
libthe is distributed under the terms of MIT License, see [LICENSE file](LICENSE) for details.
