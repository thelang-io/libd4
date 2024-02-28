#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

FROM ubuntu

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install --no-install-recommends -y build-essential cmake ninja-build valgrind && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN mkdir -p build
RUN cmake . -B ./build -G Ninja -DLIBTHE_BUILD_EXAMPLES=ON -DLIBTHE_BUILD_TESTS=ON
RUN cmake --build build --config Debug
RUN cmake --install build

ENTRYPOINT ["scripts/docker-entrypoint.sh"]
