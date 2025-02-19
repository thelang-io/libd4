/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_FN_H
#define D4_FN_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include "safe.h"
#include "string.h"

/**
 * Macro that can be used to define a function object without parameters.
 * @param prefix Function prefix can be one of: a (asynchronous) and s (synchronous).
 * @param return_type_name Name of the function return type.
 * @param return_type Function return type.
 */
#define D4_FUNCTION_DEFINE(prefix, return_type_name, return_type) \
  D4_FUNCTION_DEFINE_BASE(return_type, fn_##prefix##FR##return_type_name##FE)

/**
 * Macro that can be used to define a function object with parameters.
 * @param prefix Function prefix can be one of: a (asynchronous) and s (synchronous).
 * @param return_type_name Name of the function return type.
 * @param return_type Function return type.
 * @param params_declaration Declaration of parameters to be used to construct function name.
 */
#define D4_FUNCTION_DEFINE_WITH_PARAMS(prefix, return_type_name, return_type, params_declaration) \
  D4_FUNCTION_DEFINE_BASE(return_type, fn_##prefix##params_declaration##FR##return_type_name##FE)

/**
 * Macro that is used internally to define function object.
 * @param return_type Function return type.
 * @param type_name Generated name of the function type.
 */
#define D4_FUNCTION_DEFINE_BASE(return_type, type_name) \
  d4_##type_name##_t d4_##type_name##_alloc (const d4_str_t name, void *ctx, d4_fn_copy_cb copy_cb, d4_fn_free_cb free_cb, d4_##type_name##_func func) { \
    return (d4_##type_name##_t) {d4_str_copy(name), ctx, copy_cb, free_cb, func}; \
  } \
  \
  d4_##type_name##_t d4_##type_name##_copy (const d4_##type_name##_t self) { \
    return self.ctx == NULL \
      ? (d4_##type_name##_t) {d4_str_copy(self.name), NULL, NULL, NULL, self.func} \
      : (d4_##type_name##_t) {d4_str_copy(self.name), self.copy_cb(self.ctx), self.copy_cb, self.free_cb, self.func}; \
  } \
  \
  bool d4_##type_name##_eq (const d4_##type_name##_t self, const d4_##type_name##_t rhs) { \
    return self.func == rhs.func; \
  } \
  \
  void d4_##type_name##_free (d4_##type_name##_t self) { \
    if (self.ctx != NULL && self.free_cb != NULL) self.free_cb(self.ctx); \
    d4_str_free(self.name); \
  } \
  \
  d4_##type_name##_t d4_##type_name##_realloc (d4_##type_name##_t self, const d4_##type_name##_t rhs) { \
    d4_##type_name##_free(self); \
    return d4_##type_name##_copy(rhs); \
  } \
  \
  d4_str_t d4_##type_name##_str (const d4_##type_name##_t self) { \
    return d4_str_copy(self.name); \
  }

#endif
