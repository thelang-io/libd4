/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "../include/d4/safe.h"

int main (void) {
  size_t l = sizeof(int);
  void *d1 = d4_safe_alloc(l);
  void *d2 = d4_safe_alloc(2 * l);

  d2 = d4_safe_realloc(d2, l);
  d4_safe_swap(d1, d2, l);

  d4_safe_free(d2);
  d4_safe_free(d1);

  return 0;
}
