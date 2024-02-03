#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

FROM ubuntu

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y build-essential cmake git valgrind && \
    apt-get autoclean && \
    apt-get autoremove && \
    apt-get clean && \
    rm -rf /tmp/* /var/lib/apt/lists/* /var/tmp/*

WORKDIR /app
COPY . .
RUN mkdir -p build
RUN cmake . -B ./build -D CMAKE_BUILD_TYPE=Debug -D LIBTHE_BUILD_EXAMPLES=ON -D LIBTHE_BUILD_TESTS=ON
RUN cmake --build build
RUN cmake --install build

ENTRYPOINT ["scripts/docker-entrypoint.sh"]
