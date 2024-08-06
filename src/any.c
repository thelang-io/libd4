/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "any.h"
#include <d4/string.h>

d4_any_t d4_any_copy (const d4_any_t self) {
  return self.ctx == NULL
    ? (d4_any_t) {self.type, NULL, NULL, NULL, NULL, NULL}
    : (d4_any_t) {self.type, self.copy_cb(self.ctx), self.copy_cb, self.eq_cb, self.free_cb, self.str_cb};
}

bool d4_any_eq (const d4_any_t self, const d4_any_t rhs) {
  if (self.ctx == NULL || rhs.ctx == NULL) {
    return self.ctx == rhs.ctx;
  } else if (self.type != rhs.type) {
    return false;
  }

  return self.eq_cb(self.ctx, rhs.ctx);
}

void d4_any_free (d4_any_t self) {
  if (self.ctx != NULL) self.free_cb(self.ctx);
}

d4_any_t d4_any_realloc (d4_any_t self, const d4_any_t rhs) {
  d4_any_free(self);
  return d4_any_copy(rhs);
}

d4_str_t d4_any_str (const d4_any_t self) {
  return self.ctx == NULL ? d4_str_alloc(L"any") : self.str_cb(self.ctx);
}
