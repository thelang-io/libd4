/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_FN_H
#define THE_FN_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/fn-macro.h>
#include <string.h>

// todo test
#define THE_FUNCTION_DEFINE(type_name, return_type) \
  the_##type_name##_t the_##type_name##_alloc (const the_str_t name, the_##type_name##_func func, void *ctx, the_fn_copy_cb copy_cb, the_fn_free_cb free_cb) { \
    return (the_##type_name##_t) {name, func, ctx, copy_cb, free_cb}; \
  } \
  \
  the_##type_name##_t the_##type_name##_copy (const the_##type_name##_t self) { \
    return self.ctx == NULL \
      ? (the_##type_name##_t) {the_str_copy(self.name), self.func, self.copy_cb(self.ctx), self.copy_cb, self.free_cb} \
      : (the_##type_name##_t) {the_str_copy(self.name), self.func, NULL, NULL, NULL}; \
  } \
  \
  void the_##type_name##_free (the_##type_name##_t self) { \
    if (self.ctx != NULL) self.free_cb(self.ctx); \
    the_str_free(self.name); \
  } \
  \
  bool the_##type_name##_eq (const the_##type_name##_t self, const the_##type_name##_t rhs) { \
    return self.func == rhs.func; \
  } \
  \
  the_##type_name##_t the_##type_name##_realloc (the_##type_name##_t self, const the_##type_name##_t rhs) { \
    the_##type_name##_free(self); \
    return the_##type_name##_copy(rhs); \
  } \
  \
  the_str_t the_##type_name##_str (const the_##type_name##_t self) { \
    return the_str_copy(self.name); \
  }

/**
 * Function to be used with function context object that has no properties to free.
 * @param ctx Context of the function.
 */
void the_fn_ctx_free_generic (void *ctx);

#endif
