/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "../include/d4/array.h"
#include "../include/d4/number.h"

D4_ARRAY_DECLARE(int, int32_t)
D4_ARRAY_DEFINE(int, int32_t, int, element, lhs_element == rhs_element, (void) element, d4_i32_str(element))

D4_ARRAY_DECLARE(arr_str, d4_arr_str_t)
D4_ARRAY_DEFINE(arr_str, d4_arr_str_t, d4_arr_str_t, d4_arr_str_copy(element), d4_arr_str_eq(lhs_element, rhs_element), d4_arr_str_free(element), d4_arr_str_str(element))

int main (void) {
  d4_arr_int_t a1 = d4_arr_int_alloc(0);
  d4_arr_int_t a2 = d4_arr_int_alloc(1, 100);
  d4_arr_int_t a3 = d4_arr_int_alloc(4, 1, 2, 3, 4);
  d4_arr_int_t a4 = d4_arr_int_concat(a3, a2);
  d4_arr_int_t a5 = d4_arr_int_copy(a2);
  d4_arr_int_t a6 = d4_arr_int_reverse(a3);
  d4_arr_int_t a7 = d4_arr_int_slice(a3, 1, 1, 1, -1);

  d4_str_t s1 = d4_arr_int_str(a1);
  d4_str_t s2 = d4_arr_int_str(a2);
  d4_str_t s3 = d4_arr_int_str(a3);
  d4_str_t s4 = d4_arr_int_str(a4);
  d4_str_t s5 = d4_arr_int_str(a5);
  d4_str_t s6 = d4_arr_int_str(a6);
  d4_str_t s7 = d4_arr_int_str(a7);
  d4_str_t s8 = d4_arr_int_join(a3, 0, d4_str_alloc(L""));

  int32_t *v1 = d4_arr_int_at(&d4_err_state, __LINE__, 0, a2, 0);
  int32_t *v2 = d4_arr_int_first(&d4_err_state, __LINE__, 0, &a3);
  int32_t *v3 = d4_arr_int_last(&d4_err_state, __LINE__, 0, &a3);

  wprintf(L"%ls %ls %ls %ls %ls %ls %d %d %d\n", s1.data, s2.data, s3.data, s4.data, s5.data, s6.data, *v1, *v2, *v3);
  wprintf(L"a3 joined %ls\n", s8.data);
  wprintf(L"%ls\n", d4_arr_int_empty(a1) ? L"a1 is empty" : L"a1 is not empty");
  wprintf(L"%ls\n", d4_arr_int_empty(a3) ? L"a3 is empty" : L"a3 is not empty");
  wprintf(L"%ls\n", d4_arr_int_eq(a2, a4) ? L"a2 == a4" : L"a2 != a4");
  wprintf(L"%ls\n", d4_arr_int_eq(a2, a5) ? L"a2 == a5" : L"a2 != a5");
  wprintf(L"%ls\n", d4_arr_int_contains(a3, 0) ? L"a3 contains 0" : L"a3 doesn't contain 0");
  wprintf(L"%ls\n", d4_arr_int_contains(a3, 2) ? L"a3 contains 2" : L"a3 doesn't contain 2");

  d4_arr_int_clear(&a3);

  a5 = d4_arr_int_realloc(a5, d4_arr_int_copy(a3));

  wprintf(L"%ls\n", d4_arr_int_empty(a3) ? L"a3 is empty" : L"a3 is not empty");
  wprintf(L"%ls\n", d4_arr_int_eq(a2, a5) ? L"a2 == a5" : L"a2 != a5");

  wprintf(L"length of a6 before merge %zu\n", a6.len);
  d4_arr_int_merge(&a6, a2);
  wprintf(L"length of a6 after merge %zu\n", a6.len);
  d4_arr_int_push(&a6, a2);
  d4_arr_int_push(&a6, a3);
  wprintf(L"length of a6 after push %zu\n", a6.len);
  d4_arr_int_pop(&a6);
  wprintf(L"length of a6 after pop %zu\n", a6.len);
  d4_arr_int_remove(&d4_err_state, __LINE__, 0, &a6, 3);
  wprintf(L"length of a6 after remove %zu\n", a6.len);

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s6);
  d4_str_free(s7);
  d4_str_free(s8);

  d4_arr_int_free(a1);
  d4_arr_int_free(a2);
  d4_arr_int_free(a3);
  d4_arr_int_free(a4);
  d4_arr_int_free(a5);
  d4_arr_int_free(a6);
  d4_arr_int_free(a7);

  return 0;
}
