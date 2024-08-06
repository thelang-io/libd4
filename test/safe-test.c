/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <assert.h>
#include "../src/safe.h"
#include "../src/string.h"

static void test_safe_alloc (void) {
  void *d2 = d4_safe_alloc(64);
  assert(((void) "Allocates 64", d2 != NULL));
  d4_safe_free(d2);
}

static void test_safe_calloc (void) {
  void *d1 = d4_safe_alloc(64);
  void *d2 = d4_safe_calloc(d1, sizeof(int));

  assert(((void) "Allocates 64", d1 != NULL));
  assert(((void) "Allocates 64", d2 != NULL));

  d4_safe_free(d2);
  d4_safe_free(d1);
}

static void test_safe_free (void) {
  void *d2 = d4_safe_alloc(64);
  d4_safe_free(d2);
}

static void test_safe_realloc (void) {
  void *d = NULL;

  d = d4_safe_realloc(d, 64);
  assert(((void) "Reallocates from 0 to 64", d != NULL));
  d = d4_safe_realloc(d, 128);
  assert(((void) "Reallocates from 64 to 128", d != NULL));

  d4_safe_free(d);
}

static void test_safe_swap (void) {
  int a = 1;
  int b = 2;
  d4_str_t c = d4_str_alloc(L"test1");
  d4_str_t d = d4_str_alloc(L"test2");
  d4_str_t e = d4_str_alloc(L"test1");
  d4_str_t f = d4_str_alloc(L"test2");

  d4_safe_swap(&a, &b, sizeof(int));
  d4_safe_swap(&c, &d, sizeof(d4_str_t));

  assert(((void) "Swaps integers", a == 2 && b == 1));
  assert(((void) "Swaps strings", d4_str_eq(c, f) && d4_str_eq(d, e)));

  d4_str_free(c);
  d4_str_free(d);
  d4_str_free(e);
  d4_str_free(f);
}

int main (void) {
  test_safe_alloc();
  test_safe_calloc();
  test_safe_free();
  test_safe_realloc();
  test_safe_swap();
}
