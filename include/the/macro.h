/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_MACRO_H
#define THE_MACRO_H

/* See https://github.com/thelang-io/helpers for reference. */

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__WIN32__)
  #define THE_OS_WINDOWS
#elif defined(__APPLE__)
  #define THE_OS_MACOS
#elif defined(__linux__)
  #define THE_OS_LINUX
#endif

#if defined(THE_OS_WINDOWS)
  #define THE_EOL L"\r\n"
#else
  #define THE_EOL L"\n"
#endif

#if defined(THE_OS_WINDOWS)
  #define THE_PATH_SEP L"\\"
#else
  #define THE_PATH_SEP L"/"
#endif

#if defined(THE_OS_WINDOWS)
  #define THE_NORETURN __declspec(noreturn)
#else
  #define THE_NORETURN __attribute__((noreturn))
#endif

#if defined(THE_OS_WINDOWS)
  #define THE_UNUSED
#else
  #define THE_UNUSED __attribute__((unused))
#endif

#endif
