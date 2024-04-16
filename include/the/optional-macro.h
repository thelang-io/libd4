/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_OPTIONAL_MACRO_H
#define THE_OPTIONAL_MACRO_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/string-type.h>

/**
 * Macro that should be used to generate optional type.
 * @param underlying_type_name Name of the underlying type of the optional type.
 * @param underlying_type Underlying type of the optional type.
 */
#define THE_OPTIONAL_DECLARE(underlying_type_name, underlying_type) \
  /** Object representation of the optional type. */ \
  typedef underlying_type *the_opt_##underlying_type_name##_t; \
  \
  /**
   * Allocates optional object.
   * @param val Underlying value of the optional object.
   * @return Allocated optional object.
   */ \
  the_opt_##underlying_type_name##_t the_opt_##underlying_type_name##_alloc (const underlying_type val); \
  \
  /**
   * Copies optional object.
   * @param self Optional object to copy.
   * @return Newly copied optional object.
   */ \
  the_opt_##underlying_type_name##_t the_opt_##underlying_type_name##_copy (const the_opt_##underlying_type_name##_t self); \
  \
  /**
   * Compares two optional objects.
   * @param self First optional object to compare.
   * @param rhs Second optional object to compare.
   * @return Whether two optional objects are the same.
   */ \
  bool the_opt_##underlying_type_name##_eq (const the_opt_##underlying_type_name##_t self, const the_opt_##underlying_type_name##_t rhs); \
  \
  /**
   * Deallocates optional object.
   * @param self Optional object to deallocate.
   */ \
  void the_opt_##underlying_type_name##_free (the_opt_##underlying_type_name##_t self); \
  \
  /**
   * Reallocates first optional object and returns copy of second optional object.
   * @param self Optional object to reallocate.
   * @param rhs Optional object to copy from.
   * @return Second optional object copied.
   */ \
  the_opt_##underlying_type_name##_t the_opt_##underlying_type_name##_realloc (the_opt_##underlying_type_name##_t self, const the_opt_##underlying_type_name##_t rhs); \
  \
  /**
   * Generates string representation of the optional object.
   * @param self Optional object to generate string representation for.
   * @return String representation of the optional object.
   */ \
  the_str_t the_opt_##underlying_type_name##_str (const the_opt_##underlying_type_name##_t self);

#endif
