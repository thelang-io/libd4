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

int main (void) {
  the_arr_int_t a1 = the_arr_int_alloc(0);
  the_arr_int_t a2 = the_arr_int_alloc(1, 100);
  the_arr_int_t a3 = the_arr_int_alloc(4, 1, 2, 3, 4);
  the_arr_int_t a4 = the_arr_int_concat(a3, a2);
  the_arr_int_t a5 = the_arr_int_copy(a2);
  the_arr_int_t a6 = the_arr_int_reverse(a3);
  the_arr_int_t a7 = the_arr_int_slice(a3, 1, 1, 1, -1);

  the_str_t s1 = the_arr_int_str(a1);
  the_str_t s2 = the_arr_int_str(a2);
  the_str_t s3 = the_arr_int_str(a3);
  the_str_t s4 = the_arr_int_str(a4);
  the_str_t s5 = the_arr_int_str(a5);
  the_str_t s6 = the_arr_int_str(a6);
  the_str_t s7 = the_arr_int_str(a7);
  the_str_t s8 = the_arr_int_join(a3, 0, the_str_alloc(L""));

  int32_t *v1 = the_arr_int_at(&the_err_state, __LINE__, 0, a2, 0);
  int32_t *v2 = the_arr_int_first(&the_err_state, __LINE__, 0, &a3);
  int32_t *v3 = the_arr_int_last(&the_err_state, __LINE__, 0, &a3);

  wprintf(L"%s %s %s %s %s %s %d %d %d\n", s1.data, s2.data, s3.data, s4.data, s5.data, s6.data, *v1, *v2, *v3);
  wprintf(L"a3 joined %s\n", s8.data);
  wprintf(the_arr_int_empty(a1) ? L"a1 is empty\n" : L"a1 is not empty\n");
  wprintf(the_arr_int_empty(a3) ? L"a3 is empty\n" : L"a3 is not empty\n");
  wprintf(the_arr_int_eq(a2, a4) ? L"a2 == a4\n" : L"a2 != a4\n");
  wprintf(the_arr_int_eq(a2, a5) ? L"a2 == a5\n" : L"a2 != a5\n");
  wprintf(the_arr_int_contains(a3, 0) ? L"a3 contains 0\n" : L"a3 doesn't contain 0\n");
  wprintf(the_arr_int_contains(a3, 2) ? L"a3 contains 2\n" : L"a3 doesn't contain 2\n");

  the_arr_int_clear(&a3);

  a5 = the_arr_int_realloc(a5, the_arr_int_copy(a3));

  wprintf(the_arr_int_empty(a3) ? L"a3 is empty\n" : L"a3 is not empty\n");
  wprintf(the_arr_int_eq(a2, a5) ? L"a2 == a5\n" : L"a2 != a5\n");

  wprintf(L"length of a6 before merge %d\n", a6.len);
  the_arr_int_merge(&a6, a2);
  wprintf(L"length of a6 after merge %d\n", a6.len);
  the_arr_int_push(&a6, 1, *the_arr_int_at(&the_err_state, 0, 0, a7, 0));
//  the_arr_int_push(&a6, 2, *the_arr_int_at(&the_err_state, 0, 0, a7, 1), *the_arr_int_at(&the_err_state, 0, 0, a7, 2));
  wprintf(L"length of a6 after push %d\n", a6.len);
  the_arr_int_pop(&a6);
  wprintf(L"length of a6 after pop %d\n", a6.len);
  the_arr_int_remove(&the_err_state, __LINE__, 0, &a6, 3);
  wprintf(L"length of a6 after remove %d\n", a6.len);

  the_str_free(s1);
  the_str_free(s2);
  the_str_free(s3);
  the_str_free(s4);
  the_str_free(s5);
  the_str_free(s6);
  the_str_free(s7);
  the_str_free(s8);

  the_arr_int_free(a1);
  the_arr_int_free(a2);
  the_arr_int_free(a3);
  the_arr_int_free(a4);
  the_arr_int_free(a5);
  the_arr_int_free(a6);
  the_arr_int_free(a7);

  return 0;
}
