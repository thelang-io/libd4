/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_ARRAY_H
#define D4_ARRAY_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include <d4/error.h>
#include <d4/fn.h>
#include <inttypes.h>
#include <string.h>

/**
 * Macro that can be used to define an array object.
 * @param element_type_name Type name of the element.
 * @param element_type Element type of the array object.
 * @param alloc_element_type Element type of the array object to be used inside variadic argument (cast to int in some cases).
 * @param copy_block Block that is used for copy method of array object.
 * @param eq_block Block that is used for equals method of array object.
 * @param free_block Block that is used for free method of array object.
 * @param str_block Block that is used for str method of array object.
 */
#define D4_ARRAY_DEFINE(element_type_name, element_type, alloc_element_type, copy_block, eq_block, free_block, str_block) \
  D4_FUNCTION_DEFINE_WITH_PARAMS(es, bool, bool, FP3##element_type_name) \
  D4_FUNCTION_DEFINE_WITH_PARAMS(es, void, void, FP3##element_type_name##FP3int) \
  D4_FUNCTION_DEFINE_WITH_PARAMS(es, int, int32_t, FP3##element_type_name##FP3##element_type_name) \
  \
  d4_arr_##element_type_name##_t d4_arr_##element_type_name##_alloc (size_t length, ...) { \
    element_type *data; \
    va_list args; \
    if (length == 0) return (d4_arr_##element_type_name##_t) {NULL, 0}; \
    data = d4_safe_alloc(length * sizeof(element_type)); \
    va_start(args, length); \
    for (size_t i = 0; i < length; i++) { \
      const element_type element = va_arg(args, alloc_element_type); \
      data[i] = copy_block; \
    } \
    va_end(args); \
    return (d4_arr_##element_type_name##_t) {data, length}; \
  } \
  \
  element_type *d4_arr_##element_type_name##_at (d4_err_state_t *state, int line, int col, const d4_arr_##element_type_name##_t self, int32_t index) { \
    if ((index >= 0 && (size_t) index >= self.len) || (index < 0 && index < -((int32_t) self.len))) { \
      d4_str_t message = d4_str_alloc(L"index %" PRId32 L" out of array bounds", index); \
      d4_error_assign_generic(state, line, col, message); \
      d4_str_free(message); \
      longjmp(state->buf_last->buf, state->id); \
    } \
    return index < 0 ? &self.data[self.len + index] : &self.data[index]; \
  } \
  \
  d4_arr_##element_type_name##_t *d4_arr_##element_type_name##_clear (d4_arr_##element_type_name##_t *self) { \
    d4_arr_##element_type_name##_free(*self); \
    self->data = NULL; \
    self->len = 0; \
    return self; \
  } \
  \
  d4_arr_##element_type_name##_t d4_arr_##element_type_name##_concat (const d4_arr_##element_type_name##_t self, const d4_arr_##element_type_name##_t other) { \
    size_t len = self.len + other.len; \
    element_type *data = d4_safe_alloc(len * sizeof(element_type)); \
    size_t k = 0; \
    for (size_t i = 0; i < self.len; i++) { \
      const element_type element = self.data[i]; \
      data[k++] = copy_block; \
    } \
    for (size_t i = 0; i < other.len; i++) { \
      const element_type element = other.data[i]; \
      data[k++] = copy_block; \
    } \
    return (d4_arr_##element_type_name##_t) {data, len}; \
  } \
  \
  bool d4_arr_##element_type_name##_contains (const d4_arr_##element_type_name##_t self, const element_type search) { \
    const element_type rhs_element = search; \
    for (size_t i = 0; i < self.len; i++) { \
      const element_type lhs_element = self.data[i]; \
      if (eq_block) return true; \
    } \
    return false; \
  } \
  \
  d4_arr_##element_type_name##_t d4_arr_##element_type_name##_copy (const d4_arr_##element_type_name##_t self) { \
    element_type *data; \
    if (self.len == 0) return (d4_arr_##element_type_name##_t) {NULL, 0}; \
    data = d4_safe_alloc(self.len * sizeof(element_type)); \
    for (size_t i = 0; i < self.len; i++) { \
      const element_type element = self.data[i]; \
      data[i] = copy_block; \
    } \
    return (d4_arr_##element_type_name##_t) {data, self.len}; \
  } \
  \
  bool d4_arr_##element_type_name##_empty (const d4_arr_##element_type_name##_t self) { \
    return self.len == 0; \
  } \
  \
  bool d4_arr_##element_type_name##_eq (const d4_arr_##element_type_name##_t self, const d4_arr_##element_type_name##_t rhs) { \
    if (self.len != rhs.len) return false; \
    for (size_t i = 0; i < self.len; i++) { \
      const element_type lhs_element = self.data[i]; \
      const element_type rhs_element = rhs.data[i]; \
      if (!(eq_block)) return false; \
    } \
    return true; \
  } \
  \
  d4_arr_##element_type_name##_t d4_arr_##element_type_name##_filter (d4_err_state_t *state, int line, int col, const d4_arr_##element_type_name##_t self, const d4_fn_esFP3##element_type_name##FRboolFE_t predicate) { \
    size_t len = 0; \
    element_type *data = d4_safe_alloc(self.len * sizeof(element_type)); \
    for (size_t i = 0; i < self.len; i++) { \
      void *params = d4_safe_calloc( \
        &(d4_fn_esFP3##element_type_name##FRboolFE_params_t) {state, line, col, self.data[i]}, \
        sizeof(d4_fn_esFP3##element_type_name##FRboolFE_params_t) \
      ); \
      if (predicate.func(predicate.ctx, params)) { \
        const element_type element = self.data[i]; \
        data[len++] = copy_block; \
      } \
      d4_safe_free(params); \
    } \
    return (d4_arr_##element_type_name##_t) {data, len}; \
  } \
  \
  element_type *d4_arr_##element_type_name##_first (d4_err_state_t *state, int line, int col, d4_arr_##element_type_name##_t *self) { \
    if (self->len == 0) { \
      d4_str_t message = d4_str_alloc(L"tried getting first element of empty array"); \
      d4_error_assign_generic(state, line, col, message); \
      d4_str_free(message); \
      longjmp(state->buf_last->buf, state->id); \
    } \
    return &self->data[0]; \
  } \
  \
  void d4_arr_##element_type_name##_forEach (d4_err_state_t *state, int line, int col, const d4_arr_##element_type_name##_t self, const d4_fn_esFP3##element_type_name##FP3intFRvoidFE_t iterator) { \
    for (size_t i = 0; i < self.len; i++) { \
      void *params = d4_safe_calloc( \
        &(d4_fn_esFP3##element_type_name##FP3intFRvoidFE_params_t) {state, line, col, self.data[i], i}, \
        sizeof(d4_fn_esFP3##element_type_name##FP3intFRvoidFE_params_t) \
      ); \
      iterator.func(iterator.ctx, params); \
      d4_safe_free(params); \
    } \
  } \
  \
  void d4_arr_##element_type_name##_free (d4_arr_##element_type_name##_t self) { \
    for (size_t i = 0; i < self.len; i++) { \
      element_type element = self.data[i]; \
      free_block; \
    } \
    if (self.data != NULL) d4_safe_free(self.data); \
  } \
  \
  d4_str_t d4_arr_##element_type_name##_join (const d4_arr_##element_type_name##_t self, unsigned char o1, const d4_str_t separator) { \
    d4_str_t x = o1 == 0 ? d4_str_alloc(L",") : separator; \
    d4_str_t result = (d4_str_t) {NULL, 0, false}; \
    d4_str_t t1; \
    d4_str_t t2; \
    for (size_t i = 0; i < self.len; i++) { \
      const element_type element = self.data[i]; \
      if (i != 0) { \
        result = d4_str_realloc(result, t1 = d4_str_concat(result, x)); \
        d4_str_free(t1); \
      } \
      result = d4_str_realloc(result, t1 = d4_str_concat(result, t2 = str_block)); \
      d4_str_free(t1); \
      d4_str_free(t2); \
    } \
    if (o1 == 0) d4_str_free(x); \
    return result; \
  } \
  \
  element_type *d4_arr_##element_type_name##_last (d4_err_state_t *state, int line, int col, d4_arr_##element_type_name##_t *self) { \
    if (self->len == 0) { \
      d4_str_t message = d4_str_alloc(L"tried getting last element of empty array"); \
      d4_error_assign_generic(state, line, col, message); \
      d4_str_free(message); \
      longjmp(state->buf_last->buf, state->id); \
    } \
    return &self->data[self->len - 1]; \
  } \
  \
  d4_arr_##element_type_name##_t *d4_arr_##element_type_name##_merge (d4_arr_##element_type_name##_t *self, const d4_arr_##element_type_name##_t other) { \
    size_t k = self->len; \
    self->len += other.len; \
    self->data = d4_safe_realloc(self->data, self->len * sizeof(element_type)); \
    for (size_t i = 0; i < other.len; i++) { \
      const element_type element = other.data[i]; \
      self->data[k++] = copy_block; \
    } \
    return self; \
  } \
  \
  element_type d4_arr_##element_type_name##_pop (d4_arr_##element_type_name##_t *self) { \
    self->len--; \
    return self->data[self->len]; \
  } \
  \
  void d4_arr_##element_type_name##_push (d4_arr_##element_type_name##_t *self, size_t length, ...) { \
    va_list args; \
    if (length == 0) return; \
    self->len += length; \
    self->data = d4_safe_realloc(self->data, self->len * sizeof(element_type)); \
    va_start(args, length); \
    for (size_t i = self->len - length; i < self->len; i++) { \
      const element_type element = va_arg(args, alloc_element_type); \
      self->data[i] = copy_block; \
    } \
    va_end(args); \
  } \
  \
  d4_arr_##element_type_name##_t d4_arr_##element_type_name##_realloc (d4_arr_##element_type_name##_t self, const d4_arr_##element_type_name##_t rhs) { \
    d4_arr_##element_type_name##_free(self); \
    return d4_arr_##element_type_name##_copy(rhs); \
  } \
  \
  d4_arr_##element_type_name##_t *d4_arr_##element_type_name##_remove (d4_err_state_t *state, int line, int col, d4_arr_##element_type_name##_t *self, int32_t index) { \
    size_t i; \
    element_type element; \
    if ((index >= 0 && (size_t) index >= self->len) || (index < 0 && index < -((int32_t) self->len))) { \
      d4_str_t message = d4_str_alloc(L"index %" PRId32 " out of array bounds", index); \
      d4_error_assign_generic(state, line, col, message); \
      d4_str_free(message); \
      longjmp(state->buf_last->buf, state->id); \
    } \
    i = index < 0 ? (size_t) (index + (int32_t) self->len) : (size_t) index; \
    element = self->data[i]; \
    free_block; \
    if (i != self->len - 1) { \
      memmove(&self->data[i], &self->data[i + 1], (--self->len - i) * sizeof(element_type)); \
    } else { \
      self->len--; \
    } \
    return self; \
  } \
  \
  d4_arr_##element_type_name##_t d4_arr_##element_type_name##_reverse (const d4_arr_##element_type_name##_t self) { \
    element_type *data; \
    if (self.len == 0) { \
      return (d4_arr_##element_type_name##_t) {NULL, 0}; \
    } \
    data = d4_safe_alloc(self.len * sizeof(element_type)); \
    for (size_t i = 0; i < self.len; i++) { \
      const element_type element = self.data[i]; \
      data[self.len - i - 1] = copy_block; \
    } \
    return (d4_arr_##element_type_name##_t) {data, self.len}; \
  } \
  \
  d4_arr_##element_type_name##_t d4_arr_##element_type_name##_slice (const d4_arr_##element_type_name##_t self, unsigned int o1, int32_t start, unsigned int o2, int32_t end) { \
    int32_t i = 0; \
    int32_t j = 0; \
    element_type *data; \
    size_t len; \
    if (o1 != 0 && start < 0 && start >= -((int32_t) self.len)) { \
      i = (int32_t) ((size_t) start + self.len); \
    } else if (o1 != 0 && start >= 0) { \
      i = (int32_t) ((size_t) start > self.len ? self.len : (size_t) start); \
    } \
    if (o2 == 0 || (end >= 0 && (size_t) end > self.len)) { \
      j = (int32_t) self.len; \
    } else if (end < 0 && end >= -((int32_t) self.len)) { \
      j = (int32_t) ((size_t) end + self.len); \
    } else if (end >= 0) { \
      j = (int32_t) end; \
    } \
    if (i > j || (size_t) i >= self.len) { \
      return (d4_arr_##element_type_name##_t) {NULL, 0}; \
    } \
    len = j - i; \
    data = d4_safe_alloc(len * sizeof(element_type)); \
    for (size_t k = 0; i < j; i++) { \
      const element_type element = self.data[i]; \
      data[k++] = copy_block; \
    } \
    return (d4_arr_##element_type_name##_t) {data, len}; \
  } \
  \
  d4_arr_##element_type_name##_t *d4_arr_##element_type_name##_sort (d4_err_state_t *state, int line, int col, d4_arr_##element_type_name##_t *self, const d4_fn_esFP3##element_type_name##FP3##element_type_name##FRintFE_t comparator) { \
    if (self->len <= 1) return self; \
    while (1) { \
      unsigned char b = 0; \
      for (size_t i = 1; i < self->len; i++) { \
        void *params = d4_safe_calloc( \
          &(d4_fn_esFP3##element_type_name##FP3##element_type_name##FRintFE_params_t) {state, line, col, self->data[i - 1], self->data[i]}, \
          sizeof(d4_fn_esFP3##element_type_name##FP3##element_type_name##FRintFE_params_t) \
        ); \
        int32_t c = comparator.func(comparator.ctx, params); \
        if (c > 0) { \
          element_type t = self->data[i]; \
          self->data[i] = self->data[i - 1]; \
          self->data[i - 1] = t; \
          b = 1; \
        } \
        d4_safe_free(params); \
      } \
      if (b == 0) return self; \
    } \
  } \
  \
  d4_str_t d4_arr_##element_type_name##_str (const d4_arr_##element_type_name##_t self) { \
    d4_str_t t1; \
    d4_str_t t2; \
    d4_str_t b = d4_str_alloc(L"]"); \
    d4_str_t c = d4_str_alloc(L", "); \
    d4_str_t r = d4_str_alloc(L"["); \
    for (size_t i = 0; i < self.len; i++) { \
      const element_type element = self.data[i]; \
      if (i != 0) { \
        r = d4_str_realloc(r, t1 = d4_str_concat(r, c)); \
        d4_str_free(t1); \
      } \
      r = d4_str_realloc(r, t1 = d4_str_concat(r, t2 = str_block)); \
      d4_str_free(t1); \
      d4_str_free(t2); \
    } \
    r = d4_str_realloc(r, t1 = d4_str_concat(r, b)); \
    d4_str_free(t1); \
    d4_str_free(b); \
    d4_str_free(c); \
    return r; \
  }

#endif
