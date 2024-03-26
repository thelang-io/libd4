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

/**
 * Generates byte representation of the object.
 * @param self Object to generate byte representation for.
 * @return Byte representation of the object.
 */
unsigned char the_char_byte (char self);

/**
 * Checks whether character is a digit.
 * @param self Object to make a check against.
 * @return Whether character is a digit.
 */
bool the_char_isDigit (char self);

/**
 * Checks whether character is a letter.
 * @param self Object to make a check against.
 * @return Whether character is a letter.
 */
bool the_char_isLetter (char self);

/**
 * Checks whether character is a letter or a digit.
 * @param self Object to make a check against.
 * @return Whether character is a letter or a digit.
 */
bool the_char_isLetterOrDigit (char self);

/**
 * Checks whether character is in a lower case.
 * @param self Object to make a check against.
 * @return Whether character is in a lower case.
 */
bool the_char_isLower (char self);

/**
 * Checks whether character is in a upper case.
 * @param self Object to make a check against.
 * @return Whether character is in a upper case.
 */
bool the_char_isUpper (char self);

/**
 * Checks whether character is a whitespace.
 * @param self Object to make a check against.
 * @return Whether character is a whitespace.
 */
bool the_char_isWhitespace (char self);

/**
 * Converts character to a lowercase representation.
 * @param self Object to make a conversion against.
 * @return Lowercase representation of a character.
 */
char the_char_lower (char self);

/**
 * Generate a string by repeating the character X amount of times.
 * @param self Character to repeat.
 * @param times Amount of times to repeat a character.
 * @return String resulted by repeating the character X amount of times.
 */
the_str_t the_char_repeat (char self, int32_t times);

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
the_str_t the_char_str (char self);

/**
 * Converts character to an uppercase representation.
 * @param self Object to make a conversion against.
 * @return Uppercase representation of a character.
 */
char the_char_upper (char self);

#endif
