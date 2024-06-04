/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/array.h>
#include <assert.h>

THE_ARRAY_DECLARE(arr_str, the_arr_str_t)
THE_ARRAY_DEFINE(arr_str, the_arr_str_t, the_arr_str_t, the_arr_str_copy(element), the_arr_str_eq(lhs_element, rhs_element), the_arr_str_free(element), the_arr_str_str(element))

static void test_array_alloc (void) {
  // todo
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
  // todo
}

static void test_array_empty (void) {
  // todo
}

static void test_array_eq (void) {
  // todo
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
  // todo
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
  // todo
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
  // todo
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
