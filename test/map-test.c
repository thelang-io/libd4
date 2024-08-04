/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/error.h>
#include <the/number.h>
#include <assert.h>
#include "../src/map.h"
#include "utils.h"

THE_ARRAY_DECLARE(int, int32_t)
THE_ARRAY_DEFINE(int, int32_t, int, element, lhs_element == rhs_element, (void) element, the_i32_str(element))

THE_MAP_DECLARE(int, int32_t, str, the_str_t)
THE_MAP_DEFINE(int, int32_t, int, key, lhs_key == rhs_key, (void) key, the_i32_str(key), str, the_str_t, the_str_t, the_str_copy(val), the_str_eq(lhs_val, rhs_val), the_str_free(val), the_str_quoted_escape(val))

static void test_map_alloc (void) {
  the_str_t val1 = the_str_alloc(L"val1");
  the_str_t val2 = the_str_alloc(L"val2");
  the_str_t val3 = the_str_alloc(L"val3");

  the_map_intMSstrME_t m1 = the_map_intMSstrME_alloc(0);
  the_map_intMSstrME_t m2 = the_map_intMSstrME_alloc(1, 1, val1);
  the_map_intMSstrME_t m3 = the_map_intMSstrME_alloc(2, 2, val2, 3, val3);

  assert(((void) "Creates map with zero pairs", m1.len == 0));
  assert(((void) "Creates map with one pair", m2.len == 1));
  assert(((void) "Creates map with two pairs", m3.len == 2));

  the_map_intMSstrME_free(m1);
  the_map_intMSstrME_free(m2);
  the_map_intMSstrME_free(m3);

  the_str_free(val1);
  the_str_free(val2);
  the_str_free(val3);
}

static void test_map_clear (void) {
  the_str_t val = the_str_alloc(L"val");

  the_map_intMSstrME_t m1 = the_map_intMSstrME_alloc(0);
  the_map_intMSstrME_t m2 = the_map_intMSstrME_alloc(1, 1, val);
  the_map_intMSstrME_t m3 = the_map_intMSstrME_alloc(2, 2, val, 3, val);

  the_map_intMSstrME_clear(&m1);
  the_map_intMSstrME_clear(&m2);
  the_map_intMSstrME_clear(&m3);

  assert(((void) "Clears map with zero pairs", m1.len == 0));
  assert(((void) "Clears map with one pair", m2.len == 0));
  assert(((void) "Clears map with two pairs", m3.len == 0));

  the_map_intMSstrME_free(m1);
  the_map_intMSstrME_free(m2);
  the_map_intMSstrME_free(m3);

  the_str_free(val);
}

static void test_map_copy (void) {
  the_str_t val = the_str_alloc(L"val");

  the_map_intMSstrME_t m1 = the_map_intMSstrME_alloc(0);
  the_map_intMSstrME_t m2 = the_map_intMSstrME_alloc(1, 1, val);
  the_map_intMSstrME_t m3 = the_map_intMSstrME_alloc(2, 2, val, 3, val);

  the_map_intMSstrME_t m4 = the_map_intMSstrME_copy(m1);
  the_map_intMSstrME_t m5 = the_map_intMSstrME_copy(m2);
  the_map_intMSstrME_t m6 = the_map_intMSstrME_copy(m3);

  assert(((void) "Copies map with zero pairs", the_map_intMSstrME_eq(m1, m4)));
  assert(((void) "Copies map with one pair", the_map_intMSstrME_eq(m2, m5)));
  assert(((void) "Copies map with two pairs", the_map_intMSstrME_eq(m3, m6)));

  the_map_intMSstrME_free(m1);
  the_map_intMSstrME_free(m2);
  the_map_intMSstrME_free(m3);

  the_map_intMSstrME_free(m4);
  the_map_intMSstrME_free(m5);
  the_map_intMSstrME_free(m6);

  the_str_free(val);
}

