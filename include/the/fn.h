/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_FN_H
#define THE_FN_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/safe.h>
#include <the/string.h>

// todo test

/** Macro that can be used to define a function object without parameters. */
#define THE_FUNCTION_DEFINE(prefix, return_type) \
  THE_FUNCTION_DEFINE_BASE(return_type, fn_##prefix##FR##return_type##FE)

/** Macro that can be used to define a function object with parameters. */
#define THE_FUNCTION_DEFINE_WITH_PARAMS(prefix, return_type, params_declaration) \
  THE_FUNCTION_DEFINE_BASE(return_type, fn_##prefix##params_declaration##FR##return_type##FE)

/** Macro that is used internally to define function object. */
#define THE_FUNCTION_DEFINE_BASE(return_type, type_name) \
  the_##type_name##_t the_##type_name##_alloc (const the_str_t name, void *ctx, the_fn_copy_cb copy_cb, the_fn_free_cb free_cb, the_##type_name##_func func) { \
    return (the_##type_name##_t) {name, ctx, copy_cb, free_cb, func}; \
  } \
  \
  the_##type_name##_t the_##type_name##_copy (const the_##type_name##_t self) { \
    return self.ctx == NULL \
      ? (the_##type_name##_t) {the_str_copy(self.name), self.copy_cb(self.ctx), self.copy_cb, self.free_cb, self.func} \
      : (the_##type_name##_t) {the_str_copy(self.name), NULL, NULL, NULL, self.func}; \
  } \
  \
  void the_##type_name##_free (the_##type_name##_t self) { \
    if (self.ctx != NULL && self.free_cb != NULL) self.free_cb(self.ctx); \
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

#endif
