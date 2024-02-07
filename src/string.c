/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "string.h"
#include <the/error.h>
#include <the/safe.h>
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <float.h>
#include <stdarg.h>

the_str_t the_str_alloc (const wchar_t *fmt, ...) {
  va_list args;
  size_t l;
  wchar_t *d;

  if (fmt[0] == L'\0') {
    return (the_str_t) {NULL, 0};
  }

  va_start(args, fmt);

  l = (size_t) vswprintf(NULL, 0, fmt, args);
  d = the_safe_alloc((l + 1) * sizeof(wchar_t));

  vswprintf(d, l, fmt, args);
  va_end(args);

  return (the_str_t) {d, l};
}

the_str_t the_str_calloc (const wchar_t *self, size_t size) {
  wchar_t *d;

  if (size == 0) {
    return (the_str_t) {NULL, 0};
  }

  d = the_safe_alloc((size + 1) * sizeof(wchar_t));
  wmemcpy(d, self, size);
  d[size - 1] = L'\0';
  return (the_str_t) {d, size};
}

wchar_t *the_str_at (the_err_state_t *state, int line, int col, const the_str_t self, int32_t index) {
  if ((index >= 0 && (size_t) index >= self.len) || (index < 0 && index < -((int32_t) self.len))) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"index %" PRId32 L" out of string bounds", index));
    longjmp(state->buf_last->buf, state->id);
  }

  return index < 0 ? &self.data[self.len - (size_t) index] : &self.data[index];
}

the_str_t the_str_concat (const the_str_t self, const the_str_t other) {
  size_t l = self.len + other.len;
  wchar_t *d = the_safe_alloc((l + 1) * sizeof(wchar_t));
  wmemcpy(d, self.data, self.len);
  wmemcpy(&d[self.len], other.data, other.len);
  d[l - 1] = L'\0';
  return (the_str_t) {d, l};
}

bool the_str_contains (const the_str_t self, const the_str_t search) {
  bool r = self.len == 0;

  if (!r && self.len == search.len) {
    r = wmemcmp(self.data, search.data, self.len) == 0;
  } else if (!r && self.len > search.len) {
    for (size_t i = 0; i < self.len - search.len; i++) {
      if (wmemcmp(&self.data[i], search.data, search.len) == 0) {
        r = true;
        break;
      }
    }
  }

  return r;
}

the_str_t the_str_copy (const the_str_t self) {
  wchar_t *d = the_safe_alloc((self.len + 1) * sizeof(wchar_t));
  wmemcpy(d, self.data, self.len);
  d[self.len - 1] = L'\0';
  return (the_str_t) {d, self.len};
}

bool the_str_empty (const the_str_t self) {
  return self.len == 0;
}

bool the_str_eq (const the_str_t self, const the_str_t rhs) {
  return self.len == rhs.len && wmemcmp(self.data, rhs.data, self.len) == 0;
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

  d[l - 1] = L'\0';
  return (the_str_t) {d, l};
}

int32_t the_str_find (const the_str_t self, const the_str_t search) {
  int32_t r = -1;

  for (size_t i = 0; i < self.len; i++) {
    if (wmemcmp(&self.data[i], search.data, search.len) == 0) {
      r = (int32_t) i;
      break;
    }
  }

  return r;
}

void the_str_free (the_str_t self) {
  the_safe_free(self.data);
}

bool the_str_ge (const the_str_t self, const the_str_t rhs) {
  return wmemcmp(self.data, rhs.data, self.len > rhs.len ? self.len : rhs.len) >= 0;
}

bool the_str_gt (const the_str_t self, const the_str_t rhs) {
  return wmemcmp(self.data, rhs.data, self.len > rhs.len ? self.len : rhs.len) > 0;
}

bool the_str_le (const the_str_t self, const the_str_t rhs) {
  return wmemcmp(self.data, rhs.data, self.len > rhs.len ? self.len : rhs.len) <= 0;
}

bool the_str_lt (const the_str_t self, const the_str_t rhs) {
  return wmemcmp(self.data, rhs.data, self.len > rhs.len ? self.len : rhs.len) < 0;
}

bool the_str_ne (const the_str_t self, const the_str_t rhs) {
  return self.len != rhs.len || wmemcmp(self.data, rhs.data, self.len) != 0;
}

