/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "number.h"
#include <the/string.h>
#include <inttypes.h>

static the_str_t str_float_truncate (the_str_t s) {
  for (size_t i = s.len - 1; i >= 1; i--) {
    if (s.data[i] == '0' && s.data[i - 1] != '.') {
      s.data[i] = '\0';
      s.len--;
      continue;
    }

    break;
  }

  return s;
}

the_str_t the_f32_str (float self) {
  return str_float_truncate(the_str_alloc(L"%f", (double) self));
}

the_str_t the_f64_str (double self) {
  return str_float_truncate(the_str_alloc(L"%f", self));
}

the_str_t the_float_str (double self) {
  return str_float_truncate(the_str_alloc(L"%f", self));
}

the_str_t the_i8_str (int8_t self) {
  return the_str_alloc(L"%" PRId8, self);
}

the_str_t the_i16_str (int16_t self) {
  return the_str_alloc(L"%" PRId16, self);
}

the_str_t the_i32_str (int32_t self) {
  return the_str_alloc(L"%" PRId32, self);
}

the_str_t the_i64_str (int64_t self) {
  return the_str_alloc(L"%" PRId64, self);
}

the_str_t the_int_str (int32_t self) {
  return the_str_alloc(L"%" PRId32, self);
}

the_str_t the_isize_str (ptrdiff_t self) {
  return the_str_alloc(L"%zd", self);
}

the_str_t the_u8_str (uint8_t self) {
  return the_str_alloc(L"%" PRIu8, self);
}

the_str_t the_u16_str (uint16_t self) {
  return the_str_alloc(L"%" PRIu16, self);
}

the_str_t the_u32_str (uint32_t self) {
  return the_str_alloc(L"%" PRIu32, self);
}

the_str_t the_u64_str (uint64_t self) {
  return the_str_alloc(L"%" PRIu64, self);
}

the_str_t the_usize_str (size_t self) {
  return the_str_alloc(L"%zu", self);
}
