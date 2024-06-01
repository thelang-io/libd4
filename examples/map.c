/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/array.h>
#include <the/error.h>
#include <the/number.h>
#include <the/safe.h>
#include <the/string.h>
#include <stdarg.h>
#include <string.h>

THE_ARRAY_DECLARE(int, int32_t)
THE_ARRAY_DEFINE(int, int32_t, int, element, lhs_element == rhs_element, (void) element, the_i32_str(element))

const double THE_MAP_LOAD_FACTOR = 0.75;

typedef struct the_map_intMSstrME_pair {
  the_str_t id;
  int32_t key;
  the_str_t value;
  struct the_map_intMSstrME_pair *next;
} the_map_intMSstrME_pair_t;

typedef struct {
  the_map_intMSstrME_pair_t **data;
  size_t cap;
  size_t len;
} the_map_intMSstrME_t;

the_map_intMSstrME_t the_map_intMSstrME_alloc (size_t len, ...);
the_map_intMSstrME_t *the_map_intMSstrME_clear (the_map_intMSstrME_t *self);
the_map_intMSstrME_t the_map_intMSstrME_copy (const the_map_intMSstrME_t self);
bool the_map_intMSstrME_empty (const the_map_intMSstrME_t self);
bool the_map_intMSstrME_eq (const the_map_intMSstrME_t self, const the_map_intMSstrME_t rhs);
void the_map_intMSstrME_free (the_map_intMSstrME_t self);
the_str_t the_map_intMSstrME_get (the_err_state_t *state, int line, int col, const the_map_intMSstrME_t self, int32_t key);
bool the_map_intMSstrME_has (const the_map_intMSstrME_t self, int32_t key);
the_arr_int_t the_map_intMSstrME_keys (const the_map_intMSstrME_t self);
the_map_intMSstrME_t *the_map_intMSstrME_merge (the_map_intMSstrME_t *self, const the_map_intMSstrME_t other);
void the_map_intMSstrME_place (the_map_intMSstrME_t self, the_str_t id, int32_t key, the_str_t value);
the_map_intMSstrME_t the_map_intMSstrME_realloc (the_map_intMSstrME_t self, const the_map_intMSstrME_t rhs);
the_map_intMSstrME_t *the_map_intMSstrME_remove (the_err_state_t *state, int line, int col, the_map_intMSstrME_t *self, int32_t key);
the_map_intMSstrME_t *the_map_intMSstrME_reserve (the_map_intMSstrME_t *self, int32_t size);
the_map_intMSstrME_t *the_map_intMSstrME_set (the_map_intMSstrME_t *self, int32_t key, const the_str_t value);
the_map_intMSstrME_t *the_map_intMSstrME_shrink (the_map_intMSstrME_t *self);
the_str_t the_map_intMSstrME_str (const the_map_intMSstrME_t self);
the_arr_str_t the_map_intMSstrME_values (const the_map_intMSstrME_t self);

void the_map_intMSstrME_print (const the_map_intMSstrME_t self);

size_t the_map_calc_cap (size_t cap, size_t len);
size_t the_map_hash (the_str_t id, size_t cap);
bool the_map_should_calc_cap (size_t cap, size_t len);

size_t the_map_calc_cap (size_t cap, size_t len) {
  while (the_map_should_calc_cap(cap, len)) {
    cap *= 2;
  }

  return cap;
}

size_t the_map_hash (the_str_t id, size_t cap) {
  size_t result = 0xCBF29CE484222325;

  for (size_t i = 0; i < id.len; i++) {
    result = (size_t) ((size_t) (result * (size_t) 0x00000100000001B3) ^ (size_t) id.data[i]);
  }

  return result % cap;
}

bool the_map_should_calc_cap (size_t cap, size_t len) {
  return len >= (size_t) ((double) cap * THE_MAP_LOAD_FACTOR);
}

the_map_intMSstrME_t the_map_intMSstrME_alloc (size_t len, ...) {
  size_t cap = the_map_calc_cap(0x0F, len);
  the_map_intMSstrME_t self = {the_safe_alloc(cap * sizeof(the_map_intMSstrME_pair_t *)), cap, len};
  va_list args;

  memset(self.data, 0, cap * sizeof(the_map_intMSstrME_pair_t *));

  if (len == 0) {
    return self;
  }

  va_start(args, len);

  for (size_t i = 0; i < len; i++) {
    const int32_t key = va_arg(args, int32_t);
    const the_str_t value = va_arg(args, the_str_t);
    the_str_t id = the_i32_str(key);
    the_map_intMSstrME_place(self, id, key, value);
    the_str_free(id);
  }

  va_end(args);
  return self;
}

