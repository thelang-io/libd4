/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <assert.h>
#include "../src/bool.h"
#include "../src/string.h"

static void test_bool_str (void) {
  d4_str_t a1 = d4_bool_str(true);
  d4_str_t a2 = d4_bool_str(false);

  d4_str_t s1_cmp = d4_str_alloc(L"true");
  d4_str_t s2_cmp = d4_str_alloc(L"false");

  assert(((void) "Stringifies true", d4_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies false", d4_str_eq(a2, s2_cmp)));

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);

  d4_str_free(a1);
  d4_str_free(a2);
}

int main (void) {
  test_bool_str();
}
