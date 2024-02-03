/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "string.h"
#include <errno.h>
#include <inttypes.h>
#include <float.h>
#include <limits.h>
#include <stdlib.h>
#include "error.h"
#include "safe.h"

the_str_t the_str_alloc (const wchar_t *fmt, ...) {
  va_list args;
  size_t l;
  wchar_t *d;
  if (fmt[0] == L'\0') return (the_str_t) {NULL, 0};
  va_start(args, fmt);
  l = (size_t) vswprintf(NULL, 0, fmt, args);
  d = the_safe_alloc((l + 1) * sizeof(wchar_t));
  vswprintf(d, l, fmt, args);
  va_end(args);
  return (the_str_t) {d, l};
}

the_str_t the_str_calloc (const wchar_t *self, size_t size) {
  wchar_t *d;
  if (size == 0) return (the_str_t) {NULL, 0};
  d = the_safe_alloc(size * sizeof(wchar_t));
  wmemcpy(d, self, size);
  return (the_str_t) {d, size};
}

wchar_t *the_str_at (the_err_state_t *state, int line, int col, const the_str_t self, int32_t index) {
  if ((index >= 0 && (size_t) index >= self.l) || (index < 0 && index < -((int32_t) self.l))) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"index %" PRId32 L" out of string bounds", index));
    longjmp(state->buf_last->buf, state->id);
  }
  return index < 0 ? &self.d[self.l - (size_t) index] : &self.d[index];
}

the_str_t the_str_concat (const the_str_t self, const the_str_t other) {
  size_t l = self.l + other.l;
  wchar_t *d = the_safe_alloc(l * sizeof(wchar_t));
  wmemcpy(d, self.d, self.l);
  wmemcpy(&d[self.l], other.d, other.l);
  return (the_str_t) {d, l};
}

bool the_str_contains (const the_str_t self, const the_str_t search) {
  bool r = self.l == 0;
  if (!r && self.l == search.l) {
    r = wmemcmp(self.d, search.d, self.l) == 0;
  } else if (!r && self.l > search.l) {
    for (size_t i = 0; i < self.l - search.l; i++) {
      if (wmemcmp(&self.d[i], search.d, search.l) == 0) {
        r = true;
        break;
      }
    }
  }
  return r;
}

the_str_t the_str_copy (const the_str_t self) {
  wchar_t *d = the_safe_alloc(self.l * sizeof(wchar_t));
  wmemcpy(d, self.d, self.l);
  return (the_str_t) {d, self.l};
}

wchar_t *the_str_cstr (const the_str_t self) {
  wchar_t *d = the_safe_alloc((self.l + 1) * sizeof(wchar_t));
  wmemcpy(d, self.d, self.l);
  d[self.l] = L'\0';
  return d;
}

bool the_str_empty (const the_str_t self) {
  return self.l == 0;
}

bool the_str_eq (const the_str_t self, const the_str_t rhs) {
  return self.l == rhs.l && wmemcmp(self.d, rhs.d, self.l) == 0;
}

the_str_t the_str_escape (const the_str_t self) {
  wchar_t *d = the_safe_alloc(self.l * sizeof(wchar_t));
  size_t l = 0;
  for (size_t i = 0; i < self.l; i++) {
    wchar_t c = self.d[i];
    if (c == L'\f' || c == L'\n' || c == L'\r' || c == L'\t' || c == L'\v' || c == L'"') {
      if (l + 2 > self.l) d = the_safe_realloc(d, (l + 2) * sizeof(wchar_t));
      d[l++] = L'\\';
      if (c == L'\f') d[l++] = L'f';
      else if (c == L'\n') d[l++] = L'n';
      else if (c == L'\r') d[l++] = L'r';
      else if (c == L'\t') d[l++] = L't';
      else if (c == L'\v') d[l++] = L'v';
      else if (c == L'"') d[l++] = L'"';
      continue;
    }
    if (l + 1 > self.l) d = the_safe_realloc(d, (l + 1) * sizeof(wchar_t));
    d[l++] = c;
  }
  return (the_str_t) {d, l};
}

