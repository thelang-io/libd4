/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_ARC_H
#define D4_ARC_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include "safe.h"
#include "arc-macro.h"

/**
 * Macro used to define automatic reference counter type.
 * @param type_name Name of the automatic reference counter type.
 * @param ref_type Reference type of the automatic reference counter object.
 * @param copy_block Block used for copy method of automatic reference counter type.
 * @param eq_block Block used for eq method of automatic reference counter type.
 * @param free_block Block used for free method of automatic reference counter type.
 * @param str_block Block used for str method of automatic reference counter type.
 */
#define D4_ARC_DEFINE(type_name, ref_type, copy_block, eq_block, free_block, str_block) \
  d4_arc_##type_name##_t d4_arc_##type_name##_alloc (const ref_type ref) { \
    d4_arc_##type_name##_t self = d4_safe_alloc(sizeof(struct d4_arc_##type_name##_t)); \
    self->count = 1; \
    self->ref = copy_block; \
    return self; \
  } \
  \
  d4_arc_##type_name##_t d4_arc_##type_name##_copy (const d4_arc_##type_name##_t self) { \
    self->count++; \
    return self; \
  } \
  \
  bool d4_arc_##type_name##_eq (const d4_arc_##type_name##_t self, const d4_arc_##type_name##_t rhs) { \
    const ref_type lhs_ref = self->ref; \
    const ref_type rhs_ref = rhs->ref; \
    return eq_block; \
  } \
  \
  void d4_arc_##type_name##_free (d4_arc_##type_name##_t self) { \
    ref_type ref = self->ref; \
    self->count--; \
    if (self->count != 0) return; \
    free_block; \
    d4_safe_free(self); \
  } \
  \
  d4_arc_##type_name##_t d4_arc_##type_name##_realloc (d4_arc_##type_name##_t self, const ref_type ref) { \
    { \
      ref_type ref = self->ref; \
      free_block; \
    } \
    self->ref = copy_block; \
    return self; \
  } \
  \
  d4_str_t d4_arc_##type_name##_str (const d4_arc_##type_name##_t self) { \
    const ref_type ref = self->ref; \
    return str_block; \
  }

#endif