the_map_intMSstrME_t *the_map_intMSstrME_clear (the_map_intMSstrME_t *self) {
  for (size_t i = 0; i < self->cap; i++) {
    while (self->data[i] != NULL) {
      the_map_intMSstrME_pair_t *it = self->data[i];
      the_str_free(it->id);
      the_str_free(it->value);
      self->data[i] = it->next;
      the_safe_free(it);
    }
  }

  memset(self->data, 0, self->cap * sizeof(the_map_intMSstrME_pair_t *));
  self->len = 0;

  return self;
}

the_map_intMSstrME_t the_map_intMSstrME_copy (const the_map_intMSstrME_t self) {
  the_map_intMSstrME_t new_self = {
    the_safe_alloc(self.cap * sizeof(the_map_intMSstrME_pair_t *)),
    self.cap,
    self.len
  };

  memset(new_self.data, 0, new_self.cap * sizeof(the_map_intMSstrME_pair_t *));

  for (size_t i = 0; i < self.cap; i++) {
    the_map_intMSstrME_pair_t *it = self.data[i];

    while (it != NULL) {
      the_map_intMSstrME_place(new_self, it->id, it->key, it->value);
      it = it->next;
    }
  }

  return new_self;
}

bool the_map_intMSstrME_empty (const the_map_intMSstrME_t self) {
  return self.len == 0;
}

bool the_map_intMSstrME_eq (const the_map_intMSstrME_t self, const the_map_intMSstrME_t rhs) {
  if (self.len != rhs.len) {
    return false;
  }

  for (size_t i = 0; i < self.cap; i++) {
    the_map_intMSstrME_pair_t *it1 = self.data[i];

    while (it1 != NULL) {
      size_t rhs_index = the_map_hash(it1->id, rhs.cap);
      the_map_intMSstrME_pair_t *it2 = rhs.data[rhs_index];

      while (it2 != NULL) {
        if (the_str_eq(it2->id, it1->id)) {
          break;
        }

        it2 = it2->next;
      }

      if (it2 == NULL) {
        return false;
      }

      it1 = it1->next;
    }
  }

  return true;
}

void the_map_intMSstrME_free (the_map_intMSstrME_t self) {
  for (size_t i = 0; i < self.cap; i++) {
    while (self.data[i] != NULL) {
      the_map_intMSstrME_pair_t *it = self.data[i];
      the_str_free(it->id);
      the_str_free(it->value);
      self.data[i] = it->next;
      the_safe_free(it);
    }
  }

  the_safe_free(self.data);
}

