/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_STRING_TYPE_H
#define THE_STRING_TYPE_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <stddef.h>
#include <wchar.h>

/** Structure representing string object. */
typedef struct {
  /** String object representation as wide character array. */
  wchar_t *data;

  /** Length of the string object. */
  size_t len;
} the_str_t;

#endif
