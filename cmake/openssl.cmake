#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

include(ExternalProject)
include(ProcessorCount)

ProcessorCount(N)

set(openssl_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/openssl-src")
set(openssl_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/openssl")
set(openssl_INCLUDE_DIR "${openssl_INSTALL_DIR}/include")
set(openssl_CRYPTO_LIBRARY_PATH "${openssl_INSTALL_DIR}/lib/libcrypto${CMAKE_STATIC_LIBRARY_SUFFIX}")
set(openssl_SSL_LIBRARY_PATH "${openssl_INSTALL_DIR}/lib/libssl${CMAKE_STATIC_LIBRARY_SUFFIX}")

if (WIN32)
  set(openssl_MAKE_PROGRAM nmake)
else ()
  set(openssl_MAKE_PROGRAM make -j${N})
endif ()

ExternalProject_Add(
  openssl
  URL https://github.com/openssl/openssl/releases/download/openssl-3.2.1/openssl-3.2.1.tar.gz
  URL_HASH SHA256=83c7329fe52c850677d75e5d0b0ca245309b97e8ecbcfdc1dfdc4ab9fac35b39
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  SOURCE_DIR "${openssl_SOURCE_DIR}"
  INSTALL_DIR "${openssl_INSTALL_DIR}"
  BUILD_BYPRODUCTS "${openssl_CRYPTO_LIBRARY_PATH}" "${openssl_SSL_LIBRARY_PATH}"
  CONFIGURE_COMMAND perl "${openssl_SOURCE_DIR}/Configure" no-shared no-tests --libdir=lib "--prefix=${openssl_INSTALL_DIR}" "--openssldir=${openssl_INSTALL_DIR}"
  BUILD_COMMAND ${openssl_MAKE_PROGRAM}
  INSTALL_COMMAND ${openssl_MAKE_PROGRAM} install_sw
  TEST_COMMAND ""
  UPDATE_COMMAND ""
)

file(MAKE_DIRECTORY "${openssl_INCLUDE_DIR}")

add_library(OpenSSL::Crypto STATIC IMPORTED GLOBAL)
set_property(TARGET OpenSSL::Crypto PROPERTY IMPORTED_LOCATION "${openssl_CRYPTO_LIBRARY_PATH}")
set_property(TARGET OpenSSL::Crypto PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${openssl_INCLUDE_DIR}")
add_dependencies(OpenSSL::Crypto openssl)

add_library(OpenSSL::SSL STATIC IMPORTED GLOBAL)
set_property(TARGET OpenSSL::SSL PROPERTY IMPORTED_LOCATION "${openssl_SSL_LIBRARY_PATH}")
set_property(TARGET OpenSSL::SSL PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${openssl_INCLUDE_DIR}")
add_dependencies(OpenSSL::SSL openssl)
