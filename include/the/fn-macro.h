/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_FN_MACRO_H
#define THE_FN_MACRO_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/string.h>

/** Macro that should be used to generate function type entities. */
#define THE_FUNCTION_DECLARE(type_name, return_type) \
  \
  /**
   * Functor that is used as main call entry of the function object.
   * @param ctx Context of the function.
   * @param params Params object used when calling this function.
   * @return Returns function result.
   */ \
  typedef return_type (*the_##type_name##_func) (void *ctx, void *params); \
  \
  /** Object representation of the function type. */ \
  typedef struct { \
    \
    /** Name of the function object. */ \
    the_str_t name; \
    \
    /** Functor of the function object. */ \
    the_##type_name##_func func; \
    \
    /** Context to be used when calling functor. */ \
    void *ctx; \
    \
    /** Callback to copy function object. */ \
    the_fn_copy_cb copy_cb; \
    \
    /** Callback to deallocate function object. */ \
    the_fn_free_cb free_cb; \
  } the_##type_name##_t; \
  \
  /**
   * Allocates function object.
   * @param name Name of the function object.
   * @param func Context of the object to copy.
   * @param ctx Context of the function object.
   * @param copy_cb Callback to copy function object.
   * @param free_cb Callback to deallocate function object.
   * @return Allocated function object.
   */ \
  the_##type_name##_t the_##type_name##_alloc (const the_str_t name, the_##type_name##_func func, void *ctx, the_fn_copy_cb copy_cb, the_fn_free_cb free_cb); \
  \
  /**
   * Copies function object.
   * @param self Function object to copy.
   * @return Newly copied function object.
   */ \
  the_##type_name##_t the_##type_name##_copy (const the_##type_name##_t self); \
  \
  /**
   * Compare two function objects.
   * @param self First function object to compare.
   * @param rhs Second function object to compare.
   * @return Whether two function objects share the same address of functors.
   */ \
  bool the_##type_name##_eq (const the_##type_name##_t self, const the_##type_name##_t rhs); \
  \
  /**
   * Deallocate function object.
   * @param self Function object to deallocate.
   */ \
  void the_##type_name##_free (the_##type_name##_t self); \
  \
  /**
   * Reallocates first function object and returns copy of second function object.
   * @param self Function object to reallocate.
   * @param rhs Function object to copy from.
   * @return Second function object copied.
   */ \
  the_##type_name##_t the_##type_name##_realloc (the_##type_name##_t self, const the_##type_name##_t rhs); \
  \
  /**
   * Generates string representation of the function object.
   * @param self Function object to generate string representation for.
   * @return String representation of the function object.
   */ \
  the_str_t the_##type_name##_str (const the_##type_name##_t self);

/**
 * Callback that is used as a property of function object to copy the object.
 * @param ctx Context of the function to copy.
 * @return Newly copied function context.
 */
typedef void *(*the_fn_copy_cb) (const void *ctx);

/**
 * Callback that is used as a property of function object to deallocate the object.
 * @param ctx Context of the function to deallocate.
 */
typedef void (*the_fn_free_cb) (void *ctx);

#endif