int32_t the_str_find (const the_str_t self, const the_str_t search) {
  int32_t r = -1;
  for (size_t i = 0; i < self.l; i++) {
    if (wmemcmp(&self.d[i], search.d, search.l) == 0) {
      r = (int32_t) i;
      break;
    }
  }
  return r;
}

void the_str_free (the_str_t self) {
  free(self.d);
}

bool the_str_ge (const the_str_t self, const the_str_t rhs) {
  return wmemcmp(self.d, rhs.d, self.l > rhs.l ? self.l : rhs.l) >= 0;
}

bool the_str_gt (const the_str_t self, const the_str_t rhs) {
  return wmemcmp(self.d, rhs.d, self.l > rhs.l ? self.l : rhs.l) > 0;
}

bool the_str_le (const the_str_t self, const the_str_t rhs) {
  return wmemcmp(self.d, rhs.d, self.l > rhs.l ? self.l : rhs.l) <= 0;
}

size_t the_str_len (const the_str_t self) {
  return self.l;
}

bool the_str_lt (const the_str_t self, const the_str_t rhs) {
  return wmemcmp(self.d, rhs.d, self.l > rhs.l ? self.l : rhs.l) < 0;
}

bool the_str_ne (const the_str_t self, const the_str_t rhs) {
  return self.l != rhs.l || wmemcmp(self.d, rhs.d, self.l) != 0;
}

the_str_t the_str_realloc (the_str_t self, const the_str_t rhs) {
  the_str_free(self);
  return the_str_copy(rhs);
}

