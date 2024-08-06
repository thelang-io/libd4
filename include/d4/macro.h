/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_MACRO_H
#define D4_MACRO_H

/* See https://github.com/thelang-io/libd4 for reference. */

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__WIN32__)
  /** Whether current operating system is Windows. */
  #define D4_OS_WINDOWS
#elif defined(__APPLE__)
  /** Whether current operating system is macOS. */
  #define D4_OS_MACOS
#elif defined(__linux__)
  /** Whether current operating system is Linux. */
  #define D4_OS_LINUX
#endif

/** Platform specific end of line. */
#if defined(D4_OS_WINDOWS)
  #define D4_EOL L"\r\n"
#else
  #define D4_EOL L"\n"
#endif

/** Platform specific path separator. */
#if defined(D4_OS_WINDOWS)
  #define D4_PATH_SEP L"\\"
#else
  #define D4_PATH_SEP L"/"
#endif

/** Platform specific noreturn attribute. */
#if defined(D4_OS_WINDOWS)
  #define D4_NORETURN __declspec(noreturn)
#else
  #define D4_NORETURN __attribute__((noreturn))
#endif

/** Platform specific unused attribute. */
#if defined(D4_OS_WINDOWS)
  #define D4_UNUSED
#else
  #define D4_UNUSED __attribute__((unused))
#endif

#endif
