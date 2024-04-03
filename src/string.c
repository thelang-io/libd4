/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "string.h"
#include <the/array.h>
#include <the/macro.h>
#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <string.h>

THE_ARRAY_DEFINE(str, the_str_t, the_str_t, the_str_copy(element), the_str_eq(lhs_element, rhs_element), the_str_free(element), the_str_copy(element))

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
  wchar_t *buffer = the_safe_alloc(buf_size * sizeof(wchar_t));
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
    buffer = the_safe_realloc(buffer, buf_size * sizeof(wchar_t));
  }

  the_safe_free(buffer);
  return fmt_size;
}

the_str_t the_str_alloc (const wchar_t *fmt, ...) {
  va_list args;
  size_t l = 0;
  wchar_t *d = NULL;

  va_start(args, fmt);

  if (fmt[0] != L'\0') {
    l = (size_t) vsnwprintf(fmt, args);
    d = the_safe_alloc((l + 1) * sizeof(wchar_t));
    vswprintf(d, l + 1, fmt, args);
  }

  va_end(args);
  return (the_str_t) {d, l};
}

the_str_t the_str_calloc (const wchar_t *self, size_t length) {
  wchar_t *d;

  if (length == 0) {
    return (the_str_t) {NULL, 0};
  }

  d = the_safe_alloc((length + 1) * sizeof(wchar_t));
  wmemcpy(d, self, length);
  d[length] = L'\0';
  return (the_str_t) {d, length};
}

