/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/number.h>
#include <the/string.h>

int main (void) {
  the_str_t a_str = the_int_str(12345);
  the_str_t b_str = the_float_str(12.34);

  wprintf(L"12345 as string = %ls\n", a_str.data);
  wprintf(L"12.34 as string = %ls\n", b_str.data);

  the_str_free(b_str);
  the_str_free(a_str);

  return 0;
}
