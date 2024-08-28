/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_OBJECT_MACRO_H
#define D4_OBJECT_MACRO_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include <d4/string.h>

/**
 * Macro used to declare object type.
 * @param type_name Name of the object type.
 * @param definition Definition of the fields that are going to be declared as object type.
 * @param ... Allocation function parameters declaration for object type fields.
 */
#define D4_OBJECT_DECLARE(type_name, definition, ...) \
  /** Object representation of the object type. */ \
  typedef struct definition d4_obj_##type_name##_t; \
  \
  /**
   * Allocates object type.
   * @param ... Allocation function parameters specified during declaration.
   * @return Allocated object type.
   */ \
  d4_obj_##type_name##_t d4_obj_##type_name##_alloc (__VA_ARGS__); \
  \
  /**
   * Creates a copy of object type.
   * @param self Object type to create a copy of.
   * @return Copy of the provided object type.
   */ \
  d4_obj_##type_name##_t d4_obj_##type_name##_copy (const d4_obj_##type_name##_t self); \
  \
  /**
   * Compares two object types.
   * @param self First object type to compare.
   * @param rhs Second object type to compare.
   * @return Whether two object types are the same.
   */ \
  bool d4_obj_##type_name##_eq (const d4_obj_##type_name##_t self, const d4_obj_##type_name##_t rhs); \
  \
  /**
   * Deallocates object type.
   * @param self Object type to deallocate.
   */ \
  void d4_obj_##type_name##_free (d4_obj_##type_name##_t self); \
  \
  /**
   * Reallocates first object type and returns a copy of second object type.
   * @param self Object type to deallocate.
   * @param rhs Object type to create a copy of.
   * @return Copy of the second object type.
   */ \
  d4_obj_##type_name##_t d4_obj_##type_name##_realloc (d4_obj_##type_name##_t self, const d4_obj_##type_name##_t rhs); \
  \
  /**
   * Generates string representation of the object type.
   * @param self Object type to generate string representation for.
   * @return String representation of the object type.
   */ \
  d4_str_t d4_obj_##type_name##_str (const d4_obj_##type_name##_t self);

#endif
