/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_OPTIONAL_H
#define THE_OPTIONAL_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/optional-macro.h>
#include <the/safe.h>
#include <the/string.h>

/**
 * Macro that should be used to generate optional type.
 * @param underlying_type_name Name of the underlying type of the optional type.
 * @param underlying_type Underlying type of the optional type.
 * @param copy_block Block that is used for copy method of optional object.
 * @param eq_block Block that is used for equals method of optional object.
 * @param free_block Block that is used for free method of optional object.
 * @param str_block Block that is used for str method of optional object.
 */
#define THE_OPTIONAL_DEFINE(underlying_type_name, underlying_type, copy_block, eq_block, free_block, str_block) \
  the_opt_##underlying_type_name##_t the_opt_##underlying_type_name##_alloc (const underlying_type val) { \
    the_opt_##underlying_type_name##_t r = the_safe_alloc(sizeof(underlying_type)); \
    *r = copy_block; \
    return r; \
  } \
  \
  the_opt_##underlying_type_name##_t the_opt_##underlying_type_name##_copy (const the_opt_##underlying_type_name##_t self) { \
    underlying_type val; \
    the_opt_##underlying_type_name##_t r; \
    if (self == NULL) return NULL; \
    r = the_safe_alloc(sizeof(underlying_type)); \
    val = *self; \
    *r = copy_block; \
    return r; \
  } \
  \
  bool the_opt_##underlying_type_name##_eq (const the_opt_##underlying_type_name##_t self, const the_opt_##underlying_type_name##_t rhs) { \
    underlying_type lhs_val; \
    underlying_type rhs_val; \
    if (self == NULL || rhs == NULL) return self == rhs; \
    lhs_val = *self; \
    rhs_val = *rhs; \
    return eq_block; \
  } \
  \
  void the_opt_##underlying_type_name##_free (the_opt_##underlying_type_name##_t self) { \
    underlying_type val; \
    if (self == NULL) return; \
    val = *self; \
    free_block; \
    the_safe_free(self); \
  } \
  \
  the_opt_##underlying_type_name##_t the_opt_##underlying_type_name##_realloc (the_opt_##underlying_type_name##_t self, const the_opt_##underlying_type_name##_t rhs) { \
    the_opt_##underlying_type_name##_free(self); \
    return the_opt_##underlying_type_name##_copy(rhs); \
  } \
  \
  the_str_t the_opt_##underlying_type_name##_str (const the_opt_##underlying_type_name##_t self) { \
    underlying_type val; \
    if (self == NULL) return the_str_alloc(L"nil"); \
    val = *self; \
    return str_block; \
  }

#endif
