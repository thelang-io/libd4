/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_MAP_H
#define D4_MAP_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include "map-macro.h"
#include "array.h"

/**
 * Macro that can be used to define a map object.
 * @param key_type_name Type name of the key.
 * @param key_type Key type of the array object.
 * @param key_alloc_type Key type of the key to be used inside variadic argument (should be cast to int in some cases).
 * @param key_copy_block Block that is used for copy method of key.
 * @param key_eq_block Block that is used for equals method of key.
 * @param key_free_block Block that is used for free method of key.
 * @param key_hash_block Block that is used to hash key.
 * @param key_str_block Block that is used for str method of key.
 * @param value_type_name Type name of the value.
 * @param value_type Value type of the array object.
 * @param value_alloc_type Value type of the value to be used inside variadic argument (should be cast to int in some cases).
 * @param value_copy_block Block that is used for copy method of value.
 * @param value_eq_block Block that is used for equals method of value.
 * @param value_free_block Block that is used for free method of value.
 * @param value_str_block Block that is used for str method of value.
 */
#define D4_MAP_DEFINE(key_type_name, key_type, key_alloc_type, key_copy_block, key_eq_block, key_free_block, key_hash_block, key_str_block, value_type_name, value_type, value_alloc_type, value_copy_block, value_eq_block, value_free_block, value_str_block) \
  d4_map_##key_type_name##MS##value_type_name##ME_t d4_map_##key_type_name##MS##value_type_name##ME_alloc (size_t len, ...) { \
    size_t cap = d4_map_calc_cap(0x0F, len); \
    d4_map_##key_type_name##MS##value_type_name##ME_t self = {d4_safe_alloc(cap * sizeof(d4_map_##key_type_name##MS##value_type_name##ME_pair_t *)), cap, len}; \
    va_list args; \
    memset(self.data, 0, cap * sizeof(d4_map_##key_type_name##MS##value_type_name##ME_pair_t *)); \
    if (len == 0) return self; \
    va_start(args, len); \
    for (size_t i = 0; i < len; i++) { \
      const key_type key = va_arg(args, key_alloc_type); \
      const value_type value = va_arg(args, value_alloc_type); \
      d4_str_t id = key_hash_block; \
      d4_map_##key_type_name##MS##value_type_name##ME_place(self, id, key, value); \
      d4_str_free(id); \
    } \
    va_end(args); \
    return self; \
  } \
  \
  d4_map_##key_type_name##MS##value_type_name##ME_t *d4_map_##key_type_name##MS##value_type_name##ME_clear (d4_map_##key_type_name##MS##value_type_name##ME_t *self) { \
    for (size_t i = 0; i < self->cap; i++) { \
      while (self->data[i] != NULL) { \
        d4_map_##key_type_name##MS##value_type_name##ME_pair_t *it = self->data[i]; \
        key_type key = it->key; \
        value_type val = it->value; \
        d4_str_free(it->id); \
        key_free_block; \
        value_free_block; \
        self->data[i] = it->next; \
        d4_safe_free(it); \
      } \
    } \
    memset(self->data, 0, self->cap * sizeof(d4_map_##key_type_name##MS##value_type_name##ME_pair_t *)); \
    self->len = 0; \
    return self; \
  } \
  \
  d4_map_##key_type_name##MS##value_type_name##ME_t d4_map_##key_type_name##MS##value_type_name##ME_copy (const d4_map_##key_type_name##MS##value_type_name##ME_t self) { \
    d4_map_##key_type_name##MS##value_type_name##ME_t new_self = { \
      d4_safe_alloc(self.cap * sizeof(d4_map_##key_type_name##MS##value_type_name##ME_pair_t *)), \
      self.cap, \
      self.len \
    }; \
    memset(new_self.data, 0, new_self.cap * sizeof(d4_map_##key_type_name##MS##value_type_name##ME_pair_t *)); \
    for (size_t i = 0; i < self.cap; i++) { \
      d4_map_##key_type_name##MS##value_type_name##ME_pair_t *it = self.data[i]; \
      while (it != NULL) { \
        d4_map_##key_type_name##MS##value_type_name##ME_place(new_self, it->id, it->key, it->value); \
        it = it->next; \
      } \
    } \
    return new_self; \
  } \
  \
  bool d4_map_##key_type_name##MS##value_type_name##ME_empty (const d4_map_##key_type_name##MS##value_type_name##ME_t self) { \
    return self.len == 0; \
  } \
  \
  bool d4_map_##key_type_name##MS##value_type_name##ME_eq (const d4_map_##key_type_name##MS##value_type_name##ME_t self, const d4_map_##key_type_name##MS##value_type_name##ME_t rhs) { \
    if (self.len != rhs.len) return false; \
    for (size_t i = 0; i < self.cap; i++) { \
      d4_map_##key_type_name##MS##value_type_name##ME_pair_t *it1 = self.data[i]; \
      while (it1 != NULL) { \
        size_t rhs_index = d4_map_hash(it1->id, rhs.cap); \
        value_type lhs_val = it1->value; \
        value_type rhs_val; \
        d4_map_##key_type_name##MS##value_type_name##ME_pair_t *it2 = rhs.data[rhs_index]; \
        while (it2 != NULL) { \
          if (d4_str_eq(it2->id, it1->id)) break; \
          it2 = it2->next; \
        } \
        if (it2 == NULL) return false; \
        rhs_val = it2->value; \
        if (!(value_eq_block)) return false; \
        it1 = it1->next; \
      } \
    } \
    return true; \
  } \
  \
  void d4_map_##key_type_name##MS##value_type_name##ME_free (d4_map_##key_type_name##MS##value_type_name##ME_t self) { \
    for (size_t i = 0; i < self.cap; i++) { \
      while (self.data[i] != NULL) { \
        d4_map_##key_type_name##MS##value_type_name##ME_pair_t *it = self.data[i]; \
        key_type key = it->key; \
        value_type val = it->value; \
        d4_str_free(it->id); \
        key_free_block; \
        value_free_block; \
        self.data[i] = it->next; \
        d4_safe_free(it); \
      } \
    } \
    d4_safe_free(self.data); \
  } \
  \
  value_type d4_map_##key_type_name##MS##value_type_name##ME_get (d4_err_state_t *state, int line, int col, const d4_map_##key_type_name##MS##value_type_name##ME_t self, const key_type key) { \
    d4_str_t id = key_hash_block; \
    size_t index = d4_map_hash(id, self.cap); \
    value_type val; \
    d4_map_##key_type_name##MS##value_type_name##ME_pair_t *it = self.data[index]; \
    while (it != NULL) { \
      if (d4_str_eq(it->id, id)) break; \
      it = it->next; \
    } \
    if (it == NULL) { \
      d4_str_t message = d4_str_alloc(L"failed to find key '%ls'", id.data); \
      d4_error_assign_generic(state, line, col, message); \
      d4_str_free(message); \
    } \
    d4_str_free(id); \
    if (state->id != -1) longjmp(state->buf_last->buf, state->id); \
    val = it->value; \
    return value_copy_block; \
  } \
  \
  bool d4_map_##key_type_name##MS##value_type_name##ME_has (const d4_map_##key_type_name##MS##value_type_name##ME_t self, const key_type key) { \
    d4_str_t id = key_hash_block; \
    size_t index = d4_map_hash(id, self.cap); \
    d4_map_##key_type_name##MS##value_type_name##ME_pair_t *it = self.data[index]; \
    bool r = false; \
    while (it != NULL) { \
      if (d4_str_eq(it->id, id)) break; \
      it = it->next; \
    } \
    r = it != NULL; \
    d4_str_free(id); \
    return r; \
  } \
  \
  d4_arr_##key_type_name##_t d4_map_##key_type_name##MS##value_type_name##ME_keys (const d4_map_##key_type_name##MS##value_type_name##ME_t self) { \
    key_type *data = d4_safe_alloc(self.len * sizeof(key_type)); \
    size_t j = 0; \
    for (size_t i = 0; i < self.cap; i++) { \
      d4_map_##key_type_name##MS##value_type_name##ME_pair_t *it = self.data[i]; \
      while (it != NULL) { \
        key_type key = it->key; \
        data[j++] = key_copy_block; \
        it = it->next; \
      } \
    } \
    return (d4_arr_##key_type_name##_t) {data, self.len}; \
  } \
  \
  d4_map_##key_type_name##MS##value_type_name##ME_t *d4_map_##key_type_name##MS##value_type_name##ME_merge (d4_map_##key_type_name##MS##value_type_name##ME_t *self, const d4_map_##key_type_name##MS##value_type_name##ME_t other) { \
    self->len += other.len; \
    if (d4_map_should_reserve(self->cap, self->len)) { \
      size_t new_cap = d4_map_calc_cap(self->cap, self->len); \
      d4_map_##key_type_name##MS##value_type_name##ME_reserve(self, (int32_t) new_cap); \
    } \
    for (size_t i = 0; i < other.cap; i++) { \
      d4_map_##key_type_name##MS##value_type_name##ME_pair_t *it = other.data[i]; \
      while (it != NULL) { \
        d4_map_##key_type_name##MS##value_type_name##ME_place(*self, it->id, it->key, it->value); \
        it = it->next; \
      } \
    } \
    return self; \
  } \
  \
  void d4_map_##key_type_name##MS##value_type_name##ME_place (d4_map_##key_type_name##MS##value_type_name##ME_t self, const d4_str_t id, const key_type key, const value_type value) { \
    size_t index = d4_map_hash(id, self.cap); \
    d4_map_##key_type_name##MS##value_type_name##ME_pair_t *it = self.data[index]; \
    while (it != NULL) { \
      if (d4_str_eq(it->id, id)) break; \
      it = it->next; \
    } \
    if (it == NULL) { \
      d4_map_##key_type_name##MS##value_type_name##ME_pair_t *new_item = d4_safe_alloc(sizeof(d4_map_##key_type_name##MS##value_type_name##ME_pair_t)); \
      value_type val = value; \
      new_item->id = d4_str_copy(id); \
      new_item->key = key_copy_block; \
      new_item->value = value_copy_block; \
      new_item->next = self.data[index]; \
      self.data[index] = new_item; \
    } else { \
      value_type val = it->value; \
      value_free_block; \
      val = value; \
      it->value = value_copy_block; \
    } \
  } \
  \
  d4_map_##key_type_name##MS##value_type_name##ME_t d4_map_##key_type_name##MS##value_type_name##ME_realloc (d4_map_##key_type_name##MS##value_type_name##ME_t self, const d4_map_##key_type_name##MS##value_type_name##ME_t rhs) { \
    d4_map_##key_type_name##MS##value_type_name##ME_free(self); \
    return d4_map_##key_type_name##MS##value_type_name##ME_copy(rhs); \
  } \
  \
  d4_map_##key_type_name##MS##value_type_name##ME_t *d4_map_##key_type_name##MS##value_type_name##ME_remove (d4_err_state_t *state, int line, int col, d4_map_##key_type_name##MS##value_type_name##ME_t *self, const key_type search_key) { \
    key_type key = search_key; \
    value_type val; \
    d4_str_t id = key_hash_block; \
    size_t index = d4_map_hash(id, self->cap); \
    d4_map_##key_type_name##MS##value_type_name##ME_pair_t *prev = NULL; \
    d4_map_##key_type_name##MS##value_type_name##ME_pair_t *it = self->data[index]; \
    while (it != NULL) { \
      if (d4_str_eq(it->id, id)) break; \
      prev = it; \
      it = it->next; \
    } \
    if (it == NULL) { \
      d4_str_t message = d4_str_alloc(L"failed to remove key '%ls'", id.data); \
      d4_error_assign_generic(state, line, col, message); \
      d4_str_free(message); \
    } \
    d4_str_free(id); \
    if (state->id != -1) longjmp(state->buf_last->buf, state->id); \
    if (prev == NULL) { \
      self->data[index] = it->next; \
    } else { \
      prev->next = it->next; \
    } \
    d4_str_free(it->id); \
    key = it->key; \
    val = it->value; \
    key_free_block; \
    value_free_block; \
    d4_safe_free(it); \
    self->len -= 1; \
    return self; \
  } \
  \
  d4_map_##key_type_name##MS##value_type_name##ME_t *d4_map_##key_type_name##MS##value_type_name##ME_reserve (d4_map_##key_type_name##MS##value_type_name##ME_t *self, int32_t size) { \
    d4_map_##key_type_name##MS##value_type_name##ME_t new_self; \
    if (size < 0x0F) size = 0x0F; \
    new_self.data = d4_safe_alloc(size * sizeof(d4_map_##key_type_name##MS##value_type_name##ME_pair_t *)); \
    new_self.cap = size; \
    new_self.len = 0; \
    memset(new_self.data, 0, new_self.cap * sizeof(d4_map_##key_type_name##MS##value_type_name##ME_pair_t *)); \
    for (size_t i = 0; i < self->cap; i++) { \
      while (self->data[i] != NULL) { \
        d4_map_##key_type_name##MS##value_type_name##ME_pair_t *it = self->data[i]; \
        d4_map_##key_type_name##MS##value_type_name##ME_pair_t *next = it->next; \
        size_t index = d4_map_hash(it->id, new_self.cap); \
        it->next = new_self.data[index]; \
        new_self.data[index] = it; \
        self->data[i] = next; \
      } \
    } \
    d4_safe_free(self->data); \
    self->cap = new_self.cap; \
    self->data = new_self.data; \
    return self; \
  } \
  \
  d4_map_##key_type_name##MS##value_type_name##ME_t *d4_map_##key_type_name##MS##value_type_name##ME_set (d4_map_##key_type_name##MS##value_type_name##ME_t *self, const key_type key, const value_type value) { \
    bool existed = d4_map_##key_type_name##MS##value_type_name##ME_has(*self, key); \
    d4_str_t id = key_hash_block; \
    d4_map_##key_type_name##MS##value_type_name##ME_place(*self, id, key, value); \
    d4_str_free(id); \
    if (!existed) self->len += 1; \
    if (d4_map_should_reserve(self->cap, self->len)) { \
      size_t new_cap = d4_map_calc_cap(self->cap, self->len); \
      d4_map_##key_type_name##MS##value_type_name##ME_reserve(self, (int32_t) new_cap); \
    } \
    return self; \
  } \
  \
  d4_map_##key_type_name##MS##value_type_name##ME_t *d4_map_##key_type_name##MS##value_type_name##ME_shrink (d4_map_##key_type_name##MS##value_type_name##ME_t *self) { \
    d4_map_##key_type_name##MS##value_type_name##ME_reserve(self, (int32_t) (self->len * 2)); \
    return self; \
  } \
  \
  d4_str_t d4_map_##key_type_name##MS##value_type_name##ME_str (const d4_map_##key_type_name##MS##value_type_name##ME_t self) { \
    d4_str_t s = d4_str_alloc(L": "); \
    d4_str_t c = d4_str_alloc(L", "); \
    d4_str_t b = d4_str_alloc(L"}"); \
    d4_str_t r = d4_str_alloc(L"{"); \
    d4_str_t result; \
    d4_map_##key_type_name##MS##value_type_name##ME_pair_t *it; \
    size_t j = 0; \
    for (size_t i = 0; i < self.cap; i++) { \
      it = self.data[i]; \
      while (it != NULL) { \
        key_type key = it->key; \
        value_type val = it->value; \
        d4_str_t key_str = key_str_block; \
        d4_str_t value_str = value_str_block; \
        d4_str_t key_quoted = d4_str_quoted_escape(key_str); \
        d4_str_t r_with_key; \
        d4_str_t r_with_colon; \
        d4_str_t r_with_val; \
        if (j++ != 0) { \
          d4_str_t r_with_comma = d4_str_concat(r, c); \
          r = d4_str_realloc(r, r_with_comma); \
          d4_str_free(r_with_comma); \
        } \
        r_with_key = d4_str_concat(r, key_quoted); \
        r_with_colon = d4_str_concat(r_with_key, s); \
        r_with_val = d4_str_concat(r_with_colon, value_str); \
        r = d4_str_realloc(r, r_with_val); \
        d4_str_free(key_str); \
        d4_str_free(value_str); \
        d4_str_free(key_quoted); \
        d4_str_free(r_with_key); \
        d4_str_free(r_with_colon); \
        d4_str_free(r_with_val); \
        it = it->next; \
      } \
    } \
    result = d4_str_concat(r, b); \
    d4_str_free(s); \
    d4_str_free(c); \
    d4_str_free(b); \
    d4_str_free(r); \
    return result; \
  } \
  \
  d4_arr_##value_type_name##_t d4_map_##key_type_name##MS##value_type_name##ME_values (const d4_map_##key_type_name##MS##value_type_name##ME_t self) { \
    value_type *data = d4_safe_alloc(self.len * sizeof(value_type)); \
    size_t j = 0; \
    for (size_t i = 0; i < self.cap; i++) { \
      d4_map_##key_type_name##MS##value_type_name##ME_pair_t *it = self.data[i]; \
      while (it != NULL) { \
        value_type val = it->value; \
        data[j++] = value_copy_block; \
        it = it->next; \
      } \
    } \
    return (d4_arr_##value_type_name##_t) {data, self.len}; \
  }

/**
 * Calculates new map capacity.
 * @param cap Current map capacity.
 * @param len Current map length.
 * @return New map capacity.
 */
size_t d4_map_calc_cap (size_t cap, size_t len);

/**
 * Hashes and maps identifier to correct index inside of the map.
 * @param id Identifier to find index for.
 * @param cap Current map capacity.
 * @return Index of the identifier inside of the map.
 */
size_t d4_map_hash (d4_str_t id, size_t cap);

/**
 * Determines whether map needs to reallocate.
 * @param cap Current map capacity.
 * @param len Current map length.
 * @return Whether map needs to reallocate.
 */
bool d4_map_should_reserve (size_t cap, size_t len);

#endif
