/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/enum.h>
#include <the/string.h>

enum Color {
  Red = 10,
  Green = 20,
};

int main (void) {
  the_str_t a_str = the_enum_str(Red);
  the_str_t b_str = the_enum_str(Green);

  wprintf(L"Red as string = %ls\n", a_str.data);
  wprintf(L"Green as string = %ls\n", b_str.data);

  the_str_free(b_str);
  the_str_free(a_str);

  return 0;
}
