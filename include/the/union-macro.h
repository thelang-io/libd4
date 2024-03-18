/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_UNION_MACRO_H
#define THE_UNION_MACRO_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/string-type.h>
#include <stdbool.h>

// todo documentation

/**
 * Macro that should be used to generate union type entities.
 * @param subtypes_type_name Subtypes type name joined by "US" (short for union separator).
 * @param subtypes_definition Block definition of subtypes that is used with union.
 */
#define THE_UNION_DECLARE(subtypes_type_name, subtypes_definition) \
  /** Object representation of the union type. */ \
  typedef struct { \
    /** Type of the union object. */ \
    int type; \
    \
    /** Field that is holding data value of the union type. */ \
    union subtypes_definition data; \
  } the_union_##subtypes_type_name##UE_t; \
  \
  the_union_##subtypes_type_name##UE_t the_union_##subtypes_type_name##UE_alloc (int type, ...); \
  the_union_##subtypes_type_name##UE_t the_union_##subtypes_type_name##UE_copy (const the_union_##subtypes_type_name##UE_t self); \
  bool the_union_##subtypes_type_name##UE_eq (const the_union_##subtypes_type_name##UE_t self, const the_union_##subtypes_type_name##UE_t rhs); \
  void the_union_##subtypes_type_name##UE_free (the_union_##subtypes_type_name##UE_t self); \
  the_union_##subtypes_type_name##UE_t the_union_##subtypes_type_name##UE_realloc (the_union_##subtypes_type_name##UE_t self, const the_union_##subtypes_type_name##UE_t rhs); \
  the_str_t the_union_##subtypes_type_name##UE_str (const the_union_##subtypes_type_name##UE_t self);

#endif
