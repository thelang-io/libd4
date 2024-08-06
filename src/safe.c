/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "safe.h"
#include <stdlib.h>
#include <string.h>
#include "error.h"

void *d4_safe_alloc (size_t size) {
  void *d = malloc(size);

  if (d == NULL) {
    d4_error_alloc(&d4_err_state, size); // LCOV_EXCL_LINE
  }

  return d;
}

void *d4_safe_calloc (const void *ptr, size_t size) {
  void *d = malloc(size);

  if (d == NULL) {
    d4_error_alloc(&d4_err_state, size); // LCOV_EXCL_LINE
  }

  memcpy(d, ptr, size);
  return d;
}

void d4_safe_free (void *self) {
  free(self);
}

void *d4_safe_realloc (void *self, size_t size) {
  void *d = realloc(self, size);

  if (d == NULL) {
    d4_error_alloc(&d4_err_state, size); // LCOV_EXCL_LINE
  }

  return d;
}

void d4_safe_swap (void *a, void *b, size_t size) {
  void *tmp = d4_safe_alloc(size);
  memcpy(tmp, a, size);
  memcpy(a, b, size);
  memcpy(b, tmp, size);
  d4_safe_free(tmp);
}
