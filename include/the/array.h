/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_ARRAY_H
#define THE_ARRAY_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/error.h>
#include <the/fn.h>
#include <inttypes.h>

// todo test
// todo check all params have correct "const" in definition

#define THE_ARRAY_DEFINE(element_type_name, element_type) \
  THE_FUNCTION_DEFINE_WITH_PARAMS(s, bool, bool, FP3##element_type_name) \
  THE_FUNCTION_DEFINE_WITH_PARAMS(s, void, void, FP3##element_type_name##FP3int) \
  THE_FUNCTION_DEFINE_WITH_PARAMS(s, i32, int32_t, FP3##element_type_name##FP3##element_type_name) \
  \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_alloc (size_t length, ...) { \
    element_type *data; \
    va_list args; \
    if (length == 0) return (the_arr_##element_type_name##_t) {NULL, 0, NULL, NULL, NULL, NULL}; /* todo pass functions */ \
    data = the_safe_alloc(length * sizeof(element_type)); \
    va_start(args, length); \
    for (size_t i = 0; i < length; i++) { \
      data[i] = va_arg(args, element_type); \
    } \
    va_end(args); \
    return (the_arr_##element_type_name##_t) {data, length, NULL, NULL, NULL, NULL}; /* todo */ \
  } \
  \
  element_type *the_arr_##element_type_name##_at (the_err_state_t *state, int line, int col, const the_arr_##element_type_name##_t self, int32_t index) { \
    if ((index >= 0 && (size_t) index >= self.len) || (index < 0 && index < -((int32_t) self.len))) { \
      the_str_t message = the_str_alloc(L"index %" PRId32 L" out of array bounds", index); \
      the_error_assign_generic(state, line, col, message); \
      the_str_free(message); \
      longjmp(state->buf_last->buf, state->id); \
    } \
    return index < 0 ? &self.data[self.len + index] : &self.data[index]; \
  } \
  \
  the_arr_##element_type_name##_t *the_arr_##element_type_name##_clear (the_arr_##element_type_name##_t *self) { \
    the_arr_##element_type_name##_free(*self); \
    self->data = NULL; \
    self->len = 0; \
    return self; \
  } \
  \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_concat (const the_arr_##element_type_name##_t self, const the_arr_##element_type_name##_t other) { \
    size_t len = self.len + other.len; \
    element_type *data = the_safe_alloc(len * sizeof(element_type)); \
    size_t k = 0; \
    for (size_t i = 0; i < self.len; i++) data[k++] = self.copy_cb == NULL ? self.data[i] : self.copy_cb(self.data[i]); \
    for (size_t i = 0; i < other.len; i++) data[k++] = other.copy_cb == NULL ? other.data[i] : other.copy_cb(other.data[i]); \
    return (the_arr_##element_type_name##_t) {data, len, self.copy_cb, self.eq_cb, self.free_cb, self.str_cb}; \
  } \
  \
  bool the_arr_##element_type_name##_contains (const the_arr_##element_type_name##_t self, const element_type search) { \
    for (size_t i = 0; i < self.len; i++) { \
      /* if (self.eq_cb == NULL ? self.data[i] == search : self.eq_cb(self.data[i], search)) { todo */ \
        (void) search; /* todo remove */ \
        return true; \
      /* } */ \
    } \
    return false; \
  } \
  \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_copy (const the_arr_##element_type_name##_t self) { \
    element_type *data; \
    if (self.len == 0) return (the_arr_##element_type_name##_t) {NULL, 0, self.copy_cb, self.eq_cb, self.free_cb, self.str_cb}; \
    data = the_safe_alloc(self.len * sizeof(element_type)); \
    for (size_t i = 0; i < self.len; i++) { \
      data[i] = self.copy_cb == NULL ? self.data[i] : self.copy_cb(self.data[i]); \
    } \
    return (the_arr_##element_type_name##_t) {data, self.len, self.copy_cb, self.eq_cb, self.free_cb, self.str_cb}; \
  } \
  \
  bool the_arr_##element_type_name##_empty (const the_arr_##element_type_name##_t self) { \
    return self.len == 0; \
  } \
  \
  bool the_arr_##element_type_name##_eq (const the_arr_##element_type_name##_t self, const the_arr_##element_type_name##_t rhs) { \
    if (self.len != rhs.len) return false; \
    for (size_t i = 0; i < self.len; i++) { \
      /* if (self.eq_cb == NULL ? self.data[i] == rhs.data[i] : self.eq_cb(self.data[i], rhs.data[i])) { todo */ \
        (void) rhs; /* todo remove */ \
        return false; \
      /* } */ \
    } \
    return true; \
  } \
  \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_filter (the_err_state_t *state, int line, int col, const the_arr_##element_type_name##_t self, const the_fn_sFP3##element_type_name##FRboolFE_t predicate) { \
    size_t len = 0; \
    element_type *data = the_safe_alloc(self.len * sizeof(element_type)); \
    for (size_t i = 0; i < self.len; i++) { \
      if ( \
        predicate.func( \
          predicate.ctx, \
          the_safe_calloc( \
            &(the_fn_sFP3##element_type_name##FRboolFE_params_t) {state, line, col, self.data[i]}, \
            sizeof(the_fn_sFP3##element_type_name##FRboolFE_params_t) \
          ) \
        ) \
      ) { \
        data[len++] = self.copy_cb == NULL ? self.data[i] : self.copy_cb(self.data[i]); \
      } \
    } \
    return (the_arr_##element_type_name##_t) {data, len, self.copy_cb, self.eq_cb, self.free_cb, self.str_cb}; \
  } \
  \
  element_type *the_arr_##element_type_name##_first (the_err_state_t *state, int line, int col, the_arr_##element_type_name##_t *self) { \
    if (self->len == 0) { \
      the_str_t message = the_str_alloc(L"tried getting first element of empty array"); \
      the_error_assign_generic(state, line, col, message); \
      the_str_free(message); \
      longjmp(state->buf_last->buf, state->id); \
    } \
    return &self->data[0]; \
  } \
  \
  void the_arr_##element_type_name##_forEach (the_err_state_t *state, int line, int col, const the_arr_##element_type_name##_t self, const the_fn_sFP3##element_type_name##FP3intFRvoidFE_t iterator) { \
    for (size_t i = 0; i < self.len; i++) { \
      iterator.func( \
        iterator.ctx, \
        the_safe_calloc( \
          &(the_fn_sFP3##element_type_name##FP3intFRvoidFE_params_t) {state, line, col, self.data[i], i}, \
          sizeof(the_fn_sFP3##element_type_name##FP3intFRvoidFE_params_t) \
        ) \
      ); \
    } \
  } \
  \
  void the_arr_##element_type_name##_free (the_arr_##element_type_name##_t self) { \
    if (self.free_cb != NULL) { \
      for (size_t i = 0; i < self.len; i++) self.free_cb(self.data[i]); \
    } \
    if (self.data != NULL) the_safe_free(self.data); \
  } \
  \
  the_str_t the_arr_##element_type_name##_join (the_arr_##element_type_name##_t self, unsigned char o1, the_str_t separator) { \
    the_str_t x = o1 == 0 ? the_str_alloc(L",") : separator; \
    the_str_t result = the_str_alloc(L""); \
    for (size_t i = 0; i < self.len; i++) { \
      if (i != 0) result = the_str_realloc(result, the_str_concat(result, x)); \
      result = the_str_realloc(result, the_str_concat(result, self.str_cb(self.data[i]))); \
    } \
    if (o1 == 0) the_str_free(x); \
    return result; \
  } \
  \
  element_type *the_arr_##element_type_name##_last (the_err_state_t *state, int line, int col, the_arr_##element_type_name##_t *self) { \
    if (self->len == 0) { \
      the_str_t message = the_str_alloc(L"tried getting last element of empty array"); \
      the_error_assign_generic(state, line, col, message); \
      the_str_free(message); \
      longjmp(state->buf_last->buf, state->id); \
    } \
    return &self->data[self->len - 1]; \
  } \
  \
  the_arr_##element_type_name##_t *the_arr_##element_type_name##_merge (the_arr_##element_type_name##_t *self, const the_arr_##element_type_name##_t other) { \
    size_t k = self->len; \
    self->len += other.len; \
    self->data = the_safe_realloc(self->data, self->len * sizeof(element_type)); \
    for (size_t i = 0; i < other.len; i++) self->data[k++] = other.copy_cb == NULL ? other.data[i] : other.copy_cb(other.data[i]); \
    return self; \
  } \
  \
  bool the_arr_##element_type_name##_ne (const the_arr_##element_type_name##_t self, const the_arr_##element_type_name##_t rhs) { \
    if (self.len != rhs.len) return true; \
    for (size_t i = 0; i < self.len; i++) { \
      /* if (!(self.eq_cb == NULL ? self.data[i] == rhs.data[i] : self.eq_cb(self.data[i], rhs.data[i])) { todo */ \
        (void) rhs; /* todo remove */ \
        return true; \
      /* } */ \
    } \
    return false; \
  } \
  \
  element_type the_arr_##element_type_name##_pop (the_arr_##element_type_name##_t *self) { \
    self->len--; \
    return self->data[self->len]; \
  } \
  \
  void the_arr_##element_type_name##_push (the_arr_##element_type_name##_t *self, const the_arr_##element_type_name##_t elements) { \
    size_t k = 0; \
    if (elements.len == 0) return; \
    self->len += elements.len; \
    self->data = the_safe_realloc(self->data, self->len * sizeof(element_type)); \
    for (size_t i = self->len - elements.len; i < self->len; i++) self->data[i] = self->copy_cb == NULL ? elements.data[k++] : self->copy_cb(elements.data[k++]); \
  } \
  \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_realloc (the_arr_##element_type_name##_t self, const the_arr_##element_type_name##_t rhs) { \
    the_arr_##element_type_name##_free(self); \
    return the_arr_##element_type_name##_copy(rhs); \
  } \

