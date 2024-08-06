/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <assert.h>
#include "../src/enum.h"
#include "../src/string.h"

typedef enum {
  Color_Red,
  Color_Green = 10,
  Color_Blue
} Color;

static void test_enum_str (void) {
  d4_str_t a1 = d4_enum_str(Color_Red);
  d4_str_t a2 = d4_enum_str(Color_Green);

  d4_str_t s1_cmp = d4_str_alloc(L"0");
  d4_str_t s2_cmp = d4_str_alloc(L"10");

  assert(((void) "Stringifies Color.Red", d4_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies Color.Green", d4_str_eq(a2, s2_cmp)));

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);

  d4_str_free(a1);
  d4_str_free(a2);
}

int main (void) {
  test_enum_str();
}
