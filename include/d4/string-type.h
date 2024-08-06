/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_STRING_TYPE_H
#define D4_STRING_TYPE_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include <stdbool.h>
#include <stddef.h>
#include <wchar.h>

/** Structure representing string object. */
typedef struct {
  /** String object representation as wide character array. */
  wchar_t *data;

  /** Length of the string object. */
  size_t len;

  /** Whether or not string is static. */
  bool is_static;
} d4_str_t;

#endif
