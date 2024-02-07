/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_ANY_H
#define THE_ANY_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/string-type.h>
#include <stdbool.h>

/**
 * Callback that is used as a property of the_any_t object to copy the object.
 * @param ctx Context of the object to copy.
 * @return Newly copied object.
 */
typedef struct the_any_s (*the_any_copy_cb) (const void *);

/**
 * Callback that is used as a property of the_any_t object to compare two objects.
 * @param lhs_ctx Context of the object to compare from.
 * @param rhs_ctx Context of the object to compare to.
 * @return Whether objects are equal or not.
 */
typedef bool (*the_any_eq_cb) (const void *, const void *);

/**
 * Callback that is used as a property of the_any_t object to deallocate the object.
 * @param ctx Object to deallocate.
 */
typedef void (*the_any_free_cb) (void *);

/**
 * Callback that is used as a property of the_any_t object to convert the object to a string.
 * @param ctx Context of the object to generate string representation for.
 * @return String representation of the object.
 */
typedef the_str_t (*the_any_str_cb) (const void *);

/** Structure representing the_any_t object. */
typedef struct the_any_s {
  /** Type of the object. */
  int type;

  /** Context of the_any_t object. */
  void *ctx;

  /** Callback of the_any_t object used inside `the_any_copy`, `the_any_realloc` functions. */
  the_any_copy_cb copy_cb;

  /** Callback of the_any_t object used inside `the_any_eq`, `the_any_ne` functions. */
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
 * Checks whether two objects are not equal.
 * @param self Object to compare from.
 * @param rhs Object to compare to.
 * @return Whether objects are not equal.
 */
bool the_any_ne (const the_any_t self, const the_any_t rhs);

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

#endif
