/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "bool.h"
#include "string.h"

the_str_t the_bool_str (bool self) {
  return the_str_alloc(self ? L"true" : L"false");
}
