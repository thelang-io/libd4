#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

FROM ubuntu:24.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update
RUN apt-get install -y build-essential
RUN apt-get install -y cmake
RUN apt-get install -y ninja-build
RUN rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN cmake . -B ./build -G Ninja \
  -D LIBD4_BUILD_EXAMPLES=ON \
  -D LIBD4_BUILD_TESTS=ON \
  -D LIBD4_SANITIZER=ON

RUN cmake --build build --config Debug
RUN cmake --install build

ENTRYPOINT ["ctest", "--output-on-failure", "--test-dir", "build"]
