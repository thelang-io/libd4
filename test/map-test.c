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

D4_MAP_DECLARE(int, int32_t, int, int32_t)
D4_MAP_DEFINE(int, int32_t, int, key, lhs_key == rhs_key, (void) key, d4_i32_str(key), d4_i32_str(key), int, int32_t, int, val, lhs_val == rhs_val, (void) val, d4_i32_str(val))

D4_MAP_DECLARE(int, int32_t, str, d4_str_t)
D4_MAP_DEFINE(int, int32_t, int, key, lhs_key == rhs_key, (void) key, d4_i32_str(key), d4_i32_str(key), str, d4_str_t, d4_str_t, d4_str_copy(val), d4_str_eq(lhs_val, rhs_val), d4_str_free(val), d4_str_quoted_escape(val))

D4_MAP_DECLARE(str, d4_str_t, str, d4_str_t)
D4_MAP_DEFINE(str, d4_str_t, d4_str_t, d4_str_copy(key), d4_str_eq(lhs_key, rhs_key), d4_str_free(key), d4_str_copy(key), d4_str_copy(key), str, d4_str_t, d4_str_t, d4_str_copy(val), d4_str_eq(lhs_val, rhs_val), d4_str_free(val), d4_str_quoted_escape(val))

static void test_map_alloc (void) {
  d4_str_t val1 = d4_str_alloc(L"val1");
  d4_str_t val2 = d4_str_alloc(L"val2");
  d4_str_t val3 = d4_str_alloc(L"val3");

  d4_map_intMSstrME_t m1 = d4_map_intMSstrME_alloc(0);
  d4_map_intMSstrME_t m2 = d4_map_intMSstrME_alloc(1, 1, val1);
  d4_map_intMSstrME_t m3 = d4_map_intMSstrME_alloc(2, 2, val2, 3, val3);

  assert(((void) "Creates map with zero pairs", m1.len == 0 && m1.cap == 0x0F));
  assert(((void) "Creates map with one pair", m2.len == 1 && m2.cap == 0x0F));
  assert(((void) "Creates map with two pairs", m3.len == 2 && m3.cap == 0x0F));

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
  d4_str_t val = d4_str_alloc(L"val");

  d4_map_intMSstrME_t m1 = d4_map_intMSstrME_alloc(0);
  d4_map_intMSstrME_t m2 = d4_map_intMSstrME_alloc(1, 1, val);
  d4_map_intMSstrME_t m3 = d4_map_intMSstrME_alloc(2, 2, val, 3, val);

  d4_map_intMSstrME_merge(&m1, m2);
  assert(((void) "Merges into empty map", m1.len == 1));
  d4_map_intMSstrME_merge(&m1, m2);
  assert(((void) "Merges into filled empty map", m1.len == 2));
  d4_map_intMSstrME_merge(&m2, m3);
  assert(((void) "Merges into filled map", m2.len == 3));
  d4_map_intMSstrME_merge(&m2, m1);
  assert(((void) "Merges previously filled into filled map", m2.len == 5));

  d4_map_intMSstrME_free(m1);
  d4_map_intMSstrME_free(m2);
  d4_map_intMSstrME_free(m3);

  d4_str_free(val);
}

static void test_map_place (void) {
  // todo
}

static void test_map_realloc (void) {
  d4_map_intMSintME_t m1 = d4_map_intMSintME_alloc(0);
  d4_map_intMSintME_t m2 = d4_map_intMSintME_alloc(1, 1, 10);
  d4_map_intMSintME_t m3 = d4_map_intMSintME_alloc(2, 2, 20, 3, 30);
  d4_map_intMSintME_t m4 = d4_map_intMSintME_alloc(0);

  m4 = d4_map_intMSintME_realloc(m4, m1);
  assert(((void) "Re-allocates map with zero pairs having zero pairs", m4.len == 0));
  m4 = d4_map_intMSintME_realloc(m4, m2);
  assert(((void) "Re-allocates map with one pair having zero pairs", m4.len == 1));
  m4 = d4_map_intMSintME_realloc(m4, m1);
  assert(((void) "Re-allocates map with zero pairs having one pair", m4.len == 0));
  m4 = d4_map_intMSintME_realloc(m4, m3);
  assert(((void) "Re-allocates map with two pairs having zero pairs", m4.len == 2));
  m4 = d4_map_intMSintME_realloc(m4, m1);
  assert(((void) "Re-allocates map with zero pairs having two pairs", m4.len == 0));

  d4_map_intMSintME_free(m1);
  d4_map_intMSintME_free(m2);
  d4_map_intMSintME_free(m3);
  d4_map_intMSintME_free(m4);
}

