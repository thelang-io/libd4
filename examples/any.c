/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <d4/any.h>
#include <d4/number.h>
#include <d4/string.h>

#define TYPE_u64 1

D4_ANY_DECLARE(u64, uint64_t)
D4_ANY_DEFINE(TYPE_u64, u64, uint64_t, val, lhs_val == rhs_val, (void) val, d4_u64_str(val))

int main (void) {
  d4_any_t a = d4_any_u64_alloc(10);
  d4_any_t b = d4_any_u64_alloc(20);
  d4_any_t c = d4_any_copy(b);

  d4_str_t a_str;
  d4_str_t b_str;

  a = d4_any_realloc(a, b);

  a_str = d4_any_str(a);
  b_str = d4_any_str(b);

  if (d4_any_eq(a, b)) {
    wprintf(L"a = %ls\n", a_str.data);
  }

  d4_str_free(b_str);
  d4_str_free(a_str);

  d4_any_free(c);
  d4_any_free(b);
  d4_any_free(a);

  return 0;
}
