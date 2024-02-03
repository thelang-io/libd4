/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "byte.h"
#include "string.h"

the_str_t the_byte_str (unsigned char self) {
  return the_str_alloc(L"%u", self);
}
