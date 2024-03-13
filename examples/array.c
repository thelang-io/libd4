/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/array.h>

THE_ARRAY_DECLARE(arr_u64, uint64_t)
THE_ARRAY_DEFINE(arr_u64, uint64_t)

// todo
int main (void) {
  the_arr_u64_t a1 = the_arr_u64_alloc(0);
  the_arr_u64_t a2 = the_arr_u64_alloc(1, 10ull);

  the_arr_u64_free(a1);
  the_arr_u64_free(a2);

  return 0;
}
