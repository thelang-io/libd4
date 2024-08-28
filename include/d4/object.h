/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_OBJECT_H
#define D4_OBJECT_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include <d4/object-macro.h>

/**
 * Macro used to define object type.
 * @param type_name Name of the object type.
 * @param display_name Name that is used when converting object type to string representation.
 * @param alloc_block Block used for alloc method of object type.
 * @param copy_block Block used for copy method of object type.
 * @param eq_block Block used for eq method of object type.
 * @param free_block Block used for free method of object type.
 * @param str_block Block used for str method of object type.
 */
#define D4_OBJECT_DEFINE(type_name, display_name, alloc_block, copy_block, eq_block, free_block, str_block, ...) \
  d4_obj_##type_name##_t d4_obj_##type_name##_alloc (__VA_ARGS__) { \
    d4_obj_##type_name##_t self; \
    alloc_block \
    return self; \
  } \
  \
  d4_obj_##type_name##_t d4_obj_##type_name##_copy (const d4_obj_##type_name##_t self) { \
    d4_obj_##type_name##_t result; \
    copy_block \
    return result; \
  } \
  \
  bool d4_obj_##type_name##_eq (const d4_obj_##type_name##_t self, const d4_obj_##type_name##_t rhs) eq_block \
  \
  void d4_obj_##type_name##_free (d4_obj_##type_name##_t self) free_block \
  \
  d4_obj_##type_name##_t d4_obj_##type_name##_realloc (d4_obj_##type_name##_t self, const d4_obj_##type_name##_t rhs) { \
    d4_obj_##type_name##_free(self); \
    return d4_obj_##type_name##_copy(rhs); \
  } \
  \
  d4_str_t d4_obj_##type_name##_str (const d4_obj_##type_name##_t self) { \
    d4_str_t right_brace = d4_str_alloc(L"}"); \
    d4_str_t result = d4_str_empty_val; \
    d4_str_t tmp; \
    str_block \
    result = d4_str_realloc(result, tmp = d4_str_concat(d4_str_alloc(#display_name  L"{"), result)); \
    d4_str_free(tmp); \
    result = d4_str_realloc(result, tmp = d4_str_concat(result, right_brace)); \
    d4_str_free(tmp); \
    d4_str_free(right_brace); \
    return result; \
  }

/**
 * Helper function to make object type definition str_block generation easier.
 * @param result String to append data to.
 * @param name Name of the field.
 * @param value Value fo the object type field.
 * @return Resulting string with information about new field added.
 */
d4_str_t d4_obj_str_append (d4_str_t result, d4_str_t name, d4_str_t value);

#endif
