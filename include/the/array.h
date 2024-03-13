/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_ARRAY_H
#define THE_ARRAY_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/fn.h>
#include <inttypes.h>

// todo test
// todo check all params have correct "const" in definition

#define THE_ARRAY_DEFINE(underlying_type_name, underlying_type) \
  THE_FUNCTION_DEFINE_WITH_PARAMS(s, bool, FP3###underlying_type_name) \
  THE_FUNCTION_DEFINE_WITH_PARAMS(s, void, FP3##underlying_type_name##FP3int) \
  THE_FUNCTION_DEFINE_WITH_PARAMS(s, int, FP3##underlying_type_name##FP3##underlying_type_name) \
  \
  the_arr_##underlying_type_name##_t the_arr_##underlying_type_name##_alloc (size_t length, ...) { \
    underlying_type *data; \
    va_list args; \
    if (length == 0) return (the_arr_##underlying_type_name##_t) {NULL, 0}; \
    data = the_safe_alloc(length * sizeof(underlying_type)); \
    va_start(args, length); \
    for (size_t i = 0; i < length; i++) { \
      data[i] = va_arg(args, underlying_type); \
    } \
    va_end(args); \
    return (the_arr_##underlying_type_name##_t) {data, length}; \
  } \
  \
  underlying_type *the_arr_##underlying_type_name##_at (the_err_state_t *state, int line, int col, const the_arr_##underlying_type_name##_t self, int32_t index) { \
    if ((index >= 0 && (size_t) index >= self.len) || (index < 0 && index < -((int32_t) self.len))) { \
      the_str_t message = the_str_alloc(L"index %" PRId32 L" out of array bounds", index); \
      the_error_assign_generic(state, line, col, message); \
      the_str_free(message); \
      longjmp(state->buf_last->buf, state->id); \
    } \
    return index < 0 ? &self.data[self.len + index] : &self.data[index]; \
  } \
  \
  the_arr_##underlying_type_name##_t the_arr_##underlying_type_name##_copy (const the_arr_##underlying_type_name##_t self) { \
    underlying_type *data; \
    if (self.len == 0) return (the_arr_##underlying_type_name##_t) {NULL, 0}; \
    data = the_safe_alloc(self.len * sizeof(underlying_type)); \
    for (size_t i = 0; i < self.len; i++) data[i] = copy_block; \
    return (the_arr_##underlying_type_name##_t) {data, self.len}; \
  } \
  \
  void the_arr_##underlying_type_name##_free (the_arr_##underlying_type_name##_t self) { \
    for (size_t i = 0; i < self.len; i++) free_block; \
    if (self.data != NULL) the_safe_free(self.data); \
  }

//the_arr_##underlying_type_name##_t *the_arr_##underlying_type_name##_clear (the_arr_##underlying_type_name##_t *self) {
//  " + this->_genFreeFn(type, cFree)->str() + ";
//  self->d = NULL;
//  self->l = 0;
//  return self;
//}
//
//the_arr_##underlying_type_name##_t the_arr_##underlying_type_name##_concat (the_arr_##underlying_type_name##_t self, " + param1TypeInfo.typeCode + "n1) {
//  size_t l = self.l + n1.l;
//  " + elementTypeInfo.typeRefCode + "d = alloc(l * sizeof(" + elementTypeInfo.typeCodeTrimmed + "));
//  size_t k = 0;
//  for (size_t i = 0; i < self.l; i++) d[k++] = ";
//this->_genCopyFn(elementTypeInfo.type, cCopy1)->str() + ";
//  for (size_t i = 0; i < n1.l; i++) d[k++] = ";
//this->_genCopyFn(elementTypeInfo.type, cCopy2)->str() + ";
//  " + this->_genFreeFn(type, CodegenASTExprAccess::create("n1"))->str() + ";
//  " + this->_genFreeFn(type, CodegenASTExprAccess::create("self"))->str() + ";
//  return (the_arr_##underlying_type_name##_t) {d, l};
//}
//
//bool the_arr_##underlying_type_name##_contains (the_arr_##underlying_type_name##_t self, " + param1TypeInfo.typeCode + "n1) {
//  bool r = false;
//  for (size_t i = 0; i < self.l; i++) {
//    if (" + this->_genEqFn(elementTypeInfo.type, cEq1, cEq2)->str() + ") {
//      r = true;
//      break;
//    }
//  }
//if (param1TypeInfo.type->shouldBeFreed()) {
//  " + this->_genFreeFn(param1TypeInfo.type, CodegenASTExprAccess::create("n1"))->str() + ";
//}
//  " + this->_genFreeFn(type, CodegenASTExprAccess::create("self"))->str() + ";
//  return r;
//}
//
//bool the_arr_##underlying_type_name##_empty (the_arr_##underlying_type_name##_t n) {
//  bool r = n.l == 0;
//  " + this->_genFreeFn(type, CodegenASTExprAccess::create("n"))->str() + ";
//  return r;
//}
//
//
//bool the_arr_##underlying_type_name##_eq (the_arr_##underlying_type_name##_t n1, the_arr_##underlying_type_name##_t n2) {
//  bool r = n1.l == n2.l;
//  if (r) {
//    for (size_t i = 0; i < n1.l; i++) {
//      if (" + this->_genEqFn(elementTypeInfo.type, cEq1, cEq2, true)->str() + ") {
//        r = false;
//        break;
//      }
//    }
//  }
//  " + this->_genFreeFn(type, CodegenASTExprAccess::create("n1"))->str() + ";
//  " + this->_genFreeFn(type, CodegenASTExprAccess::create("n2"))->str() + ";
//  return r;
//}
//
//the_arr_##underlying_type_name##_t the_arr_##underlying_type_name##_filter (err_state_t *state, int line, int col, the_arr_##underlying_type_name##_t self, " + param1TypeInfo.typeCode + "n1) {
//  size_t l = 0;
//  " + elementTypeInfo.typeRefCode + "d = alloc(self.l * sizeof(" + elementTypeInfo.typeCodeTrimmed + "));
//  for (size_t i = 0; i < self.l; i++) {
//    if (n1.f(n1.x, xalloc(&(struct _{" + param1TypeInfo.typeName + "P}) ";
//{state, line, col, " + this->_genCopyFn(elementTypeInfo.type, cCopy)->str() + "}, sizeof(struct _{" + param1TypeInfo.typeName + "P})))) {
//      d[l++] = " + this->_genCopyFn(elementTypeInfo.type, cCopy)->str() + ";
//    }
//  }
//  " + this->_genFreeFn(param1TypeInfo.type, CodegenASTExprAccess::create("n1"))->str() + ";
//  " + this->_genFreeFn(type, CodegenASTExprAccess::create("self"))->str() + ";
//  return (the_arr_##underlying_type_name##_t) {d, l};
//}
//
//elementTypeInfo.typeRefCode + typeName + "_first (err_state_t *state, int line, int col, the_arr_##underlying_type_name##_t *self) {
//  if (self->l == 0) {
//    error_assign(state, TYPE_error_Error, (void *) error_Error_alloc(str_alloc("tried getting first element of empty array"), (the_str_t) {NULL, 0}), (void (*) (void *)) &error_Error_free, line, col);
//    longjmp(state->buf_last->buf, state->id);
//  }
//  return &self->d[0];
//}
//
//
//void the_arr_##underlying_type_name##_forEach (err_state_t *state, int line, int col, the_arr_##underlying_type_name##_t self, " + param1TypeInfo.typeCode + "n1) {
//  for (size_t i = 0; i < self.l; i++) {
//    n1.f(n1.x, xalloc(&(struct _{" + param1TypeInfo.typeName + "P}) ";
//{state, line, col, " + this->_genCopyFn(elementTypeInfo.type, cCopy)->str() + ", i}, ";
//sizeof(struct _{" + param1TypeInfo.typeName + "P})));
//  }
//  " + this->_genFreeFn(param1TypeInfo.type, CodegenASTExprAccess::create("n1"))->str() + ";
//  " + this->_genFreeFn(type, CodegenASTExprAccess::create("self"))->str() + ";
//}
//
//the_str_t the_arr_##underlying_type_name##_join (the_arr_##underlying_type_name##_t n, unsigned char o1, the_str_t n1) {
//  the_str_t x = o1 == 0 ? str_alloc(",") : n1;
//  the_str_t r = str_alloc("");
//  for (size_t i = 0; i < n.l; i++) {
//    if (i != 0) r = str_concat_str(r, str_copy(x));
//    r = str_concat_str(r, " + this->_genStrFn(elementTypeInfo.realType, cElementRealType, true, false)->str() + ");
//  }
//  " + this->_genFreeFn(this->ast->typeMap.get("str"), CodegenASTExprAccess::create("x"))->str() + ";
//  " + this->_genFreeFn(type, CodegenASTExprAccess::create("n"))->str() + ";
//  return r;
//}
//
//elementTypeInfo.typeRefCode + typeName + "_last (err_state_t *state, int line, int col, the_arr_##underlying_type_name##_t *self) {
//  if (self->l == 0) {
//    error_assign(state, TYPE_error_Error, (void *) error_Error_alloc(str_alloc("tried getting last element of empty array"), (the_str_t) {NULL, 0}), (void (*) (void *)) &error_Error_free, line, col);
//    longjmp(state->buf_last->buf, state->id);
//  }
//  return &self->d[self->l - 1];
//}
//
//size_t the_arr_##underlying_type_name##_len (the_arr_##underlying_type_name##_t n) {
//  size_t l = n.l;
//  " + this->_genFreeFn(type, CodegenASTExprAccess::create("n"))->str() + ";
//  return l;
//}
//
//the_arr_##underlying_type_name##_t *the_arr_##underlying_type_name##_merge (the_arr_##underlying_type_name##_t *self, " + param1TypeInfo.typeCode + "n1) {
//  size_t k = self->l;
//  self->l += n1.l;
//  self->d = re_alloc(self->d, self->l * sizeof(" + elementTypeInfo.typeCodeTrimmed + "));
//  for (size_t i = 0; i < n1.l; i++) self->d[k++] = " + this->_genCopyFn(elementTypeInfo.type, cCopy)->str() + ";
//  " + this->_genFreeFn(type, CodegenASTExprAccess::create("n1"))->str() + ";
//  return self;
//}
//
//bool the_arr_##underlying_type_name##_ne (the_arr_##underlying_type_name##_t n1, the_arr_##underlying_type_name##_t n2) {
//  bool r = n1.l != n2.l;
//  if (!r) {
//    for (size_t i = 0; i < n1.l; i++) {
//      if (" + this->_genEqFn(elementTypeInfo.type, cEq1, cEq2, true)->str() + ") {
//        r = true;
//        break;
//      }
//    }
//  }
//  " + this->_genFreeFn(type, CodegenASTExprAccess::create("n1"))->str() + ";
//  " + this->_genFreeFn(type, CodegenASTExprAccess::create("n2"))->str() + ";
//  return r;
//}
//
//elementTypeInfo.typeCode + typeName + "_pop (the_arr_##underlying_type_name##_t *n) {
//  n->l--;
//  return n->d[n->l];
//}
//
//void the_arr_##underlying_type_name##_push (the_arr_##underlying_type_name##_t *n, the_arr_##underlying_type_name##_t m) {
//  if (m.l == 0) return;
//  n->l += m.l;
//  n->d = re_alloc(n->d, n->l * sizeof(" + elementTypeInfo.typeCodeTrimmed + "));
//  size_t k = 0;
//  for (size_t i = n->l - m.l; i < n->l; i++) n->d[i] = m.d[k++];
//  the_safe_free(m.d);
//}
//
//the_arr_##underlying_type_name##_t the_arr_##underlying_type_name##_realloc (the_arr_##underlying_type_name##_t n1, const the_arr_##underlying_type_name##_t n2) {
//  " + this->_genFreeFn(type, CodegenASTExprAccess::create("n1"))->str() + ";
//  return n2;
//}
//
//the_arr_##underlying_type_name##_t *the_arr_##underlying_type_name##_remove (err_state_t *state, int line, int col, the_arr_##underlying_type_name##_t *self, int32_t n1) {
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
//the_arr_##underlying_type_name##_t the_arr_##underlying_type_name##_reverse (the_arr_##underlying_type_name##_t n) {
//  if (n.l == 0) {
//    " + this->_genFreeFn(type, CodegenASTExprAccess::create("n"))->str() + ";
//    return (the_arr_##underlying_type_name##_t) {NULL, 0};
//  }
//  " + elementTypeInfo.typeRefCode + "d = alloc(n.l * sizeof(" + elementTypeInfo.typeCodeTrimmed + "));
//  for (size_t i = 0; i < n.l; i++) d[i] = " + this->_genCopyFn(elementTypeInfo.type, cCopy)->str() + ";
//  " + this->_genFreeFn(type, CodegenASTExprAccess::create("n"))->str() + ";
//  return (the_arr_##underlying_type_name##_t) {d, n.l};
//}
//
//the_arr_##underlying_type_name##_t the_arr_##underlying_type_name##_slice (the_arr_##underlying_type_name##_t n, ";
//unsigned int o1, int32_t n1, unsigned int o2, int32_t n2) {
//  int32_t i1 = o1 == 0 ? 0 : (int32_t) (n1 < 0 ? (n1 < -((int32_t) n.l) ? 0 : n1 + n.l) ";
//: (n1 > n.l ? n.l : n1));
//  int32_t i2 = o2 == 0 ? (int32_t) n.l : (int32_t) (n2 < 0 ? (n2 < -((int32_t) n.l) ? 0 : n2 + n.l) ";
//: (n2 > n.l ? n.l : n2));
//  if (i1 > i2 || i1 >= n.l) {
//    " + this->_genFreeFn(type, CodegenASTExprAccess::create("n"))->str() + ";
//    return (the_arr_##underlying_type_name##_t) {NULL, 0};
//  }
//  size_t l = i2 - i1;
//  " + elementTypeInfo.typeRefCode + "d = alloc(l * sizeof(" + elementTypeInfo.typeCodeTrimmed + "));
//  for (size_t i = 0; i1 < i2; i1++) d[i++] = " + this->_genCopyFn(elementTypeInfo.type, cCopy)->str() + ";
//  " + this->_genFreeFn(type, CodegenASTExprAccess::create("n"))->str() + ";
//  return (the_arr_##underlying_type_name##_t) {d, l};
//}
//
//the_arr_##underlying_type_name##_t *the_arr_##underlying_type_name##_sort (err_state_t *state, int line, int col, the_arr_##underlying_type_name##_t *self, " + param1TypeInfo.typeCode + "n1) {
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
//the_str_t the_arr_##underlying_type_name##_str (the_arr_##underlying_type_name##_t n) {
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
