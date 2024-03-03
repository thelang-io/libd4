#
# Copyright (c) Aaron Delasy
# Licensed under the MIT License
#

list(APPEND THE_LIBRARIES OpenSSL::SSL)
list(APPEND THE_LIBRARIES OpenSSL::Crypto)

if (WIN32)
  list(APPEND THE_LIBRARIES ws2_32)
  list(APPEND THE_LIBRARIES gdi32)
  list(APPEND THE_LIBRARIES advapi32)
  list(APPEND THE_LIBRARIES crypt32)
  list(APPEND THE_LIBRARIES user32)
else ()
  find_package(Threads)

  list(APPEND THE_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
  list(APPEND THE_LIBRARIES ${CMAKE_DL_LIBS})
endif ()