the_arr_str_t the_str_lines (const the_str_t self, unsigned char o1, bool keepLineBreaks) {
  bool k;
  the_str_t *r = NULL;
  size_t l = 0;
  wchar_t *d;
  size_t i = 0;
  wchar_t *a;
  if (self.l != 0) return (the_arr_str_t) {NULL, 0};
  k = o1 == 0 ? false : keepLineBreaks;
  d = the_safe_alloc(self.l * sizeof(wchar_t));
  for (size_t j = 0; j < self.l; j++) {
    wchar_t c = self.d[j];
    if (c == L'\r' || c == L'\n') {
      if (k) d[i++] = c;
      if (c == L'\r' && j + 1 < self.l && self.d[j + 1] == L'\n') {
        j++;
        if (k) d[i++] = self.d[j];
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
  free(d);
  return (the_arr_str_t) {r, l};
}

the_str_t the_str_lower (const the_str_t self) {
  the_str_t d = the_str_copy(self);
  if (self.l == 0) return d;
  for (size_t i = 0; i < d.l; i++) d.d[i] = (wchar_t) tolower(d.d[i]);
  return d;
}

the_str_t the_str_lowerFirst (const the_str_t self) {
  the_str_t d = the_str_copy(self);
  if (self.l == 0) return d;
  d.d[0] = (wchar_t) tolower(d.d[0]);
  return d;
}

bool the_str_not (const the_str_t self) {
  return self.l == 0;
}

the_str_t the_str_replace (const the_str_t self, const the_str_t search, const the_str_t replacement, __attribute__((unused)) unsigned char o3, int32_t count) {
  size_t l = 0;
  wchar_t *d = NULL;
  int32_t k = 0;
  size_t j = 0;
  if (search.l == 0 && replacement.l > 0) {
    l = self.l + (count > 0 && (size_t) count <= self.l ? (size_t) count : self.l + 1) * replacement.l;
    d = the_safe_alloc(l * sizeof(wchar_t));
    wmemcpy(d, replacement.d, replacement.l);
    j = replacement.l;
    for (size_t i = 0; i < self.l; i++) {
      d[j++] = self.d[i];
      if (count <= 0 || ++k < count) {
        wmemcpy(&d[j], replacement.d, replacement.l);
        j += replacement.l;
      }
    }
  } else if (self.l == search.l && search.l > 0) {
    if (wmemcmp(self.d, search.d, search.l) != 0) {
      l = self.l;
      d = the_safe_alloc(l * sizeof(wchar_t));
      wmemcpy(d, self.d, l);
    } else if (replacement.l > 0) {
      l = replacement.l;
      d = the_safe_alloc(l * sizeof(wchar_t));
      wmemcpy(d, replacement.d, l);
    }
  } else if (self.l > search.l && search.l > 0 && replacement.l == 0) {
    d = the_safe_alloc(self.l * sizeof(wchar_t));
    for (size_t i = 0; i < self.l; i++) {
      if (i <= self.l - search.l && wmemcmp(&self.d[i], search.d, search.l) == 0 && (count <= 0 || k++ < count)) {
        i += search.l - 1;
      } else {
        d[l++] = self.d[i];
      }
    }
    if (l == 0) {
      free(d);
      d = NULL;
    } else if (l != self.l) {
      d = the_safe_realloc(d, l * sizeof(wchar_t));
    }
  } else if (self.l > search.l && search.l > 0 && replacement.l > 0) {
    l = self.l;
    d = the_safe_alloc(l * sizeof(wchar_t));
    for (size_t i = 0; i < self.l; i++) {
      if (i <= self.l - search.l && wmemcmp(&self.d[i], search.d, search.l) == 0 && (count <= 0 || k++ < count)) {
        if (search.l < replacement.l) {
          l += replacement.l - search.l;
          if (l > self.l) {
            d = the_safe_realloc(d, l * sizeof(wchar_t));
          }
        } else if (search.l > replacement.l) {
          l -= search.l - replacement.l;
        }
        wmemcpy(&d[j], replacement.d, replacement.l);
        j += replacement.l;
        i += search.l - 1;
      } else {
        d[j++] = self.d[i];
      }
    }
    d = the_safe_realloc(d, l * sizeof(wchar_t));
  } else if (self.l > 0) {
    l = self.l;
    d = the_safe_alloc(l * sizeof(wchar_t));
    wmemcpy(d, self.d, l);
  }
  return (the_str_t) {d, l};
}

the_str_t the_str_slice (const the_str_t self, unsigned char o1, int32_t start, unsigned char o2, int32_t end) {
  int32_t i = o1 == 0 ? 0 : (int32_t) (start < 0 ? (start < -((int32_t) self.l) ? 0 : (size_t) start + self.l) : ((size_t) start > self.l ? self.l : (size_t) start));
  int32_t j = o2 == 0 ? (int32_t) self.l : (int32_t) (end < 0 ? (end < -((int32_t) self.l) ? 0 : (size_t) end + self.l) : ((size_t) end > self.l ? self.l : (size_t) end));
  size_t l;
  if (i >= j || (size_t) i >= self.l) return the_str_alloc(L"");
  l = (size_t) (j - i);
  return the_str_calloc(&self.d[i], l);
}

the_arr_str_t the_str_split (const the_str_t self, __attribute__((unused)) unsigned char o1, const the_str_t delimiter) {
  the_str_t *r = NULL;
  size_t l = 0;
  if (self.l > 0 && delimiter.l == 0) {
    l = self.l;
    r = the_safe_alloc(l * sizeof(the_str_t));
    for (size_t i = 0; i < l; i++) {
      r[i] = the_str_calloc(&self.d[i], 1);
    }
  } else if (self.l < delimiter.l) {
    r = the_safe_realloc(r, ++l * sizeof(the_str_t));
    r[0] = the_str_calloc(self.d, self.l);
  } else if (delimiter.l > 0) {
    size_t i = 0;
    for (size_t j = 0; j <= self.l - delimiter.l; j++) {
      if (wmemcmp(&self.d[j], delimiter.d, delimiter.l) == 0) {
        r = the_safe_realloc(r, ++l * sizeof(the_str_t));
        r[l - 1] = the_str_calloc(&self.d[i], j - i);
        j += delimiter.l;
        i = j;
      }
    }
    r = the_safe_realloc(r, ++l * sizeof(the_str_t));
    r[l - 1] = the_str_calloc(&self.d[i], self.l - i);
  }
  return (the_arr_str_t) {r, l};
}

double the_str_toFloat (the_err_state_t *state, int line, int col, const the_str_t self) {
  wchar_t *c = the_str_cstr(self);
  wchar_t *e = NULL;
  errno = 0;
  double r = wcstod(c, &e);
  if (errno == ERANGE || r < -DBL_MAX || DBL_MAX < r) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` out of range", c));
  } else if (errno != 0 || e == c || *e != 0) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", c));
  }
  free(c);
  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return r;
}

float the_str_toF32 (the_err_state_t *state, int line, int col, const the_str_t self) {
  wchar_t *c = the_str_cstr(self);
  wchar_t *e = NULL;
  errno = 0;
  float r = wcstof(c, &e);
  if (errno == ERANGE || r < -FLT_MAX || FLT_MAX < r) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` out of range", c));
  } else if (errno != 0 || e == c || *e != 0) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", c));
  }
  free(c);
  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return r;
}

double the_str_toF64 (the_err_state_t *state, int line, int col, const the_str_t self) {
  wchar_t *c = the_str_cstr(self);
  wchar_t *e = NULL;
  errno = 0;
  double r = wcstod(c, &e);
  if (errno == ERANGE || r < -DBL_MAX || DBL_MAX < r) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` out of range", c));
  } else if (errno != 0 || e == c || *e != 0) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", c));
  }
  free(c);
  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return r;
}

ptrdiff_t the_str_toIsize (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix));
    longjmp(state->buf_last->buf, state->id);
  }
  wchar_t *c = the_str_cstr(self);
  wchar_t *e = NULL;
  errno = 0;
  long long r = wcstoll(c, &e, o1 == 0 ? 10 : radix);
  if (errno == ERANGE || r < PTRDIFF_MIN || PTRDIFF_MAX < r) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` out of range", c));
  } else if (errno != 0 || e == c || *e != 0) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", c));
  }
  free(c);
  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (ptrdiff_t) r;
}

