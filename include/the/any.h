/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_ANY_H
#define THE_ANY_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/safe.h>
#include <the/string-type.h>
#include <stdbool.h>

/**
 * Callback that is used as a property of the_any_t object to copy the object.
 * @param ctx Context of the object to copy.
 * @return Newly copied object.
 */
typedef void *(*the_any_copy_cb) (const void *ctx);

/**
 * Callback that is used as a property of the_any_t object to compare two objects.
 * @param lhs_ctx Context of the object to compare from.
 * @param rhs_ctx Context of the object to compare to.
 * @return Whether objects are equal or not.
 */
typedef bool (*the_any_eq_cb) (const void *lhs_ctx, const void *rhs_ctx);

/**
 * Callback that is used as a property of the_any_t object to deallocate the object.
 * @param ctx Object to deallocate.
 */
typedef void (*the_any_free_cb) (void *ctx);

/**
 * Callback that is used as a property of the_any_t object to convert the object to a string.
 * @param ctx Context of the object to generate string representation for.
 * @return String representation of the object.
 */
typedef the_str_t (*the_any_str_cb) (const void *ctx);

/** Structure representing the_any_t object. */
typedef struct the_any_s {
  /** Type of the object. */
  int type;

  /** Context of the_any_t object. */
  void *ctx;

  /** Callback of the_any_t object used inside `the_any_copy`, `the_any_realloc` functions. */
  the_any_copy_cb copy_cb;

  /** Callback of the_any_t object used inside `the_any_eq` function. */
  the_any_eq_cb eq_cb;

  /** Callback of the_any_t object used inside `the_any_free`, `the_any_realloc` functions. */
  the_any_free_cb free_cb;

  /** Callback of the_any_t object used inside `the_any_str` function. */
  the_any_str_cb str_cb;
} the_any_t;

/**
 * Copies the object.
 * @param self Object to copy.
 * @return Newly copied object.
 */
the_any_t the_any_copy (const the_any_t self);

/**
 * Checks whether two objects are equal or not.
 * @param self Object to compare from.
 * @param rhs Object to compare to.
 * @return Whether objects are equal or not.
 */
bool the_any_eq (const the_any_t self, const the_any_t rhs);

/**
 * Deallocates the object.
 * @param self Object to deallocate.
 */
void the_any_free (the_any_t self);

/**
 * Reallocates the object with value copied from another object.
 * @param self Object to reallocate.
 * @param rhs Another object to copy value from.
 * @return Reallocated object with new value copied from another object.
 */
the_any_t the_any_realloc (the_any_t self, const the_any_t rhs);

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
the_str_t the_any_str (const the_any_t self);

/**
 * Macro that should be used to generate any object.
 * @param underlying_type_name Name of the underlying type.
 * @param underlying_type Underlying type of the any object.
 */
#define THE_ANY_DECLARE(underlying_type_name, underlying_type) \
  /**
   * Allocates any object.
   * @param val Underlying value of the any object.
   * @return Allocated any object.
   */ \
  the_any_t the_any_##underlying_type_name (underlying_type val); \
  \
  /**
   * Copies any object.
   * @param ctx Any object to copy.
   * @return Newly copied any object.
   */ \
  void *the_any_##underlying_type_name##_copy (const void *ctx); \
  \
  /**
   * Compares two any objects.
   * @param ctx First any object to compare.
   * @param rhs_ctx Second any object to compare.
   * @return Whether two any objects are the same.
   */ \
  bool the_any_##underlying_type_name##_eq (const void *ctx, const void *rhs_ctx); \
  \
  /**
   * Deallocates any object.
   * @param ctx Any object to deallocate.
   */ \
  void the_any_##underlying_type_name##_free (void *ctx); \
  \
  /**
   * Generates string representation of the any object.
   * @param ctx Any object to generate string representation for.
   * @return String representation of the any object.
   */ \
  the_str_t the_any_##underlying_type_name##_str (const void *ctx); \

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
#define THE_ANY_DEFINE(underlying_type_id, underlying_type_name, underlying_type, copy_block, eq_block, free_block, str_block) \
  the_any_t the_any_##underlying_type_name (underlying_type val) { \
    underlying_type *data = the_safe_alloc(sizeof(underlying_type)); \
    *data = copy_block; \
    return (the_any_t) {underlying_type_id, data, the_any_##underlying_type_name##_copy, the_any_##underlying_type_name##_eq, the_any_##underlying_type_name##_free, the_any_##underlying_type_name##_str}; \
  } \
  \
  void *the_any_##underlying_type_name##_copy (const void *ctx) { \
    underlying_type *data = the_safe_alloc(sizeof(underlying_type)); \
    const underlying_type val = *(const underlying_type *) ctx; \
    *data = copy_block; \
    return data; \
  } \
  \
  bool the_any_##underlying_type_name##_eq (const void *lhs_ctx, const void *rhs_ctx) { \
    const underlying_type lhs_val = *(const underlying_type *) lhs_ctx; \
    const underlying_type rhs_val = *(const underlying_type *) rhs_ctx; \
    return eq_block; \
  } \
  \
  void the_any_##underlying_type_name##_free (void *ctx) { \
    underlying_type val = *(underlying_type *) ctx; \
    free_block; \
    the_safe_free(ctx); \
  } \
  \
  the_str_t the_any_##underlying_type_name##_str (const void *ctx) { \
    const underlying_type val = *(const underlying_type *) ctx; \
    return str_block; \
  }

#endif
