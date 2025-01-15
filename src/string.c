/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <d4/macro.h>
#include "string.h"
#include <d4/array.h>
#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <string.h>

D4_ARRAY_DEFINE(str, d4_str_t, d4_str_t, d4_str_copy(element), d4_str_eq(lhs_element, rhs_element), d4_str_free(element), d4_str_copy(element))

d4_str_t d4_str_empty_val = {NULL, 0, true};

int snwprintf (const wchar_t *fmt, ...) {
  va_list args;
  int result;

  va_start(args, fmt);
  result = vsnwprintf(fmt, args);
  va_end(args);

  return result;
}

int vsnwprintf (const wchar_t *fmt, va_list args) {
  unsigned long long buf_size = 1024;
  wchar_t *buffer = d4_safe_alloc(buf_size * sizeof(wchar_t));
  int fmt_size = -1;
  va_list args_copy;
  int y;

  while (buf_size <= INT_MAX) {
    va_copy(args_copy, args);
    y = vswprintf(buffer, (size_t) buf_size, fmt, args_copy);
    va_end(args_copy);

    if (y >= 0) {
      fmt_size = y;
      break;
    }

    buf_size *= 2;
    buffer = d4_safe_realloc(buffer, buf_size * sizeof(wchar_t));
  }

  d4_safe_free(buffer);
  return fmt_size;
}

d4_str_t d4_str_alloc (const wchar_t *fmt, ...) {
  wchar_t *d = NULL;
  size_t l = 0;

  if (fmt != NULL) {
    va_list args;
    va_start(args, fmt);
    l = (size_t) vsnwprintf(fmt, args);

    if (l != 0) {
      d = d4_safe_alloc((l + 1) * sizeof(wchar_t));
      vswprintf(d, l + 1, fmt, args);
    }

    va_end(args);
  }

  if (l == 0) {
    return d4_str_empty_val;
  }

  return (d4_str_t) {d, l, false};
}

d4_str_t d4_str_calloc (const wchar_t *self, size_t length) {
  wchar_t *d;

  if (length == 0) {
    return d4_str_empty_val;
  }

  d = d4_safe_alloc((length + 1) * sizeof(wchar_t));
  wmemcpy(d, self, length);
  d[length] = L'\0';
  return (d4_str_t) {d, length, false};
}