static void test_map_empty (void) {
  the_str_t val = the_str_alloc(L"val");

  the_map_intMSstrME_t m1 = the_map_intMSstrME_alloc(0);
  the_map_intMSstrME_t m2 = the_map_intMSstrME_alloc(1, 1, val);
  the_map_intMSstrME_t m3 = the_map_intMSstrME_alloc(2, 2, val, 3, val);

  assert(((void) "Map with zero pairs is empty", the_map_intMSstrME_empty(m1)));
  assert(((void) "Map with one pair is not empty", !the_map_intMSstrME_empty(m2)));
  assert(((void) "Map with two pairs is not empty", !the_map_intMSstrME_empty(m3)));

  the_map_intMSstrME_free(m1);
  the_map_intMSstrME_free(m2);
  the_map_intMSstrME_free(m3);

  the_str_free(val);
}

static void test_map_eq (void) {
  the_str_t val = the_str_alloc(L"val");

  the_map_intMSstrME_t m1 = the_map_intMSstrME_alloc(0);
  the_map_intMSstrME_t m2 = the_map_intMSstrME_alloc(1, 1, val);
  the_map_intMSstrME_t m3 = the_map_intMSstrME_alloc(2, 2, val, 3, val);

  the_map_intMSstrME_t m4 = the_map_intMSstrME_alloc(0);
  the_map_intMSstrME_t m5 = the_map_intMSstrME_alloc(1, 1, val);
  the_map_intMSstrME_t m6 = the_map_intMSstrME_alloc(2, 2, val, 3, val);

  assert(((void) "Maps with zero pairs are equal", the_map_intMSstrME_eq(m1, m4)));
  assert(((void) "Maps with one pair are equal", the_map_intMSstrME_eq(m2, m5)));
  assert(((void) "Maps with two pairs are equal", the_map_intMSstrME_eq(m3, m6)));
  assert(((void) "Maps with and without pairs are not equal", !the_map_intMSstrME_eq(m1, m2)));
  assert(((void) "Maps with different amount of pairs are not equal", !the_map_intMSstrME_eq(m2, m3)));

  the_map_intMSstrME_free(m1);
  the_map_intMSstrME_free(m2);
  the_map_intMSstrME_free(m3);

  the_map_intMSstrME_free(m4);
  the_map_intMSstrME_free(m5);
  the_map_intMSstrME_free(m6);

  the_str_free(val);
}

static void test_map_free (void) {
  the_str_t val = the_str_alloc(L"val");

  the_map_intMSstrME_t m1 = the_map_intMSstrME_alloc(0);
  the_map_intMSstrME_t m2 = the_map_intMSstrME_alloc(1, 1, val);
  the_map_intMSstrME_t m3 = the_map_intMSstrME_alloc(2, 2, val, 3, val);

  the_map_intMSstrME_free(m1);
  the_map_intMSstrME_free(m2);
  the_map_intMSstrME_free(m3);

  the_str_free(val);
}

static void test_map_get (void) {
  the_str_t val1 = the_str_alloc(L"val1");
  the_str_t val2 = the_str_alloc(L"val2");
  the_str_t val3 = the_str_alloc(L"val3");

  the_map_intMSstrME_t m1 = the_map_intMSstrME_alloc(1, 1, val1);
  the_map_intMSstrME_t m2 = the_map_intMSstrME_alloc(2, 2, val2, 3, val3);

  ASSERT_NO_THROW(GET1, {
    the_str_t v1 = the_map_intMSstrME_get(&the_err_state, 0, 0, m1, 1);
    the_str_t v2 = the_map_intMSstrME_get(&the_err_state, 0, 0, m2, 2);
    the_str_t v3 = the_map_intMSstrME_get(&the_err_state, 0, 0, m2, 3);

    assert(((void) "Gets an element from map with one pair", the_str_eq(v1, val1)));
    assert(((void) "Gets first element from map with two pairs", the_str_eq(v2, val2)));
    assert(((void) "Gets second element from map with two pairs", the_str_eq(v3, val3)));

    the_str_free(v1);
    the_str_free(v2);
    the_str_free(v3);
  });

  the_map_intMSstrME_free(m1);
  the_map_intMSstrME_free(m2);

  the_str_free(val1);
  the_str_free(val2);
  the_str_free(val3);
}

