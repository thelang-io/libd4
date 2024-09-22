/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "rune.h"
#include <d4/safe.h>
#include <ctype.h>
#include <wctype.h>
#include "string.h"

unsigned char d4_rune_byte (wchar_t self) {
  return (unsigned char) self;
}

bool d4_rune_isDigit (wchar_t self) {
  return iswdigit(self);
}

bool d4_rune_isLetter (wchar_t self) {
  return isalpha(self);
}

bool d4_rune_isLetterOrDigit (wchar_t self) {
  return isalnum(self);
}

bool d4_rune_isLower (wchar_t self) {
  return islower(self);
}

bool d4_rune_isUpper (wchar_t self) {
  return isupper(self);
}

bool d4_rune_isWhitespace (wchar_t self) {
  return isspace(self);
}

wchar_t d4_rune_lower (wchar_t self) {
  return (wchar_t) towlower(self);
}

d4_str_t d4_rune_repeat (wchar_t self, int32_t times) {
  size_t l;
  wchar_t *d;
  if (times <= 0) return d4_str_empty_val;
  l = (size_t) times;
  d = d4_safe_alloc(l * sizeof(wchar_t));
  for (size_t i = 0; i < l; i++) d[i] = (wchar_t) self;
  return (d4_str_t) {d, l, false};
}

d4_str_t d4_rune_str (wchar_t self) {
  wchar_t buf[2] = {self, '\0'};
  return d4_str_alloc(buf);
}

wchar_t d4_rune_upper (wchar_t self) {
  return (wchar_t) toupper(self);
}