the_str_t the_map_intMSstrME_get (the_err_state_t *state, int line, int col, the_map_intMSstrME_t self, int32_t key) {
  the_str_t id = the_i32_str(key);
  size_t index = the_map_hash(id, self.cap);
  the_map_intMSstrME_pair_t *it = self.data[index];

  while (it != NULL) {
    if (the_str_eq(it->id, id)) {
      break;
    }

    it = it->next;
  }

  if (it == NULL) {
    the_str_t message = the_str_alloc(L"failed to find key '%ls'", id.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  }

  the_str_free(id);
  if (state->id != -1) longjmp(state->buf_last->buf, state->id);

  return the_str_copy(it->value);
}

bool the_map_intMSstrME_has (the_map_intMSstrME_t self, int32_t key) {
  the_str_t id = the_i32_str(key);
  size_t index = the_map_hash(id, self.cap);
  the_map_intMSstrME_pair_t *it = self.data[index];
  bool r = false;

  while (it != NULL) {
    if (the_str_eq(it->id, id)) {
      break;
    }

    it = it->next;
  }

  r = it != NULL;
  the_str_free(id);
  return r;
}

the_arr_int_t the_map_intMSstrME_keys (const the_map_intMSstrME_t self) {
  int32_t *data = the_safe_alloc(self.len * sizeof(int32_t));
  size_t j = 0;

  for (size_t i = 0; i < self.cap; i++) {
    the_map_intMSstrME_pair_t *it = self.data[i];

    while (it != NULL) {
      data[j++] = it->key;
      it = it->next;
    }
  }

  return (the_arr_int_t) {data, self.len};
}

the_map_intMSstrME_t *the_map_intMSstrME_merge (the_map_intMSstrME_t *self, const the_map_intMSstrME_t other) {
  self->len += other.len;

  if (the_map_should_calc_cap(self->cap, self->len)) {
    size_t new_cap = the_map_calc_cap(self->cap, self->len);
    the_map_intMSstrME_reserve(self, (int32_t) new_cap);
  }

  for (size_t i = 0; i < other.cap; i++) {
    the_map_intMSstrME_pair_t *it = other.data[i];

    while (it != NULL) {
      the_map_intMSstrME_place(*self, it->id, it->key, it->value);
      it = it->next;
    }
  }

  return self;
}

void the_map_intMSstrME_place (the_map_intMSstrME_t self, the_str_t id, int32_t key, the_str_t value) {
  size_t index = the_map_hash(id, self.cap);
  the_map_intMSstrME_pair_t *it = self.data[index];

  while (it != NULL) {
    if (the_str_eq(it->id, id)) {
      break;
    }

    it = it->next;
  }

  if (it == NULL) {
    the_map_intMSstrME_pair_t *new_item = the_safe_alloc(sizeof(the_map_intMSstrME_pair_t));
    new_item->id = the_str_copy(id);
    new_item->key = key;
    new_item->value = the_str_copy(value);
    new_item->next = self.data[index];
    self.data[index] = new_item;
  } else {
    the_str_free(it->value);
    it->value = the_str_copy(value);
  }
}

void the_map_intMSstrME_print (the_map_intMSstrME_t self) {
  for (size_t i = 0; i < self.cap; i++) {
    the_map_intMSstrME_pair_t *it = self.data[i];

    while (it != NULL) {
      wprintf(L"---- %zu %ls: %ls\n", i, it->id.data, it->value.data);
      it = it->next;
    }
  }

  wprintf(L"cap: %zu, len: %zu, empty: %ls\n", self.cap, self.len, the_map_intMSstrME_empty(self) ? L"true" : L"false");
}

the_map_intMSstrME_t the_map_intMSstrME_realloc (the_map_intMSstrME_t self, const the_map_intMSstrME_t rhs) {
  the_map_intMSstrME_free(self);
  return the_map_intMSstrME_copy(rhs);
}

the_map_intMSstrME_t *the_map_intMSstrME_remove (the_err_state_t *state, int line, int col, the_map_intMSstrME_t *self, int32_t key) {
  the_str_t id = the_i32_str(key);
  size_t index = the_map_hash(id, self->cap);
  the_map_intMSstrME_pair_t *prev = NULL;
  the_map_intMSstrME_pair_t *it = self->data[index];

  while (it != NULL) {
    if (the_str_eq(it->id, id)) {
      break;
    }

    prev = it;
    it = it->next;
  }

  if (it == NULL) {
    the_str_t message = the_str_alloc(L"failed to find key '%ls'", id.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  }

  the_str_free(id);
  if (state->id != -1) longjmp(state->buf_last->buf, state->id);

  if (prev == NULL) {
    self->data[index] = it->next;
  } else {
    prev->next = it->next;
  }

  the_str_free(it->id);
  the_str_free(it->value);
  the_safe_free(it);
  self->len -= 1;

  return self;
}

the_map_intMSstrME_t *the_map_intMSstrME_reserve (the_map_intMSstrME_t *self, int32_t size) {
  the_map_intMSstrME_t new_self;

  if (size < 0x0F) {
    size = 0x0F;
  }

  new_self.data = the_safe_alloc(size * sizeof(the_map_intMSstrME_pair_t *));
  new_self.cap = size;
  new_self.len = 0;
  memset(new_self.data, 0, new_self.cap * sizeof(the_map_intMSstrME_pair_t *));

  for (size_t i = 0; i < self->cap; i++) {
    while (self->data[i] != NULL) {
      the_map_intMSstrME_pair_t *it = self->data[i];
      the_map_intMSstrME_pair_t *next = it->next;
      size_t index = the_map_hash(it->id, new_self.cap);
      it->next = new_self.data[index];
      new_self.data[index] = it;
      self->data[i] = next;
    }
  }

  the_safe_free(self->data);
  self->cap = new_self.cap;
  self->data = new_self.data;

  return self;
}

the_map_intMSstrME_t *the_map_intMSstrME_set (the_map_intMSstrME_t *self, int32_t key, the_str_t value) {
  the_str_t id = the_i32_str(key);
  the_map_intMSstrME_place(*self, id, key, value);
  the_str_free(id);
  self->len += 1;

  if (the_map_should_calc_cap(self->cap, self->len)) {
    size_t new_cap = the_map_calc_cap(self->cap, self->len);
    the_map_intMSstrME_reserve(self, (int32_t) new_cap);
  }

  return self;
}

the_map_intMSstrME_t *the_map_intMSstrME_shrink (the_map_intMSstrME_t *self) {
  the_map_intMSstrME_reserve(self, (int32_t) (self->len * 2));
  return self;
}

the_str_t the_map_intMSstrME_str (const the_map_intMSstrME_t self) {
  the_str_t q = the_str_alloc(L"\"");
  the_str_t s = the_str_alloc(L": ");
  the_str_t c = the_str_alloc(L", ");
  the_str_t b = the_str_alloc(L"}");
  the_str_t r = the_str_alloc(L"{");
  the_map_intMSstrME_pair_t *it;
  size_t j = 0;

  for (size_t i = 0; i < self.cap; i++) {
    it = self.data[i];

    while (it != NULL) {
      the_str_t key_quoted = the_str_concat(the_str_concat(q, the_str_copy(it->id)), q);
      if (j++ != 0) r = the_str_realloc(r, the_str_concat(r, c));
      r = the_str_realloc(r, the_str_concat(the_str_concat(the_str_concat(r, key_quoted), s), the_str_copy(it->value)));
      it = it->next;
    }
  }

  r = the_str_realloc(r, the_str_concat(r, b));

  the_str_free(q);
  the_str_free(s);
  the_str_free(c);
  the_str_free(b);

  return r;
}

the_arr_str_t the_map_intMSstrME_values (const the_map_intMSstrME_t self) {
  the_str_t *data = the_safe_alloc(self.len * sizeof(the_str_t));
  size_t j = 0;

  for (size_t i = 0; i < self.cap; i++) {
    the_map_intMSstrME_pair_t *it = self.data[i];

    while (it != NULL) {
      data[j++] = the_str_copy(it->value);
      it = it->next;
    }
  }

  return (the_arr_str_t) {data, self.len};
}

int main (void) {
  the_str_t val = the_str_alloc(L"string");
  the_map_intMSstrME_t m1 = the_map_intMSstrME_alloc(0);
  the_map_intMSstrME_t m2 = the_map_intMSstrME_alloc(0);
  the_map_intMSstrME_t m3;
  the_map_intMSstrME_t m4;
  the_map_intMSstrME_t m5 = the_map_intMSstrME_alloc(1, 3, val);
  the_map_intMSstrME_t m6 = the_map_intMSstrME_alloc(2, 4, val, 5, val);
  the_map_intMSstrME_t m7 = the_map_intMSstrME_alloc(1, 2, val);
  the_str_t val2;
  the_arr_int_t keys;
  the_str_t keys_str;
  the_arr_str_t values;
  the_str_t values_str;
  the_str_t m2_str;
  the_str_t m5_str;
  the_str_t m6_str;
  the_str_t m7_str;

  the_map_intMSstrME_merge(&m7, m5);
  the_map_intMSstrME_merge(&m7, m6);

  for (size_t i = 0; i < 1000; i++) {
    the_map_intMSstrME_set(&m1, (int32_t) i, val);
  }

  m3 = the_map_intMSstrME_copy(m1);
  val2 = the_map_intMSstrME_get(&the_err_state, 0, 0, m1, 10);
  the_map_intMSstrME_remove(&the_err_state, 0, 0, &m1, 10);
  m4 = the_map_intMSstrME_copy(m1);

  keys = the_map_intMSstrME_keys(m1);
  keys_str = the_arr_int_str(keys);
  values = the_map_intMSstrME_values(m1);
  values_str = the_arr_str_str(values);
  m2_str = the_map_intMSstrME_str(m2);
  m5_str = the_map_intMSstrME_str(m5);
  m6_str = the_map_intMSstrME_str(m6);
  m7_str = the_map_intMSstrME_str(m7);

  the_map_intMSstrME_print(m1);
  wprintf(L"keys: %ls\n", keys_str.data);
  wprintf(L"values: %ls\n", values_str.data);
  wprintf(L"found value: %ls\n", val2.data);
  wprintf(L"has 10: %ls\n", the_map_intMSstrME_has(m1, 10) ? L"true" : L"false");
  wprintf(L"has 11: %ls\n", the_map_intMSstrME_has(m1, 11) ? L"true" : L"false");
  the_map_intMSstrME_clear(&m1);
  the_map_intMSstrME_print(m1);
  the_map_intMSstrME_reserve(&m1, 10000);
  the_map_intMSstrME_print(m1);
  the_map_intMSstrME_shrink(&m1);
  the_map_intMSstrME_print(m1);

  wprintf(L"1 eq 2: %ls\n", the_map_intMSstrME_eq(m1, m2) ? L"true" : L"false");
  wprintf(L"3 eq 4: %ls\n", the_map_intMSstrME_eq(m3, m4) ? L"true" : L"false");
  the_map_intMSstrME_remove(&the_err_state, 0, 0, &m3, 10);
  the_map_intMSstrME_shrink(&m1);
  wprintf(L"again 3 eq 4: %ls\n", the_map_intMSstrME_eq(m3, m4) ? L"true" : L"false");
  m3 = the_map_intMSstrME_realloc(m3, m2);
  wprintf(L"and again 3 eq 2: %ls\n", the_map_intMSstrME_eq(m3, m2) ? L"true" : L"false");
  wprintf(L"m2: %ls\n", m2_str.data);
  wprintf(L"m5: %ls\n", m5_str.data);
  wprintf(L"m6: %ls\n", m6_str.data);
  wprintf(L"m7: %ls\n", m7_str.data);

  the_map_intMSstrME_free(m1);

  the_str_free(val);
  the_str_free(val2);

  return 0;
}
