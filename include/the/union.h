/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_UNION_H
#define THE_UNION_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/union-macro.h>

/**
 * Macro that can be used to define an union object.
 * @param subtypes_type_name All sub-types joined by US (short for "union separator") separator.
 * @param alloc_block Block that is used for alloc method of union object.
 * @param copy_block Block that is used for copy method of union object.
 * @param eq_block Block that is used for equals method of union object.
 * @param free_block Block that is used for free method of union object.
 * @param str_block Block that is used for str method of union object.
 */
#define THE_UNION_DEFINE(subtypes_type_name, alloc_block, copy_block, eq_block, free_block, str_block) \
  the_union_##subtypes_type_name##UE_t the_union_##subtypes_type_name##UE_alloc (int type, ...) { \
    the_union_##subtypes_type_name##UE_t self; \
    va_list args; \
    self.type = type; \
    if (type == -1) return self; \
    va_start(args, type); \
    alloc_block \
    va_end(args); \
    return self; \
  } \
  \
  the_union_##subtypes_type_name##UE_t the_union_##subtypes_type_name##UE_copy (const the_union_##subtypes_type_name##UE_t self) { \
    the_union_##subtypes_type_name##UE_t result; \
    result.type = self.type; \
    copy_block \
    return result; \
  } \
  \
  bool the_union_##subtypes_type_name##UE_eq (const the_union_##subtypes_type_name##UE_t self, const the_union_##subtypes_type_name##UE_t rhs) { \
    if (self.type != rhs.type) return false; \
    eq_block \
    return false; \
  } \
  \
  void the_union_##subtypes_type_name##UE_free (the_union_##subtypes_type_name##UE_t self) free_block \
  \
  the_union_##subtypes_type_name##UE_t the_union_##subtypes_type_name##UE_realloc (the_union_##subtypes_type_name##UE_t self, const the_union_##subtypes_type_name##UE_t rhs) { \
    the_union_##subtypes_type_name##UE_free(self); \
    return the_union_##subtypes_type_name##UE_copy(rhs); \
  } \
  \
  the_str_t the_union_##subtypes_type_name##UE_str (const the_union_##subtypes_type_name##UE_t self) { \
    str_block \
    return (the_str_t) {NULL, 0, false}; \
  }

#endif
