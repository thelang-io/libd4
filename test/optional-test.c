/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <d4/number.h>
#include <d4/optional.h>
#include <assert.h>

D4_OPTIONAL_DECLARE(u32, uint32_t)
D4_OPTIONAL_DEFINE(u32, uint32_t, val, lhs_val == rhs_val, (void) val, d4_i32_str(val))

static void test_optional_alloc (void) {
  d4_opt_u32_t a = d4_opt_u32_alloc(10);
  d4_opt_u32_t b = NULL;

  assert(((void) "Optional is not NULL", a != NULL));
  assert(((void) "Optional has correct value", *a == 10));
  assert(((void) "Optional is NULL", b == NULL));

  d4_opt_u32_free(a);
}

static void test_optional_copy (void) {
  d4_opt_u32_t a = NULL;
  d4_opt_u32_t b = d4_opt_u32_alloc(10);
  d4_opt_u32_t c = d4_opt_u32_copy(a);
  d4_opt_u32_t d = d4_opt_u32_copy(b);

  assert(((void) "Optional copy of NULL is same as initial value", d4_opt_u32_eq(a, c)));
  assert(((void) "Optional copy of value is same as initial value", d4_opt_u32_eq(b, d)));

  d4_opt_u32_free(a);
  d4_opt_u32_free(b);
  d4_opt_u32_free(c);
  d4_opt_u32_free(d);
}

static void test_optional_eq (void) {
  d4_opt_u32_t a = NULL;
  d4_opt_u32_t b = NULL;
  d4_opt_u32_t c = d4_opt_u32_alloc(10);
  d4_opt_u32_t d = d4_opt_u32_alloc(10);

  assert(((void) "Two NULLs are equal", d4_opt_u32_eq(a, b)));
  assert(((void) "Two values are equal", d4_opt_u32_eq(c, d)));

  d4_opt_u32_free(a);
  d4_opt_u32_free(b);
  d4_opt_u32_free(c);
  d4_opt_u32_free(d);
}

static void test_optional_free (void) {
  d4_opt_u32_t a = NULL;
  d4_opt_u32_t b = d4_opt_u32_alloc(10);

  d4_opt_u32_free(a);
  d4_opt_u32_free(b);
}

static void test_optional_realloc (void) {
  d4_opt_u32_t a = NULL;
  d4_opt_u32_t b = NULL;
  d4_opt_u32_t c = d4_opt_u32_alloc(10);

  a = d4_opt_u32_realloc(a, b);
  assert(((void) "Reallocates NULL value into NULL value", d4_opt_u32_eq(a, b)));

  a = d4_opt_u32_realloc(a, c);
  assert(((void) "Reallocates NULL value into real value", d4_opt_u32_eq(a, c)));

  a = d4_opt_u32_realloc(a, b);
  assert(((void) "Reallocates real value back into NULL value", d4_opt_u32_eq(a, b)));

  d4_opt_u32_free(a);
  d4_opt_u32_free(b);
  d4_opt_u32_free(c);
}

static void test_optional_str (void) {
  d4_opt_u32_t a = NULL;
  d4_opt_u32_t b = d4_opt_u32_alloc(10);

  d4_str_t s1 = d4_opt_u32_str(a);
  d4_str_t s2 = d4_opt_u32_str(b);

  d4_str_t s1_cmp = d4_str_alloc(L"nil");
  d4_str_t s2_cmp = d4_str_alloc(L"10");

  assert(((void) "Stringifies NULL", d4_str_eq(s1, s1_cmp)));
  assert(((void) "Stringifies value", d4_str_eq(s2, s2_cmp)));

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);

  d4_str_free(s1);
  d4_str_free(s2);

  d4_opt_u32_free(a);
  d4_opt_u32_free(b);
}

int main (void) {
  test_optional_alloc();
  test_optional_copy();
  test_optional_eq();
  test_optional_free();
  test_optional_realloc();
  test_optional_str();
}
