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
  /**
   * Allocates map object.
   * @param len Number of key pairs that are passed as arguments.
   * @param ... Arguments list that consists of pairs with key followed by value.
   * @return Allocated map object.
   */ \
  d4_map_##key_type_name##MS##value_type_name##ME_t d4_map_##key_type_name##MS##value_type_name##ME_alloc (size_t len, ...); \
  \
  /**
   * Removes all elements and changes length to zero without affecting capacity.
   * @return Reference to itself.
   */ \
  d4_map_##key_type_name##MS##value_type_name##ME_t *d4_map_##key_type_name##MS##value_type_name##ME_clear (d4_map_##key_type_name##MS##value_type_name##ME_t *self); \
  \
  /**
   * Creates a copy of provided map object.
   * @param self Map object to create copy of.
   * @return Copy of provided map object
   */ \
  d4_map_##key_type_name##MS##value_type_name##ME_t d4_map_##key_type_name##MS##value_type_name##ME_copy (const d4_map_##key_type_name##MS##value_type_name##ME_t self); \
  \
  /**
   * Checks whether map has any elements.
   * @param self Map object to check.
   * @return Whether map has any elements.
   */ \
  bool d4_map_##key_type_name##MS##value_type_name##ME_empty (const d4_map_##key_type_name##MS##value_type_name##ME_t self); \
  \
  /**
   * Compares whether map object is equal to right-hand map object.
   * @param self Map object to check.
   * @param rhs Right-hand map object to check.
   * @return Whether two map objects are equal.
   */ \
  bool d4_map_##key_type_name##MS##value_type_name##ME_eq (const d4_map_##key_type_name##MS##value_type_name##ME_t self, const d4_map_##key_type_name##MS##value_type_name##ME_t rhs); \
  \
  /**
   * Deallocates map object.
   * @param self Map object to deallocate.
   */ \
  void d4_map_##key_type_name##MS##value_type_name##ME_free (d4_map_##key_type_name##MS##value_type_name##ME_t self); \
  \
  /**
   * Retrieves value by key and throws if key doesn’t exist.
   * @param state Error state to perform action on.
   * @param line Line where error appeared.
   * @param col Line column where error appeared.
   * @param self Map object to perform action on.
   * @param key Key of map object pair to retrieve.
   * @return Value of found map object pair.
   */ \
  value_type d4_map_##key_type_name##MS##value_type_name##ME_get (d4_err_state_t *state, int line, int col, const d4_map_##key_type_name##MS##value_type_name##ME_t self, const key_type key); \
  \
  /**
   * Checks whether map object contains a pair with provided key.
   * @param self Map object to check.
   * @param key Key of map object pair to check.
   * @return Whether map object contains a pair with provided key.
   */ \
  bool d4_map_##key_type_name##MS##value_type_name##ME_has (const d4_map_##key_type_name##MS##value_type_name##ME_t self, const key_type key); \
  \
  /**
   * Returns array of map keys.
   * @param self Map object to use.
   * @return Array of map keys.
   */ \
  d4_arr_##key_type_name##_t d4_map_##key_type_name##MS##value_type_name##ME_keys (const d4_map_##key_type_name##MS##value_type_name##ME_t self); \
  \
  /**
   * Merges other map’s data into self map. When iterating, if key exists it will update pair with a new value. Reallocates map object if load factor more than 75%.
   * @param self Map object to merge into.
   * @param other Map object to merge from.
   * @return Reference to itself.
   */ \
  d4_map_##key_type_name##MS##value_type_name##ME_t *d4_map_##key_type_name##MS##value_type_name##ME_merge (d4_map_##key_type_name##MS##value_type_name##ME_t *self, const d4_map_##key_type_name##MS##value_type_name##ME_t other); \
  \
  /**
   * Creates and places a pair inside map object.
   * @param self Map object to place pair into.
   * @param id Hash of the new pair.
   * @param key Key of the new pair.
   * @param value Value of the new pair.
   */ \
  void d4_map_##key_type_name##MS##value_type_name##ME_place (d4_map_##key_type_name##MS##value_type_name##ME_t self, const d4_str_t id, const key_type key, const value_type value); \
  \
  /**
   * Deallocates current map object and returns a copy of another map object.
   * @param self Map object to deallocate.
   * @param rhs Map object to return a copy of.
   * @return Copy of another map object.
   */ \
  d4_map_##key_type_name##MS##value_type_name##ME_t d4_map_##key_type_name##MS##value_type_name##ME_realloc (d4_map_##key_type_name##MS##value_type_name##ME_t self, const d4_map_##key_type_name##MS##value_type_name##ME_t rhs); \
  \
  /**
   * Removes provided key from the map object and if key doesn’t exist throws error.
   * @param state Error state to perform action on.
   * @param line Line where error appeared.
   * @param col Line column where error appeared.
   * @return Reference to itself.
   */ \
  d4_map_##key_type_name##MS##value_type_name##ME_t *d4_map_##key_type_name##MS##value_type_name##ME_remove (d4_err_state_t *state, int line, int col, d4_map_##key_type_name##MS##value_type_name##ME_t *self, const key_type search_key); \
  \
  /**
   * Reserves a room for a specified number of pairs. Does nothing if the size provided is lower than the current capacity.
   * @param self Map object to increase capacity of.
   * @param size New map object capacity.
   * @return Reference to itself.
   */ \
  d4_map_##key_type_name##MS##value_type_name##ME_t *d4_map_##key_type_name##MS##value_type_name##ME_reserve (d4_map_##key_type_name##MS##value_type_name##ME_t *self, int32_t size); \
  \
  /**
   * Sets a key inside map object, if key exists - updates its value. Reallocates map object if load factor more than 75%.
   * @param self Map object to set a pair for.
   * @param key Key of the pair.
   * @param value Value of the pair.
   * @return Reference to itself.
   */ \
  d4_map_##key_type_name##MS##value_type_name##ME_t *d4_map_##key_type_name##MS##value_type_name##ME_set (d4_map_##key_type_name##MS##value_type_name##ME_t *self, const key_type key, const value_type value); \
  \
  /**
   * Reduces capacity to a current map object length multiplied by 2.
   * @param self Map object to reduce capacity of.
   * @return Reference to itself.
   */ \
  d4_map_##key_type_name##MS##value_type_name##ME_t *d4_map_##key_type_name##MS##value_type_name##ME_shrink (d4_map_##key_type_name##MS##value_type_name##ME_t *self); \
  \
  /**
   * Generates string representation of the map object.
   * @param self Map object to generate string representation for.
   * @return String representation of the map object.
   */ \
  d4_str_t d4_map_##key_type_name##MS##value_type_name##ME_str (const d4_map_##key_type_name##MS##value_type_name##ME_t self); \
  \
  /**
   * Returns array of map values.
   * @param self Map object to use.
   * @return Array of map values.
   */ \
  d4_arr_##value_type_name##_t d4_map_##key_type_name##MS##value_type_name##ME_values (const d4_map_##key_type_name##MS##value_type_name##ME_t self);

#endif
