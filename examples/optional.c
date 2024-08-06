/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <d4/number.h>
#include <d4/optional.h>

D4_OPTIONAL_DECLARE(int, int32_t)
D4_OPTIONAL_DEFINE(int, int32_t, val, lhs_val == rhs_val, (void) val, d4_i32_str(val))

D4_OPTIONAL_DECLARE(str, d4_str_t)
D4_OPTIONAL_DEFINE(str, d4_str_t, d4_str_copy(val), d4_str_eq(lhs_val, rhs_val), d4_str_free(val), d4_str_copy(val))

int main (void) {
  d4_opt_int_t a1 = NULL;
  d4_opt_int_t a2 = d4_opt_int_alloc(1);
  d4_opt_int_t a3 = d4_opt_int_copy(a1);

  d4_str_t s1 = d4_opt_int_str(a1);
  d4_str_t s2 = d4_opt_int_str(a2);
  d4_str_t s3 = d4_opt_int_str(a3);

  wprintf(L"a1: %ls\n", s1.data);
  wprintf(L"a2: %ls\n", s2.data);
  wprintf(L"a3: %ls\n", s3.data);

  wprintf(d4_opt_int_eq(a1, a2) ? L"a1 == a2\n" : L"a1 != a2\n");
  wprintf(d4_opt_int_eq(a1, a3) ? L"a1 == a3\n" : L"a1 != a3\n");

  a3 = d4_opt_int_realloc(a3, a2);
  d4_str_free(s3);
  s3 = d4_opt_int_str(a3);

  wprintf(L"a3: %ls\n", s3.data);

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);

  d4_opt_int_free(a1);
  d4_opt_int_free(a2);
  d4_opt_int_free(a3);

  return 0;
}
