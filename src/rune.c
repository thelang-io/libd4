/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "rune.h"
#include <the/safe.h>
#include <the/string.h>

unsigned char the_rune_byte (wchar_t self) {
  return (unsigned char) self;
}

bool the_rune_isDigit (wchar_t self) {
  return iswdigit(self);
}

bool the_rune_isLetter (wchar_t self) {
  return isalpha(self);
}

bool the_rune_isLetterOrDigit (wchar_t self) {
  return isalnum(self);
}

bool the_rune_isLower (wchar_t self) {
  return islower(self);
}

bool the_rune_isUpper (wchar_t self) {
  return isupper(self);
}

bool the_rune_isWhitespace (wchar_t self) {
  return isspace(self);
}

wchar_t the_rune_lower (wchar_t self) {
  return (wchar_t) towlower(self);
}

the_str_t the_rune_repeat (wchar_t self, int32_t times) {
  size_t l;
  wchar_t *d;
  if (times <= 0) return the_str_alloc(L"");
  l = (size_t) times;
  d = the_safe_alloc(l * sizeof(wchar_t));
  for (size_t i = 0; i < l; i++) d[i] = (wchar_t) self;
  return (the_str_t) {d, l};
}

the_str_t the_rune_str (wchar_t self) {
  wchar_t buf[2] = {self, '\0'};
  return the_str_alloc(buf);
}

wchar_t the_rune_upper (wchar_t self) {
  return (wchar_t) toupper(self);
}
