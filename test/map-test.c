/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <d4/error.h>
#include <d4/number.h>
#include <assert.h>
#include "../src/map.h"
#include "utils.h"

D4_ARRAY_DECLARE(int, int32_t)
D4_ARRAY_DEFINE(int, int32_t, int, element, lhs_element == rhs_element, (void) element, d4_i32_str(element))

D4_MAP_DECLARE(int, int32_t, str, d4_str_t)
D4_MAP_DEFINE(int, int32_t, int, key, lhs_key == rhs_key, (void) key, d4_i32_str(key), str, d4_str_t, d4_str_t, d4_str_copy(val), d4_str_eq(lhs_val, rhs_val), d4_str_free(val), d4_str_quoted_escape(val))

static void test_map_alloc (void) {
  d4_str_t val1 = d4_str_alloc(L"val1");
  d4_str_t val2 = d4_str_alloc(L"val2");
  d4_str_t val3 = d4_str_alloc(L"val3");

  d4_map_intMSstrME_t m1 = d4_map_intMSstrME_alloc(0);
  d4_map_intMSstrME_t m2 = d4_map_intMSstrME_alloc(1, 1, val1);
  d4_map_intMSstrME_t m3 = d4_map_intMSstrME_alloc(2, 2, val2, 3, val3);

  assert(((void) "Creates map with zero pairs", m1.len == 0));
  assert(((void) "Creates map with one pair", m2.len == 1));
  assert(((void) "Creates map with two pairs", m3.len == 2));

  d4_map_intMSstrME_free(m1);
  d4_map_intMSstrME_free(m2);
  d4_map_intMSstrME_free(m3);

  d4_str_free(val1);
  d4_str_free(val2);
  d4_str_free(val3);
}

static void test_map_clear (void) {
  d4_str_t val = d4_str_alloc(L"val");

  d4_map_intMSstrME_t m1 = d4_map_intMSstrME_alloc(0);
  d4_map_intMSstrME_t m2 = d4_map_intMSstrME_alloc(1, 1, val);
  d4_map_intMSstrME_t m3 = d4_map_intMSstrME_alloc(2, 2, val, 3, val);

  d4_map_intMSstrME_clear(&m1);
  d4_map_intMSstrME_clear(&m2);
  d4_map_intMSstrME_clear(&m3);

  assert(((void) "Clears map with zero pairs", m1.len == 0));
  assert(((void) "Clears map with one pair", m2.len == 0));
  assert(((void) "Clears map with two pairs", m3.len == 0));

  d4_map_intMSstrME_free(m1);
  d4_map_intMSstrME_free(m2);
  d4_map_intMSstrME_free(m3);

  d4_str_free(val);
}

static void test_map_copy (void) {
  d4_str_t val = d4_str_alloc(L"val");

  d4_map_intMSstrME_t m1 = d4_map_intMSstrME_alloc(0);
  d4_map_intMSstrME_t m2 = d4_map_intMSstrME_alloc(1, 1, val);
  d4_map_intMSstrME_t m3 = d4_map_intMSstrME_alloc(2, 2, val, 3, val);

  d4_map_intMSstrME_t m4 = d4_map_intMSstrME_copy(m1);
  d4_map_intMSstrME_t m5 = d4_map_intMSstrME_copy(m2);
  d4_map_intMSstrME_t m6 = d4_map_intMSstrME_copy(m3);

  assert(((void) "Copies map with zero pairs", d4_map_intMSstrME_eq(m1, m4)));
  assert(((void) "Copies map with one pair", d4_map_intMSstrME_eq(m2, m5)));
  assert(((void) "Copies map with two pairs", d4_map_intMSstrME_eq(m3, m6)));

  d4_map_intMSstrME_free(m1);
  d4_map_intMSstrME_free(m2);
  d4_map_intMSstrME_free(m3);

  d4_map_intMSstrME_free(m4);
  d4_map_intMSstrME_free(m5);
  d4_map_intMSstrME_free(m6);

  d4_str_free(val);
}