static void test_map_remove (void) {
  d4_str_t val = d4_str_alloc(L"val");

  d4_map_intMSintME_t m1 = d4_map_intMSintME_alloc(0);
  d4_map_intMSintME_t m2 = d4_map_intMSintME_alloc(1, 1, 10);
  d4_map_intMSstrME_t m3 = d4_map_intMSstrME_alloc(2, 2, val, 3, val);

  d4_map_intMSintME_remove(&d4_err_state, 0, 0, &m2, 1);
  assert(((void) "Removes pair from one-pair map", m2.len == 0));
  d4_map_intMSstrME_remove(&d4_err_state, 0, 0, &m3, 2);
  assert(((void) "Removes pair from two-pairs map", m3.len == 1));
  d4_map_intMSstrME_remove(&d4_err_state, 0, 0, &m3, 3);
  assert(((void) "Removes last pair from two-pairs map", m3.len == 0));

  ASSERT_THROW_WITH_MESSAGE(REMOVE1, {
    d4_map_intMSintME_remove(&d4_err_state, 0, 0, &m1, 1);
  }, L"failed to remove key '1'");

  ASSERT_THROW_WITH_MESSAGE(REMOVE2, {
    d4_map_intMSintME_remove(&d4_err_state, 0, 0, &m2, -1);
  }, L"failed to remove key '-1'");

  d4_map_intMSintME_free(m1);
  d4_map_intMSintME_free(m2);
  d4_map_intMSstrME_free(m3);

  d4_str_free(val);
}

static void test_map_reserve (void) {
  d4_str_t key1 = d4_str_alloc(L"key1");
  d4_str_t key2 = d4_str_alloc(L"key2");
  d4_str_t val1 = d4_str_alloc(L"val1");
  d4_str_t val2 = d4_str_alloc(L"val2");

  d4_map_intMSintME_t m1 = d4_map_intMSintME_alloc(0);
  d4_map_intMSintME_t m2 = d4_map_intMSintME_alloc(1, 1, 10);
  d4_map_strMSstrME_t m3 = d4_map_strMSstrME_alloc(2, key1, val1, key2, val2);

  d4_map_intMSintME_reserve(&m1, 1000);
  assert(((void) "Reserves with zero pairs", (m1.cap == 1000 && m1.len == 0)));
  d4_map_intMSintME_reserve(&m2, 2000);
  assert(((void) "Reserves with zero pairs", (m2.cap == 2000 && m2.len == 1)));
  d4_map_strMSstrME_reserve(&m3, 3000);
  assert(((void) "Reserves with two pairs", (m3.cap == 3000 && m3.len == 2)));

  d4_map_intMSintME_free(m1);
  d4_map_intMSintME_free(m2);
  d4_map_strMSstrME_free(m3);

  d4_str_free(key1);
  d4_str_free(key2);
  d4_str_free(val1);
  d4_str_free(val2);
}

static void test_map_set (void) {
  d4_str_t key = d4_str_alloc(L"key");
  d4_str_t val = d4_str_alloc(L"val");
  d4_str_t val2 = d4_str_alloc(L"val2");

  d4_str_t m1_val;

  d4_map_strMSstrME_t m1 = d4_map_strMSstrME_alloc(0);
  d4_map_intMSintME_t m2 = d4_map_intMSintME_alloc(1, 1, 10);
  d4_map_intMSstrME_t m3 = d4_map_intMSstrME_alloc(2, 2, val, 3, val);

  d4_map_strMSstrME_set(&m1, key, val);
  assert(((void) "Sets with zero pairs", m1.len == 1));
  d4_map_strMSstrME_set(&m1, key, val2);
  assert(((void) "Sets repeated pair", m1.len == 1));
  m1_val = d4_map_strMSstrME_get(&d4_err_state, 0, 0, m1, key);
  assert(((void) "Updates repeated pair", d4_str_eq(m1_val, val2)));
  d4_map_intMSintME_set(&m2, 2, 20);
  assert(((void) "Sets with one pair", m2.len == 2));
  d4_map_intMSstrME_set(&m3, 4, val2);
  assert(((void) "Sets with two pairs", m3.len == 3));

  d4_map_strMSstrME_free(m1);
  d4_map_intMSintME_free(m2);
  d4_map_intMSstrME_free(m3);

  d4_str_free(m1_val);
  d4_str_free(key);
  d4_str_free(val);
  d4_str_free(val2);
}

