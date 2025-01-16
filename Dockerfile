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

WORKDIR /app
COPY . .

RUN mkdir -p build

RUN cmake . -B ./build -G Ninja \
  -D LIBD4_BUILD_EXAMPLES=ON \
  -D LIBD4_BUILD_TESTS=ON \
  -D LIBD4_SANITIZER=ON

RUN cmake --build build --config Debug
RUN cmake --install build

ENTRYPOINT ["ctest", "--output-on-failure", "--test-dir", "build"]
