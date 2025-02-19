/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_FN_MACRO_H
#define D4_FN_MACRO_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include "string-type.h"

/**
 * Macro that should be used to generate function type entities.
 * @param prefix Function prefix can be one of: a (asynchronous) and s (synchronous).
 * @param return_type_name Name of the function return type.
 * @param return_type Function return type.
 */
#define D4_FUNCTION_DECLARE(prefix, return_type_name, return_type) \
  D4_FUNCTION_DECLARE_BASE(return_type, fn_##prefix##FR##return_type_name##FE)

/**
 * Macro that should be used to generate function type entities along with params.
 * @param prefix Function prefix can be one of: a (asynchronous) and s (synchronous).
 * @param return_type_name Name of the function return type.
 * @param return_type Function return type.
 * @param params_type_name Name of parameters type to be used when generating name of the function type.
 * @param params_definition Definition of parameters that is going to be declared as corresponding object.
 */
#define D4_FUNCTION_DECLARE_WITH_PARAMS(prefix, return_type_name, return_type, params_type_name, params_definition) \
  /** Object representation of the function params type. */ \
  typedef struct params_definition d4_fn_##prefix##params_type_name##FR##return_type_name##FE_params_t; \
  \
  D4_FUNCTION_DECLARE_BASE(return_type, fn_##prefix##params_type_name##FR##return_type_name##FE)

/**
 * Macro that is used internally to generate function type entities.
 * @param return_type Function return type.
 * @param type_name Generated name of the function type.
 */
#define D4_FUNCTION_DECLARE_BASE(return_type, type_name) \
  /**
   * Functor that is used as main call entry of the function object.
   * @param ctx Context of the function.
   * @param params Params object used when calling this function.
   * @return Returns function result.
   */ \
  typedef return_type (*d4_##type_name##_func) (void *ctx, void *params); \
  \
  /** Object representation of the function type. */ \
  typedef struct { \
    \
    /** Name of the function object. */ \
    d4_str_t name; \
    \
    /** Context to be used when calling functor. */ \
    void *ctx; \
    \
    /** Callback to copy function object. */ \
    d4_fn_copy_cb copy_cb; \
    \
    /** Callback to deallocate function object. */ \
    d4_fn_free_cb free_cb; \
    \
    /** Functor of the function object. */ \
    d4_##type_name##_func func; \
  } d4_##type_name##_t; \
  \
  /**
   * Allocates function object.
   * @param name Name of the function object.
   * @param ctx Context of the function object.
   * @param copy_cb Callback to copy function object.
   * @param free_cb Callback to deallocate function object.
   * @param func Context of the object to copy.
   * @return Allocated function object.
   */ \
  d4_##type_name##_t d4_##type_name##_alloc (const d4_str_t name, void *ctx, d4_fn_copy_cb copy_cb, d4_fn_free_cb free_cb, d4_##type_name##_func func); \
  \
  /**
   * Copies function object.
   * @param self Function object to copy.
   * @return Newly copied function object.
   */ \
  d4_##type_name##_t d4_##type_name##_copy (const d4_##type_name##_t self); \
  \
  /**
   * Compares two function objects.
   * @param self First function object to compare.
   * @param rhs Second function object to compare.
   * @return Whether two function objects share the same address of functors.
   */ \
  bool d4_##type_name##_eq (const d4_##type_name##_t self, const d4_##type_name##_t rhs); \
  \
  /**
   * Deallocates function object.
   * @param self Function object to deallocate.
   */ \
  void d4_##type_name##_free (d4_##type_name##_t self); \
  \
  /**
   * Reallocates first function object and returns copy of second function object.
   * @param self Function object to reallocate.
   * @param rhs Function object to copy from.
   * @return Second function object copied.
   */ \
  d4_##type_name##_t d4_##type_name##_realloc (d4_##type_name##_t self, const d4_##type_name##_t rhs); \
  \
  /**
   * Generates string representation of the function object.
   * @param self Function object to generate string representation for.
   * @return String representation of the function object.
   */ \
  d4_str_t d4_##type_name##_str (const d4_##type_name##_t self);

/**
 * Callback that is used as a property of function object to copy the object.
 * @param ctx Context of the function to copy.
 * @return Newly copied function context.
 */
typedef void *(*d4_fn_copy_cb) (const void *ctx);

/**
 * Callback that is used as a property of function object to deallocate the object.
 * @param ctx Context of the function to deallocate.
 */
typedef void (*d4_fn_free_cb) (void *ctx);

#endif
