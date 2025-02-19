/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "../include/d4/bool.h"
#include "../include/d4/string.h"

int main (void) {
  d4_str_t a_str = d4_bool_str(true);
  d4_str_t b_str = d4_bool_str(false);

  wprintf(L"true as string = %ls\n", a_str.data);
  wprintf(L"false as string = %ls\n", b_str.data);

  d4_str_free(b_str);
  d4_str_free(a_str);

  return 0;
}
