/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_ARRAY_MACRO_H
#define THE_ARRAY_MACRO_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/error-type.h>
#include <the/fn-macro.h>
#include <stdarg.h>
#include <stdint.h>

// todo documentation

#define THE_ARRAY_DECLARE(underlying_type_name, underlying_type) \
  THE_FUNCTION_DECLARE_WITH_PARAMS(s, bool, FP3##underlying_type_name, { \
    the_err_state_t *state; \
    int line; \
    int col; \
    underlying_type n0; \
  }) \
  \
  THE_FUNCTION_DECLARE_WITH_PARAMS(s, void, FP3##underlying_type_name##FP3int, { \
    the_err_state_t *state; \
    int line; \
    int col; \
    underlying_type n0; \
    int32_t n1; \
  }) \
  \
  THE_FUNCTION_DECLARE_WITH_PARAMS(s, int, FP3##underlying_type_name##FP3##underlying_type_name, { \
    the_err_state_t *state; \
    int line; \
    int col; \
    underlying_type n0; \
    underlying_type n1; \
  }) \
  \
  typedef struct { \
    underlying_type *data; \
    size_t len; \
  } the_arr_##underlying_type_name##_t; \
  \
  the_arr_##underlying_type_name##_t the_arr_##underlying_type_name##_alloc (size_t length, ...); \
  underlying_type *the_arr_##underlying_type_name##_at (the_err_state_t *state, int line, int col, const the_arr_##underlying_type_name##_t self, int32_t index); \
  the_arr_##underlying_type_name##_t *the_arr_##underlying_type_name##_clear (the_arr_##underlying_type_name##_t *self); \
  the_arr_##underlying_type_name##_t the_arr_##underlying_type_name##_concat (const the_arr_##underlying_type_name##_t self, const the_arr_##underlying_type_name##_t other); \
  bool the_arr_##underlying_type_name##_contains (const the_arr_##underlying_type_name##_t self, underlying_type search); \
  the_arr_##underlying_type_name##_t the_arr_##underlying_type_name##_copy (const the_arr_##underlying_type_name##_t self); \
  bool the_arr_##underlying_type_name##_empty (const the_arr_##underlying_type_name##_t self); \
  bool the_arr_##underlying_type_name##_eq (const the_arr_##underlying_type_name##_t self, const the_arr_##underlying_type_name##_t rhs); \
  the_arr_##underlying_type_name##_t the_arr_##underlying_type_name##_filter (the_err_state_t *state, int line, int col, the_arr_##underlying_type_name##_t self, the_fn_sFP3##underlying_type_name##FRboolFE_t predicate); \
  underlying_type *the_arr_##underlying_type_name##_first (the_err_state_t *state, int line, int col, the_arr_##underlying_type_name##_t *self); \
  void the_arr_##underlying_type_name##_forEach (the_err_state_t *state, int line, int col, const the_arr_##underlying_type_name##_t self, the_fn_sFP3##underlying_type_name##FP3intFRvoidFE_t iterator); \
  void the_arr_##underlying_type_name##_free (the_arr_##underlying_type_name##_t self); \
  the_str_t the_arr_##underlying_type_name##_join (const the_arr_##underlying_type_name##_t self, unsigned char o1, the_str_t separator); \
  underlying_type *the_arr_##underlying_type_name##_last (the_err_state_t *state, int line, int col, the_arr_##underlying_type_name##_t *self); \
  the_arr_##underlying_type_name##_t *the_arr_##underlying_type_name##_merge (the_arr_##underlying_type_name##_t *self, const the_arr_##underlying_type_name##_t other); \
  bool the_arr_##underlying_type_name##_ne (const the_arr_##underlying_type_name##_t self, const the_arr_##underlying_type_name##_t rhs); \
  underlying_type the_arr_##underlying_type_name##_pop (the_arr_##underlying_type_name##_t *self); \
  void the_arr_##underlying_type_name##_push (the_arr_##underlying_type_name##_t *self, const the_arr_##underlying_type_name##_t elements); \
  the_arr_##underlying_type_name##_t the_arr_##underlying_type_name##_realloc (the_arr_##underlying_type_name##_t self, const the_arr_##underlying_type_name##_t rhs); \
  the_arr_##underlying_type_name##_t *the_arr_##underlying_type_name##_remove (the_err_state_t *state, int line, int col, the_arr_##underlying_type_name##_t *self, int32_t index); \
  the_arr_##underlying_type_name##_t the_arr_##underlying_type_name##_reverse (const the_arr_##underlying_type_name##_t self); \
  the_arr_##underlying_type_name##_t the_arr_##underlying_type_name##_slice (const the_arr_##underlying_type_name##_t self, unsigned int o1, int32_t start, unsigned int o2, int32_t end); \
  the_arr_##underlying_type_name##_t *the_arr_##underlying_type_name##_sort (the_err_state_t *state, int line, int col, the_arr_##underlying_type_name##_t *self, the_fn_sFP3##underlying_type_name##FP3##underlying_type_name##FRintFE_t comparator); \
  the_str_t the_arr_##underlying_type_name##_str (const the_arr_##underlying_type_name##_t self);

#endif