static void test_map_empty (void) {
  d4_str_t val = d4_str_alloc(L"val");

  d4_map_intMSstrME_t m1 = d4_map_intMSstrME_alloc(0);
  d4_map_intMSstrME_t m2 = d4_map_intMSstrME_alloc(1, 1, val);
  d4_map_intMSstrME_t m3 = d4_map_intMSstrME_alloc(2, 2, val, 3, val);

  assert(((void) "Map with zero pairs is empty", d4_map_intMSstrME_empty(m1)));
  assert(((void) "Map with one pair is not empty", !d4_map_intMSstrME_empty(m2)));
  assert(((void) "Map with two pairs is not empty", !d4_map_intMSstrME_empty(m3)));

  d4_map_intMSstrME_free(m1);
  d4_map_intMSstrME_free(m2);
  d4_map_intMSstrME_free(m3);

  d4_str_free(val);
}

static void test_map_eq (void) {
  d4_str_t val = d4_str_alloc(L"val");

  d4_map_intMSstrME_t m1 = d4_map_intMSstrME_alloc(0);
  d4_map_intMSstrME_t m2 = d4_map_intMSstrME_alloc(1, 1, val);
  d4_map_intMSstrME_t m3 = d4_map_intMSstrME_alloc(2, 2, val, 3, val);

  d4_map_intMSstrME_t m4 = d4_map_intMSstrME_alloc(0);
  d4_map_intMSstrME_t m5 = d4_map_intMSstrME_alloc(1, 1, val);
  d4_map_intMSstrME_t m6 = d4_map_intMSstrME_alloc(2, 2, val, 3, val);

  assert(((void) "Maps with zero pairs are equal", d4_map_intMSstrME_eq(m1, m4)));
  assert(((void) "Maps with one pair are equal", d4_map_intMSstrME_eq(m2, m5)));
  assert(((void) "Maps with two pairs are equal", d4_map_intMSstrME_eq(m3, m6)));
  assert(((void) "Maps with and without pairs are not equal", !d4_map_intMSstrME_eq(m1, m2)));
  assert(((void) "Maps with different amount of pairs are not equal", !d4_map_intMSstrME_eq(m2, m3)));

  d4_map_intMSstrME_free(m1);
  d4_map_intMSstrME_free(m2);
  d4_map_intMSstrME_free(m3);

  d4_map_intMSstrME_free(m4);
  d4_map_intMSstrME_free(m5);
  d4_map_intMSstrME_free(m6);

  d4_str_free(val);
}

static void test_map_free (void) {
  d4_str_t val = d4_str_alloc(L"val");

  d4_map_intMSstrME_t m1 = d4_map_intMSstrME_alloc(0);
  d4_map_intMSstrME_t m2 = d4_map_intMSstrME_alloc(1, 1, val);
  d4_map_intMSstrME_t m3 = d4_map_intMSstrME_alloc(2, 2, val, 3, val);

  d4_map_intMSstrME_free(m1);
  d4_map_intMSstrME_free(m2);
  d4_map_intMSstrME_free(m3);

  d4_str_free(val);
}

static void test_map_get (void) {
  d4_str_t val1 = d4_str_alloc(L"val1");
  d4_str_t val2 = d4_str_alloc(L"val2");
  d4_str_t val3 = d4_str_alloc(L"val3");

  d4_map_intMSstrME_t m1 = d4_map_intMSstrME_alloc(1, 1, val1);
  d4_map_intMSstrME_t m2 = d4_map_intMSstrME_alloc(2, 2, val2, 3, val3);

  ASSERT_NO_THROW(GET1, {
    d4_str_t v1 = d4_map_intMSstrME_get(&d4_err_state, 0, 0, m1, 1);
    d4_str_t v2 = d4_map_intMSstrME_get(&d4_err_state, 0, 0, m2, 2);
    d4_str_t v3 = d4_map_intMSstrME_get(&d4_err_state, 0, 0, m2, 3);

    assert(((void) "Gets an element from map with one pair", d4_str_eq(v1, val1)));
    assert(((void) "Gets first element from map with two pairs", d4_str_eq(v2, val2)));
    assert(((void) "Gets second element from map with two pairs", d4_str_eq(v3, val3)));

    d4_str_free(v1);
    d4_str_free(v2);
    d4_str_free(v3);
  });

  d4_map_intMSstrME_free(m1);
  d4_map_intMSstrME_free(m2);

  d4_str_free(val1);
  d4_str_free(val2);
  d4_str_free(val3);
}

