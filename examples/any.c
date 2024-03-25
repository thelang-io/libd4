/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/any.h>
#include <the/number.h>
#include <the/safe.h>
#include <the/string.h>

#define TYPE_u64 1

// todo implement generator
//THE_ANY_DEFINE(u64, uint64_t, {
//  uint64_t *data = the_safe_alloc(sizeof(uint64_t));
//  *data = value;
//  return (the_any_t) {TYPE_u64, data, any_u64_copy, any_u64_eq, any_u64_free, any_u64_str};
//}, {
//  uint64_t *data = the_safe_alloc(sizeof(uint64_t));
//  *data = *(const uint64_t *) ctx;
//  return data;
//}, {
//  return *(const uint64_t *) lhs_ctx == *(const uint64_t *) rhs_ctx;
//}, {
//  the_safe_free(ctx);
//}, {
//  return the_u64_str(*(const uint64_t *) ctx);
//})

the_any_t any_u64 (uint64_t value);
void *any_u64_copy (const void *ctx);
bool any_u64_eq (const void *lhs_ctx, const void *rhs_ctx);
void any_u64_free (void *ctx);
the_str_t any_u64_str (const void *ctx);

the_any_t any_u64 (uint64_t value) {
  uint64_t *data = the_safe_alloc(sizeof(uint64_t));
  *data = value;
  return (the_any_t) {TYPE_u64, data, any_u64_copy, any_u64_eq, any_u64_free, any_u64_str};
}

void *any_u64_copy (const void *ctx) {
  uint64_t *data = the_safe_alloc(sizeof(uint64_t));
  *data = *(const uint64_t *) ctx;
  return data;
}

bool any_u64_eq (const void *lhs_ctx, const void *rhs_ctx) {
  return *(const uint64_t *) lhs_ctx == *(const uint64_t *) rhs_ctx;
}

void any_u64_free (void *ctx) {
  the_safe_free(ctx);
}

the_str_t any_u64_str (const void *ctx) {
  return the_u64_str(*(const uint64_t *) ctx);
}

int main (void) {
  the_any_t a = any_u64(10);
  the_any_t b = any_u64(20);
  the_any_t c = the_any_copy(b);

  the_str_t a_str;
  the_str_t b_str;

  a = the_any_realloc(a, b);

  a_str = the_any_str(a);
  b_str = the_any_str(b);

  if (the_any_eq(a, b)) {
    wprintf(L"a = %ls\n", a_str.data);
  }

  the_str_free(b_str);
  the_str_free(a_str);

  the_any_free(c);
  the_any_free(b);
  the_any_free(a);

  return 0;
}
