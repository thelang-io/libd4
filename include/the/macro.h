/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_MACRO_H
#define THE_MACRO_H

/* See https://github.com/thelang-io/helpers for reference. */

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__WIN32__)
  /** Whether current operating system is Windows. */
  #define THE_OS_WINDOWS
#elif defined(__APPLE__)
  /** Whether current operating system is macOS. */
  #define THE_OS_MACOS
#elif defined(__linux__)
  /** Whether current operating system is Linux. */
  #define THE_OS_LINUX
#endif

/** Platform specific end of line. */
#if defined(THE_OS_WINDOWS)
  #define THE_EOL L"\r\n"
#else
  #define THE_EOL L"\n"
#endif

/** Platform specific path separator. */
#if defined(THE_OS_WINDOWS)
  #define THE_PATH_SEP L"\\"
#else
  #define THE_PATH_SEP L"/"
#endif

/** Platform specific noreturn attribute. */
#if defined(THE_OS_WINDOWS)
  #define THE_NORETURN __declspec(noreturn)
#else
  #define THE_NORETURN __attribute__((noreturn))
#endif

/** Platform specific unused attribute. */
#if defined(THE_OS_WINDOWS)
  #define THE_UNUSED
#else
  #define THE_UNUSED __attribute__((unused))
#endif

#endif