int8_t the_str_toI8 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix));
    longjmp(state->buf_last->buf, state->id);
  }
  wchar_t *c = the_str_cstr(self);
  wchar_t *e = NULL;
  errno = 0;
  long r = wcstol(c, &e, o1 == 0 ? 10 : radix);
  if (errno == ERANGE || r < INT8_MIN || INT8_MAX < r) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` out of range", c));
  } else if (errno != 0 || e == c || *e != 0) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", c));
  }
  free(c);
  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (int8_t) r;
}

int16_t the_str_toI16 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix));
    longjmp(state->buf_last->buf, state->id);
  }
  wchar_t *c = the_str_cstr(self);
  wchar_t *e = NULL;
  errno = 0;
  long r = wcstol(c, &e, o1 == 0 ? 10 : radix);
  if (errno == ERANGE || r < INT16_MIN || INT16_MAX < r) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` out of range", c));
  } else if (errno != 0 || e == c || *e != 0) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", c));
  }
  free(c);
  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (int16_t) r;
}

int32_t the_str_toI32 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix));
    longjmp(state->buf_last->buf, state->id);
  }
  wchar_t *c = the_str_cstr(self);
  wchar_t *e = NULL;
  errno = 0;
  long r = wcstol(c, &e, o1 == 0 ? 10 : radix);
  if (errno == ERANGE || r < INT32_MIN || INT32_MAX < r) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` out of range", c));
  } else if (errno != 0 || e == c || *e != 0) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", c));
  }
  free(c);
  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (int32_t) r;
}

int64_t the_str_toI64 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix));
    longjmp(state->buf_last->buf, state->id);
  }
  wchar_t *c = the_str_cstr(self);
  wchar_t *e = NULL;
  errno = 0;
  long long r = wcstoll(c, &e, o1 == 0 ? 10 : radix);
  if (errno == ERANGE || r < INT64_MIN || INT64_MAX < r) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` out of range", c));
  } else if (errno != 0 || e == c || *e != 0) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", c));
  }
  free(c);
  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (int64_t) r;
}

