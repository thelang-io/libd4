/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_MAP_MACRO_H
#define THE_MAP_MACRO_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/array-macro.h>

/**
 * Macro that should be used to generate map type.
 * @param key_type_name Type name of the key.
 * @param key_type Key type of the map object.
 * @param value_type_name Type name of the value.
 * @param value_type Value type of the map object.
 */
#define THE_MAP_DECLARE(key_type_name, key_type, value_type_name, value_type) \
  /** Object representation of the map pair type. */ \
  typedef struct the_map_##key_type_name##MS##value_type_name##ME_pair { \
    \
    /* Identifier of the map pair (used internally). */ \
    the_str_t id; \
    \
    /* Key of the map pair. */ \
    key_type key; \
    \
    /* Value of the map pair. */ \
    value_type value; \
    \
    /* Pointer to the next pair of the linked list. */ \
    struct the_map_##key_type_name##MS##value_type_name##ME_pair *next; \
  } the_map_##key_type_name##MS##value_type_name##ME_pair_t; \
  \
  /** Object representation of the map type. */ \
  typedef struct { \
    /* Data container of the pair pointers. */ \
    the_map_##key_type_name##MS##value_type_name##ME_pair_t **data; \
    \
    /* Total allocated size of the map object. */ \
    size_t cap; \
    \
    /* Length of the map object. */ \
    size_t len; \
  } the_map_##key_type_name##MS##value_type_name##ME_t; \
  \
  /* todo */ \
  the_map_##key_type_name##MS##value_type_name##ME_t the_map_##key_type_name##MS##value_type_name##ME_alloc (size_t len, ...); \
  \
  /* todo */ \
  the_map_##key_type_name##MS##value_type_name##ME_t *the_map_##key_type_name##MS##value_type_name##ME_clear (the_map_##key_type_name##MS##value_type_name##ME_t *self); \
  \
  /* todo */ \
  the_map_##key_type_name##MS##value_type_name##ME_t the_map_##key_type_name##MS##value_type_name##ME_copy (const the_map_##key_type_name##MS##value_type_name##ME_t self); \
  \
  /* todo */ \
  bool the_map_##key_type_name##MS##value_type_name##ME_empty (const the_map_##key_type_name##MS##value_type_name##ME_t self); \
  \
  /* todo */ \
  bool the_map_##key_type_name##MS##value_type_name##ME_eq (const the_map_##key_type_name##MS##value_type_name##ME_t self, const the_map_##key_type_name##MS##value_type_name##ME_t rhs); \
  \
  /* todo */ \
  void the_map_##key_type_name##MS##value_type_name##ME_free (the_map_##key_type_name##MS##value_type_name##ME_t self); \
  \
  /* todo */ \
  value_type the_map_##key_type_name##MS##value_type_name##ME_get (the_err_state_t *state, int line, int col, const the_map_##key_type_name##MS##value_type_name##ME_t self, const key_type key); \
  \
  /* todo */ \
  bool the_map_##key_type_name##MS##value_type_name##ME_has (const the_map_##key_type_name##MS##value_type_name##ME_t self, const key_type key); \
  \
  /* todo */ \
  the_arr_int_t the_map_##key_type_name##MS##value_type_name##ME_keys (const the_map_##key_type_name##MS##value_type_name##ME_t self); \
  \
  /* todo */ \
  the_map_##key_type_name##MS##value_type_name##ME_t *the_map_##key_type_name##MS##value_type_name##ME_merge (the_map_##key_type_name##MS##value_type_name##ME_t *self, const the_map_##key_type_name##MS##value_type_name##ME_t other); \
  \
  /* todo */ \
  void the_map_##key_type_name##MS##value_type_name##ME_place (the_map_##key_type_name##MS##value_type_name##ME_t self, const the_str_t id, const key_type key, const value_type value); \
  \
  /* todo */ \
  the_map_##key_type_name##MS##value_type_name##ME_t the_map_##key_type_name##MS##value_type_name##ME_realloc (the_map_##key_type_name##MS##value_type_name##ME_t self, const the_map_##key_type_name##MS##value_type_name##ME_t rhs); \
  \
  /* todo */ \
  the_map_##key_type_name##MS##value_type_name##ME_t *the_map_##key_type_name##MS##value_type_name##ME_remove (the_err_state_t *state, int line, int col, the_map_##key_type_name##MS##value_type_name##ME_t *self, const key_type search_key); \
  \
  /* todo */ \
  the_map_##key_type_name##MS##value_type_name##ME_t *the_map_##key_type_name##MS##value_type_name##ME_reserve (the_map_##key_type_name##MS##value_type_name##ME_t *self, int32_t size); \
  \
  /* todo */ \
  the_map_##key_type_name##MS##value_type_name##ME_t *the_map_##key_type_name##MS##value_type_name##ME_set (the_map_##key_type_name##MS##value_type_name##ME_t *self, const key_type key, const value_type value); \
  \
  /* todo */ \
  the_map_##key_type_name##MS##value_type_name##ME_t *the_map_##key_type_name##MS##value_type_name##ME_shrink (the_map_##key_type_name##MS##value_type_name##ME_t *self); \
  \
  /* todo */ \
  the_str_t the_map_##key_type_name##MS##value_type_name##ME_str (const the_map_##key_type_name##MS##value_type_name##ME_t self); \
  \
  /* todo */ \
  the_arr_##value_type_name##_t the_map_##key_type_name##MS##value_type_name##ME_values (const the_map_##key_type_name##MS##value_type_name##ME_t self);

#endif
