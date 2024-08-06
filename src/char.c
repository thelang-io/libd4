/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "char.h"
#include <d4/safe.h>
#include <ctype.h>
#include "string.h"

unsigned char d4_char_byte (char self) {
  return (unsigned char) self;
}

bool d4_char_isDigit (char self) {
  return isdigit(self);
}

bool d4_char_isLetter (char self) {
  return isalpha(self);
}

bool d4_char_isLetterOrDigit (char self) {
  return isalnum(self);
}

bool d4_char_isLower (char self) {
  return islower(self);
}

bool d4_char_isUpper (char self) {
  return isupper(self);
}

bool d4_char_isWhitespace (char self) {
  return isspace(self);
}

char d4_char_lower (char self) {
  return (char) tolower(self);
}

d4_str_t d4_char_repeat (char self, int32_t times) {
  size_t l;
  wchar_t *d;
  if (times <= 0) return d4_str_empty_val;
  l = (size_t) times;
  d = d4_safe_alloc(l * sizeof(wchar_t));
  for (size_t i = 0; i < l; i++) d[i] = (wchar_t) self;
  return (d4_str_t) {d, l, false};
}

d4_str_t d4_char_str (char self) {
  wchar_t buf[2] = {self, '\0'};
  return d4_str_alloc(buf);
}

char d4_char_upper (char self) {
  return (char) toupper(self);
}
