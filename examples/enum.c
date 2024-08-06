/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <d4/enum.h>
#include <d4/string.h>

enum Color {
  Red = 10,
  Green = 20,
};

int main (void) {
  d4_str_t a_str = d4_enum_str(Red);
  d4_str_t b_str = d4_enum_str(Green);

  wprintf(L"Red as string = %ls\n", a_str.data);
  wprintf(L"Green as string = %ls\n", b_str.data);

  d4_str_free(b_str);
  d4_str_free(a_str);

  return 0;
}
