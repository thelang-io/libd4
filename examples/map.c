/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/map.h>
#include <the/number.h>

THE_ARRAY_DECLARE(int, int32_t)
THE_ARRAY_DEFINE(int, int32_t, int, element, lhs_element == rhs_element, (void) element, the_i32_str(element))

THE_MAP_DECLARE(int, int32_t, str, the_str_t)
THE_MAP_DEFINE(int, int32_t, int, key, lhs_key == rhs_key, (void) key, the_i32_str(key), str, the_str_t, the_str_t, the_str_copy(val), the_str_eq(lhs_val, rhs_val), the_str_free(val), the_str_quoted_escape(val))

int main (void) {
  the_str_t val = the_str_alloc(L"string");
  the_map_intMSstrME_t m1 = the_map_intMSstrME_alloc(0);
  the_map_intMSstrME_t m2 = the_map_intMSstrME_alloc(0);
  the_map_intMSstrME_t m3;
  the_map_intMSstrME_t m4;
  the_map_intMSstrME_t m5 = the_map_intMSstrME_alloc(1, 3, val);
  the_map_intMSstrME_t m6 = the_map_intMSstrME_alloc(2, 4, val, 5, val);
  the_map_intMSstrME_t m7 = the_map_intMSstrME_alloc(1, 2, val);
  the_str_t val2;
  the_arr_int_t keys;
  the_str_t keys_str;
  the_arr_str_t values;
  the_str_t values_str;
  the_str_t m1_str;
  the_str_t m1_str_rhs;
  the_str_t m2_str;
  the_str_t m5_str;
  the_str_t m6_str;
  the_str_t m7_str;

  the_map_intMSstrME_merge(&m7, m5);
  the_map_intMSstrME_merge(&m7, m6);

  for (size_t i = 0; i < 1000; i++) {
    the_map_intMSstrME_set(&m1, (int32_t) i, val);
  }

  m3 = the_map_intMSstrME_copy(m1);
  val2 = the_map_intMSstrME_get(&the_err_state, 0, 0, m1, 10);
  the_map_intMSstrME_remove(&the_err_state, 0, 0, &m1, 10);
  m4 = the_map_intMSstrME_copy(m1);

  keys = the_map_intMSstrME_keys(m1);
  keys_str = the_arr_int_str(keys);
  values = the_map_intMSstrME_values(m1);
  values_str = the_arr_str_str(values);
  m1_str = the_map_intMSstrME_str(m1);
  m2_str = the_map_intMSstrME_str(m2);
  m5_str = the_map_intMSstrME_str(m5);
  m6_str = the_map_intMSstrME_str(m6);
  m7_str = the_map_intMSstrME_str(m7);

  wprintf(L"m1: %ls\n", m1_str.data);
  wprintf(L"keys: %ls\n", keys_str.data);
  wprintf(L"values: %ls\n", values_str.data);
  wprintf(L"found value: %ls\n", val2.data);
  wprintf(L"has 10: %ls\n", the_map_intMSstrME_has(m1, 10) ? L"true" : L"false");
  wprintf(L"has 11: %ls\n", the_map_intMSstrME_has(m1, 11) ? L"true" : L"false");

  the_map_intMSstrME_clear(&m1);
  m1_str = the_str_realloc(m1_str, m1_str_rhs = the_map_intMSstrME_str(m1));
  the_str_free(m1_str_rhs);
  wprintf(L"m1: %ls\n", m1_str.data);

  the_map_intMSstrME_reserve(&m1, 10000);
  m1_str = the_str_realloc(m1_str, m1_str_rhs = the_map_intMSstrME_str(m1));
  the_str_free(m1_str_rhs);
  wprintf(L"m1: %ls\n", m1_str.data);

  the_map_intMSstrME_shrink(&m1);
  m1_str = the_str_realloc(m1_str, m1_str_rhs = the_map_intMSstrME_str(m1));
  the_str_free(m1_str_rhs);
  wprintf(L"m1: %ls\n", m1_str.data);

  wprintf(L"1 eq 2: %ls\n", the_map_intMSstrME_eq(m1, m2) ? L"true" : L"false");
  wprintf(L"3 eq 4: %ls\n", the_map_intMSstrME_eq(m3, m4) ? L"true" : L"false");
  the_map_intMSstrME_remove(&the_err_state, 0, 0, &m3, 10);
  the_map_intMSstrME_shrink(&m1);
  wprintf(L"again 3 eq 4: %ls\n", the_map_intMSstrME_eq(m3, m4) ? L"true" : L"false");
  m3 = the_map_intMSstrME_realloc(m3, m2);
  wprintf(L"and again 3 eq 2: %ls\n", the_map_intMSstrME_eq(m3, m2) ? L"true" : L"false");
  wprintf(L"m2: %ls\n", m2_str.data);
  wprintf(L"m5: %ls\n", m5_str.data);
  wprintf(L"m6: %ls\n", m6_str.data);
  wprintf(L"m7: %ls\n", m7_str.data);

  the_map_intMSstrME_free(m1);

  the_str_free(val);
  the_str_free(val2);

  return 0;
}
