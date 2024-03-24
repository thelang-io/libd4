/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/number.h>
#include <the/optional.h>

THE_OPTIONAL_DECLARE(int, int32_t)
THE_OPTIONAL_DEFINE(int, int32_t, val, lhs_val == rhs_val, (void) val, the_i32_str(val))

THE_OPTIONAL_DECLARE(str, the_str_t)
THE_OPTIONAL_DEFINE(str, the_str_t, the_str_copy(val), the_str_eq(lhs_val, rhs_val), the_str_free(val), the_str_copy(val))

int main (void) {
  return 0;
}
