/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <stdlib.h>
#include <wchar.h>

typedef struct {
  wchar_t *data;
  size_t len;
} the_str_t;

int main (void) {
  void *d2;
  void *d4;
  the_str_t a2;
  the_str_t s2_cmp;

  d2 = malloc(3 * sizeof(wchar_t));
  swprintf(d2, 3, L"10");

  d4 = malloc(3 * sizeof(wchar_t));
  swprintf(d4, 3, L"10");

  a2 = (the_str_t) {d2, 2};
  s2_cmp = (the_str_t) {d4, 2};

  (void) wmemcmp(a2.data, s2_cmp.data, a2.len);

  free(s2_cmp.data);
  free(a2.data);
}