size_t the_str_toUsize (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix));
    longjmp(state->buf_last->buf, state->id);
  }
  wchar_t *c = the_str_cstr(self);
  wchar_t *e = NULL;
  errno = 0;
  unsigned long long r = wcstoull(c, &e, o1 == 0 ? 10 : radix);
  if (errno == ERANGE || SIZE_MAX < r) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` out of range", c));
  } else if (errno != 0 || e == c || *e != 0 || self.d[0] == L'-') {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", c));
  }
  free(c);
  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (size_t) r;
}

uint8_t the_str_toU8 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix));
    longjmp(state->buf_last->buf, state->id);
  }
  wchar_t *c = the_str_cstr(self);
  wchar_t *e = NULL;
  errno = 0;
  unsigned long r = wcstoul(c, &e, o1 == 0 ? 10 : radix);
  if (errno == ERANGE || UINT8_MAX < r) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` out of range", c));
  } else if (errno != 0 || e == c || *e != 0 || self.d[0] == L'-') {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", c));
  }
  free(c);
  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (uint8_t) r;
}

uint16_t the_str_toU16 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix));
    longjmp(state->buf_last->buf, state->id);
  }
  wchar_t *c = the_str_cstr(self);
  wchar_t *e = NULL;
  errno = 0;
  unsigned long r = wcstoul(c, &e, o1 == 0 ? 10 : radix);
  if (errno == ERANGE || UINT16_MAX < r) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` out of range", c));
  } else if (errno != 0 || e == c || *e != 0 || self.d[0] == L'-') {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", c));
  }
  free(c);
  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (uint16_t) r;
}

uint32_t the_str_toU32 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix));
    longjmp(state->buf_last->buf, state->id);
  }
  wchar_t *c = the_str_cstr(self);
  wchar_t *e = NULL;
  errno = 0;
  unsigned long r = wcstoul(c, &e, o1 == 0 ? 10 : radix);
  if (errno == ERANGE || UINT32_MAX < r) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` out of range", c));
  } else if (errno != 0 || e == c || *e != 0 || self.d[0] == L'-') {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", c));
  }
  free(c);
  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (uint32_t) r;
}

uint64_t the_str_toU64 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix) {
  if (o1 == 1 && (radix < 2 || radix > 36) && radix != 0) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"radix %" PRId32 L" is invalid, must be >= 2 and <= 36, or 0", radix));
    longjmp(state->buf_last->buf, state->id);
  }
  wchar_t *c = the_str_cstr(self);
  wchar_t *e = NULL;
  errno = 0;
  unsigned long long r = wcstoull(c, &e, o1 == 0 ? 10 : radix);
  if (errno == ERANGE || UINT64_MAX < r) {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` out of range", c));
  } else if (errno != 0 || e == c || *e != 0 || self.d[0] == L'-') {
    the_error_assign_builtin(state, line, col, the_str_alloc(L"value `%ls` has invalid syntax", c));
  }
  free(c);
  if (state->id != -1) longjmp(state->buf_last->buf, state->id);
  return (uint64_t) r;
}

the_str_t the_str_trim (const the_str_t self) {
  if (self.l == 0) return self;
  size_t i = 0;
  size_t j = self.l;
  while (i < self.l && isspace(self.d[i])) i++;
  while (isspace(self.d[j - 1])) {
    j--;
    if (j == 0) break;
  }
  if (i >= j) return the_str_alloc(L"");
  size_t l = j - i;
  return the_str_calloc(&self.d[i], l);
}

the_str_t the_str_trimEnd (const the_str_t self) {
  if (self.l == 0) return self;
  size_t l = self.l;
  while (isspace(self.d[l - 1])) {
    l--;
    if (l == 0) return the_str_alloc(L"");
  }
  return the_str_calloc(self.d, l);
}

the_str_t the_str_trimStart (const the_str_t self) {
  if (self.l == 0) return self;
  size_t i = 0;
  while (i < self.l && isspace(self.d[i])) i++;
  if (i >= self.l) return the_str_alloc(L"");
  size_t l = self.l - i;
  return the_str_calloc(&self.d[i], l);
}

the_str_t the_str_upper (const the_str_t self) {
  the_str_t d = the_str_copy(self);
  if (self.l == 0) return d;
  for (size_t i = 0; i < d.l; i++) d.d[i] = (wchar_t) toupper(d.d[i]);
  return d;
}

the_str_t the_str_upperFirst (const the_str_t self) {
  the_str_t d = the_str_copy(self);
  if (self.l == 0) return d;
  d.d[0] = (wchar_t) toupper(d.d[0]);
  return d;
}
