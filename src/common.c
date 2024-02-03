/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <stdio.h>
#include <stdlib.h>

void the_free_simple (void *it) {
  if (it != NULL) {
    free(it);
  }
}

void the_throw (const char *message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}