static void test_map_shrink (void) {
  d4_str_t key1 = d4_str_alloc(L"key1");
  d4_str_t key2 = d4_str_alloc(L"key2");
  d4_str_t val1 = d4_str_alloc(L"val1");
  d4_str_t val2 = d4_str_alloc(L"val2");

  d4_map_intMSintME_t m1 = d4_map_intMSintME_alloc(0);
  d4_map_intMSintME_t m2 = d4_map_intMSintME_alloc(1, 1, 10);
  d4_map_strMSstrME_t m3 = d4_map_strMSstrME_alloc(2, key1, val1, key2, val2);

  d4_map_intMSintME_reserve(&m1, 1000);
  d4_map_intMSintME_shrink(&m1);
  assert(((void) "Shrinks with zero pairs", (m1.cap == 0x0F && m1.len == 0)));
  d4_map_intMSintME_reserve(&m2, 2000);
  d4_map_intMSintME_shrink(&m2);
  assert(((void) "Shrinks with zero pairs", (m2.cap == 0x0F && m2.len == 1)));
  d4_map_strMSstrME_reserve(&m3, 3000);
  d4_map_strMSstrME_shrink(&m3);
  assert(((void) "Shrinks with two pairs", (m3.cap == 0x0F && m3.len == 2)));

  d4_map_intMSintME_free(m1);
  d4_map_intMSintME_free(m2);
  d4_map_strMSstrME_free(m3);

  d4_str_free(key1);
  d4_str_free(key2);
  d4_str_free(val1);
  d4_str_free(val2);
}

static void test_map_str (void) {
  d4_str_t key = d4_str_alloc(L"key");
  d4_str_t val = d4_str_alloc(L"val");

  d4_str_t s1 = d4_str_alloc(L"{}");
  d4_str_t s2 = d4_str_alloc(L"{\"1\": 10}");
  d4_str_t s3 = d4_str_alloc(L"{\"2\": \"val\", \"3\": \"val\"}");
  d4_str_t s4 = d4_str_alloc(L"{\"key\": \"val\"}");

  d4_map_intMSintME_t m1 = d4_map_intMSintME_alloc(0);
  d4_map_intMSintME_t m2 = d4_map_intMSintME_alloc(1, 1, 10);
  d4_map_intMSstrME_t m3 = d4_map_intMSstrME_alloc(2, 2, val, 3, val);
  d4_map_strMSstrME_t m4 = d4_map_strMSstrME_alloc(1, key, val);

  d4_str_t s1_cmp = d4_map_intMSintME_str(m1);
  d4_str_t s2_cmp = d4_map_intMSintME_str(m2);
  d4_str_t s3_cmp = d4_map_intMSstrME_str(m3);
  d4_str_t s4_cmp = d4_map_strMSstrME_str(m4);

  assert(((void) "Int/Int map stringifies correctly with zero pairs", d4_str_eq(s1, s1_cmp)));
  assert(((void) "Int/Int map stringifies correctly with one pair", d4_str_eq(s2, s2_cmp)));
  assert(((void) "Str/Str map stringifies correctly with one pair", d4_str_eq(s4, s4_cmp)));
  // assert(((void) "Int/Str map stringifies correctly with two pairs", d4_str_eq(s3, s3_cmp))); // todo

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);
  d4_str_free(s3_cmp);
  d4_str_free(s4_cmp);

  d4_map_intMSintME_free(m1);
  d4_map_intMSintME_free(m2);
  d4_map_intMSstrME_free(m3);
  d4_map_strMSstrME_free(m4);

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);

  d4_str_free(val);
  d4_str_free(key);
}

static void test_map_values (void) {
  d4_str_t val = d4_str_alloc(L"val");

  d4_map_intMSstrME_t m1 = d4_map_intMSstrME_alloc(0);
  d4_map_intMSstrME_t m2 = d4_map_intMSstrME_alloc(1, 1, val);
  d4_map_intMSstrME_t m3 = d4_map_intMSstrME_alloc(2, 2, val, 3, val);

  d4_arr_str_t values1 = d4_map_intMSstrME_values(m1);
  d4_arr_str_t values2 = d4_map_intMSstrME_values(m2);
  d4_arr_str_t values3 = d4_map_intMSstrME_values(m3);

  assert(((void) "Map with zero keys returns zero values", values1.len == 0));
  assert(((void) "Map with one key returns one value", values2.len == 1));
  assert(((void) "Map with one key returns correct first value", d4_str_eq(values2.data[0], val)));
  assert(((void) "Map with two keys returns two values", values3.len == 2));
  assert(((void) "Map with two keys returns correct first value", d4_str_eq(values3.data[0], val)));
  assert(((void) "Map with two keys returns correct second value", d4_str_eq(values3.data[1], val)));

  d4_arr_str_free(values1);
  d4_arr_str_free(values2);
  d4_arr_str_free(values3);

  d4_map_intMSstrME_free(m1);
  d4_map_intMSstrME_free(m2);
  d4_map_intMSstrME_free(m3);

  d4_str_free(val);
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
