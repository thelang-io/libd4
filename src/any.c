/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "any.h"
#include "string.h"

the_any_t the_any_copy (const the_any_t self) {
  return self.d == NULL ? (the_any_t) {0, NULL, NULL, NULL, NULL, NULL, NULL} : self._copy(self);
}

bool the_any_eq (const the_any_t self, const the_any_t rhs) {
  return self.d == NULL ? false : self._eq(self, rhs);
}

void the_any_free (the_any_t self) {
  if (self.d != NULL) self._free(self);
}

bool the_any_ne (const the_any_t self, const the_any_t rhs) {
  return self.d == NULL ? true : self._ne(self, rhs);
}

the_any_t the_any_realloc (the_any_t self, const the_any_t n) {
  the_any_free(self);
  return the_any_copy(n);
}

the_str_t the_any_str (const the_any_t self) {
  return self.d == NULL ? the_str_alloc(L"any") : self._str(self);
}
