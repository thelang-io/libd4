/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_MAP_H
#define THE_MAP_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/map-macro.h>
#include <the/array.h>

// todo check const everywhere

/**
 * Macro that can be used to define a map object.
 * @param key_type_name Type name of the key.
 * @param key_type Key type of the array object.
 * @param key_alloc_type Key type of the key to be used inside variadic argument (should be cast to int in some cases).
 * @param key_copy_block Block that is used for copy method of key.
 * @param key_eq_block Block that is used for equals method of key. todo not used
 * @param key_free_block Block that is used for free method of key.
 * @param key_str_block Block that is used for str method of key.
 * @param value_type_name Type name of the value.
 * @param value_type Value type of the array object.
 * @param value_alloc_type Value type of the value to be used inside variadic argument (should be cast to int in some cases).
 * @param value_copy_block Block that is used for copy method of value.
 * @param value_eq_block Block that is used for equals method of value. todo not used
 * @param value_free_block Block that is used for free method of value.
 * @param value_str_block Block that is used for str method of value.
 */
#define THE_MAP_DEFINE(key_type_name, key_type, key_alloc_type, key_copy_block, key_eq_block, key_free_block, key_str_block, value_type_name, value_type, value_alloc_type, value_copy_block, value_eq_block, value_free_block, value_str_block) \
  the_map_##key_type_name##MS##value_type_name##ME_t the_map_##key_type_name##MS##value_type_name##ME_alloc (size_t len, ...) { \
    size_t cap = the_map_calc_cap(0x0F, len); \
    the_map_##key_type_name##MS##value_type_name##ME_t self = {the_safe_alloc(cap * sizeof(the_map_##key_type_name##MS##value_type_name##ME_pair_t *)), cap, len}; \
    va_list args; \
    memset(self.data, 0, cap * sizeof(the_map_##key_type_name##MS##value_type_name##ME_pair_t *)); \
    if (len == 0) return self; \
    va_start(args, len); \
    for (size_t i = 0; i < len; i++) { \
      const key_type key = va_arg(args, key_alloc_type); \
      const value_type value = va_arg(args, value_alloc_type); \
      the_str_t id = the_i32_str(key); \
      the_map_##key_type_name##MS##value_type_name##ME_place(self, id, key, value); \
      the_str_free(id); \
    } \
    va_end(args); \
    return self; \
  } \
  \
  the_map_##key_type_name##MS##value_type_name##ME_t *the_map_##key_type_name##MS##value_type_name##ME_clear (the_map_##key_type_name##MS##value_type_name##ME_t *self) { \
    for (size_t i = 0; i < self->cap; i++) { \
      while (self->data[i] != NULL) { \
        the_map_##key_type_name##MS##value_type_name##ME_pair_t *it = self->data[i]; \
        key_type key = it->key; \
        value_type val = it->value; \
        the_str_free(it->id); \
        key_free_block; \
        value_free_block; \
        self->data[i] = it->next; \
        the_safe_free(it); \
      } \
    } \
    memset(self->data, 0, self->cap * sizeof(the_map_##key_type_name##MS##value_type_name##ME_pair_t *)); \
    self->len = 0; \
    return self; \
  } \
  \
  the_map_##key_type_name##MS##value_type_name##ME_t the_map_##key_type_name##MS##value_type_name##ME_copy (const the_map_##key_type_name##MS##value_type_name##ME_t self) { \
    the_map_##key_type_name##MS##value_type_name##ME_t new_self = { \
      the_safe_alloc(self.cap * sizeof(the_map_##key_type_name##MS##value_type_name##ME_pair_t *)), \
      self.cap, \
      self.len \
    }; \
    memset(new_self.data, 0, new_self.cap * sizeof(the_map_##key_type_name##MS##value_type_name##ME_pair_t *)); \
    for (size_t i = 0; i < self.cap; i++) { \
      the_map_##key_type_name##MS##value_type_name##ME_pair_t *it = self.data[i]; \
      while (it != NULL) { \
        the_map_##key_type_name##MS##value_type_name##ME_place(new_self, it->id, it->key, it->value); \
        it = it->next; \
      } \
    } \
    return new_self; \
  } \
  \
  bool the_map_##key_type_name##MS##value_type_name##ME_empty (const the_map_##key_type_name##MS##value_type_name##ME_t self) { \
    return self.len == 0; \
  } \
  \
  bool the_map_##key_type_name##MS##value_type_name##ME_eq (const the_map_##key_type_name##MS##value_type_name##ME_t self, const the_map_##key_type_name##MS##value_type_name##ME_t rhs) { \
    if (self.len != rhs.len) return false; \
    for (size_t i = 0; i < self.cap; i++) { \
      the_map_##key_type_name##MS##value_type_name##ME_pair_t *it1 = self.data[i]; \
      while (it1 != NULL) { \
        size_t rhs_index = the_map_hash(it1->id, rhs.cap); \
        the_map_##key_type_name##MS##value_type_name##ME_pair_t *it2 = rhs.data[rhs_index]; \
        while (it2 != NULL) { \
          if (the_str_eq(it2->id, it1->id)) break; \
          it2 = it2->next; \
        } \
        if (it2 == NULL) return false; \
        /* todo compare value? */ \
        it1 = it1->next; \
      } \
    } \
    return true; \
  } \
  \
  void the_map_##key_type_name##MS##value_type_name##ME_free (the_map_##key_type_name##MS##value_type_name##ME_t self) { \
    for (size_t i = 0; i < self.cap; i++) { \
      while (self.data[i] != NULL) { \
        the_map_##key_type_name##MS##value_type_name##ME_pair_t *it = self.data[i]; \
        key_type key = it->key; \
        value_type val = it->value; \
        the_str_free(it->id); \
        key_free_block; \
        value_free_block; \
        self.data[i] = it->next; \
        the_safe_free(it); \
      } \
    } \
    the_safe_free(self.data); \
  } \
  \
  value_type the_map_##key_type_name##MS##value_type_name##ME_get (the_err_state_t *state, int line, int col, the_map_##key_type_name##MS##value_type_name##ME_t self, key_type key) { \
    the_str_t id = the_i32_str(key); \
    size_t index = the_map_hash(id, self.cap); \
    value_type val; \
    the_map_##key_type_name##MS##value_type_name##ME_pair_t *it = self.data[index]; \
    while (it != NULL) { \
      if (the_str_eq(it->id, id)) break; \
      it = it->next; \
    } \
    if (it == NULL) { \
      the_str_t message = the_str_alloc(L"failed to find key '%ls'", id.data); \
      the_error_assign_generic(state, line, col, message); \
      the_str_free(message); \
    } \
    the_str_free(id); \
    if (state->id != -1) longjmp(state->buf_last->buf, state->id); \
    val = it->value; \
    return value_copy_block; \
  } \
  \
  bool the_map_##key_type_name##MS##value_type_name##ME_has (the_map_##key_type_name##MS##value_type_name##ME_t self, key_type key) { \
    the_str_t id = the_i32_str(key); \
    size_t index = the_map_hash(id, self.cap); \
    the_map_##key_type_name##MS##value_type_name##ME_pair_t *it = self.data[index]; \
    bool r = false; \
    while (it != NULL) { \
      if (the_str_eq(it->id, id)) break; \
      it = it->next; \
    } \
    r = it != NULL; \
    the_str_free(id); \
    return r; \
  } \
  \
  the_arr_int_t the_map_##key_type_name##MS##value_type_name##ME_keys (const the_map_##key_type_name##MS##value_type_name##ME_t self) { \
    key_type *data = the_safe_alloc(self.len * sizeof(key_type)); \
    size_t j = 0; \
    for (size_t i = 0; i < self.cap; i++) { \
      the_map_##key_type_name##MS##value_type_name##ME_pair_t *it = self.data[i]; \
      while (it != NULL) { \
        key_type key = it->key; \
        data[j++] = key_copy_block; \
        it = it->next; \
      } \
    } \
    return (the_arr_int_t) {data, self.len}; \
  } \
  \
  the_map_##key_type_name##MS##value_type_name##ME_t *the_map_##key_type_name##MS##value_type_name##ME_merge (the_map_##key_type_name##MS##value_type_name##ME_t *self, const the_map_##key_type_name##MS##value_type_name##ME_t other) { \
    self->len += other.len; \
    if (the_map_should_calc_cap(self->cap, self->len)) { \
      size_t new_cap = the_map_calc_cap(self->cap, self->len); \
      the_map_##key_type_name##MS##value_type_name##ME_reserve(self, (int32_t) new_cap); \
    } \
    for (size_t i = 0; i < other.cap; i++) { \
      the_map_##key_type_name##MS##value_type_name##ME_pair_t *it = other.data[i]; \
      while (it != NULL) { \
        the_map_##key_type_name##MS##value_type_name##ME_place(*self, it->id, it->key, it->value); \
        it = it->next; \
      } \
    } \
    return self; \
  } \
  \
  void the_map_##key_type_name##MS##value_type_name##ME_place (the_map_##key_type_name##MS##value_type_name##ME_t self, const the_str_t id, const key_type key, const value_type value) { \
    size_t index = the_map_hash(id, self.cap); \
    the_map_##key_type_name##MS##value_type_name##ME_pair_t *it = self.data[index]; \
    while (it != NULL) { \
      if (the_str_eq(it->id, id)) break; \
      it = it->next; \
    } \
    if (it == NULL) { \
      the_map_##key_type_name##MS##value_type_name##ME_pair_t *new_item = the_safe_alloc(sizeof(the_map_##key_type_name##MS##value_type_name##ME_pair_t)); \
      value_type val = value; \
      new_item->id = the_str_copy(id); \
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
  the_map_##key_type_name##MS##value_type_name##ME_t the_map_##key_type_name##MS##value_type_name##ME_realloc (the_map_##key_type_name##MS##value_type_name##ME_t self, const the_map_##key_type_name##MS##value_type_name##ME_t rhs) { \
    the_map_##key_type_name##MS##value_type_name##ME_free(self); \
    return the_map_##key_type_name##MS##value_type_name##ME_copy(rhs); \
  } \
  \
  the_map_##key_type_name##MS##value_type_name##ME_t *the_map_##key_type_name##MS##value_type_name##ME_remove (the_err_state_t *state, int line, int col, the_map_##key_type_name##MS##value_type_name##ME_t *self, const key_type search_key) { \
    the_str_t id = the_i32_str(search_key); \
    size_t index = the_map_hash(id, self->cap); \
    the_map_##key_type_name##MS##value_type_name##ME_pair_t *prev = NULL; \
    the_map_##key_type_name##MS##value_type_name##ME_pair_t *it = self->data[index]; \
    key_type key; \
    value_type val; \
    while (it != NULL) { \
      if (the_str_eq(it->id, id)) break; \
      prev = it; \
      it = it->next; \
    } \
    if (it == NULL) { \
      the_str_t message = the_str_alloc(L"failed to find key '%ls'", id.data); \
      the_error_assign_generic(state, line, col, message); \
      the_str_free(message); \
    } \
    the_str_free(id); \
    if (state->id != -1) longjmp(state->buf_last->buf, state->id); \
    if (prev == NULL) { \
      self->data[index] = it->next; \
    } else { \
      prev->next = it->next; \
    } \
    the_str_free(it->id); \
    key = it->key; \
    val = it->value; \
    key_free_block; \
    value_free_block; \
    the_safe_free(it); \
    self->len -= 1; \
    return self; \
  } \
  \
  the_map_##key_type_name##MS##value_type_name##ME_t *the_map_##key_type_name##MS##value_type_name##ME_reserve (the_map_##key_type_name##MS##value_type_name##ME_t *self, int32_t size) { \
    the_map_##key_type_name##MS##value_type_name##ME_t new_self; \
    if (size < 0x0F) size = 0x0F; \
    new_self.data = the_safe_alloc(size * sizeof(the_map_##key_type_name##MS##value_type_name##ME_pair_t *)); \
    new_self.cap = size; \
    new_self.len = 0; \
    memset(new_self.data, 0, new_self.cap * sizeof(the_map_##key_type_name##MS##value_type_name##ME_pair_t *)); \
    for (size_t i = 0; i < self->cap; i++) { \
      while (self->data[i] != NULL) { \
        the_map_##key_type_name##MS##value_type_name##ME_pair_t *it = self->data[i]; \
        the_map_##key_type_name##MS##value_type_name##ME_pair_t *next = it->next; \
        size_t index = the_map_hash(it->id, new_self.cap); \
        it->next = new_self.data[index]; \
        new_self.data[index] = it; \
        self->data[i] = next; \
      } \
    } \
    the_safe_free(self->data); \
    self->cap = new_self.cap; \
    self->data = new_self.data; \
    return self; \
  } \
  \
  the_map_##key_type_name##MS##value_type_name##ME_t *the_map_##key_type_name##MS##value_type_name##ME_set (the_map_##key_type_name##MS##value_type_name##ME_t *self, key_type key, value_type value) { \
    the_str_t id = the_i32_str(key); \
    the_map_##key_type_name##MS##value_type_name##ME_place(*self, id, key, value); \
    the_str_free(id); \
    self->len += 1; \
    if (the_map_should_calc_cap(self->cap, self->len)) { \
      size_t new_cap = the_map_calc_cap(self->cap, self->len); \
      the_map_##key_type_name##MS##value_type_name##ME_reserve(self, (int32_t) new_cap); \
    } \
    return self; \
  } \
  \
  the_map_##key_type_name##MS##value_type_name##ME_t *the_map_##key_type_name##MS##value_type_name##ME_shrink (the_map_##key_type_name##MS##value_type_name##ME_t *self) { \
    the_map_##key_type_name##MS##value_type_name##ME_reserve(self, (int32_t) (self->len * 2)); \
    return self; \
  } \
  \
  the_str_t the_map_##key_type_name##MS##value_type_name##ME_str (const the_map_##key_type_name##MS##value_type_name##ME_t self) { \
    the_str_t s = the_str_alloc(L": "); \
    the_str_t c = the_str_alloc(L", "); \
    the_str_t b = the_str_alloc(L"}"); \
    the_str_t r = the_str_alloc(L"{"); \
    the_str_t result; \
    the_map_##key_type_name##MS##value_type_name##ME_pair_t *it; \
    size_t j = 0; \
    for (size_t i = 0; i < self.cap; i++) { \
      it = self.data[i]; \
      while (it != NULL) { \
        key_type key = it->key; \
        value_type val = it->value; \
        the_str_t key_str = key_str_block; \
        the_str_t value_str = value_str_block; \
        the_str_t key_quoted = the_str_quoted_escape(key_str); \
        the_str_t r_with_key; \
        the_str_t r_with_colon; \
        the_str_t r_with_val; \
        if (j++ != 0) { \
          the_str_t r_with_comma = the_str_concat(r, c); \
          r = the_str_realloc(r, r_with_comma); \
          the_str_free(r_with_comma); \
        } \
        r_with_key = the_str_concat(r, key_quoted); \
        r_with_colon = the_str_concat(r_with_key, s); \
        r_with_val = the_str_concat(r_with_colon, value_str); \
        r = the_str_realloc(r, r_with_val); \
        the_str_free(key_str); \
        the_str_free(value_str); \
        the_str_free(r_with_key); \
        the_str_free(r_with_colon); \
        the_str_free(r_with_val); \
        it = it->next; \
      } \
    } \
    result = the_str_concat(r, b); \
    the_str_free(s); \
    the_str_free(c); \
    the_str_free(b); \
    the_str_free(r); \
    return result; \
  } \
  \
  the_arr_str_t the_map_##key_type_name##MS##value_type_name##ME_values (const the_map_##key_type_name##MS##value_type_name##ME_t self) { \
    value_type *data = the_safe_alloc(self.len * sizeof(value_type)); \
    size_t j = 0; \
    for (size_t i = 0; i < self.cap; i++) { \
      the_map_##key_type_name##MS##value_type_name##ME_pair_t *it = self.data[i]; \
      while (it != NULL) { \
        value_type val = it->value; \
        data[j++] = value_copy_block; \
        it = it->next; \
      } \
    } \
    return (the_arr_str_t) {data, self.len}; \
  }

/** todo */
size_t the_map_calc_cap (size_t cap, size_t len);

/** todo */
size_t the_map_hash (the_str_t id, size_t cap);

/** todo */
bool the_map_should_calc_cap (size_t cap, size_t len);

#endif
