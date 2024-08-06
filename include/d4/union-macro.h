/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_UNION_MACRO_H
#define D4_UNION_MACRO_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include <d4/string-type.h>

/**
 * Macro that should be used to generate union type entities.
 * @param subtypes_type_name Subtypes type name joined by "US" (short for union separator).
 * @param subtypes_definition Block definition of subtypes that is used with union.
 */
#define D4_UNION_DECLARE(subtypes_type_name, subtypes_definition) \
  /** Object representation of the union type. */ \
  typedef struct { \
    /** Type of the union object. */ \
    int type; \
    \
    /** Field that is holding data value of the union type. */ \
    union subtypes_definition data; \
  } d4_union_##subtypes_type_name##UE_t; \
  \
  /**
   * Allocates union object.
   * @param type Type of the union object. If union has no initializer then -1.
   * @param ... Initializer of the union object.
   * @return Allocated union object.
   */ \
  d4_union_##subtypes_type_name##UE_t d4_union_##subtypes_type_name##UE_alloc (int type, ...); \
  \
  /**
   * Copies union object.
   * @param self Union object to copy.
   * @return Newly copied union object.
   */ \
  d4_union_##subtypes_type_name##UE_t d4_union_##subtypes_type_name##UE_copy (const d4_union_##subtypes_type_name##UE_t self); \
  \
  /**
   * Compares two union objects.
   * @param self First union object to compare.
   * @param rhs Second union object to compare.
   * @return Whether two union objects are equal.
   */ \
  bool d4_union_##subtypes_type_name##UE_eq (const d4_union_##subtypes_type_name##UE_t self, const d4_union_##subtypes_type_name##UE_t rhs); \
  \
  /**
   * Deallocates union object.
   * @param self Union object to deallocate.
   */ \
  void d4_union_##subtypes_type_name##UE_free (d4_union_##subtypes_type_name##UE_t self); \
  \
  /**
   * Reallocates first union object and returns a copy of second union object.
   * @param self Union object to reallocate.
   * @param rhs Union object to copy from.
   * @return Second union object copied.
   */ \
  d4_union_##subtypes_type_name##UE_t d4_union_##subtypes_type_name##UE_realloc (d4_union_##subtypes_type_name##UE_t self, const d4_union_##subtypes_type_name##UE_t rhs); \
  \
  /**
   * Generates string representation of the union object.
   * @param self Union object to generate string representation for.
   * @return String representation of the union object.
   */ \
  d4_str_t d4_union_##subtypes_type_name##UE_str (const d4_union_##subtypes_type_name##UE_t self);

#endif
