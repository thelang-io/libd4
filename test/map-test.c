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
  d4_str_t key = d4_str_alloc(L"key");
  d4_str_t key2 = d4_str_alloc(L"2");
  d4_str_t key4 = d4_str_alloc(L"4");
  d4_str_t val = d4_str_alloc(L"val");
  d4_str_t val2 = d4_str_alloc(L"val2");

  d4_map_strMSstrME_t m1 = d4_map_strMSstrME_alloc(0);
  d4_map_intMSintME_t m2 = d4_map_intMSintME_alloc(1, 1, 10);
  d4_map_intMSstrME_t m3 = d4_map_intMSstrME_alloc(2, 2, val, 3, val);

  ASSERT_NO_THROW(PLACE1, {
    d4_str_t v1;
    d4_str_t v2;
    int v3;
    d4_str_t v4;

    d4_map_strMSstrME_place(m1, key, key, val);
    v1 = d4_map_strMSstrME_get(&d4_err_state, 0, 0, m1, key);
    assert(((void) "Sets with zero pairs", d4_str_eq(v1, val)));

    d4_map_strMSstrME_place(m1, key, key, val2);
    v2 = d4_map_strMSstrME_get(&d4_err_state, 0, 0, m1, key);
    assert(((void) "Sets repeated pair", d4_str_eq(v2, val2)));

    d4_map_intMSintME_place(m2, key2, 2, 20);
    v3 = d4_map_intMSintME_get(&d4_err_state, 0, 0, m2, 2);
    assert(((void) "Sets with one pair", v3 == 20));

    d4_map_intMSstrME_place(m3, key4, 4, val2);
    v4 = d4_map_intMSstrME_get(&d4_err_state, 0, 0, m3, 4);
    assert(((void) "Sets with two pairs", d4_str_eq(v4, val2)));

    d4_str_free(v1);
    d4_str_free(v2);
    d4_str_free(v4);
  });

  d4_map_strMSstrME_free(m1);
  d4_map_intMSintME_free(m2);
  d4_map_intMSstrME_free(m3);

  d4_str_free(val);
  d4_str_free(val2);
  d4_str_free(key);
  d4_str_free(key2);
  d4_str_free(key4);
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

  ASSERT_NO_THROW(REMOVE1, {
    d4_map_intMSintME_remove(&d4_err_state, 0, 0, &m2, 1);
    assert(((void) "Removes pair from one-pair map", m2.len == 0));
    d4_map_intMSstrME_remove(&d4_err_state, 0, 0, &m3, 2);
    assert(((void) "Removes pair from two-pairs map", m3.len == 1));
    d4_map_intMSstrME_remove(&d4_err_state, 0, 0, &m3, 3);
    assert(((void) "Removes last pair from two-pairs map", m3.len == 0));
  });

  ASSERT_THROW_WITH_MESSAGE(REMOVE2, {
    d4_map_intMSintME_remove(&d4_err_state, 0, 0, &m1, 1);
  }, L"failed to remove key '1'");

  ASSERT_THROW_WITH_MESSAGE(REMOVE3, {
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

  ASSERT_NO_THROW(REMOVE1, {
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
  });

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
  d4_str_t s3 = d4_str_alloc(L"{\"3\": \"val\", \"2\": \"val\"}");
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
  assert(((void) "Int/Str map stringifies correctly with two pairs", d4_str_eq(s3, s3_cmp)));

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

static void test_map_calc_cap (void) {
  assert(((void) "Calculates new capacity when cap < len", d4_map_calc_cap(0x01, 0x0F) == 0x20));
  assert(((void) "Calculates new capacity when capacity does not satisfy load factor", d4_map_calc_cap(0x10, 0x0F) == 0x20));
  assert(((void) "Returns same capacity when should not reserve", d4_map_calc_cap(0x20, 0x0F) == 0x20));
}

static void test_map_hash (void) {
  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"h");
  d4_str_t s3 = d4_str_alloc(L"he");
  d4_str_t s4 = d4_str_alloc(L"hel");
  d4_str_t s5 = d4_str_alloc(L"hell");
  d4_str_t s6 = d4_str_alloc(L"hello");
  d4_str_t s7 = d4_str_alloc(L"hello ");
  d4_str_t s8 = d4_str_alloc(L"hello w");
  d4_str_t s9 = d4_str_alloc(L"hello wo");
  d4_str_t s10 = d4_str_alloc(L"hello wor");
  d4_str_t s11 = d4_str_alloc(L"hello worl");
  d4_str_t s12 = d4_str_alloc(L"hello world");
  d4_str_t s13 = d4_str_alloc(L"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur accumsan nec orci id scelerisque. Sed ante massa, tempus id gravida sit amet, dictum vel dui. In imperdiet dapibus dolor euismod consequat. Vivamus fermentum, urna sit amet pretium accumsan, dolor lacus vulputate metus, eget molestie orci turpis vel dui. Nunc egestas sem et risus consequat consectetur sit amet suscipit eros. Aliquam sed orci sed odio laoreet pretium quis in arcu. Aliquam tempus turpis vel sem fermentum, sit amet elementum elit congue. Nunc vel faucibus nulla, et rhoncus orci.");

  assert(((void) "Calculates hash for s1 with cap 0xFFFFFFFF", d4_map_hash(s1, 0xFFFFFFFF) == 0x5014c00a));
  assert(((void) "Calculates hash for s2 with cap 0xFFFFFFFF", d4_map_hash(s2, 0xFFFFFFFF) == 0x35657504));
  assert(((void) "Calculates hash for s3 with cap 0xFFFFFFFF", d4_map_hash(s3, 0xFFFFFFFF) == 0xbd1d8b97));
  assert(((void) "Calculates hash for s4 with cap 0xFFFFFFFF", d4_map_hash(s4, 0xFFFFFFFF) == 0x445fc2f5));
  assert(((void) "Calculates hash for s5 with cap 0xFFFFFFFF", d4_map_hash(s5, 0xFFFFFFFF) == 0xc9be2137));
  assert(((void) "Calculates hash for s6 with cap 0xFFFFFFFF", d4_map_hash(s6, 0xFFFFFFFF) == 0x39072851));
  assert(((void) "Calculates hash for s7 with cap 0xFFFFFFFF", d4_map_hash(s7, 0xFFFFFFFF) == 0xa4fe4812));
  assert(((void) "Calculates hash for s8 with cap 0xFFFFFFFF", d4_map_hash(s8, 0xFFFFFFFF) == 0xeca27bd2));
  assert(((void) "Calculates hash for s9 with cap 0xFFFFFFFF", d4_map_hash(s9, 0xFFFFFFFF) == 0xb96a6ed9));
  assert(((void) "Calculates hash for s10 with cap 0xFFFFFFFF", d4_map_hash(s10, 0xFFFFFFFF) == 0x2e3e5222));
  assert(((void) "Calculates hash for s11 with cap 0xFFFFFFFF", d4_map_hash(s11, 0xFFFFFFFF) == 0x37c25731));
  assert(((void) "Calculates hash for s12 with cap 0xFFFFFFFF", d4_map_hash(s12, 0xFFFFFFFF) == 0x2f60713d));
  assert(((void) "Calculates hash for s13 with cap 0xFFFFFFFF", d4_map_hash(s13, 0xFFFFFFFF) == 0xde2e4162));

  assert(((void) "Calculates hash for s1 with cap 0xFFFFFFFFFFFFFFFF", d4_map_hash(s1, 0xFFFFFFFFFFFFFFFF) == 0xcbf29ce484222325));
  assert(((void) "Calculates hash for s2 with cap 0xFFFFFFFFFFFFFFFF", d4_map_hash(s2, 0xFFFFFFFFFFFFFFFF) == 0xaf63bd4c8601b7b7));
  assert(((void) "Calculates hash for s3 with cap 0xFFFFFFFFFFFFFFFF", d4_map_hash(s3, 0xFFFFFFFFFFFFFFFF) == 0x08326007b4eb2b90));
  assert(((void) "Calculates hash for s4 with cap 0xFFFFFFFFFFFFFFFF", d4_map_hash(s4, 0xFFFFFFFFFFFFFFFF) == 0xd8c4bd186b9b05dc));
  assert(((void) "Calculates hash for s5 with cap 0xFFFFFFFFFFFFFFFF", d4_map_hash(s5, 0xFFFFFFFFFFFFFFFF) == 0xf1532c7ed86af4b8));
  assert(((void) "Calculates hash for s6 with cap 0xFFFFFFFFFFFFFFFF", d4_map_hash(s6, 0xFFFFFFFFFFFFFFFF) == 0x7b495389bdbdd4c7));
  assert(((void) "Calculates hash for s7 with cap 0xFFFFFFFFFFFFFFFF", d4_map_hash(s7, 0xFFFFFFFFFFFFFFFF) == 0x3b6dba0d69908e05));
  assert(((void) "Calculates hash for s8 with cap 0xFFFFFFFFFFFFFFFF", d4_map_hash(s8, 0xFFFFFFFFFFFFFFFF) == 0x8c0129ca60a15208));
  assert(((void) "Calculates hash for s9 with cap 0xFFFFFFFFFFFFFFFF", d4_map_hash(s9, 0xFFFFFFFFFFFFFFFF) == 0x874c0ae2321e63f7));
  assert(((void) "Calculates hash for s10 with cap 0xFFFFFFFFFFFFFFFF", d4_map_hash(s10, 0xFFFFFFFFFFFFFFFF) == 0x049a755b29a3dcc7));
  assert(((void) "Calculates hash for s11 with cap 0xFFFFFFFFFFFFFFFF", d4_map_hash(s11, 0xFFFFFFFFFFFFFFFF) == 0x765230e7c1702649));
  assert(((void) "Calculates hash for s12 with cap 0xFFFFFFFFFFFFFFFF", d4_map_hash(s12, 0xFFFFFFFFFFFFFFFF) == 0x7dcf62cdb1910e6f));
  assert(((void) "Calculates hash for s13 with cap 0xFFFFFFFFFFFFFFFF", d4_map_hash(s13, 0xFFFFFFFFFFFFFFFF) == 0x03071530db272c32));

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s6);
  d4_str_free(s7);
  d4_str_free(s8);
  d4_str_free(s9);
  d4_str_free(s10);
  d4_str_free(s11);
  d4_str_free(s12);
  d4_str_free(s13);
}

static void test_map_should_reserve (void) {
  assert(((void) "Reserves when len == cap", d4_map_should_reserve(0x0F, 0x0F)));
  assert(((void) "Reserves when len > cap", d4_map_should_reserve(0x00, 0x0F)));
  assert(((void) "Does not reserve when capacity satisfies load factor", !d4_map_should_reserve(0xFF, 0x0F)));
}

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
  test_map_calc_cap();
  test_map_hash();
  test_map_should_reserve();
}
