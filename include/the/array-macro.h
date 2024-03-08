/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_ARRAY_MACRO_H
#define THE_ARRAY_MACRO_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/error.h>
#include <the/safe.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>

#define THE_DECLARE_ARRAY(type_name, underlying_type) \
  typedef struct { \
    underlying_type *data; \
    size_t len; \
  } the_##type_name##_t; \
  \
  the_##type_name##_t the_##type_name##_alloc (size_t length, ...); \
  underlying_type *the_##type_name##_at (the_err_state_t *state, int line, int col, the_##type_name##_t self, int32_t index); \
  the_##type_name##_t *the_##type_name##_clear (the_##type_name##_t *self); \
  the_##type_name##_t the_##type_name##_concat (the_##type_name##_t self, the_##type_name##_t other); \
  bool the_##type_name##_contains (the_##type_name##_t self, underlying_type search); \
  the_##type_name##_t the_##type_name##_copy (const the_##type_name##_t self); \
  bool the_##type_name##_empty (the_##type_name##_t self); \
  bool the_##type_name##_eq (the_##type_name##_t self, the_##type_name##_t rhs); \
  underlying_type *the_##type_name##_first (the_err_state_t *state, int line, int col, the_##type_name##_t *self); \
  void the_##type_name##_free (the_##type_name##_t self); \
  the_str_t the_##type_name##_join (the_##type_name##_t self, unsigned char o1, the_str_t separator); \
  underlying_type *the_##type_name##_last (the_err_state_t *state, int line, int col, the_##type_name##_t *self); \
  the_##type_name##_t *the_##type_name##_merge (the_##type_name##_t *self, the_##type_name##_t other); \
  bool the_##type_name##_ne (the_##type_name##_t self, the_##type_name##_t rhs); \
  underlying_type the_##type_name##_pop (the_##type_name##_t *self); \
  void the_##type_name##_push (the_##type_name##_t *self, the_##type_name##_t elements); \
  the_##type_name##_t the_##type_name##_realloc (the_##type_name##_t self, the_##type_name##_t rhs); \
  the_##type_name##_t *the_##type_name##_remove (the_err_state_t *state, int line, int col, the_##type_name##_t *self, int32_t index); \
  the_##type_name##_t the_##type_name##_reverse (the_##type_name##_t self); \
  the_##type_name##_t the_##type_name##_slice (the_##type_name##_t self, unsigned int o1, int32_t start, unsigned int o2, int32_t end); \
  the_str_t the_##type_name##_str (the_##type_name##_t self);

THE_DECLARE_ARRAY(arr_str, the_str_t)

#endif
