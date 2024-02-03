/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "enum.h"
#include "string.h"

the_str_t the_enum_str (int self) {
  return the_str_alloc(L"%d", self);
}
