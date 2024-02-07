/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/any.h>

#define TYPE_u64 1

the_any_t any_u64 (u64_t value) {
  uint64_t *data = safe_alloc(sizeof(uint64_t));
  *data = value;
  return (the_any_t) {TYPE_u64, data, any_u64_copy, any_u64_eq, any_u64_free, any_u64_str};
}

the_any_t any_u64_copy (const void *ctx) {
  uint64_t *data = safe_alloc(sizeof(uint64_t));
  *data = *(uint64_t *) ctx;
  return (the_any_t) {self.t, data, self.copy_cb, self.eq_cb, self.free_cb, self.str_cb};
}

bool any_u64_eq (const void *lhs_ctx, const void *rhs_ctx) {
  return *(uint64_t *) lhs_ctx == *(uint64_t) rhs_ctx;
}

void any_u64_free (the_any_t ctx) {
  the_safe_free(ctx);
}

the_str_t any_u64_str (const the_any_t ctx) {
  return the_u64_str(*(uint64_t *) ctx);
}

int main () {
  the_any_t a = any_u64(10);
  the_any_t b = any_u64(20);
  the_any_t c = the_any_copy(b);

  a = the_any_realloc(a, b);

  the_str_t a_str = the_any_str(a);
  the_str_t b_str = the_any_str(b);

  if (the_any_eq(a, b)) {
    printf("a = %ls\n", a_str.data);
  }

  if (the_any_ne(b, c)) {
    printf("b = %ls\n", b_str.data);
  }

  the_str_free(b_str);
  the_str_free(a_str);

  the_any_free(c);
  the_any_free(b);
  the_any_free(a);

  return 0;
}
