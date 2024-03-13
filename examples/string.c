/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/error.h>
#include <the/macro.h>
#include <the/string.h>

int main (void) {
  the_str_t a1 = the_str_alloc(L"Hello");
  the_str_t a2 = the_str_alloc(L"Hello, %ls", L"World!");
  the_str_t a3 = the_str_calloc(a1.data, 4);
  the_str_t a4 = the_str_copy(a2);
  the_str_t a5 = the_str_concat(a1, a2);
  the_str_t a6 = the_str_slice(a2, 1, 7, 1, -1);
  the_str_t _7;
  the_str_t a8 = the_str_lower(a2);
  wchar_t *c1 = the_str_at(&the_err_state, 10, 10, a1, 2);

  a3 = the_str_realloc(a3, a1);

  wprintf(L"string a1 = %ls" THE_EOL, a1.data);
  wprintf(L"string a2 = %ls" THE_EOL, a2.data);
  wprintf(L"string a3 = %ls" THE_EOL, a3.data);
  wprintf(L"string a4 = %ls" THE_EOL, a4.data);
  wprintf(L"string a5 = %ls" THE_EOL, a5.data);
  wprintf(L"string a6 = %ls" THE_EOL, a6.data);
  wprintf(L"string a8 = %ls" THE_EOL, a8.data);
  wprintf(L"string a1 at position 2 = %c" THE_EOL, c1);

  if (the_str_contains(a2, a1)) {
    wprintf(L"string a2 contains string a1" THE_EOL);
  }

  if (the_str_eq(a2, a4)) {
    wprintf(L"string a2 equals string a4" THE_EOL);
  }

  if (the_str_gt(a1, a2)) {
    wprintf(L"string a1 greater than string a2" THE_EOL);
  } else {
    wprintf(L"string a2 greater than string a1" THE_EOL);
  }

  wprintf(L"position of 'lo' in a2 = %d" THE_EOL, (int) the_str_find(a2, _7 = the_str_alloc(L"lo")));

  the_str_free(a8);
  the_str_free(_7);
  the_str_free(a6);
  the_str_free(a5);
  the_str_free(a4);
  the_str_free(a3);
  the_str_free(a2);
  the_str_free(a1);

  return 0;
}