static void test_map_get_throws (void) {
  the_str_t val = the_str_alloc(L"val");

  the_map_intMSstrME_t m1 = the_map_intMSstrME_alloc(0);
  the_map_intMSstrME_t m2 = the_map_intMSstrME_alloc(1, 1, val);
  the_map_intMSstrME_t m3 = the_map_intMSstrME_alloc(2, 2, val, 3, val);

  ASSERT_THROW_WITH_MESSAGE(GET1, {
    the_map_intMSstrME_get(&the_err_state, 0, 0, m1, -1);
  }, L"failed to find key '-1'");

  ASSERT_THROW_WITH_MESSAGE(GET2, {
    the_map_intMSstrME_get(&the_err_state, 0, 0, m2, 0);
  }, L"failed to find key '0'");

  ASSERT_THROW_WITH_MESSAGE(GET3, {
    the_map_intMSstrME_get(&the_err_state, 0, 0, m3, 1);
  }, L"failed to find key '1'");

  the_map_intMSstrME_free(m1);
  the_map_intMSstrME_free(m2);
  the_map_intMSstrME_free(m3);

  the_str_free(val);
}

static void test_map_has (void) {
  the_str_t val = the_str_alloc(L"val");

  the_map_intMSstrME_t m1 = the_map_intMSstrME_alloc(0);
  the_map_intMSstrME_t m2 = the_map_intMSstrME_alloc(1, 1, val);
  the_map_intMSstrME_t m3 = the_map_intMSstrME_alloc(2, 2, val, 3, val);

  assert(((void) "Has no element in map with zero pairs", !the_map_intMSstrME_has(m1, 0)));
  assert(((void) "Has no element in map with one pair", !the_map_intMSstrME_has(m2, 0)));
  assert(((void) "Has an element in map with one pair", the_map_intMSstrME_has(m2, 1)));
  assert(((void) "Has no element in map with two pairs", !the_map_intMSstrME_has(m3, 1)));
  assert(((void) "Has first element in map with two pairs", the_map_intMSstrME_has(m3, 2)));
  assert(((void) "Has second element in map with two pairs", the_map_intMSstrME_has(m3, 3)));

  the_map_intMSstrME_free(m1);
  the_map_intMSstrME_free(m2);
  the_map_intMSstrME_free(m3);

  the_str_free(val);
}

static void test_map_keys (void) {
  the_str_t val = the_str_alloc(L"val");

  the_map_intMSstrME_t m1 = the_map_intMSstrME_alloc(0);
  the_map_intMSstrME_t m2 = the_map_intMSstrME_alloc(1, 1, val);
  the_map_intMSstrME_t m3 = the_map_intMSstrME_alloc(2, 2, val, 3, val);

  the_arr_int_t keys1 = the_map_intMSstrME_keys(m1);
  the_arr_int_t keys2 = the_map_intMSstrME_keys(m2);
  the_arr_int_t keys3 = the_map_intMSstrME_keys(m3);

  assert(((void) "Map with zero keys returns zero keys", keys1.len == 0));
  assert(((void) "Map with one key returns one key", keys2.len == 1));
  assert(((void) "Map with one key returns correct first key", keys2.data[0] == 1));
  assert(((void) "Map with two keys returns two keys", keys3.len == 2));
  assert(((void) "Map with two keys returns correct first key", keys3.data[0] == 3));
  assert(((void) "Map with two keys returns correct second key", keys3.data[1] == 2));

  the_arr_int_free(keys1);
  the_arr_int_free(keys2);
  the_arr_int_free(keys3);

  the_map_intMSstrME_free(m1);
  the_map_intMSstrME_free(m2);
  the_map_intMSstrME_free(m3);

  the_str_free(val);
}

static void test_map_merge (void) {
  // todo
}

static void test_map_place (void) {
  // todo
}

static void test_map_realloc (void) {
  // todo
}

static void test_map_remove (void) {
  // todo
}

static void test_map_reserve (void) {
  // todo
}

static void test_map_set (void) {
  // todo
}

static void test_map_shrink (void) {
  // todo
}

static void test_map_str (void) {
  // todo
}

static void test_map_values (void) {
  // todo
}

// todo test hash
// todo test should change cap
// todo test change cap

int main (void) {
  test_map_alloc();
  test_map_clear();
  test_map_copy();
  test_map_empty();
  test_map_eq();
  test_map_free();
  test_map_get();
  test_map_get_throws();
  test_map_has();
  test_map_keys();
  test_map_merge();
  test_map_place();
  test_map_realloc();
  test_map_remove();
  test_map_reserve();
  test_map_set();
  test_map_shrink();
  test_map_str();
  test_map_values();
}
