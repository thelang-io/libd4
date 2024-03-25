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
  the_opt_int_t a1 = NULL;
  the_opt_int_t a2 = the_opt_int_alloc(1);
  the_opt_int_t a3 = the_opt_int_copy(a1);

  the_str_t s1 = the_opt_int_str(a1);
  the_str_t s2 = the_opt_int_str(a2);
  the_str_t s3 = the_opt_int_str(a3);

  wprintf(L"a1: %ls\n", s1.data);
  wprintf(L"a2: %ls\n", s2.data);
  wprintf(L"a3: %ls\n", s3.data);

  wprintf(the_opt_int_eq(a1, a2) ? L"a1 == a2\n" : L"a1 != a2\n");
  wprintf(the_opt_int_eq(a1, a3) ? L"a1 == a3\n" : L"a1 != a3\n");

  a3 = the_opt_int_realloc(a3, a2);
  the_str_free(s3);
  s3 = the_opt_int_str(a3);

  wprintf(L"a3: %ls\n", s3.data);

  the_str_free(s1);
  the_str_free(s2);
  the_str_free(s3);

  the_opt_int_free(a1);
  the_opt_int_free(a2);
  the_opt_int_free(a3);

  return 0;
}
