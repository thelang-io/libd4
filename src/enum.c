/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "enum.h"
#include "../include/d4/string.h"

d4_str_t d4_enum_str (int self) {
  return d4_str_alloc(L"%d", self);
}
