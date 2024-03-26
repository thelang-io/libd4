/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/any.h>
#include <the/number.h>
#include <the/string.h>

#define TYPE_u64 1

THE_ANY_DECLARE(u64, uint64_t)
THE_ANY_DEFINE(TYPE_u64, u64, uint64_t, val, lhs_val == rhs_val, (void) val, the_u64_str(val))

int main (void) {
  the_any_t a = the_any_u64(10);
  the_any_t b = the_any_u64(20);
  the_any_t c = the_any_copy(b);

  the_str_t a_str;
  the_str_t b_str;

  a = the_any_realloc(a, b);

  a_str = the_any_str(a);
  b_str = the_any_str(b);

  if (the_any_eq(a, b)) {
    wprintf(L"a = %ls\n", a_str.data);
  }

  the_str_free(b_str);
  the_str_free(a_str);

  the_any_free(c);
  the_any_free(b);
  the_any_free(a);

  return 0;
}
