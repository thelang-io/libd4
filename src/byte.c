/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "byte.h"
#include "../include/d4/string.h"

d4_str_t d4_byte_str (unsigned char self) {
  return d4_str_alloc(L"%d", self);
}
