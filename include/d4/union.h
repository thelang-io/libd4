/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_UNION_H
#define D4_UNION_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include "union-macro.h"

/**
 * Macro that can be used to define an union object.
 * @param subtypes_type_name All sub-types joined by US (short for "union separator") separator.
 * @param alloc_block Block that is used for alloc method of union object.
 * @param copy_block Block that is used for copy method of union object.
 * @param eq_block Block that is used for equals method of union object.
 * @param free_block Block that is used for free method of union object.
 * @param str_block Block that is used for str method of union object.
 */
#define D4_UNION_DEFINE(subtypes_type_name, alloc_block, copy_block, eq_block, free_block, str_block) \
  d4_union_##subtypes_type_name##UE_t d4_union_##subtypes_type_name##UE_alloc (int type, ...) { \
    d4_union_##subtypes_type_name##UE_t self; \
    va_list args; \
    self.type = type; \
    if (type == -1) return self; \
    va_start(args, type); \
    alloc_block \
    va_end(args); \
    return self; \
  } \
  \
  d4_union_##subtypes_type_name##UE_t d4_union_##subtypes_type_name##UE_copy (const d4_union_##subtypes_type_name##UE_t self) { \
    d4_union_##subtypes_type_name##UE_t result; \
    result.type = self.type; \
    copy_block \
    return result; \
  } \
  \
  bool d4_union_##subtypes_type_name##UE_eq (const d4_union_##subtypes_type_name##UE_t self, const d4_union_##subtypes_type_name##UE_t rhs) { \
    if (self.type != rhs.type) return false; \
    eq_block \
    return false; \
  } \
  \
  void d4_union_##subtypes_type_name##UE_free (d4_union_##subtypes_type_name##UE_t self) free_block \
  \
  d4_union_##subtypes_type_name##UE_t d4_union_##subtypes_type_name##UE_realloc (d4_union_##subtypes_type_name##UE_t self, const d4_union_##subtypes_type_name##UE_t rhs) { \
    d4_union_##subtypes_type_name##UE_free(self); \
    return d4_union_##subtypes_type_name##UE_copy(rhs); \
  } \
  \
  d4_str_t d4_union_##subtypes_type_name##UE_str (const d4_union_##subtypes_type_name##UE_t self) { \
    str_block \
    return (d4_str_t) {NULL, 0, false}; \
  }

#endif
