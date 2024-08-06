/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_ANY_H
#define D4_ANY_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include <d4/safe.h>
#include <d4/string-type.h>

/**
 * Callback that is used as a property of d4_any_t object to copy the object.
 * @param ctx Context of the object to copy.
 * @return Newly copied object.
 */
typedef void *(*d4_any_copy_cb) (const void *ctx);

/**
 * Callback that is used as a property of d4_any_t object to compare two objects.
 * @param lhs_ctx Context of the object to compare from.
 * @param rhs_ctx Context of the object to compare to.
 * @return Whether objects are equal or not.
 */
typedef bool (*d4_any_eq_cb) (const void *lhs_ctx, const void *rhs_ctx);

/**
 * Callback that is used as a property of d4_any_t object to deallocate the object.
 * @param ctx Object to deallocate.
 */
typedef void (*d4_any_free_cb) (void *ctx);

/**
 * Callback that is used as a property of d4_any_t object to convert the object to a string.
 * @param ctx Context of the object to generate string representation for.
 * @return String representation of the object.
 */
typedef d4_str_t (*d4_any_str_cb) (const void *ctx);

/** Structure representing d4_any_t object. */
typedef struct d4_any_s {
  /** Type of the object. */
  int type;

  /** Context of d4_any_t object. */
  void *ctx;

  /** Callback of d4_any_t object used inside `d4_any_copy`, `d4_any_realloc` functions. */
  d4_any_copy_cb copy_cb;

  /** Callback of d4_any_t object used inside `d4_any_eq` function. */
  d4_any_eq_cb eq_cb;

  /** Callback of d4_any_t object used inside `d4_any_free`, `d4_any_realloc` functions. */
  d4_any_free_cb free_cb;

  /** Callback of d4_any_t object used inside `d4_any_str` function. */
  d4_any_str_cb str_cb;
} d4_any_t;

/**
 * Copies the object.
 * @param self Object to copy.
 * @return Newly copied object.
 */
d4_any_t d4_any_copy (const d4_any_t self);

/**
 * Checks whether two objects are equal or not.
 * @param self Object to compare from.
 * @param rhs Object to compare to.
 * @return Whether objects are equal or not.
 */
bool d4_any_eq (const d4_any_t self, const d4_any_t rhs);

/**
 * Deallocates the object.
 * @param self Object to deallocate.
 */
void d4_any_free (d4_any_t self);

/**
 * Reallocates the object with value copied from another object.
 * @param self Object to reallocate.
 * @param rhs Another object to copy value from.
 * @return Reallocated object with new value copied from another object.
 */
d4_any_t d4_any_realloc (d4_any_t self, const d4_any_t rhs);

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
d4_str_t d4_any_str (const d4_any_t self);

/**
 * Macro that should be used to generate any object.
 * @param underlying_type_name Name of the underlying type.
 * @param underlying_type Underlying type of the any object.
 */
#define D4_ANY_DECLARE(underlying_type_name, underlying_type) \
  /** Object representation of the any type. */ \
  typedef underlying_type *d4_any_##underlying_type_name##_t; \
  \
  /**
   * Allocates any object.
   * @param val Underlying value of the any object.
   * @return Allocated any object.
   */ \
  d4_any_t d4_any_##underlying_type_name##_alloc (underlying_type val); \
  \
  /**
   * Copies any object.
   * @param ctx Any object to copy.
   * @return Newly copied any object.
   */ \
  void *d4_any_##underlying_type_name##_copy (const void *ctx); \
  \
  /**
   * Compares two any objects.
   * @param ctx First any object to compare.
   * @param rhs_ctx Second any object to compare.
   * @return Whether two any objects are the same.
   */ \
  bool d4_any_##underlying_type_name##_eq (const void *ctx, const void *rhs_ctx); \
  \
  /**
   * Deallocates any object.
   * @param ctx Any object to deallocate.
   */ \
  void d4_any_##underlying_type_name##_free (void *ctx); \
  \
  /**
   * Generates string representation of the any object.
   * @param ctx Any object to generate string representation for.
   * @return String representation of the any object.
   */ \
  d4_str_t d4_any_##underlying_type_name##_str (const void *ctx); \

/**
 * Macro that should be used to generate any object.
 * @param underlying_type_id ID of the underlying type of the any type.
 * @param underlying_type_name Name of the underlying type of the any type.
 * @param underlying_type Underlying type of the any type.
 * @param copy_block Block that is used for copy method of any object.
 * @param eq_block Block that is used for equals method of any object.
 * @param free_block Block that is used for free method of any object.
 * @param str_block Block that is used for str method of any object.
 */
#define D4_ANY_DEFINE(underlying_type_id, underlying_type_name, underlying_type, copy_block, eq_block, free_block, str_block) \
  d4_any_t d4_any_##underlying_type_name##_alloc (underlying_type val) { \
    d4_any_##underlying_type_name##_t data = d4_safe_alloc(sizeof(underlying_type)); \
    *data = copy_block; \
    return (d4_any_t) {underlying_type_id, data, d4_any_##underlying_type_name##_copy, d4_any_##underlying_type_name##_eq, d4_any_##underlying_type_name##_free, d4_any_##underlying_type_name##_str}; \
  } \
  \
  void *d4_any_##underlying_type_name##_copy (const void *ctx) { \
    d4_any_##underlying_type_name##_t data = d4_safe_alloc(sizeof(underlying_type)); \
    const underlying_type val = *(const underlying_type *) ctx; \
    *data = copy_block; \
    return data; \
  } \
  \
  bool d4_any_##underlying_type_name##_eq (const void *lhs_ctx, const void *rhs_ctx) { \
    const underlying_type lhs_val = *(const underlying_type *) lhs_ctx; \
    const underlying_type rhs_val = *(const underlying_type *) rhs_ctx; \
    return eq_block; \
  } \
  \
  void d4_any_##underlying_type_name##_free (void *ctx) { \
    underlying_type val = *(d4_any_##underlying_type_name##_t) ctx; \
    free_block; \
    d4_safe_free(ctx); \
  } \
  \
  d4_str_t d4_any_##underlying_type_name##_str (const void *ctx) { \
    const underlying_type val = *(const underlying_type *) ctx; \
    return str_block; \
  }

#endif
