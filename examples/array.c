/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/array.h>
#include <the/number.h>

THE_ARRAY_DECLARE(int, int32_t)
THE_ARRAY_DEFINE(int, int32_t, element, lhs_element == rhs_element, (void) element, the_i32_str(element))

THE_ARRAY_DECLARE(arr_str, the_arr_str_t)
THE_ARRAY_DEFINE(arr_str, the_arr_str_t, the_arr_str_copy(element), the_arr_str_eq(lhs_element, rhs_element), the_arr_str_free(element), the_arr_str_str(element))

// todo the decision I made is to go with structure similar to the one in union
//  for any, array, fn

// todo
int main (void) {
  the_arr_int_t a1 = the_arr_int_alloc(0);
  the_arr_int_t a2 = the_arr_int_alloc(1, 100);

  the_arr_int_free(a1);
  the_arr_int_free(a2);

  return 0;
}
