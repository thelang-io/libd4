/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "safe.h"
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"

the_err_state_t the_err_state = (the_err_state_t) {0, NULL, NULL, NULL, NULL, NULL, NULL};

void *the_safe_alloc (size_t size) {
  void *d = malloc(size);
  if (d == NULL) the_error_alloc(&the_err_state, size);
  return d;
}

void *the_safe_realloc (void *self, size_t size) {
  void *d = realloc(self, size);
  if (d == NULL) the_error_alloc(&the_err_state, size);
  return d;
}

void the_safe_swap (void *a, void *b, size_t size) {
  void *tmp = the_safe_alloc(size);
  memcpy(tmp, a, size);
  memcpy(a, b, size);
  memcpy(b, tmp, size);
  free(tmp);
}