static void test_map_get_throws (void) {
  d4_str_t val = d4_str_alloc(L"val");

  d4_map_intMSstrME_t m1 = d4_map_intMSstrME_alloc(0);
  d4_map_intMSstrME_t m2 = d4_map_intMSstrME_alloc(1, 1, val);
  d4_map_intMSstrME_t m3 = d4_map_intMSstrME_alloc(2, 2, val, 3, val);

  ASSERT_THROW_WITH_MESSAGE(GET1, {
    d4_map_intMSstrME_get(&d4_err_state, 0, 0, m1, -1);
  }, L"failed to find key '-1'");

  ASSERT_THROW_WITH_MESSAGE(GET2, {
    d4_map_intMSstrME_get(&d4_err_state, 0, 0, m2, 0);
  }, L"failed to find key '0'");

  ASSERT_THROW_WITH_MESSAGE(GET3, {
    d4_map_intMSstrME_get(&d4_err_state, 0, 0, m3, 1);
  }, L"failed to find key '1'");

  d4_map_intMSstrME_free(m1);
  d4_map_intMSstrME_free(m2);
  d4_map_intMSstrME_free(m3);

  d4_str_free(val);
}

static void test_map_has (void) {
  d4_str_t val = d4_str_alloc(L"val");

  d4_map_intMSstrME_t m1 = d4_map_intMSstrME_alloc(0);
  d4_map_intMSstrME_t m2 = d4_map_intMSstrME_alloc(1, 1, val);
  d4_map_intMSstrME_t m3 = d4_map_intMSstrME_alloc(2, 2, val, 3, val);

  assert(((void) "Has no element in map with zero pairs", !d4_map_intMSstrME_has(m1, 0)));
  assert(((void) "Has no element in map with one pair", !d4_map_intMSstrME_has(m2, 0)));
  assert(((void) "Has an element in map with one pair", d4_map_intMSstrME_has(m2, 1)));
  assert(((void) "Has no element in map with two pairs", !d4_map_intMSstrME_has(m3, 1)));
  assert(((void) "Has first element in map with two pairs", d4_map_intMSstrME_has(m3, 2)));
  assert(((void) "Has second element in map with two pairs", d4_map_intMSstrME_has(m3, 3)));

  d4_map_intMSstrME_free(m1);
  d4_map_intMSstrME_free(m2);
  d4_map_intMSstrME_free(m3);

  d4_str_free(val);
}

static void test_map_keys (void) {
  d4_str_t val = d4_str_alloc(L"val");

  d4_map_intMSstrME_t m1 = d4_map_intMSstrME_alloc(0);
  d4_map_intMSstrME_t m2 = d4_map_intMSstrME_alloc(1, 1, val);
  d4_map_intMSstrME_t m3 = d4_map_intMSstrME_alloc(2, 2, val, 3, val);

  d4_arr_int_t keys1 = d4_map_intMSstrME_keys(m1);
  d4_arr_int_t keys2 = d4_map_intMSstrME_keys(m2);
  d4_arr_int_t keys3 = d4_map_intMSstrME_keys(m3);

  assert(((void) "Map with zero keys returns zero keys", keys1.len == 0));
  assert(((void) "Map with one key returns one key", keys2.len == 1));
  assert(((void) "Map with one key returns correct first key", keys2.data[0] == 1));
  assert(((void) "Map with two keys returns two keys", keys3.len == 2));
  assert(((void) "Map with two keys returns correct first key", keys3.data[0] == 3));
  assert(((void) "Map with two keys returns correct second key", keys3.data[1] == 2));

  d4_arr_int_free(keys1);
  d4_arr_int_free(keys2);
  d4_arr_int_free(keys3);

  d4_map_intMSstrME_free(m1);
  d4_map_intMSstrME_free(m2);
  d4_map_intMSstrME_free(m3);

  d4_str_free(val);
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
