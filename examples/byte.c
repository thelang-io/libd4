/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/byte.h>
#include <the/string.h>
#include <stdio.h>

int main (void) {
  the_str_t a_str = the_byte_str(0x0);
  the_str_t b_str = the_byte_str(0xFF);

  printf("0x00 as string = %ls\n", a_str.data);
  printf("0xFF as string = %ls\n", b_str.data);

  the_str_free(b_str);
  the_str_free(a_str);

  return 0;
}
