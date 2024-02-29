/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <stdbool.h>
#include <stdlib.h>
#include <wchar.h>

typedef struct {
  wchar_t *data;
  size_t len;
} the_str_t;

static bool the_str_eq (const the_str_t self, const the_str_t rhs) {
  return self.len == rhs.len && wmemcmp(self.data, rhs.data, self.len) == 0;
}

int main (void) {
  void *d1;
  void *d2;
  void *d3;
  void *d4;

  the_str_t a1;
  the_str_t a2;

  the_str_t s1_cmp;
  the_str_t s2_cmp;

  d1 = malloc(2 * sizeof(wchar_t));
  swprintf(d1, 2, L"0");

  d2 = malloc(3 * sizeof(wchar_t));
  swprintf(d2, 3, L"10");

  d3 = malloc(2 * sizeof(wchar_t));
  swprintf(d3, 2, L"0");

  d4 = malloc(3 * sizeof(wchar_t));
  swprintf(d4, 3, L"10");

  a1 = (the_str_t) {d1, 1};
  a2 = (the_str_t) {d2, 2};

  s1_cmp = (the_str_t) {d3, 1};
  s2_cmp = (the_str_t) {d4, 2};

  the_str_eq(a1, s1_cmp);
  the_str_eq(a2, s2_cmp);

  free(s1_cmp.data);
  free(s2_cmp.data);

  free(a1.data);
  free(a2.data);
}