//the_arr_##element_type_name##_t *the_arr_##element_type_name##_remove (err_state_t *state, int line, int col, the_arr_##element_type_name##_t *self, int32_t n1) {
//  if ((n1 >= 0 && n1 >= self->l) || (n1 < 0 && n1 < -((int32_t) self->l))) {
//    const char *fmt = "index %" PRId32 " out of array bounds";
//    size_t z = snprintf(NULL, 0, fmt, n1);
//    char *d = alloc(z + 1);
//    sprintf(d, fmt, n1);
//    error_assign(state, TYPE_error_Error, (void *) error_Error_alloc((the_str_t) {d, z}, (the_str_t) {NULL, 0}), (void (*) (void *)) &error_Error_free, line, col);
//    longjmp(state->buf_last->buf, state->id);
//  }
//  size_t i = n1 < 0 ? n1 + self->l : n1;
//
//if (elementTypeInfo.type->shouldBeFreed()) {
//  " + this->_genFreeFn(elementTypeInfo.type, cFree)->str() + ";
//}
//
//  if (i != self->l - 1) {
//    memmove(&self->d[i], &self->d[i + 1], (--self->l - i) * sizeof(" + elementTypeInfo.typeCodeTrimmed + "));
//  } else {
//    self->l--;
//  }
//  return self;
//}
//
//the_arr_##element_type_name##_t the_arr_##element_type_name##_reverse (the_arr_##element_type_name##_t n) {
//  if (n.l == 0) {
//    " + this->_genFreeFn(type, CodegenASTExprAccess::create("n"))->str() + ";
//    return (the_arr_##element_type_name##_t) {NULL, 0};
//  }
//  " + elementTypeInfo.typeRefCode + "d = alloc(n.l * sizeof(" + elementTypeInfo.typeCodeTrimmed + "));
//  for (size_t i = 0; i < n.l; i++) d[i] = " + this->_genCopyFn(elementTypeInfo.type, cCopy)->str() + ";
//  " + this->_genFreeFn(type, CodegenASTExprAccess::create("n"))->str() + ";
//  return (the_arr_##element_type_name##_t) {d, n.l};
//}
//
//the_arr_##element_type_name##_t the_arr_##element_type_name##_slice (the_arr_##element_type_name##_t n, ";
//unsigned int o1, int32_t n1, unsigned int o2, int32_t n2) {
//  int32_t i1 = o1 == 0 ? 0 : (int32_t) (n1 < 0 ? (n1 < -((int32_t) n.l) ? 0 : n1 + n.l) ";
//: (n1 > n.l ? n.l : n1));
//  int32_t i2 = o2 == 0 ? (int32_t) n.l : (int32_t) (n2 < 0 ? (n2 < -((int32_t) n.l) ? 0 : n2 + n.l) ";
//: (n2 > n.l ? n.l : n2));
//  if (i1 > i2 || i1 >= n.l) {
//    " + this->_genFreeFn(type, CodegenASTExprAccess::create("n"))->str() + ";
//    return (the_arr_##element_type_name##_t) {NULL, 0};
//  }
//  size_t l = i2 - i1;
//  " + elementTypeInfo.typeRefCode + "d = alloc(l * sizeof(" + elementTypeInfo.typeCodeTrimmed + "));
//  for (size_t i = 0; i1 < i2; i1++) d[i++] = " + this->_genCopyFn(elementTypeInfo.type, cCopy)->str() + ";
//  " + this->_genFreeFn(type, CodegenASTExprAccess::create("n"))->str() + ";
//  return (the_arr_##element_type_name##_t) {d, l};
//}
//
//the_arr_##element_type_name##_t *the_arr_##element_type_name##_sort (err_state_t *state, int line, int col, the_arr_##element_type_name##_t *self, " + param1TypeInfo.typeCode + "n1) {
//  if (self->l > 1) {
//    while (1) {
//      unsigned char b = 0;
//      for (size_t i = 1; i < self->l; i++) {
//        int32_t c = n1.f(n1.x, xalloc(&(struct _{" + param1TypeInfo.typeName + "P}) {state, line, col, ";
//this->_genCopyFn(elementTypeInfo.type, cCopy1)->str() + ", ";
//this->_genCopyFn(elementTypeInfo.type, cCopy2)->str() + "}, sizeof(struct _{" + param1TypeInfo.typeName + "P})));
//        if (c > 0) {
//          b = 1;
//          " + elementTypeInfo.typeCode + "t = self->d[i];
//          self->d[i] = self->d[i - 1];
//          self->d[i - 1] = t;
//        }
//      }
//      if (b == 0) break;
//    }
//  }
//  " + this->_genFreeFn(param1TypeInfo.type, CodegenASTExprAccess::create("n1"))->str() + ";
//  return self;
//}
//
//the_str_t the_arr_##element_type_name##_str (the_arr_##element_type_name##_t n) {
//  the_str_t r = str_alloc("[");
//  for (size_t i = 0; i < n.l; i++) {
//    if (i != 0) r = str_concat_cstr(r, ", ");
//
//if (elementTypeInfo.realType->isStr()) {
//    r = str_concat_cstr(r, "\"");
//}
//
//    r = str_concat_str(r, " + this->_genStrFn(elementTypeInfo.realType, cElementRealType)->str() + ");
//
//if (elementTypeInfo.realType->isStr()) {
//    r = str_concat_cstr(r, "\"");
//}
//
//  }
//  " + this->_genFreeFn(type, CodegenASTExprAccess::create("n"))->str() + ";
//  return str_concat_cstr(r, "]");
//}

#endif
