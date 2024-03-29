/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/number.h>
#include <the/optional.h>
#include <assert.h>

THE_OPTIONAL_DECLARE(u32, uint32_t)
THE_OPTIONAL_DEFINE(u32, uint32_t, val, lhs_val == rhs_val, (void) val, the_i32_str(val))

static void test_optional_alloc (void) {
  the_opt_u32_t a = the_opt_u32_alloc(10);

  assert(((void) "Optional is not NULL", a != NULL));
  assert(((void) "Optional has correct value", *a == 10));

  the_opt_u32_free(a);
}

static void test_optional_copy (void) {
  the_opt_u32_t a = NULL;
  the_opt_u32_t b = the_opt_u32_alloc(10);
  the_opt_u32_t c = the_opt_u32_copy(a);
  the_opt_u32_t d = the_opt_u32_copy(b);

  assert(((void) "Optional copy of NULL is same as initial value", the_opt_u32_eq(a, c)));
  assert(((void) "Optional copy of value is same as initial value", the_opt_u32_eq(b, d)));

  the_opt_u32_free(a);
  the_opt_u32_free(b);
  the_opt_u32_free(c);
  the_opt_u32_free(d);
}

static void test_optional_eq (void) {
  the_opt_u32_t a = NULL;
  the_opt_u32_t b = NULL;
  the_opt_u32_t c = the_opt_u32_alloc(10);
  the_opt_u32_t d = the_opt_u32_alloc(10);

  assert(((void) "Two NULLs are equal", the_opt_u32_eq(a, b)));
  assert(((void) "Two values are equal", the_opt_u32_eq(c, d)));

  the_opt_u32_free(a);
  the_opt_u32_free(b);
  the_opt_u32_free(c);
  the_opt_u32_free(d);
}

static void test_optional_free (void) {
  the_opt_u32_t a = NULL;
  the_opt_u32_t b = the_opt_u32_alloc(10);

  the_opt_u32_free(a);
  the_opt_u32_free(b);
}

static void test_optional_realloc (void) {
  the_opt_u32_t a = NULL;
  the_opt_u32_t b = NULL;
  the_opt_u32_t c = the_opt_u32_alloc(10);

  a = the_opt_u32_realloc(a, b);
  assert(((void) "Reallocates NULL value into NULL value", the_opt_u32_eq(a, b)));

  a = the_opt_u32_realloc(a, c);
  assert(((void) "Reallocates NULL value into real value", the_opt_u32_eq(a, c)));

  a = the_opt_u32_realloc(a, b);
  assert(((void) "Reallocates real value back into NULL value", the_opt_u32_eq(a, b)));

  the_opt_u32_free(a);
  the_opt_u32_free(b);
  the_opt_u32_free(c);
}

static void test_optional_str (void) {
  the_opt_u32_t a = NULL;
  the_opt_u32_t b = the_opt_u32_alloc(10);

  the_str_t s1 = the_opt_u32_str(a);
  the_str_t s2 = the_opt_u32_str(b);

  the_str_t s1_cmp = the_str_alloc(L"nil");
  the_str_t s2_cmp = the_str_alloc(L"10");

  assert(((void) "Stringifies NULL", the_str_eq(s1, s1_cmp)));
  assert(((void) "Stringifies value", the_str_eq(s2, s2_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);

  the_str_free(s1);
  the_str_free(s2);

  the_opt_u32_free(a);
  the_opt_u32_free(b);
}

int main (void) {
  test_optional_alloc();
  test_optional_copy();
  test_optional_eq();
  test_optional_free();
  test_optional_realloc();
  test_optional_str();
}
