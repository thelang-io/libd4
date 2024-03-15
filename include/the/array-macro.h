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

#define THE_ARRAY_DECLARE(element_type_name, element_type) \
  THE_FUNCTION_DECLARE_WITH_PARAMS(s, bool, bool, FP3##element_type_name, { \
    the_err_state_t *state; \
    int line; \
    int col; \
    element_type n0; \
  }) \
  \
  THE_FUNCTION_DECLARE_WITH_PARAMS(s, void, void, FP3##element_type_name##FP3int, { \
    the_err_state_t *state; \
    int line; \
    int col; \
    element_type n0; \
    int32_t n1; \
  }) \
  \
  THE_FUNCTION_DECLARE_WITH_PARAMS(s, i32, int32_t, FP3##element_type_name##FP3##element_type_name, { \
    the_err_state_t *state; \
    int line; \
    int col; \
    element_type n0; \
    element_type n1; \
  }) \
  \
  typedef element_type (*the_arr_##element_type_name##_copy_cb) (const element_type ctx); \
  \
  typedef bool (*the_arr_##element_type_name##_eq_cb) (const element_type lhs_ctx, const element_type rhs_ctx); \
  \
  typedef void (*the_arr_##element_type_name##_free_cb) (element_type ctx); \
  \
  typedef the_str_t (*the_arr_##element_type_name##_str_cb) (const element_type ctx); \
  \
  typedef struct { \
    element_type *data; \
    size_t len; \
    the_arr_##element_type_name##_copy_cb copy_cb; \
    the_arr_##element_type_name##_eq_cb eq_cb; \
    the_arr_##element_type_name##_free_cb free_cb; \
    the_arr_##element_type_name##_str_cb str_cb; \
  } the_arr_##element_type_name##_t; \
  \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_alloc (size_t length, ...); \
  element_type *the_arr_##element_type_name##_at (the_err_state_t *state, int line, int col, const the_arr_##element_type_name##_t self, int32_t index); \
  the_arr_##element_type_name##_t *the_arr_##element_type_name##_clear (the_arr_##element_type_name##_t *self); \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_concat (const the_arr_##element_type_name##_t self, const the_arr_##element_type_name##_t other); \
  bool the_arr_##element_type_name##_contains (const the_arr_##element_type_name##_t self, const element_type search); \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_copy (const the_arr_##element_type_name##_t self); \
  bool the_arr_##element_type_name##_empty (const the_arr_##element_type_name##_t self); \
  bool the_arr_##element_type_name##_eq (const the_arr_##element_type_name##_t self, const the_arr_##element_type_name##_t rhs); \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_filter (the_err_state_t *state, int line, int col, const the_arr_##element_type_name##_t self, const the_fn_sFP3##element_type_name##FRboolFE_t predicate); \
  element_type *the_arr_##element_type_name##_first (the_err_state_t *state, int line, int col, the_arr_##element_type_name##_t *self); \
  void the_arr_##element_type_name##_forEach (the_err_state_t *state, int line, int col, const the_arr_##element_type_name##_t self, const the_fn_sFP3##element_type_name##FP3intFRvoidFE_t iterator); \
  void the_arr_##element_type_name##_free (the_arr_##element_type_name##_t self); \
  the_str_t the_arr_##element_type_name##_join (const the_arr_##element_type_name##_t self, unsigned char o1, const the_str_t separator); \
  element_type *the_arr_##element_type_name##_last (the_err_state_t *state, int line, int col, the_arr_##element_type_name##_t *self); \
  the_arr_##element_type_name##_t *the_arr_##element_type_name##_merge (the_arr_##element_type_name##_t *self, const the_arr_##element_type_name##_t other); \
  bool the_arr_##element_type_name##_ne (const the_arr_##element_type_name##_t self, const the_arr_##element_type_name##_t rhs); \
  element_type the_arr_##element_type_name##_pop (the_arr_##element_type_name##_t *self); \
  void the_arr_##element_type_name##_push (the_arr_##element_type_name##_t *self, const the_arr_##element_type_name##_t elements); \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_realloc (the_arr_##element_type_name##_t self, const the_arr_##element_type_name##_t rhs); \
  the_arr_##element_type_name##_t *the_arr_##element_type_name##_remove (the_err_state_t *state, int line, int col, the_arr_##element_type_name##_t *self, int32_t index); \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_reverse (const the_arr_##element_type_name##_t self); \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_slice (const the_arr_##element_type_name##_t self, unsigned int o1, int32_t start, unsigned int o2, int32_t end); \
  the_arr_##element_type_name##_t *the_arr_##element_type_name##_sort (the_err_state_t *state, int line, int col, the_arr_##element_type_name##_t *self, const the_fn_sFP3##element_type_name##FP3##element_type_name##FRintFE_t comparator); \
  the_str_t the_arr_##element_type_name##_str (const the_arr_##element_type_name##_t self);

#endif