wchar_t *the_str_at (the_err_state_t *state, int line, int col, const the_str_t self, int32_t index) {
  if ((index >= 0 && (size_t) index >= self.len) || (index < 0 && index < -((int32_t) self.len))) {
    the_str_t message = the_str_alloc(L"index %" PRId32 L" out of string bounds", index);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  return index < 0 ? &self.data[self.len + (size_t) index] : &self.data[index];
}

the_str_t the_str_concat (const the_str_t self, const the_str_t other) {
  size_t l = self.len + other.len;
  wchar_t *d = the_safe_alloc((l + 1) * sizeof(wchar_t));
  wmemcpy(d, self.data, self.len);
  wmemcpy(&d[self.len], other.data, other.len);
  d[l] = L'\0';
  return (the_str_t) {d, l};
}

bool the_str_contains (const the_str_t self, const the_str_t search) {
  if (self.len == search.len) {
    return memcmp(self.data, search.data, self.len * sizeof(wchar_t)) >= 0;
  } else if (self.len > 0 && self.len > search.len) {
    for (size_t i = 0; i < self.len - search.len + 1; i++) {
      if (memcmp(&self.data[i], search.data, search.len * sizeof(wchar_t)) >= 0) {
        return true;
      }
    }
  }

  return false;
}

the_str_t the_str_copy (const the_str_t self) {
  wchar_t *d = the_safe_alloc((self.len + 1) * sizeof(wchar_t));
  wmemcpy(d, self.data, self.len);
  d[self.len] = L'\0';
  return (the_str_t) {d, self.len};
}

bool the_str_empty (const the_str_t self) {
  return self.len == 0;
}

bool the_str_eq (const the_str_t self, const the_str_t rhs) {
  return self.len == rhs.len && memcmp(self.data, rhs.data, self.len * sizeof(wchar_t)) == 0;
}

the_str_t the_str_escape (const the_str_t self) {
  wchar_t *d = the_safe_alloc((self.len + 1) * sizeof(wchar_t));
  size_t l = 0;

  for (size_t i = 0; i < self.len; i++) {
    wchar_t c = self.data[i];

    if (c == L'\f' || c == L'\n' || c == L'\r' || c == L'\t' || c == L'\v' || c == L'"') {
      if (l + 3 > self.len) {
        d = the_safe_realloc(d, (l + 3) * sizeof(wchar_t));
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
      d = the_safe_realloc(d, (l + 2) * sizeof(wchar_t));
    }

    d[l++] = c;
  }

  d[l] = L'\0';
  return (the_str_t) {d, l};
}

int32_t the_str_find (const the_str_t self, const the_str_t search) {
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

void the_str_free (the_str_t self) {
  the_safe_free(self.data);
}

bool the_str_ge (const the_str_t self, const the_str_t rhs) {
  return memcmp(self.data, rhs.data, (self.len > rhs.len ? self.len : rhs.len) * sizeof(wchar_t)) >= 0;
}

bool the_str_gt (const the_str_t self, const the_str_t rhs) {
  return memcmp(self.data, rhs.data, (self.len > rhs.len ? self.len : rhs.len) * sizeof(wchar_t)) > 0;
}

bool the_str_le (const the_str_t self, const the_str_t rhs) {
  return memcmp(self.data, rhs.data, (self.len > rhs.len ? self.len : rhs.len) * sizeof(wchar_t)) <= 0;
}

bool the_str_lt (const the_str_t self, const the_str_t rhs) {
  return memcmp(self.data, rhs.data, (self.len > rhs.len ? self.len : rhs.len) * sizeof(wchar_t)) < 0;
}

the_str_t the_str_realloc (the_str_t self, const the_str_t rhs) {
  if (self.len == 0) {
    self.data = the_safe_alloc((rhs.len + 1) * sizeof(wchar_t));
  } else {
    self.data = the_safe_realloc(self.data, (rhs.len + 1) * sizeof(wchar_t));
  }

  wmemcpy(self.data, rhs.data, rhs.len);
  self.data[rhs.len] = L'\0';
  return (the_str_t) {self.data, rhs.len};
}

the_arr_str_t the_str_lines (const the_str_t self, unsigned char o1, bool keepLineBreaks) {
  bool k = o1 == 0 ? false : keepLineBreaks;
  the_str_t *result = NULL;
  size_t len = 0;
  size_t start = 0;

  if (self.len != 0) {
    return (the_arr_str_t) {NULL, 0};
  }

  for (size_t j = 0; j < self.len; j++) {
    wchar_t c = self.data[j];

    if (c == L'\r' || c == L'\n') {
      size_t beforeLineBreak = j;

      if (c == L'\r' && j + 1 < self.len && self.data[j + 1] == L'\n') {
        j++;
      }

      result = the_safe_realloc(result, ++len * sizeof(the_str_t));
      result[len - 1] = the_str_calloc(&self.data[start], (k ? j + 1 : beforeLineBreak) - start);

      start = j + 1;
    }
  }

  if (start != self.len) {
    result = the_safe_realloc(result, ++len * sizeof(the_str_t));
    result[len - 1] = the_str_calloc(&self.data[start], self.len - start);
  }

  return (the_arr_str_t) {result, len};
}

the_str_t the_str_lower (const the_str_t self) {
  the_str_t d = the_str_copy(self);

  if (self.len == 0) {
    return d;
  }

  for (size_t i = 0; i < d.len; i++) {
    d.data[i] = (wchar_t) tolower(d.data[i]);
  }

  return d;
}

the_str_t the_str_lowerFirst (const the_str_t self) {
  the_str_t d = the_str_copy(self);

  if (self.len == 0) {
    return d;
  }

  d.data[0] = (wchar_t) tolower(d.data[0]);
  return d;
}

bool the_str_not (const the_str_t self) {
  return self.len == 0;
}

the_str_t the_str_replace (const the_str_t self, const the_str_t search, const the_str_t replacement, THE_UNUSED unsigned char o3, int32_t count) {
  size_t l = 0;
  wchar_t *d = NULL;
  int32_t k = 0;
  size_t j = 0;

  if (search.len == 0 && replacement.len > 0) {
    l = self.len + (count > 0 && (size_t) count <= self.len ? (size_t) count : self.len + 1) * replacement.len;
    d = the_safe_alloc((l + 1) * sizeof(wchar_t));
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
      d = the_safe_alloc((l + 1) * sizeof(wchar_t));
      wmemcpy(d, self.data, l);
    } else if (replacement.len > 0) {
      l = replacement.len;
      d = the_safe_alloc((l + 1) * sizeof(wchar_t));
      wmemcpy(d, replacement.data, l);
    }
  } else if (self.len > search.len && search.len > 0 && replacement.len == 0) {
    d = the_safe_alloc((self.len + 1) * sizeof(wchar_t));

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
      the_safe_free(d);
      d = NULL;
    } else if (l != self.len) {
      d = the_safe_realloc(d, (l + 1) * sizeof(wchar_t));
    }
  } else if (self.len > search.len && search.len > 0 && replacement.len > 0) {
    l = self.len;
    d = the_safe_alloc((l + 1) * sizeof(wchar_t));

    for (size_t i = 0; i < self.len; i++) {
      if (
        i <= self.len - search.len &&
        memcmp(&self.data[i], search.data, search.len * sizeof(wchar_t)) == 0 &&
        (count <= 0 || k++ < count)
      ) {
        if (search.len < replacement.len) {
          l += replacement.len - search.len;

          if (l > self.len) {
            d = the_safe_realloc(d, (l + 1) * sizeof(wchar_t));
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

    d = the_safe_realloc(d, (l + 1) * sizeof(wchar_t));
  } else if (self.len > 0) {
    l = self.len;
    d = the_safe_alloc((l + 1) * sizeof(wchar_t));
    wmemcpy(d, self.data, l);
  }

  if (d != NULL) {
    d[l] = '\0';
  }

  return (the_str_t) {d, l};
}

the_str_t the_str_slice (const the_str_t self, unsigned char o1, int32_t start, unsigned char o2, int32_t end) {
  int32_t i = 0;
  int32_t j = 0;
  size_t l;

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
    return the_str_alloc(L"");
  }

  l = (size_t) (j - i);
  return the_str_calloc(&self.data[i], l);
}

the_arr_str_t the_str_split (const the_str_t self, THE_UNUSED unsigned char o1, const the_str_t delimiter) {
  the_str_t *r = NULL;
  size_t l = 0;

  if (self.len > 0 && delimiter.len == 0) {
    l = self.len;
    r = the_safe_alloc(l * sizeof(the_str_t));

    for (size_t i = 0; i < l; i++) {
      r[i] = the_str_calloc(&self.data[i], 1);
    }
  } else if (self.len < delimiter.len) {
    r = the_safe_realloc(r, ++l * sizeof(the_str_t));
    r[0] = the_str_calloc(self.data, self.len);
  } else if (delimiter.len > 0) {
    size_t i = 0;

    for (size_t j = 0; j <= self.len - delimiter.len; j++) {
      if (memcmp(&self.data[j], delimiter.data, delimiter.len * sizeof(wchar_t)) == 0) {
        r = the_safe_realloc(r, ++l * sizeof(the_str_t));
        r[l - 1] = the_str_calloc(&self.data[i], j - i);
        j += delimiter.len;
        i = j;
      }
    }

    r = the_safe_realloc(r, ++l * sizeof(the_str_t));
    r[l - 1] = the_str_calloc(&self.data[i], self.len - i);
  }

  return (the_arr_str_t) {r, l};
}

double the_str_toFloat (the_err_state_t *state, int line, int col, const the_str_t self) {
  wchar_t *e = NULL;
  double r;

  errno = 0;
  r = wcstod(self.data, &e);

  if (errno == ERANGE || r < -DBL_MAX || DBL_MAX < r) {
    the_str_t message = the_str_alloc(L"value `%ls` out of range", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    the_str_t message = the_str_alloc(L"value `%ls` has invalid syntax", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return r;
}

float the_str_toF32 (the_err_state_t *state, int line, int col, const the_str_t self) {
  wchar_t *e = NULL;
  float r;

  errno = 0;
  r = wcstof(self.data, &e);

  if (errno == ERANGE || r < -FLT_MAX || FLT_MAX < r) {
    the_str_t message = the_str_alloc(L"value `%ls` out of range", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    the_str_t message = the_str_alloc(L"value `%ls` has invalid syntax", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return r;
}

double the_str_toF64 (the_err_state_t *state, int line, int col, const the_str_t self) {
  wchar_t *e = NULL;
  double r;

  errno = 0;
  r = wcstod(self.data, &e);

  if (errno == ERANGE || r < -DBL_MAX || DBL_MAX < r) {
    the_str_t message = the_str_alloc(L"value `%ls` out of range", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    the_str_t message = the_str_alloc(L"value `%ls` has invalid syntax", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return r;
}

ptrdiff_t the_str_toIsize (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  long long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_str_t message = the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = wcstoll(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || r < PTRDIFF_MIN || PTRDIFF_MAX < r) {
    the_str_t message = the_str_alloc(L"value `%ls` out of range", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    the_str_t message = the_str_alloc(L"value `%ls` has invalid syntax", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (ptrdiff_t) r;
}

int8_t the_str_toI8 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_str_t message = the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = wcstol(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || r < INT8_MIN || INT8_MAX < r) {
    the_str_t message = the_str_alloc(L"value `%ls` out of range", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    the_str_t message = the_str_alloc(L"value `%ls` has invalid syntax", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (int8_t) r;
}

int16_t the_str_toI16 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_str_t message = the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = wcstol(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || r < INT16_MIN || INT16_MAX < r) {
    the_str_t message = the_str_alloc(L"value `%ls` out of range", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    the_str_t message = the_str_alloc(L"value `%ls` has invalid syntax", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (int16_t) r;
}

int32_t the_str_toI32 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_str_t message = the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = wcstol(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || r < INT32_MIN || INT32_MAX < r) {
    the_str_t message = the_str_alloc(L"value `%ls` out of range", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    the_str_t message = the_str_alloc(L"value `%ls` has invalid syntax", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (int32_t) r;
}

int64_t the_str_toI64 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  long long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_str_t message = the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = wcstoll(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || r < INT64_MIN || INT64_MAX < r) {
    the_str_t message = the_str_alloc(L"value `%ls` out of range", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0) {
    the_str_t message = the_str_alloc(L"value `%ls` has invalid syntax", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (int64_t) r;
}

size_t the_str_toUsize (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  unsigned long long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_str_t message = the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = wcstoull(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || SIZE_MAX < r) {
    the_str_t message = the_str_alloc(L"value `%ls` out of range", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0 || self.data[0] == L'-') {
    the_str_t message = the_str_alloc(L"value `%ls` has invalid syntax", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (size_t) r;
}

uint8_t the_str_toU8 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {\
  wchar_t *e = NULL;
  unsigned long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_str_t message = the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = wcstoul(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || UINT8_MAX < r) {
    the_str_t message = the_str_alloc(L"value `%ls` out of range", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0 || self.data[0] == L'-') {
    the_str_t message = the_str_alloc(L"value `%ls` has invalid syntax", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (uint8_t) r;
}

uint16_t the_str_toU16 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  unsigned long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_str_t message = the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = wcstoul(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || UINT16_MAX < r) {
    the_str_t message = the_str_alloc(L"value `%ls` out of range", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0 || self.data[0] == L'-') {
    the_str_t message = the_str_alloc(L"value `%ls` has invalid syntax", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (uint16_t) r;
}

uint32_t the_str_toU32 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  unsigned long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_str_t message = the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = wcstoul(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || UINT32_MAX < r) {
    the_str_t message = the_str_alloc(L"value `%ls` out of range", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0 || self.data[0] == L'-') {
    the_str_t message = the_str_alloc(L"value `%ls` has invalid syntax", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (uint32_t) r;
}

uint64_t the_str_toU64 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  unsigned long long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_str_t message = the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = wcstoull(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || UINT64_MAX < r) {
    the_str_t message = the_str_alloc(L"value `%ls` out of range", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  } else if (errno != 0 || e == self.data || *e != 0 || self.data[0] == L'-') {
    the_str_t message = the_str_alloc(L"value `%ls` has invalid syntax", self.data);
    the_error_assign_generic(state, line, col, message);
    the_str_free(message);
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (uint64_t) r;
}

the_str_t the_str_trim (const the_str_t self) {
  size_t i = 0;
  size_t j = self.len;
  size_t l;

  if (self.len == 0) {
    return self;
  }

  while (i < self.len && isspace(self.data[i])) {
    i++;
  }

  while (isspace(self.data[j - 1])) {
    j--;
    if (j == 0) break;
  }

  if (i >= j) {
    return the_str_alloc(L"");
  }

  l = j - i;
  return the_str_calloc(&self.data[i], l);
}

the_str_t the_str_trimEnd (const the_str_t self) {
  size_t l = self.len;
  if (self.len == 0) return self;

  while (isspace(self.data[l - 1])) {
    l--;

    if (l == 0) {
      return the_str_alloc(L"");
    }
  }

  return the_str_calloc(self.data, l);
}

the_str_t the_str_trimStart (const the_str_t self) {
  size_t i = 0;
  size_t l;

  if (self.len == 0) {
    return self;
  }

  while (i < self.len && isspace(self.data[i])) {
    i++;
  }

  if (i >= self.len) {
    return the_str_alloc(L"");
  }

  l = self.len - i;
  return the_str_calloc(&self.data[i], l);
}

the_str_t the_str_upper (const the_str_t self) {
  the_str_t d = the_str_copy(self);

  if (self.len == 0) {
    return d;
  }

  for (size_t i = 0; i < d.len; i++) {
    d.data[i] = (wchar_t) toupper(d.data[i]);
  }

  return d;
}

the_str_t the_str_upperFirst (const the_str_t self) {
  the_str_t d = the_str_copy(self);

  if (self.len == 0) {
    return d;
  }

  d.data[0] = (wchar_t) toupper(d.data[0]);
  return d;
}
