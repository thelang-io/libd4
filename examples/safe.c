/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/safe.h>

int main (void) {
  size_t l = sizeof(int);
  void *d1 = the_safe_alloc(l);
  void *d2 = the_safe_alloc(2 * l);

  d2 = the_safe_realloc(d2, l);
  the_safe_swap(d1, d2, l);

  the_safe_free(d2);
  the_safe_free(d1);

  return 0;
}
