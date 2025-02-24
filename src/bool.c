/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "bool.h"
#include "../include/d4/string.h"

d4_str_t d4_bool_str (bool self) {
  return d4_str_alloc(self ? L"true" : L"false");
}
