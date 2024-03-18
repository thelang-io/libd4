/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "any-test.h"
#include <assert.h>
#include "../src/string.h"

static void test_any_copy (void) {
  the_any_t a1 = any_u64(10);
  the_any_t a2 = the_any_copy(a1);

  assert(((void) "Types equal", a1.type == a2.type));
  assert(((void) "Context has different memory address", a1.ctx != a2.ctx));

  assert((
    (void) "Addresses of functions are equal",
    a1.copy_cb == a2.copy_cb && a1.eq_cb == a2.eq_cb && a1.free_cb == a2.free_cb && a1.str_cb == a2.str_cb
  ));

  the_any_free(a1);
  the_any_free(a2);
}

static void test_any_eq (void) {
  the_any_t a1 = (the_any_t) {-1, NULL, NULL, NULL, NULL, NULL};
  the_any_t a2 = (the_any_t) {-1, NULL, NULL, NULL, NULL, NULL};
  the_any_t a3 = any_u64(10);
  the_any_t a4 = any_u64(10);
  the_any_t a5 = any_u64(20);
  the_any_t a6 = any_u32(10);

  assert(((void) "Value equals itself", the_any_eq(a3, a3)));
  assert(((void) "Value equals itself when NULL", the_any_eq(a1, a1)));
  assert(((void) "NULL equals NULL", the_any_eq(a1, a2)));
  assert(((void) "Value equals NULL", !the_any_eq(a3, a1)));
  assert(((void) "Value equals same value", the_any_eq(a3, a4)));
  assert(((void) "Value equals different value", !the_any_eq(a3, a5)));
  assert(((void) "Different types different values", !the_any_eq(a5, a6)));
  assert(((void) "Different types same values", !the_any_eq(a3, a6)));

  the_any_free(a1);
  the_any_free(a2);
  the_any_free(a3);
  the_any_free(a4);
  the_any_free(a5);
  the_any_free(a6);
}

static void test_any_free (void) {
  the_any_t a1 = (the_any_t) {-1, NULL, NULL, NULL, NULL, NULL};
  the_any_t a2 = any_u64(10);

  the_any_free(a1);
  the_any_free(a2);
}

static void test_any_realloc (void) {
  the_any_t a = (the_any_t) {-1, NULL, NULL, NULL, NULL, NULL};
  the_any_t a1 = (the_any_t) {-1, NULL, NULL, NULL, NULL, NULL};
  the_any_t a2 = any_u64(10);
  the_any_t a3 = any_u64(20);

  a = the_any_realloc(a, a1);
  assert(((void) "Reallocates NULL into NULL", the_any_eq(a, a1)));

  a = the_any_realloc(a, a2);
  assert(((void) "Reallocates NULL into value", the_any_eq(a, a2)));

  a = the_any_realloc(a, a3);
  assert(((void) "Reallocates value into different value", the_any_eq(a, a3)));

  the_any_free(a);
  the_any_free(a1);
  the_any_free(a2);
  the_any_free(a3);
}

static void test_any_str (void) {
  the_any_t a1 = (the_any_t) {-1, NULL, NULL, NULL, NULL, NULL};
  the_any_t a2 = any_u64(10);

  the_str_t s1 = the_any_str(a1);
  the_str_t s2 = the_any_str(a2);

  the_str_t s1_cmp = the_str_alloc(L"any");
  the_str_t s2_cmp = the_str_alloc(L"10");

  assert(((void) "Stringifies NULL", the_str_eq(s1, s1_cmp)));
  assert(((void) "Stringifies value", the_str_eq(s2, s2_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);

  the_str_free(s1);
  the_str_free(s2);

  the_any_free(a1);
  the_any_free(a2);
}

int main (void) {
  test_any_copy();
  test_any_eq();
  test_any_free();
  test_any_realloc();
  test_any_str();
}
