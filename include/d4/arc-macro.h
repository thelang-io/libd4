/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_ARC_MACRO_H
#define D4_ARC_MACRO_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include "string.h"

/**
 * Macro used to forward declare automatic reference counter type.
 * @param type_name Name of the automatic reference counter type.
 */
#define D4_ARC_FORWARD_DECLARE(type_name) \
  /** Typedef representation of the automatic reference counter type. */ \
  typedef struct d4_arc_##type_name##_t *d4_arc_##type_name##_t;

/**
 * Macro used to declare automatic reference counter type.
 * @param type_name Name of the automatic reference counter type.
 * @param ref_type Reference type of the automatic reference counter object.
 */
#define D4_ARC_DECLARE(type_name, ref_type) \
  /** Structure representation of the automatic reference counter type. */ \
  struct d4_arc_##type_name##_t { \
    /** Reference to automatic reference counter object. */ \
    ref_type ref; \
    \
    /** Number of references to automatic reference counter object. */ \
    int count; \
  }; \
  \
  /**
   * Allocates automatic reference counter type.
   * @param ref Allocation function parameters specified during declaration.
   * @return Allocated automatic reference counter type.
   */ \
  d4_arc_##type_name##_t d4_arc_##type_name##_alloc (const ref_type ref); \
  \
  /**
   * Creates a copy of automatic reference counter type.
   * @param self Automatic reference counter type to create a copy of.
   * @return Copy of the provided automatic reference counter type.
   */ \
  d4_arc_##type_name##_t d4_arc_##type_name##_copy (const d4_arc_##type_name##_t self); \
  \
  /**
   * Compares two automatic reference counter types.
   * @param self First automatic reference counter type to compare.
   * @param rhs Second automatic reference counter type to compare.
   * @return Whether two automatic reference counter types are the same.
   */ \
  bool d4_arc_##type_name##_eq (const d4_arc_##type_name##_t self, const d4_arc_##type_name##_t rhs); \
  \
  /**
   * Deallocates automatic reference counter type.
   * @param self Automatic reference counter type to deallocate.
   */ \
  void d4_arc_##type_name##_free (d4_arc_##type_name##_t self); \
  \
  /**
   * Reallocates automatic reference counter type.
   * @param self Automatic reference counter type to reallocate.
   * @param ref Object to set for automatic reference counter type.
   * @return Reallocated automatic reference counter type.
   */ \
  d4_arc_##type_name##_t d4_arc_##type_name##_realloc (d4_arc_##type_name##_t self, const ref_type ref); \
  \
  /**
   * Generates string representation of the automatic reference counter type.
   * @param self Automatic reference counter type to generate string representation for.
   * @return String representation of the automatic reference counter type.
   */ \
  d4_str_t d4_arc_##type_name##_str (const d4_arc_##type_name##_t self);

#endif
