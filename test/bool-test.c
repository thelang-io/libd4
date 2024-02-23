/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <assert.h>
#include "../src/bool.h"
#include "../src/string.h"

static void test_bool_str (void) {
  the_str_t a1 = the_bool_str(true);
  the_str_t a2 = the_bool_str(false);

  the_str_t s1_cmp = the_str_alloc(L"true");
  the_str_t s2_cmp = the_str_alloc(L"false");

  assert(((void) "Stringifies true", the_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies false", the_str_eq(a2, s2_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);

  the_str_free(a1);
  the_str_free(a2);
}

int main (void) {
  test_bool_str();
}
