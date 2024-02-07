/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/char.h>

int main () {
  printf("'a' as byte = %u\n", the_char_byte('a'));

  if (the_char_isLetterOrDigit('a')) {
    printf("'a' is definitely a letter or digit\n");
  }

  printf("'%c' in lower case '%c'", 'A', the_char_lower('A'));
  printf("'%c' in upper case '%c'", 'a', the_char_upper('a'));

  the_str_t a_str = the_char_str('A');
  printf("%ls\n", a_str.data);
  the_str_free(a_str);

  the_str_t b_str = the_char_repeat('a', 10);
  printf("a repeated 10 times = %ls\n", b_str.data);
  the_str_free(b_str);

  return 0;
}
