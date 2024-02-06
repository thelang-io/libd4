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
RUN cmake . -B ./build -DCMAKE_BUILD_TYPE=Debug -DLIBTHE_BUILD_EXAMPLES=ON -DLIBTHE_BUILD_TESTS=ON
RUN cmake --build build
RUN cmake --install build

ENTRYPOINT ["scripts/docker-entrypoint.sh"]
