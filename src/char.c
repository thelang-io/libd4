/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "char.h"
#include <ctype.h>
#include "safe.h"
#include "string.h"

unsigned char the_char_byte (char self) {
  return (unsigned char) self;
}

bool the_char_isDigit (char self) {
  return isdigit(self);
}

bool the_char_isLetter (char self) {
  return isalpha(self);
}

bool the_char_isLetterOrDigit (char self) {
  return isalnum(self);
}

bool the_char_isLower (char self) {
  return islower(self);
}

bool the_char_isUpper (char self) {
  return isupper(self);
}

bool the_char_isWhitespace (char self) {
  return isspace(self);
}

char the_char_lower (char self) {
  return (char) tolower(self);
}

the_str_t the_char_repeat (char self, int32_t times) {
  size_t l;
  wchar_t *d;
  if (times <= 0) return the_str_alloc(L"");
  l = (size_t) times;
  d = the_safe_alloc(l * sizeof(wchar_t));
  for (size_t i = 0; i < l; i++) d[i] = (wchar_t) self;
  return (the_str_t) {d, l};
}

the_str_t the_char_str (char self) {
  wchar_t buf[2] = {self, '\0'};
  return the_str_alloc(buf);
}

char the_char_upper (char self) {
  return (char) toupper(self);
}