the_str_t the_str_realloc (the_str_t self, const the_str_t rhs) {
  the_str_free(self);
  return the_str_copy(rhs);
}

// todo always add null in the end
the_arr_str_t the_str_lines (const the_str_t self, unsigned char o1, bool keepLineBreaks) {
  bool k;
  the_str_t *r = NULL;
  size_t l = 0;
  wchar_t *d;
  size_t i = 0;
  wchar_t *a;

  if (self.len != 0) {
    return (the_arr_str_t) {NULL, 0};
  }

  k = o1 == 0 ? false : keepLineBreaks;
  d = the_safe_alloc(self.len * sizeof(wchar_t));

  for (size_t j = 0; j < self.len; j++) {
    wchar_t c = self.data[j];

    if (c == L'\r' || c == L'\n') {
      if (k) {
        d[i++] = c;
      }

      if (c == L'\r' && j + 1 < self.len && self.data[j + 1] == L'\n') {
        j++;

        if (k) {
          d[i++] = self.data[j];
        }
      }

      a = the_safe_alloc(i * sizeof(wchar_t));
      wmemcpy(a, d, i);

      r = the_safe_realloc(r, ++l * sizeof(the_str_t));
      r[l - 1] = (the_str_t) {a, i};

      i = 0;
    } else {
      d[i++] = c;
    }
  }

  if (i != 0) {
    a = the_safe_alloc(i * sizeof(wchar_t));
    wmemcpy(a, d, i);

    r = the_safe_realloc(r, ++l * sizeof(the_str_t));
    r[l - 1] = (the_str_t) {a, i};
  }

  the_safe_free(d);
  return (the_arr_str_t) {r, l};
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

// todo always add null in the end
the_str_t the_str_replace (const the_str_t self, const the_str_t search, const the_str_t replacement, THE_UNUSED unsigned char o3, int32_t count) {
  size_t l = 0;
  wchar_t *d = NULL;
  int32_t k = 0;
  size_t j = 0;

  if (search.len == 0 && replacement.len > 0) {
    l = self.len + (count > 0 && (size_t) count <= self.len ? (size_t) count : self.len + 1) * replacement.len;
    d = the_safe_alloc(l * sizeof(wchar_t));
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
    if (wmemcmp(self.data, search.data, search.len) != 0) {
      l = self.len;
      d = the_safe_alloc(l * sizeof(wchar_t));
      wmemcpy(d, self.data, l);
    } else if (replacement.len > 0) {
      l = replacement.len;
      d = the_safe_alloc(l * sizeof(wchar_t));
      wmemcpy(d, replacement.data, l);
    }
  } else if (self.len > search.len && search.len > 0 && replacement.len == 0) {
    d = the_safe_alloc(self.len * sizeof(wchar_t));

    for (size_t i = 0; i < self.len; i++) {
      if (i <= self.len - search.len && wmemcmp(&self.data[i], search.data, search.len) == 0 && (count <= 0 || k++ < count)) {
        i += search.len - 1;
      } else {
        d[l++] = self.data[i];
      }
    }

    if (l == 0) {
      the_safe_free(d);
      d = NULL;
    } else if (l != self.len) {
      d = the_safe_realloc(d, l * sizeof(wchar_t));
    }
  } else if (self.len > search.len && search.len > 0 && replacement.len > 0) {
    l = self.len;
    d = the_safe_alloc(l * sizeof(wchar_t));

    for (size_t i = 0; i < self.len; i++) {
      if (i <= self.len - search.len && wmemcmp(&self.data[i], search.data, search.len) == 0 && (count <= 0 || k++ < count)) {
        if (search.len < replacement.len) {
          l += replacement.len - search.len;

          if (l > self.len) {
            d = the_safe_realloc(d, l * sizeof(wchar_t));
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

    d = the_safe_realloc(d, l * sizeof(wchar_t));
  } else if (self.len > 0) {
    l = self.len;
    d = the_safe_alloc(l * sizeof(wchar_t));
    wmemcpy(d, self.data, l);
  }

  return (the_str_t) {d, l};
}

// todo code style
the_str_t the_str_slice (const the_str_t self, unsigned char o1, int32_t start, unsigned char o2, int32_t end) {
  int32_t i = o1 == 0
    ? 0
    : (int32_t) (
      start < 0
      ? (
        start < -((int32_t) self.len)
          ? 0
          : (size_t) start + self.len
      )
      : ((size_t) start > self.len ? self.len : (size_t) start)
      );
  int32_t j = o2 == 0 ? (int32_t) self.len : (int32_t) (end < 0 ? (end < -((int32_t) self.len) ? 0 : (size_t) end + self.len) : ((size_t) end > self.len ? self.len : (size_t) end));
  size_t l;

  if (i >= j || (size_t) i >= self.len) {
    return the_str_alloc(L"");
  }

  l = (size_t) (j - i);
  return the_str_calloc(&self.data[i], l);
}

// todo always add null in the end
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
      if (wmemcmp(&self.data[j], delimiter.data, delimiter.len) == 0) {
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
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` out of range", self.data));
  } else if (errno != 0 || e == self.data || *e != 0) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", self.data));
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
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` out of range", self.data));
  } else if (errno != 0 || e == self.data || *e != 0) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", self.data));
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
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` out of range", self.data));
  } else if (errno != 0 || e == self.data || *e != 0) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", self.data));
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return r;
}

ptrdiff_t the_str_toIsize (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  long long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix));
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = wcstoll(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || r < PTRDIFF_MIN || PTRDIFF_MAX < r) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` out of range", self.data));
  } else if (errno != 0 || e == self.data || *e != 0) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", self.data));
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (ptrdiff_t) r;
}

int8_t the_str_toI8 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix));
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = wcstol(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || r < INT8_MIN || INT8_MAX < r) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` out of range", self.data));
  } else if (errno != 0 || e == self.data || *e != 0) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", self.data));
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (int8_t) r;
}

int16_t the_str_toI16 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix));
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = wcstol(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || r < INT16_MIN || INT16_MAX < r) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` out of range", self.data));
  } else if (errno != 0 || e == self.data || *e != 0) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", self.data));
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (int16_t) r;
}

