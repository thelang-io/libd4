#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

list(APPEND LIBD4_LIBRARIES OpenSSL::SSL)
list(APPEND LIBD4_LIBRARIES OpenSSL::Crypto)

if (WIN32)
  list(APPEND LIBD4_LIBRARIES ws2_32)
  list(APPEND LIBD4_LIBRARIES gdi32)
  list(APPEND LIBD4_LIBRARIES advapi32)
  list(APPEND LIBD4_LIBRARIES crypt32)
  list(APPEND LIBD4_LIBRARIES user32)
else ()
  find_package(Threads REQUIRED)

  list(APPEND LIBD4_LIBRARIES Threads::Threads)
  list(APPEND LIBD4_LIBRARIES ${CMAKE_DL_LIBS})
endif ()
