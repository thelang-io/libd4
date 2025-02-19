/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <assert.h>
#include "../src/any.h"
#include "../src/number.h"
#include "../src/safe.h"
#include "../src/string.h"

#define TYPE_u32 1
#define TYPE_u64 2

D4_ANY_DECLARE(u32, uint32_t)
D4_ANY_DEFINE(TYPE_u32, u32, uint32_t, val, lhs_val == rhs_val, (void) val, d4_u32_str(val))

D4_ANY_DECLARE(u64, uint64_t)
D4_ANY_DEFINE(TYPE_u64, u64, uint64_t, val, lhs_val == rhs_val, (void) val, d4_u64_str(val))

static void test_any_copy (void) {
  d4_any_t a1 = d4_any_u64_alloc(10);
  d4_any_t a2 = d4_any_copy(a1);

  assert(((void) "Types equal", a1.type == a2.type));
  assert(((void) "Context has different memory address", a1.ctx != a2.ctx));

  assert((
    (void) "Addresses of functions are equal",
    a1.copy_cb == a2.copy_cb && a1.eq_cb == a2.eq_cb && a1.free_cb == a2.free_cb && a1.str_cb == a2.str_cb
  ));

  d4_any_free(a1);
  d4_any_free(a2);
}

static void test_any_eq (void) {
  d4_any_t a1 = (d4_any_t) {-1, NULL, NULL, NULL, NULL, NULL};
  d4_any_t a2 = (d4_any_t) {-1, NULL, NULL, NULL, NULL, NULL};
  d4_any_t a3 = d4_any_u64_alloc(10);
  d4_any_t a4 = d4_any_u64_alloc(10);
  d4_any_t a5 = d4_any_u64_alloc(20);
  d4_any_t a6 = d4_any_u32_alloc(10);

  assert(((void) "Value equals itself", d4_any_eq(a3, a3)));
  assert(((void) "Value equals itself when NULL", d4_any_eq(a1, a1)));
  assert(((void) "NULL equals NULL", d4_any_eq(a1, a2)));
  assert(((void) "Value equals NULL", !d4_any_eq(a3, a1)));
  assert(((void) "Value equals same value", d4_any_eq(a3, a4)));
  assert(((void) "Value equals different value", !d4_any_eq(a3, a5)));
  assert(((void) "Different types different values", !d4_any_eq(a5, a6)));
  assert(((void) "Different types same values", !d4_any_eq(a3, a6)));

  d4_any_free(a1);
  d4_any_free(a2);
  d4_any_free(a3);
  d4_any_free(a4);
  d4_any_free(a5);
  d4_any_free(a6);
}

static void test_any_free (void) {
  d4_any_t a1 = (d4_any_t) {-1, NULL, NULL, NULL, NULL, NULL};
  d4_any_t a2 = d4_any_u64_alloc(10);

  d4_any_free(a1);
  d4_any_free(a2);
}

static void test_any_realloc (void) {
  d4_any_t a = (d4_any_t) {-1, NULL, NULL, NULL, NULL, NULL};
  d4_any_t a1 = (d4_any_t) {-1, NULL, NULL, NULL, NULL, NULL};
  d4_any_t a2 = d4_any_u64_alloc(10);
  d4_any_t a3 = d4_any_u64_alloc(20);

  a = d4_any_realloc(a, a1);
  assert(((void) "Reallocates NULL into NULL", d4_any_eq(a, a1)));

  a = d4_any_realloc(a, a2);
  assert(((void) "Reallocates NULL into value", d4_any_eq(a, a2)));

  a = d4_any_realloc(a, a3);
  assert(((void) "Reallocates value into different value", d4_any_eq(a, a3)));

  d4_any_free(a);
  d4_any_free(a1);
  d4_any_free(a2);
  d4_any_free(a3);
}

static void test_any_str (void) {
  d4_any_t a1 = (d4_any_t) {-1, NULL, NULL, NULL, NULL, NULL};
  d4_any_t a2 = d4_any_u64_alloc(10);

  d4_str_t s1 = d4_any_str(a1);
  d4_str_t s2 = d4_any_str(a2);

  d4_str_t s1_cmp = d4_str_alloc(L"any");
  d4_str_t s2_cmp = d4_str_alloc(L"10");

  assert(((void) "Stringifies NULL", d4_str_eq(s1, s1_cmp)));
  assert(((void) "Stringifies value", d4_str_eq(s2, s2_cmp)));

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);

  d4_str_free(s1);
  d4_str_free(s2);

  d4_any_free(a1);
  d4_any_free(a2);
}

int main (void) {
  test_any_copy();
  test_any_eq();
  test_any_free();
  test_any_realloc();
  test_any_str();
}
