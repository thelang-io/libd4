/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <assert.h>
#include "../src/byte.h"
#include "../src/string.h"

static void test_byte_str (void) {
  the_str_t a1 = the_byte_str(0x00);
  the_str_t a2 = the_byte_str(0x0A);

  the_str_t s1_cmp = the_str_alloc(L"0");
  the_str_t s2_cmp = the_str_alloc(L"10");

  assert(((void) "Stringifies 0x00", the_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 0x0A", the_str_eq(a2, s2_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);

  the_str_free(a1);
  the_str_free(a2);
}

int main (void) {
  test_byte_str();
}
