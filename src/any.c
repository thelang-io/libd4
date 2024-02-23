/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "any.h"
#include <the/string.h>

the_any_t the_any_copy (const the_any_t self) {
  return self.ctx == NULL
    ? (the_any_t) {self.type, NULL, NULL, NULL, NULL, NULL}
    : (the_any_t) {self.type, self.copy_cb(self.ctx), self.copy_cb, self.eq_cb, self.free_cb, self.str_cb};
}

bool the_any_eq (const the_any_t self, const the_any_t rhs) {
  if (self.ctx == NULL || rhs.ctx == NULL) {
    return self.ctx == rhs.ctx;
  } else if (self.type != rhs.type) {
    return false;
  }

  return self.eq_cb(self.ctx, rhs.ctx);
}

void the_any_free (the_any_t self) {
  if (self.ctx != NULL) self.free_cb(self.ctx);
}

bool the_any_ne (const the_any_t self, const the_any_t rhs) {
  if (self.ctx == NULL || rhs.ctx == NULL) {
    return self.ctx != rhs.ctx;
  } else if (self.type != rhs.type) {
    return true;
  }

  return !self.eq_cb(self.ctx, rhs.ctx);
}

the_any_t the_any_realloc (the_any_t self, const the_any_t rhs) {
  the_any_free(self);
  return the_any_copy(rhs);
}

the_str_t the_any_str (const the_any_t self) {
  return self.ctx == NULL ? the_str_alloc(L"any") : self.str_cb(self.ctx);
}
