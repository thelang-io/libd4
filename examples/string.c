/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "../include/d4/macro.h"
#include "../include/d4/error.h"
#include "../include/d4/string.h"

int main (void) {
  d4_str_t a1 = d4_str_alloc(L"Hello");
  d4_str_t a2 = d4_str_alloc(L"Hello, %ls", L"World!");
  d4_str_t a3 = d4_str_calloc(a1.data, 4);
  d4_str_t a4 = d4_str_copy(a2);
  d4_str_t a5 = d4_str_concat(a1, a2);
  d4_str_t a6 = d4_str_slice(a2, 1, 7, 1, -1);
  d4_str_t _7;
  d4_str_t a8 = d4_str_lower(a2);
  wchar_t *c1 = d4_str_at(&d4_err_state, 10, 10, a1, 2);

  a3 = d4_str_realloc(a3, a1);

  wprintf(L"string a1 = %ls" D4_EOL, a1.data);
  wprintf(L"string a2 = %ls" D4_EOL, a2.data);
  wprintf(L"string a3 = %ls" D4_EOL, a3.data);
  wprintf(L"string a4 = %ls" D4_EOL, a4.data);
  wprintf(L"string a5 = %ls" D4_EOL, a5.data);
  wprintf(L"string a6 = %ls" D4_EOL, a6.data);
  wprintf(L"string a8 = %ls" D4_EOL, a8.data);
  wprintf(L"string a1 at position 2 = %lc" D4_EOL, *c1);

  if (d4_str_contains(a2, a1)) {
    wprintf(L"string a2 contains string a1" D4_EOL);
  }

  if (d4_str_eq(a2, a4)) {
    wprintf(L"string a2 equals string a4" D4_EOL);
  }

  if (d4_str_gt(a1, a2)) {
    wprintf(L"string a1 greater than string a2" D4_EOL);
  } else {
    wprintf(L"string a2 greater than string a1" D4_EOL);
  }

  wprintf(L"position of 'lo' in a2 = %d" D4_EOL, (int) d4_str_find(a2, _7 = d4_str_alloc(L"lo")));
  wprintf(L"does string a2 starts with a1? %ls" D4_EOL, d4_str_startsWith(a2, a1) ? L"true" : L"false");
  wprintf(L"does string a2 ends with a1? %ls" D4_EOL, d4_str_endsWith(a2, a1) ? L"true" : L"false");

  d4_str_free(a8);
  d4_str_free(_7);
  d4_str_free(a6);
  d4_str_free(a5);
  d4_str_free(a4);
  d4_str_free(a3);
  d4_str_free(a2);
  d4_str_free(a1);

  return 0;
}
