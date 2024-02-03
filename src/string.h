/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef SRC_STRING_H
#define SRC_STRING_H

#include <the/string.h>

struct the_arr_str_s {
  the_str_t *d;
  size_t l;
};

struct the_str_s {
  wchar_t *d;
  size_t l;
};

#endif
