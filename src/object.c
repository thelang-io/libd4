/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "object.h"

d4_str_t d4_obj_str_append (d4_str_t result, d4_str_t name, d4_str_t value) {
  d4_str_t colon_space = d4_str_alloc(L": ");
  d4_str_t comma_space = d4_str_alloc(L", ");
  d4_str_t tmp;

  if (result.len != 0) {
    result = d4_str_realloc(result, tmp = d4_str_concat(result, comma_space));
    d4_str_free(tmp);
  }

  result = d4_str_realloc(result, tmp = d4_str_concat(result, name));
  d4_str_free(tmp);
  result = d4_str_realloc(result, tmp = d4_str_concat(result, colon_space));
  d4_str_free(tmp);
  result = d4_str_realloc(result, tmp = d4_str_concat(result, value));
  d4_str_free(tmp);

  d4_str_free(colon_space);
  d4_str_free(comma_space);
  d4_str_free(name);
  d4_str_free(value);

  return result;
}
