/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <d4/char.h>
#include <d4/string.h>

int main (void) {
  d4_str_t a_str;
  d4_str_t b_str;

  wprintf(L"'a' as byte = %u\n", d4_char_byte('a'));

  if (d4_char_isLetterOrDigit('a')) {
    wprintf(L"'a' is definitely a letter or digit\n");
  }

  wprintf(L"'%c' in lower case '%c'", 'A', d4_char_lower('A'));
  wprintf(L"'%c' in upper case '%c'", 'a', d4_char_upper('a'));

  a_str = d4_char_str('A');
  wprintf(L"%ls\n", a_str.data);
  d4_str_free(a_str);

  b_str = d4_char_repeat('a', 10);
  wprintf(L"a repeated 10 times = %ls\n", b_str.data);
  d4_str_free(b_str);

  return 0;
}
