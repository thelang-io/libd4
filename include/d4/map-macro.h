/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_MAP_MACRO_H
#define D4_MAP_MACRO_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include <d4/array-macro.h>

/**
 * Macro that should be used to generate map type.
 * @param key_type_name Type name of the key.
 * @param key_type Key type of the map object.
 * @param value_type_name Type name of the value.
 * @param value_type Value type of the map object.
 */
#define D4_MAP_DECLARE(key_type_name, key_type, value_type_name, value_type) \
  /** Object representation of the map pair type. */ \
  typedef struct d4_map_##key_type_name##MS##value_type_name##ME_pair { \
    \
    /* Identifier of the map pair (used internally). */ \
    d4_str_t id; \
    \
    /* Key of the map pair. */ \
    key_type key; \
    \
    /* Value of the map pair. */ \
    value_type value; \
    \
    /* Pointer to the next pair of the linked list. */ \
    struct d4_map_##key_type_name##MS##value_type_name##ME_pair *next; \
  } d4_map_##key_type_name##MS##value_type_name##ME_pair_t; \
  \
  /** Object representation of the map type. */ \
  typedef struct { \
    /* Data container of the pair pointers. */ \
    d4_map_##key_type_name##MS##value_type_name##ME_pair_t **data; \
    \
    /* Total allocated size of the map object. */ \
    size_t cap; \
    \
    /* Length of the map object. */ \
    size_t len; \
  } d4_map_##key_type_name##MS##value_type_name##ME_t; \
  \
  /* todo */ \
  d4_map_##key_type_name##MS##value_type_name##ME_t d4_map_##key_type_name##MS##value_type_name##ME_alloc (size_t len, ...); \
  \
  /* todo */ \
  d4_map_##key_type_name##MS##value_type_name##ME_t *d4_map_##key_type_name##MS##value_type_name##ME_clear (d4_map_##key_type_name##MS##value_type_name##ME_t *self); \
  \
  /* todo */ \
  d4_map_##key_type_name##MS##value_type_name##ME_t d4_map_##key_type_name##MS##value_type_name##ME_copy (const d4_map_##key_type_name##MS##value_type_name##ME_t self); \
  \
  /* todo */ \
  bool d4_map_##key_type_name##MS##value_type_name##ME_empty (const d4_map_##key_type_name##MS##value_type_name##ME_t self); \
  \
  /* todo */ \
  bool d4_map_##key_type_name##MS##value_type_name##ME_eq (const d4_map_##key_type_name##MS##value_type_name##ME_t self, const d4_map_##key_type_name##MS##value_type_name##ME_t rhs); \
  \
  /* todo */ \
  void d4_map_##key_type_name##MS##value_type_name##ME_free (d4_map_##key_type_name##MS##value_type_name##ME_t self); \
  \
  /* todo */ \
  value_type d4_map_##key_type_name##MS##value_type_name##ME_get (d4_err_state_t *state, int line, int col, const d4_map_##key_type_name##MS##value_type_name##ME_t self, const key_type key); \
  \
  /* todo */ \
  bool d4_map_##key_type_name##MS##value_type_name##ME_has (const d4_map_##key_type_name##MS##value_type_name##ME_t self, const key_type key); \
  \
  /* todo */ \
  d4_arr_##key_type_name##_t d4_map_##key_type_name##MS##value_type_name##ME_keys (const d4_map_##key_type_name##MS##value_type_name##ME_t self); \
  \
  /* todo */ \
  d4_map_##key_type_name##MS##value_type_name##ME_t *d4_map_##key_type_name##MS##value_type_name##ME_merge (d4_map_##key_type_name##MS##value_type_name##ME_t *self, const d4_map_##key_type_name##MS##value_type_name##ME_t other); \
  \
  /* todo */ \
  void d4_map_##key_type_name##MS##value_type_name##ME_place (d4_map_##key_type_name##MS##value_type_name##ME_t self, const d4_str_t id, const key_type key, const value_type value); \
  \
  /* todo */ \
  d4_map_##key_type_name##MS##value_type_name##ME_t d4_map_##key_type_name##MS##value_type_name##ME_realloc (d4_map_##key_type_name##MS##value_type_name##ME_t self, const d4_map_##key_type_name##MS##value_type_name##ME_t rhs); \
  \
  /* todo */ \
  d4_map_##key_type_name##MS##value_type_name##ME_t *d4_map_##key_type_name##MS##value_type_name##ME_remove (d4_err_state_t *state, int line, int col, d4_map_##key_type_name##MS##value_type_name##ME_t *self, const key_type search_key); \
  \
  /* todo */ \
  d4_map_##key_type_name##MS##value_type_name##ME_t *d4_map_##key_type_name##MS##value_type_name##ME_reserve (d4_map_##key_type_name##MS##value_type_name##ME_t *self, int32_t size); \
  \
  /* todo */ \
  d4_map_##key_type_name##MS##value_type_name##ME_t *d4_map_##key_type_name##MS##value_type_name##ME_set (d4_map_##key_type_name##MS##value_type_name##ME_t *self, const key_type key, const value_type value); \
  \
  /* todo */ \
  d4_map_##key_type_name##MS##value_type_name##ME_t *d4_map_##key_type_name##MS##value_type_name##ME_shrink (d4_map_##key_type_name##MS##value_type_name##ME_t *self); \
  \
  /* todo */ \
  d4_str_t d4_map_##key_type_name##MS##value_type_name##ME_str (const d4_map_##key_type_name##MS##value_type_name##ME_t self); \
  \
  /* todo */ \
  d4_arr_##value_type_name##_t d4_map_##key_type_name##MS##value_type_name##ME_values (const d4_map_##key_type_name##MS##value_type_name##ME_t self);

#endif
