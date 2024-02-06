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

if (WIN32)
  set(openssl_MAKE_PROGRAM nmake)
else ()
  set(openssl_MAKE_PROGRAM make -j${N})
endif ()

ExternalProject_Add(
  openssl
  SOURCE_DIR "${openssl_SOURCE_DIR}"
  INSTALL_DIR "${openssl_INSTALL_DIR}"
  GIT_REPOSITORY https://github.com/openssl/openssl.git
  GIT_TAG openssl-3.2.1
  BUILD_BYPRODUCTS
    "${openssl_INSTALL_DIR}/lib/libcrypto${CMAKE_SHARED_LIBRARY_SUFFIX}"
    "${openssl_INSTALL_DIR}/lib/libcrypto${CMAKE_STATIC_LIBRARY_SUFFIX}"
    "${openssl_INSTALL_DIR}/lib/libssl${CMAKE_SHARED_LIBRARY_SUFFIX}"
    "${openssl_INSTALL_DIR}/lib/libssl${CMAKE_STATIC_LIBRARY_SUFFIX}"
  CONFIGURE_COMMAND perl "${openssl_SOURCE_DIR}/Configure" no-docs no-tests --libdir=lib "--prefix=${openssl_INSTALL_DIR}" "--openssldir=${openssl_INSTALL_DIR}"
  BUILD_COMMAND ${openssl_MAKE_PROGRAM}
  INSTALL_COMMAND ${openssl_MAKE_PROGRAM} install_sw
  TEST_COMMAND ls "${openssl_INSTALL_DIR}/lib" "${openssl_INSTALL_DIR}/bin"
  UPDATE_COMMAND ""
)

file(MAKE_DIRECTORY "${openssl_INCLUDE_DIR}")

message("${openssl_INSTALL_DIR}/lib/libcrypto${CMAKE_SHARED_LIBRARY_SUFFIX}")
message("${openssl_INSTALL_DIR}/lib/libcrypto${CMAKE_STATIC_LIBRARY_SUFFIX}")
message("${openssl_INSTALL_DIR}/lib/libssl${CMAKE_SHARED_LIBRARY_SUFFIX}")
message("${openssl_INSTALL_DIR}/lib/libssl${CMAKE_STATIC_LIBRARY_SUFFIX}")

add_library(OpenSSL::Crypto SHARED IMPORTED GLOBAL)
set_property(TARGET OpenSSL::Crypto PROPERTY IMPORTED_IMPLIB "${openssl_INSTALL_DIR}/bin/libcrypto${CMAKE_SHARED_LIBRARY_SUFFIX}")
set_property(TARGET OpenSSL::Crypto PROPERTY IMPORTED_LOCATION "${openssl_INSTALL_DIR}/lib/libcrypto${CMAKE_SHARED_LIBRARY_SUFFIX}")
set_property(TARGET OpenSSL::Crypto PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${openssl_INCLUDE_DIR}")
add_dependencies(OpenSSL::Crypto openssl)

add_library(OpenSSL::Crypto_a STATIC IMPORTED GLOBAL)
set_property(TARGET OpenSSL::Crypto_a PROPERTY IMPORTED_LOCATION "${openssl_INSTALL_DIR}/lib/libcrypto${CMAKE_STATIC_LIBRARY_SUFFIX}")
set_property(TARGET OpenSSL::Crypto_a PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${openssl_INCLUDE_DIR}")
add_dependencies(OpenSSL::Crypto_a openssl)

add_library(OpenSSL::SSL SHARED IMPORTED GLOBAL)
set_property(TARGET OpenSSL::SSL PROPERTY IMPORTED_IMPLIB "${openssl_INSTALL_DIR}/bin/libssl${CMAKE_SHARED_LIBRARY_SUFFIX}")
set_property(TARGET OpenSSL::SSL PROPERTY IMPORTED_LOCATION "${openssl_INSTALL_DIR}/lib/libssl${CMAKE_SHARED_LIBRARY_SUFFIX}")
set_property(TARGET OpenSSL::SSL PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${openssl_INCLUDE_DIR}")
add_dependencies(OpenSSL::SSL openssl)

add_library(OpenSSL::SSL_a STATIC IMPORTED GLOBAL)
set_property(TARGET OpenSSL::SSL_a PROPERTY IMPORTED_LOCATION "${openssl_INSTALL_DIR}/lib/libssl${CMAKE_STATIC_LIBRARY_SUFFIX}")
set_property(TARGET OpenSSL::SSL_a PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${openssl_INCLUDE_DIR}")
add_dependencies(OpenSSL::SSL_a openssl)
