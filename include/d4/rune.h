/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_RUNE_H
#define D4_RUNE_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include <stdint.h>
#include "string-type.h"

/**
 * Generates byte representation of the object.
 * @param self Object to generate byte representation for.
 * @return Byte representation of the object.
 */
unsigned char d4_rune_byte (wchar_t self);

/**
 * Checks whether wide character is a digit.
 * @param self Object to make a check against.
 * @return Whether wide character is a digit.
 */
bool d4_rune_isDigit (wchar_t self);

/**
 * Checks whether wide character is a letter.
 * @param self Object to make a check against.
 * @return Whether wide character is a letter.
 */
bool d4_rune_isLetter (wchar_t self);

/**
 * Checks whether wide character is a letter or a digit.
 * @param self Object to make a check against.
 * @return Whether wide character is a letter or a digit.
 */
bool d4_rune_isLetterOrDigit (wchar_t self);

/**
 * Checks whether wide character is in a lower case.
 * @param self Object to make a check against.
 * @return Whether wide character is in a lower case.
 */
bool d4_rune_isLower (wchar_t self);

/**
 * Checks whether wide character is in a upper case.
 * @param self Object to make a check against.
 * @return Whether wide character is in a upper case.
 */
bool d4_rune_isUpper (wchar_t self);

/**
 * Checks whether wide character is a whitespace.
 * @param self Object to make a check against.
 * @return Whether wide character is a whitespace.
 */
bool d4_rune_isWhitespace (wchar_t self);

/**
 * Converts wide character to a lowercase representation.
 * @param self Object to make a conversion against.
 * @return Lowercase representation of a wide character.
 */
wchar_t d4_rune_lower (wchar_t self);

/**
 * Generate a string by repeating the wide character X amount of times.
 * @param self Wide character to repeat.
 * @param times Amount of times to repeat a wide character.
 * @return String resulted by repeating the wide character X amount of times.
 */
d4_str_t d4_rune_repeat (wchar_t self, int32_t times);

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
d4_str_t d4_rune_str (wchar_t self);

/**
 * Converts wide character to an uppercase representation.
 * @param self Object to make a conversion against.
 * @return Uppercase representation of a wide character.
 */
wchar_t d4_rune_upper (wchar_t self);

#endif
