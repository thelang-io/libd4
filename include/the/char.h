/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_CHAR_H
#define THE_CHAR_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/string-type.h>
#include <stdbool.h>
#include <stdint.h>

/** todo */
unsigned char the_char_byte (char self);

/** todo */
bool the_char_isDigit (char self);

/** todo */
bool the_char_isLetter (char self);

/** todo */
bool the_char_isLetterOrDigit (char self);

/** todo */
bool the_char_isLower (char self);

/** todo */
bool the_char_isUpper (char self);

/** todo */
bool the_char_isWhitespace (char self);

/** todo */
char the_char_lower (char self);

/** todo */
the_str_t the_char_repeat (char self, int32_t times);

/** todo */
the_str_t the_char_str (char self);

/** todo */
char the_char_upper (char self);

#endif
