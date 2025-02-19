/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "../include/d4/number.h"
#include "../include/d4/string.h"

int main (void) {
  d4_str_t a_str = d4_int_str(12345);
  d4_str_t b_str = d4_float_str(12.34);

  wprintf(L"12345 as string = %ls\n", a_str.data);
  wprintf(L"12.34 as string = %ls\n", b_str.data);

  d4_str_free(b_str);
  d4_str_free(a_str);

  return 0;
}
