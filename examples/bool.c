/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/bool.h>
#include <the/string.h>

int main (void) {
  the_str_t a_str = the_bool_str(true);
  the_str_t b_str = the_bool_str(false);

  wprintf(L"true as string = %ls\n", a_str.data);
  wprintf(L"false as string = %ls\n", b_str.data);

  the_str_free(b_str);
  the_str_free(a_str);

  return 0;
}
