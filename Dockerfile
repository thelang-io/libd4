#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

FROM alpine

RUN apk add build-base --no-cache
RUN apk add cmake --no-cache
RUN apk add linux-headers --no-cache
RUN apk add perl --no-cache
RUN apk add ninja --no-cache
RUN apk add valgrind --no-cache

WORKDIR /app
COPY . .

RUN mkdir -p build
RUN cmake . -B ./build -G Ninja -D LIBD4_BUILD_EXAMPLES=ON -D LIBD4_BUILD_TESTS=ON
RUN cmake --build build --config Debug
RUN cmake --install build

ENTRYPOINT ["scripts/docker-entrypoint.sh"]
