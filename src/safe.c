/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "safe.h"
#include <stdlib.h>
#include <string.h>
#include "error.h"

void *the_safe_alloc (size_t size) {
  void *d = malloc(size);

  if (d == NULL) {
    the_error_alloc(&the_err_state, size); // LCOV_EXCL_LINE
  }

  return d;
}

void the_safe_free (void *self) {
  free(self);
}

void *the_safe_realloc (void *self, size_t size) {
  void *d = realloc(self, size);

  if (d == NULL) {
    the_error_alloc(&the_err_state, size); // LCOV_EXCL_LINE
  }

  return d;
}

void the_safe_swap (void *a, void *b, size_t size) {
  void *tmp = the_safe_alloc(size);
  memcpy(tmp, a, size);
  memcpy(a, b, size);
  memcpy(b, tmp, size);
  the_safe_free(tmp);
}
