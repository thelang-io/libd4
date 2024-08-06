/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_OPTIONAL_H
#define D4_OPTIONAL_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include <d4/optional-macro.h>
#include <d4/safe.h>
#include <d4/string.h>

/**
 * Macro that should be used to generate optional type.
 * @param underlying_type_name Name of the underlying type of the optional type.
 * @param underlying_type Underlying type of the optional type.
 * @param copy_block Block that is used for copy method of optional object.
 * @param eq_block Block that is used for equals method of optional object.
 * @param free_block Block that is used for free method of optional object.
 * @param str_block Block that is used for str method of optional object.
 */
#define D4_OPTIONAL_DEFINE(underlying_type_name, underlying_type, copy_block, eq_block, free_block, str_block) \
  d4_opt_##underlying_type_name##_t d4_opt_##underlying_type_name##_alloc (const underlying_type val) { \
    d4_opt_##underlying_type_name##_t r = d4_safe_alloc(sizeof(underlying_type)); \
    *r = copy_block; \
    return r; \
  } \
  \
  d4_opt_##underlying_type_name##_t d4_opt_##underlying_type_name##_copy (const d4_opt_##underlying_type_name##_t self) { \
    underlying_type val; \
    d4_opt_##underlying_type_name##_t r; \
    if (self == NULL) return NULL; \
    r = d4_safe_alloc(sizeof(underlying_type)); \
    val = *self; \
    *r = copy_block; \
    return r; \
  } \
  \
  bool d4_opt_##underlying_type_name##_eq (const d4_opt_##underlying_type_name##_t self, const d4_opt_##underlying_type_name##_t rhs) { \
    underlying_type lhs_val; \
    underlying_type rhs_val; \
    if (self == NULL || rhs == NULL) return self == rhs; \
    lhs_val = *self; \
    rhs_val = *rhs; \
    return eq_block; \
  } \
  \
  void d4_opt_##underlying_type_name##_free (d4_opt_##underlying_type_name##_t self) { \
    underlying_type val; \
    if (self == NULL) return; \
    val = *self; \
    free_block; \
    d4_safe_free(self); \
  } \
  \
  d4_opt_##underlying_type_name##_t d4_opt_##underlying_type_name##_realloc (d4_opt_##underlying_type_name##_t self, const d4_opt_##underlying_type_name##_t rhs) { \
    d4_opt_##underlying_type_name##_free(self); \
    return d4_opt_##underlying_type_name##_copy(rhs); \
  } \
  \
  d4_str_t d4_opt_##underlying_type_name##_str (const d4_opt_##underlying_type_name##_t self) { \
    underlying_type val; \
    if (self == NULL) return d4_str_alloc(L"nil"); \
    val = *self; \
    return str_block; \
  }

#endif
