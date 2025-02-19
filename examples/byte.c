/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "../include/d4/byte.h"
#include "../include/d4/string.h"

int main (void) {
  d4_str_t a_str = d4_byte_str(0x0);
  d4_str_t b_str = d4_byte_str(0xFF);

  wprintf(L"0x00 as string = %ls\n", a_str.data);
  wprintf(L"0xFF as string = %ls\n", b_str.data);

  d4_str_free(b_str);
  d4_str_free(a_str);

  return 0;
}
