/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/char.h>
#include <the/string.h>

int main (void) {
  the_str_t a_str;
  the_str_t b_str;

  wprintf(L"'a' as byte = %u\n", the_char_byte('a'));

  if (the_char_isLetterOrDigit('a')) {
    wprintf(L"'a' is definitely a letter or digit\n");
  }

  wprintf(L"'%c' in lower case '%c'", 'A', the_char_lower('A'));
  wprintf(L"'%c' in upper case '%c'", 'a', the_char_upper('a'));

  a_str = the_char_str('A');
  wprintf(L"%ls\n", a_str.data);
  the_str_free(a_str);

  b_str = the_char_repeat('a', 10);
  wprintf(L"a repeated 10 times = %ls\n", b_str.data);
  the_str_free(b_str);

  return 0;
}