wchar_t *d4_str_at (d4_err_state_t *state, int line, int col, const d4_str_t self, int32_t index) {
  if ((index >= 0 && (size_t) index >= self.len) || (index < 0 && index < -((int32_t) self.len))) {
    d4_str_t message = d4_str_alloc(L"index %" PRId32 L" out of string bounds", index);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  return index < 0 ? &self.data[self.len + (size_t) index] : &self.data[index];
}

d4_str_t d4_str_concat (const d4_str_t self, const d4_str_t other) {
  size_t l = self.len + other.len;
  wchar_t *d = d4_safe_alloc((l + 1) * sizeof(wchar_t));
  wmemcpy(d, self.data, self.len);
  wmemcpy(&d[self.len], other.data, other.len);
  d[l] = L'\0';
  return (d4_str_t) {d, l, false};
}

bool d4_str_contains (const d4_str_t self, const d4_str_t search) {
  if (self.len == search.len) {
    return memcmp(self.data, search.data, self.len * sizeof(wchar_t)) >= 0;
  }

  if (self.len > 0 && self.len > search.len) {
    for (size_t i = 0; i < self.len - search.len + 1; i++) {
      if (memcmp(&self.data[i], search.data, search.len * sizeof(wchar_t)) >= 0) {
        return true;
      }
    }
  }

  return false;
}

d4_str_t d4_str_copy (const d4_str_t self) {
  wchar_t *d;
  if (self.len == 0) {
    return d4_str_empty_val;
  }
  d = d4_safe_alloc((self.len + 1) * sizeof(wchar_t));
  wmemcpy(d, self.data, self.len);
  d[self.len] = L'\0';
  return (d4_str_t) {d, self.len, false};
}

bool d4_str_empty (const d4_str_t self) {
  return self.len == 0;
}

bool d4_str_endsWith (const d4_str_t self, const d4_str_t search) {
  return search.len <= self.len && memcmp(&self.data[self.len - search.len], search.data, search.len * sizeof(wchar_t)) == 0;
}

bool d4_str_eq (const d4_str_t self, const d4_str_t rhs) {
  return self.len == rhs.len && memcmp(self.data, rhs.data, self.len * sizeof(wchar_t)) == 0;
}

d4_str_t d4_str_escape (const d4_str_t self) {
  wchar_t *d;
  size_t l = 0;

  if (self.len == 0) {
    return d4_str_empty_val;
  }

  d = d4_safe_alloc((self.len + 1) * sizeof(wchar_t));

  for (size_t i = 0; i < self.len; i++) {
    wchar_t c = self.data[i];

    if (c == L'\f' || c == L'\n' || c == L'\r' || c == L'\t' || c == L'\v' || c == L'"') {
      if (l + 3 > self.len) {
        d = d4_safe_realloc(d, (l + 3) * sizeof(wchar_t));
      }

      d[l++] = L'\\';

      if (c == L'\f') d[l++] = L'f';
      else if (c == L'\n') d[l++] = L'n';
      else if (c == L'\r') d[l++] = L'r';
      else if (c == L'\t') d[l++] = L't';
      else if (c == L'\v') d[l++] = L'v';
      else if (c == L'"') d[l++] = L'"';

      continue;
    }

    if (l + 2 > self.len) {
      d = d4_safe_realloc(d, (l + 2) * sizeof(wchar_t));
    }

    d[l++] = c;
  }

  d[l] = L'\0';
  return (d4_str_t) {d, l, false};
}

int32_t d4_str_find (const d4_str_t self, const d4_str_t search) {
  if (search.len == 0) {
    return 0;
  }

  for (size_t i = 0; i < self.len; i++) {
    if (memcmp(&self.data[i], search.data, search.len * sizeof(wchar_t)) == 0) {
      return (int32_t) i;
    }
  }

  return -1;
}

void d4_str_free (d4_str_t self) {
  if (!self.is_static) d4_safe_free(self.data);
}

bool d4_str_ge (const d4_str_t self, const d4_str_t rhs) {
  if (self.len == 0 || rhs.len == 0) {
    return self.len >= rhs.len;
  }
  return memcmp(self.data, rhs.data, (self.len > rhs.len ? self.len : rhs.len) * sizeof(wchar_t)) >= 0;
}

bool d4_str_gt (const d4_str_t self, const d4_str_t rhs) {
  if (self.len == 0 || rhs.len == 0) {
    return self.len > rhs.len;
  }
  return memcmp(self.data, rhs.data, (self.len > rhs.len ? self.len : rhs.len) * sizeof(wchar_t)) > 0;
}

bool d4_str_le (const d4_str_t self, const d4_str_t rhs) {
  if (self.len == 0 || rhs.len == 0) {
    return self.len <= rhs.len;
  }
  return memcmp(self.data, rhs.data, (self.len > rhs.len ? self.len : rhs.len) * sizeof(wchar_t)) <= 0;
}

bool d4_str_lt (const d4_str_t self, const d4_str_t rhs) {
  if (self.len == 0 || rhs.len == 0) {
    return self.len < rhs.len;
  }
  return memcmp(self.data, rhs.data, (self.len > rhs.len ? self.len : rhs.len) * sizeof(wchar_t)) < 0;
}

d4_str_t d4_str_quoted_escape (d4_str_t self) {
  d4_str_t q = (d4_str_t) {L"\"", 1, true};
  d4_str_t escaped = d4_str_escape(self);
  d4_str_t left_result = d4_str_concat(q, escaped);
  d4_str_t result = d4_str_concat(left_result, q);

  d4_str_free(escaped);
  d4_str_free(left_result);

  return result;
}

d4_str_t d4_str_realloc (d4_str_t self, const d4_str_t rhs) {
  if (rhs.len == 0) {
    d4_str_free(self);
    return d4_str_empty_val;
  }

  if (self.len == 0) {
    self.data = d4_safe_alloc((rhs.len + 1) * sizeof(wchar_t));
  } else {
    self.data = d4_safe_realloc(self.data, (rhs.len + 1) * sizeof(wchar_t));
  }

  wmemcpy(self.data, rhs.data, rhs.len);
  self.data[rhs.len] = L'\0';
  return (d4_str_t) {self.data, rhs.len, false};
}

d4_arr_str_t d4_str_lines (const d4_str_t self, unsigned char o1, bool keepLineBreaks) {
  bool k = o1 == 0 ? false : keepLineBreaks;
  d4_str_t *result = NULL;
  size_t len = 0;
  size_t start = 0;

  if (self.len == 0) {
    return (d4_arr_str_t) {NULL, 0};
  }

  for (size_t j = 0; j < self.len; j++) {
    wchar_t c = self.data[j];

    if (c == L'\r' || c == L'\n') {
      size_t beforeLineBreak = j;

      if (c == L'\r' && j + 1 < self.len && self.data[j + 1] == L'\n') {
        j++;
      }

      result = d4_safe_realloc(result, ++len * sizeof(d4_str_t));
      result[len - 1] = d4_str_calloc(&self.data[start], (k ? j + 1 : beforeLineBreak) - start);

      start = j + 1;
    }
  }

  if (start != self.len) {
    result = d4_safe_realloc(result, ++len * sizeof(d4_str_t));
    result[len - 1] = d4_str_calloc(&self.data[start], self.len - start);
  }

  return (d4_arr_str_t) {result, len};
}

d4_str_t d4_str_lower (const d4_str_t self) {
  d4_str_t d = d4_str_copy(self);

  if (self.len == 0) {
    return d;
  }

  for (size_t i = 0; i < d.len; i++) {
    d.data[i] = (wchar_t) tolower(d.data[i]);
  }

  return d;
}

d4_str_t d4_str_lowerFirst (const d4_str_t self) {
  d4_str_t d = d4_str_copy(self);

  if (self.len == 0) {
    return d;
  }

  d.data[0] = (wchar_t) tolower(d.data[0]);
  return d;
}

bool d4_str_not (const d4_str_t self) {
  return self.len == 0;
}

d4_str_t d4_str_replace (const d4_str_t self, const d4_str_t search, const d4_str_t replacement, D4_UNUSED unsigned char o3, int32_t count) {
  size_t l = 0;
  wchar_t *d = NULL;
  int32_t k = 0;
  size_t j = 0;

  if (search.len == 0 && replacement.len > 0) {
    l = self.len + (count > 0 && (size_t) count <= self.len ? (size_t) count : self.len + 1) * replacement.len;
    d = d4_safe_alloc((l + 1) * sizeof(wchar_t));
    wmemcpy(d, replacement.data, replacement.len);
    j = replacement.len;

    for (size_t i = 0; i < self.len; i++) {
      d[j++] = self.data[i];

      if (count <= 0 || ++k < count) {
        wmemcpy(&d[j], replacement.data, replacement.len);
        j += replacement.len;
      }
    }
  } else if (self.len == search.len && search.len > 0) {
    if (memcmp(self.data, search.data, search.len * sizeof(wchar_t)) != 0) {
      l = self.len;
      d = d4_safe_alloc((l + 1) * sizeof(wchar_t));
      wmemcpy(d, self.data, l);
    } else if (replacement.len > 0) {
      l = replacement.len;
      d = d4_safe_alloc((l + 1) * sizeof(wchar_t));
      wmemcpy(d, replacement.data, l);
    }
  } else if (self.len > search.len && search.len > 0 && replacement.len == 0) {
    d = d4_safe_alloc((self.len + 1) * sizeof(wchar_t));

    for (size_t i = 0; i < self.len; i++) {
      if (
        i <= self.len - search.len &&
        memcmp(&self.data[i], search.data, search.len * sizeof(wchar_t)) == 0 &&
        (count <= 0 || k++ < count)
      ) {
        i += search.len - 1;
      } else {
        d[l++] = self.data[i];
      }
    }

    if (l == 0) {
      d4_safe_free(d);
      d = NULL;
    } else if (l != self.len) {
      d = d4_safe_realloc(d, (l + 1) * sizeof(wchar_t));
    }
  } else if (self.len > search.len && search.len > 0 && replacement.len > 0) {
    l = self.len;
    d = d4_safe_alloc((l + 1) * sizeof(wchar_t));

    for (size_t i = 0; i < self.len; i++) {
      if (
        i <= self.len - search.len &&
        memcmp(&self.data[i], search.data, search.len * sizeof(wchar_t)) == 0 &&
        (count <= 0 || k++ < count)
      ) {
        if (search.len < replacement.len) {
          l += replacement.len - search.len;

          if (l > self.len) {
            d = d4_safe_realloc(d, (l + 1) * sizeof(wchar_t));
          }
        } else if (search.len > replacement.len) {
          l -= search.len - replacement.len;
        }

        wmemcpy(&d[j], replacement.data, replacement.len);
        j += replacement.len;
        i += search.len - 1;
      } else {
        d[j++] = self.data[i];
      }
    }

    d = d4_safe_realloc(d, (l + 1) * sizeof(wchar_t));
  } else if (self.len > 0) {
    l = self.len;
    d = d4_safe_alloc((l + 1) * sizeof(wchar_t));
    wmemcpy(d, self.data, l);
  }

  if (d != NULL) {
    d[l] = L'\0';
  }

  return (d4_str_t) {d, l, false};
}

d4_str_t d4_str_slice (const d4_str_t self, unsigned char o1, int32_t start, unsigned char o2, int32_t end) {
  int32_t i = 0;
  int32_t j = 0;

  if (o1 != 0 && start < 0 && start >= -((int32_t) self.len)) {
    i = (int32_t) ((size_t) start + self.len);
  } else if (o1 != 0 && start >= 0) {
    i = (int32_t) ((size_t) start > self.len ? self.len : (size_t) start);
  }

  if (o2 == 0 || (end >= 0 && (size_t) end > self.len)) {
    j = (int32_t) self.len;
  } else if (end < 0 && end >= -((int32_t) self.len)) {
    j = (int32_t) ((size_t) end + self.len);
  } else if (end >= 0) {
    j = (int32_t) end;
  }

  if (i >= j || (size_t) i >= self.len) {
    return d4_str_empty_val;
  }

  return d4_str_calloc(&self.data[i], (size_t) (j - i));
}

d4_arr_str_t d4_str_split (const d4_str_t self, D4_UNUSED unsigned char o1, const d4_str_t delimiter) {
  d4_str_t *r = NULL;
  size_t l = 0;

  if (self.len > 0 && delimiter.len == 0) {
    l = self.len;
    r = d4_safe_alloc(l * sizeof(d4_str_t));

    for (size_t i = 0; i < l; i++) {
      r[i] = d4_str_calloc(&self.data[i], 1);
    }
  } else if (self.len < delimiter.len) {
    r = d4_safe_realloc(r, ++l * sizeof(d4_str_t));
    r[0] = d4_str_calloc(self.data, self.len);
  } else if (delimiter.len > 0) {
    size_t i = 0;

    for (size_t j = 0; j <= self.len - delimiter.len; j++) {
      if (memcmp(&self.data[j], delimiter.data, delimiter.len * sizeof(wchar_t)) == 0) {
        r = d4_safe_realloc(r, ++l * sizeof(d4_str_t));
        r[l - 1] = d4_str_calloc(&self.data[i], j - i);
        j += delimiter.len;
        i = j;
      }
    }

    r = d4_safe_realloc(r, ++l * sizeof(d4_str_t));
    r[l - 1] = d4_str_calloc(&self.data[i], self.len - i);
  }

  return (d4_arr_str_t) {r, l};
}

bool d4_str_startsWith (const d4_str_t self, const d4_str_t search) {
  return self.len >= search.len && memcmp(self.data, search.data, search.len * sizeof(wchar_t)) == 0;
}

double d4_str_toFloat (d4_err_state_t *state, int line, int col, const d4_str_t self) {
  wchar_t *e = NULL;
  double r;

  errno = 0;
  r = self.len == 0 ? 0 : wcstod(self.data, &e);

  if (errno == ERANGE || r < -DBL_MAX || DBL_MAX < r) {
    d4_str_t message = d4_str_alloc(L"value `%ls` out of range", self.data);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    d4_str_t message;
    if (self.len == 0) {
      message = d4_str_alloc(L"value `` has invalid syntax");
    } else {
      message = d4_str_alloc(L"value `%ls` has invalid syntax", self.data);
    }
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return r;
}

float d4_str_toF32 (d4_err_state_t *state, int line, int col, const d4_str_t self) {
  wchar_t *e = NULL;
  float r;

  errno = 0;
  r = self.len == 0 ? 0 : wcstof(self.data, &e);

  if (errno == ERANGE || r < -FLT_MAX || FLT_MAX < r) {
    d4_str_t message = d4_str_alloc(L"value `%ls` out of range", self.data);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    d4_str_t message;
    if (self.len == 0) {
      message = d4_str_alloc(L"value `` has invalid syntax");
    } else {
      message = d4_str_alloc(L"value `%ls` has invalid syntax", self.data);
    }
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return r;
}

double d4_str_toF64 (d4_err_state_t *state, int line, int col, const d4_str_t self) {
  wchar_t *e = NULL;
  double r;

  errno = 0;
  r = self.len == 0 ? 0 : wcstod(self.data, &e);

  if (errno == ERANGE || r < -DBL_MAX || DBL_MAX < r) {
    d4_str_t message = d4_str_alloc(L"value `%ls` out of range", self.data);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    d4_str_t message;
    if (self.len == 0) {
      message = d4_str_alloc(L"value `` has invalid syntax");
    } else {
      message = d4_str_alloc(L"value `%ls` has invalid syntax", self.data);
    }
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return r;
}

ptrdiff_t d4_str_toIsize (d4_err_state_t *state, int line, int col, const d4_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  long long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    d4_str_t message = d4_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = self.len == 0 ? 0 : wcstoll(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || r < PTRDIFF_MIN || PTRDIFF_MAX < r) {
    d4_str_t message = d4_str_alloc(L"value `%ls` out of range", self.data);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    d4_str_t message;
    if (self.len == 0) {
      message = d4_str_alloc(L"value `` has invalid syntax");
    } else {
      message = d4_str_alloc(L"value `%ls` has invalid syntax", self.data);
    }
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (ptrdiff_t) r;
}

int8_t d4_str_toI8 (d4_err_state_t *state, int line, int col, const d4_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    d4_str_t message = d4_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = self.len == 0 ? 0 : wcstol(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || r < INT8_MIN || INT8_MAX < r) {
    d4_str_t message = d4_str_alloc(L"value `%ls` out of range", self.data);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    d4_str_t message;
    if (self.len == 0) {
      message = d4_str_alloc(L"value `` has invalid syntax");
    } else {
      message = d4_str_alloc(L"value `%ls` has invalid syntax", self.data);
    }
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (int8_t) r;
}

int16_t d4_str_toI16 (d4_err_state_t *state, int line, int col, const d4_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    d4_str_t message = d4_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = self.len == 0 ? 0 : wcstol(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || r < INT16_MIN || INT16_MAX < r) {
    d4_str_t message = d4_str_alloc(L"value `%ls` out of range", self.data);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    d4_str_t message;
    if (self.len == 0) {
      message = d4_str_alloc(L"value `` has invalid syntax");
    } else {
      message = d4_str_alloc(L"value `%ls` has invalid syntax", self.data);
    }
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (int16_t) r;
}

int32_t d4_str_toI32 (d4_err_state_t *state, int line, int col, const d4_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    d4_str_t message = d4_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = self.len == 0 ? 0 : wcstol(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || r < INT32_MIN || INT32_MAX < r) {
    d4_str_t message = d4_str_alloc(L"value `%ls` out of range", self.data);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    d4_str_t message;
    if (self.len == 0) {
      message = d4_str_alloc(L"value `` has invalid syntax");
    } else {
      message = d4_str_alloc(L"value `%ls` has invalid syntax", self.data);
    }
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (int32_t) r;
}

int64_t d4_str_toI64 (d4_err_state_t *state, int line, int col, const d4_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  long long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    d4_str_t message = d4_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = self.len == 0 ? 0 : wcstoll(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || r < INT64_MIN || INT64_MAX < r) {
    d4_str_t message = d4_str_alloc(L"value `%ls` out of range", self.data);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    d4_str_t message;
    if (self.len == 0) {
      message = d4_str_alloc(L"value `` has invalid syntax");
    } else {
      message = d4_str_alloc(L"value `%ls` has invalid syntax", self.data);
    }
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (int64_t) r;
}

size_t d4_str_toUsize (d4_err_state_t *state, int line, int col, const d4_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  unsigned long long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    d4_str_t message = d4_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = self.len == 0 ? 0 : wcstoull(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || SIZE_MAX < r || (self.len != 0 && self.data[0] == L'-')) {
    d4_str_t message = d4_str_alloc(L"value `%ls` out of range", self.data);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    d4_str_t message;
    if (self.len == 0) {
      message = d4_str_alloc(L"value `` has invalid syntax");
    } else {
      message = d4_str_alloc(L"value `%ls` has invalid syntax", self.data);
    }
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (size_t) r;
}

uint8_t d4_str_toU8 (d4_err_state_t *state, int line, int col, const d4_str_t self, unsigned char o1, int32_t radix) {\
  wchar_t *e = NULL;
  unsigned long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    d4_str_t message = d4_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = self.len == 0 ? 0 : wcstoul(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || UINT8_MAX < r || (self.len != 0 && self.data[0] == L'-')) {
    d4_str_t message = d4_str_alloc(L"value `%ls` out of range", self.data);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    d4_str_t message;
    if (self.len == 0) {
      message = d4_str_alloc(L"value `` has invalid syntax");
    } else {
      message = d4_str_alloc(L"value `%ls` has invalid syntax", self.data);
    }
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (uint8_t) r;
}

uint16_t d4_str_toU16 (d4_err_state_t *state, int line, int col, const d4_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  unsigned long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    d4_str_t message = d4_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = self.len == 0 ? 0 : wcstoul(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || UINT16_MAX < r || (self.len != 0 && self.data[0] == L'-')) {
    d4_str_t message = d4_str_alloc(L"value `%ls` out of range", self.data);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    d4_str_t message;
    if (self.len == 0) {
      message = d4_str_alloc(L"value `` has invalid syntax");
    } else {
      message = d4_str_alloc(L"value `%ls` has invalid syntax", self.data);
    }
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (uint16_t) r;
}

uint32_t d4_str_toU32 (d4_err_state_t *state, int line, int col, const d4_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  unsigned long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    d4_str_t message = d4_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = self.len == 0 ? 0 : wcstoul(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || UINT32_MAX < r || (self.len != 0 && self.data[0] == L'-')) {
    d4_str_t message = d4_str_alloc(L"value `%ls` out of range", self.data);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    d4_str_t message;
    if (self.len == 0) {
      message = d4_str_alloc(L"value `` has invalid syntax");
    } else {
      message = d4_str_alloc(L"value `%ls` has invalid syntax", self.data);
    }
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (uint32_t) r;
}

uint64_t d4_str_toU64 (d4_err_state_t *state, int line, int col, const d4_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  unsigned long long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    d4_str_t message = d4_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = self.len == 0 ? 0 : wcstoull(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || UINT64_MAX < r || (self.len != 0 && self.data[0] == L'-')) {
    d4_str_t message = d4_str_alloc(L"value `%ls` out of range", self.data);
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    d4_str_t message;
    if (self.len == 0) {
      message = d4_str_alloc(L"value `` has invalid syntax");
    } else {
      message = d4_str_alloc(L"value `%ls` has invalid syntax", self.data);
    }
    d4_error_assign_generic(state, line, col, message);
    d4_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (uint64_t) r;
}

d4_str_t d4_str_trim (const d4_str_t self) {
  size_t i = 0;
  size_t j = self.len;
  size_t l;

  if (self.len == 0) {
    return d4_str_empty_val;
  }

  while (i < self.len && isspace(self.data[i])) {
    i++;
  }

  while (isspace(self.data[j - 1])) {
    j--;
    if (j == 0) break;
  }

  if (i >= j) {
    return d4_str_empty_val;
  }

  l = j - i;
  return d4_str_calloc(&self.data[i], l);
}

d4_str_t d4_str_trimEnd (const d4_str_t self) {
  size_t l = self.len;

  if (self.len == 0) {
    return d4_str_empty_val;
  }

  while (isspace(self.data[l - 1])) {
    l--;

    if (l == 0) {
      return d4_str_empty_val;
    }
  }

  return d4_str_calloc(self.data, l);
}

d4_str_t d4_str_trimStart (const d4_str_t self) {
  size_t i = 0;

  if (self.len == 0) {
    return d4_str_empty_val;
  }

  while (i < self.len && isspace(self.data[i])) {
    i++;
  }

  if (i >= self.len) {
    return d4_str_empty_val;
  }

  return d4_str_calloc(&self.data[i], self.len - i);
}

d4_str_t d4_str_upper (const d4_str_t self) {
  d4_str_t d = d4_str_copy(self);

  if (self.len == 0) {
    return d;
  }

  for (size_t i = 0; i < d.len; i++) {
    d.data[i] = (wchar_t) toupper(d.data[i]);
  }

  return d;
}

d4_str_t d4_str_upperFirst (const d4_str_t self) {
  d4_str_t d = d4_str_copy(self);

  if (self.len == 0) {
    return d;
  }

  d.data[0] = (wchar_t) toupper(d.data[0]);
  return d;
}
