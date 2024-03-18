/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_UNION_H
#define THE_UNION_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/union-macro.h>

// todo test

/**
 * Macro that can be used to define a function object without parameters.
 * @param subtypes_type_name todo
 * @param alloc_block todo
 * @param copy_block todo
 * @param eq_block todo
 * @param free_block todo
 * @param ne_block todo
 * @param str_block todo
 */
#define THE_UNION_DEFINE(subtypes_type_name, alloc_block, copy_block, eq_block, free_block, ne_block, str_block) \
  the_union_##subtypes_type_name##UE_t the_union_##subtypes_type_name##UE_alloc (int type, ...) { \
    the_union_##subtypes_type_name##UE_t self; \
    va_list args; \
    self.type = type; \
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
    return the_str_alloc(L""); \
  }

#endif