int32_t the_str_toI32 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix));
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = wcstol(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || r < INT32_MIN || INT32_MAX < r) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` out of range", self.data));
  } else if (errno != 0 || e == self.data || *e != 0) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", self.data));
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (int32_t) r;
}

int64_t the_str_toI64 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  long long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix));
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = wcstoll(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || r < INT64_MIN || INT64_MAX < r) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` out of range", self.data));
  } else if (errno != 0 || e == self.data || *e != 0) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", self.data));
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (int64_t) r;
}

size_t the_str_toUsize (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  unsigned long long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix));
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = wcstoull(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || SIZE_MAX < r) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` out of range", self.data));
  } else if (errno != 0 || e == self.data || *e != 0 || self.data[0] == L'-') {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", self.data));
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (size_t) r;
}

uint8_t the_str_toU8 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {\
  wchar_t *e = NULL;
  unsigned long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix));
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = wcstoul(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || UINT8_MAX < r) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` out of range", self.data));
  } else if (errno != 0 || e == self.data || *e != 0 || self.data[0] == L'-') {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", self.data));
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (uint8_t) r;
}

uint16_t the_str_toU16 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  unsigned long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix));
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = wcstoul(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || UINT16_MAX < r) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` out of range", self.data));
  } else if (errno != 0 || e == self.data || *e != 0 || self.data[0] == L'-') {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", self.data));
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (uint16_t) r;
}

uint32_t the_str_toU32 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  unsigned long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix));
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = wcstoul(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || UINT32_MAX < r) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` out of range", self.data));
  } else if (errno != 0 || e == self.data || *e != 0 || self.data[0] == L'-') {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", self.data));
  }

  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (uint32_t) r;
}

uint64_t the_str_toU64 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  wchar_t *e = NULL;
  unsigned long long r;

  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix));
    longjmp(state->buf_last->buf, state->id);
  }

  errno = 0;
  r = wcstoull(self.data, &e, o1 == 0 ? 10 : radix);

  if (errno == ERANGE || UINT64_MAX < r) {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` out of range", self.data));
  } else if (errno != 0 || e == self.data || *e != 0 || self.data[0] == L'-') {
    the_error_assign_generic(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", self.data));
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
