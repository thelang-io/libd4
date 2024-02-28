/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <assert.h>
#include "../src/safe.h"
#include "../src/string.h"

static void test_safe_alloc (void) {
  void *d1 = the_safe_alloc(0);
  void *d2 = the_safe_alloc(64);

  assert(((void) "Allocates 0", d1 != NULL));
  assert(((void) "Allocates 64", d2 != NULL));

  the_safe_free(d1);
  the_safe_free(d2);
}

static void test_safe_free (void) {
  void *d1 = the_safe_alloc(0);
  void *d2 = the_safe_alloc(64);

  the_safe_free(d1);
  the_safe_free(d2);
}

static void test_safe_realloc (void) {
  void *d = the_safe_alloc(0);

  d = the_safe_realloc(d, 64);
  assert(((void) "Reallocates from 0 to 64", d != NULL));
  d = the_safe_realloc(d, 0);
  assert(((void) "Reallocates from 64 to 0", d != NULL));

  the_safe_free(d);
}

static void test_safe_swap (void) {
  int a = 1;
  int b = 2;
  the_str_t c = the_str_alloc(L"test1");
  the_str_t d = the_str_alloc(L"test2");
  the_str_t e = the_str_alloc(L"test1");
  the_str_t f = the_str_alloc(L"test2");

  the_safe_swap(&a, &b, sizeof(int));
  the_safe_swap(&c, &d, sizeof(the_str_t));

  assert(((void) "Swaps integers", a == 2 && b == 1));
  assert(((void) "Swaps strings", the_str_eq(c, f) && the_str_eq(d, e)));

  the_str_free(c);
  the_str_free(d);
  the_str_free(e);
  the_str_free(f);
}

int main (void) {
  test_safe_alloc();
  test_safe_free();
  test_safe_realloc();
  test_safe_swap();
}
