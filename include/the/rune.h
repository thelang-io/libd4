/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_RUNE_H
#define THE_RUNE_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/string-type.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * Generates byte representation of the object.
 * @param self Object to generate byte representation for.
 * @return Byte representation of the object.
 */
unsigned char the_rune_byte (wchar_t self);

/**
 * Checks whether wide character is a digit.
 * @param self Object to make a check against.
 * @return Whether wide character is a digit.
 */
bool the_rune_isDigit (wchar_t self);

/**
 * Checks whether wide character is a letter.
 * @param self Object to make a check against.
 * @return Whether wide character is a letter.
 */
bool the_rune_isLetter (wchar_t self);

/**
 * Checks whether wide character is a letter or a digit.
 * @param self Object to make a check against.
 * @return Whether wide character is a letter or a digit.
 */
bool the_rune_isLetterOrDigit (wchar_t self);

/**
 * Checks whether wide character is in a lower case.
 * @param self Object to make a check against.
 * @return Whether wide character is in a lower case.
 */
bool the_rune_isLower (wchar_t self);

/**
 * Checks whether wide character is in a upper case.
 * @param self Object to make a check against.
 * @return Whether wide character is in a upper case.
 */
bool the_rune_isUpper (wchar_t self);

/**
 * Checks whether wide character is a whitespace.
 * @param self Object to make a check against.
 * @return Whether wide character is a whitespace.
 */
bool the_rune_isWhitespace (wchar_t self);

/**
 * Converts wide character to a lowercase representation.
 * @param self Object to make a conversion against.
 * @return Lowercase representation of a wide character.
 */
wchar_t the_rune_lower (wchar_t self);

/**
 * Generate a string by repeating the wide character X amount of times.
 * @param self Wide character to repeat.
 * @param times Amount of times to repeat a wide character.
 * @return String resulted by repeating the wide character X amount of times.
 */
the_str_t the_rune_repeat (wchar_t self, int32_t times);

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
the_str_t the_rune_str (wchar_t self);

/**
 * Converts wide character to an uppercase representation.
 * @param self Object to make a conversion against.
 * @return Uppercase representation of a wide character.
 */
wchar_t the_rune_upper (wchar_t self);

#endif
