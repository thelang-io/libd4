/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <d4/array.h>
#include <d4/number.h>
#include <assert.h>

D4_ARRAY_DECLARE(int, int32_t)
D4_ARRAY_DEFINE(int, int32_t, int32_t, element, lhs_element == rhs_element, (void) element, d4_i32_str(element))

D4_ARRAY_DECLARE(arr_str, d4_arr_str_t)
D4_ARRAY_DEFINE(arr_str, d4_arr_str_t, d4_arr_str_t, d4_arr_str_copy(element), d4_arr_str_eq(lhs_element, rhs_element), d4_arr_str_free(element), d4_arr_str_str(element))

static void test_array_alloc (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");

  d4_arr_int_t a1 = d4_arr_int_alloc(1, 10);
  d4_arr_int_t a2 = d4_arr_int_alloc(2, 20, 30);
  d4_arr_str_t a3 = d4_arr_str_alloc(0);
  d4_arr_str_t a4 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a5 = d4_arr_str_alloc(2, v1, v2);

  assert(((void) "Creates int array with one element", a1.len == 1));
  assert(((void) "Creates int array with two elements", a2.len == 2));
  assert(((void) "Creates str array with zero elements", a3.len == 0));
  assert(((void) "Creates str array with one element", a4.len == 1));
  assert(((void) "Creates str array with two element", a5.len == 2));

  d4_arr_int_free(a1);
  d4_arr_int_free(a2);
  d4_arr_str_free(a3);
  d4_arr_str_free(a4);
  d4_arr_str_free(a5);

  d4_str_free(v1);
  d4_str_free(v2);
}

static void test_array_at (void) {
  // todo
}

static void test_array_clear (void) {
  // todo
}

static void test_array_concat (void) {
  // todo
}

static void test_array_contains (void) {
  // todo
}

static void test_array_copy (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v1, v2);
  d4_arr_str_t a4 = d4_arr_str_copy(a1);
  d4_arr_str_t a5 = d4_arr_str_copy(a2);
  d4_arr_str_t a6 = d4_arr_str_copy(a3);

  assert(((void) "Copies empty array", a4.len == 0));
  assert(((void) "Copies one element array", a5.len == 1));
  assert(((void) "Copies two elements array", a6.len == 2));

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);
  d4_arr_str_free(a4);
  d4_arr_str_free(a5);
  d4_arr_str_free(a6);

  d4_str_free(v1);
  d4_str_free(v2);
}

static void test_array_empty (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v1, v2);

  assert(((void) "Checks empty on array with zero elements", d4_arr_str_empty(a1)));
  assert(((void) "Checks empty on array with one element", !d4_arr_str_empty(a2)));
  assert(((void) "Checks empty on array with two elements", !d4_arr_str_empty(a3)));

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);

  d4_str_free(v1);
  d4_str_free(v2);
}

static void test_array_eq (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");
  d4_str_t v3 = d4_str_alloc(L"element3");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(0);
  d4_arr_str_t a3 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a4 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a5 = d4_arr_str_alloc(2, v1, v2);
  d4_arr_str_t a6 = d4_arr_str_alloc(2, v1, v2);
  d4_arr_str_t a7 = d4_arr_str_alloc(2, v2, v1);
  d4_arr_str_t a8 = d4_arr_str_alloc(2, v2, v3);

  assert(((void) "Equals arrays with zero elements", d4_arr_str_eq(a1, a2)));
  assert(((void) "Equals arrays with one element", d4_arr_str_eq(a3, a4)));
  assert(((void) "Equals arrays with two elements", d4_arr_str_eq(a5, a6)));
  // assert(((void) "Equals arrays with two elements and different order", d4_arr_str_eq(a6, a7))); // todo fix
  assert(((void) "Not equals arrays with different amount of elements", !d4_arr_str_eq(a1, a3)));
  assert(((void) "Not equals arrays with different amount of elements 2", !d4_arr_str_eq(a3, a5)));
  assert(((void) "Not equals arrays with different elements", !d4_arr_str_eq(a7, a8)));

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);
  d4_arr_str_free(a4);
  d4_arr_str_free(a5);
  d4_arr_str_free(a6);
  d4_arr_str_free(a7);
  d4_arr_str_free(a8);

  d4_str_free(v1);
  d4_str_free(v2);
  d4_str_free(v3);
}

static void test_array_filter (void) {
  // todo
}

static void test_array_first (void) {
  // todo
}

static void test_array_forEach (void) {
  // todo
}

static void test_array_free (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v1, v2);
  d4_arr_int_t a4 = d4_arr_int_alloc(0);
  d4_arr_int_t a5 = d4_arr_int_alloc(1, 10);
  d4_arr_int_t a6 = d4_arr_int_alloc(2, 20, 30);
  d4_arr_arr_str_t a7 = d4_arr_arr_str_alloc(0);
  d4_arr_arr_str_t a8 = d4_arr_arr_str_alloc(1, a2);
  d4_arr_arr_str_t a9 = d4_arr_arr_str_alloc(2, a2, a3);

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);
  d4_arr_int_free(a4);
  d4_arr_int_free(a5);
  d4_arr_int_free(a6);
  d4_arr_arr_str_free(a7);
  d4_arr_arr_str_free(a8);
  d4_arr_arr_str_free(a9);

  d4_str_free(v1);
  d4_str_free(v2);
}

static void test_array_join (void) {
  // todo
}

static void test_array_last (void) {
  // todo
}

static void test_array_merge (void) {
  // todo
}

static void test_array_pop (void) {
  // todo
}

static void test_array_push (void) {
  // todo
}

static void test_array_realloc (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v1, v2);
  d4_arr_str_t a4 = d4_arr_str_alloc(0);

  a4 = d4_arr_str_realloc(a4, a1);
  assert(((void) "Re-allocates empty array with empty array", a4.len == 0));
  a4 = d4_arr_str_realloc(a4, a2);
  assert(((void) "Re-allocates empty array with one element array", a4.len == 1));
  a4 = d4_arr_str_realloc(a4, a1);
  assert(((void) "Re-allocates one element array with empty array", a4.len == 0));
  a4 = d4_arr_str_realloc(a4, a3);
  assert(((void) "Re-allocates empty array with two elements array", a4.len == 2));
  a4 = d4_arr_str_realloc(a4, a1);
  assert(((void) "Re-allocates two elements array with empty array", a4.len == 0));

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);
  d4_arr_str_free(a4);

  d4_str_free(v1);
  d4_str_free(v2);
}

static void test_array_remove (void) {
  // todo
}

static void test_array_reverse (void) {
  // todo
}

static void test_array_slice (void) {
  // todo
}

static void test_array_sort (void) {
  // todo
}

static void test_array_str (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_int_t a2 = d4_arr_int_alloc(1, 10);
  d4_arr_int_t a3 = d4_arr_int_alloc(2, 20, 30);
  d4_arr_str_t a4 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a5 = d4_arr_str_alloc(2, v1, v2);

  d4_str_t r1 = d4_arr_str_str(a1);
  d4_str_t r2 = d4_arr_int_str(a2);
  d4_str_t r3 = d4_arr_int_str(a3);
  d4_str_t r4 = d4_arr_str_str(a4);
  d4_str_t r5 = d4_arr_str_str(a5);

  d4_str_t cmp1 = d4_str_alloc(L"[]");
  d4_str_t cmp2 = d4_str_alloc(L"[10]");
  d4_str_t cmp3 = d4_str_alloc(L"[20, 30]");
  d4_str_t cmp4 = d4_str_alloc(L"[\"element1\"]");
  d4_str_t cmp5 = d4_str_alloc(L"[\"element1\", \"element2\"]");

  assert(((void) "Stringifies string array with zero elements", d4_str_eq(r1, cmp1)));
  assert(((void) "Stringifies int array with one element", d4_str_eq(r2, cmp2)));
  assert(((void) "Stringifies int array with two elements", d4_str_eq(r3, cmp3)));
  // assert(((void) "Stringifies string array with one element", d4_str_eq(r4, cmp4))); // todo fix
  // assert(((void) "Stringifies string array with two elements", d4_str_eq(r5, cmp5))); // todo fix

  d4_str_free(cmp1);
  d4_str_free(cmp2);
  d4_str_free(cmp3);
  d4_str_free(cmp4);
  d4_str_free(cmp5);

  d4_str_free(r1);
  d4_str_free(r2);
  d4_str_free(r3);
  d4_str_free(r4);
  d4_str_free(r5);

  d4_arr_str_free(a1);
  d4_arr_int_free(a2);
  d4_arr_int_free(a3);
  d4_arr_str_free(a4);
  d4_arr_str_free(a5);

  d4_str_free(v1);
  d4_str_free(v2);
}

int main (void) {
  test_array_alloc();
  test_array_at();
  test_array_clear();
  test_array_concat();
  test_array_contains();
  test_array_copy();
  test_array_empty();
  test_array_eq();
  test_array_filter();
  test_array_first();
  test_array_forEach();
  test_array_free();
  test_array_join();
  test_array_last();
  test_array_merge();
  test_array_pop();
  test_array_push();
  test_array_realloc();
  test_array_remove();
  test_array_reverse();
  test_array_slice();
  test_array_sort();
  test_array_str();
}
