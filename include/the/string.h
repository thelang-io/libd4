/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_STRING_H
#define THE_STRING_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/array-macro.h>

THE_ARRAY_DECLARE(str, the_str_t)

/** Empty value that can be used when you need to initialize a string. */
extern the_str_t empty_str_value;

/**
 * Allocates string with format specifiers (similar to printf).
 * @param fmt String that contains text with format specifiers.
 * @return Newly allocated string.
 */
the_str_t the_str_alloc (const wchar_t *fmt, ...);

/**
 * Allocates string from C string of specified size.
 * @param self String to copy data from.
 * @param length Length of string that needs to be copied from self string.
 * @return Newly allocated string.
 */
the_str_t the_str_calloc (const wchar_t *self, size_t length);

/**
 * Returns a wide character at specified position in string otherwise throws error if index more than string length.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self The string to find a character in.
 * @param index Character position to search for.
 * @return Found wide character in a specified string.
 */
wchar_t *the_str_at (the_err_state_t *state, int line, int col, const the_str_t self, int32_t index);

/**
 * Concatenates two string into one.
 * @param self First string for concatenation.
 * @param other Second string for concatenation.
 * @return Resulting string of concatenation.
 */
the_str_t the_str_concat (const the_str_t self, const the_str_t other);

/**
 * Checks whether string contains search substring.
 * @param self String to check in contains substring.
 * @param search Substring to search for.
 * @return Whether string contains search substring.
 */
bool the_str_contains (const the_str_t self, const the_str_t search);

/**
 * Creates deep copy of the string.
 * @param self String to create copy of.
 * @return Deep copy of the string.
 */
the_str_t the_str_copy (const the_str_t self);

/**
 * Checks whether string is empty.
 * @param self String to check.
 * @return Whether string is empty.
 */
bool the_str_empty (const the_str_t self);

/**
 * Checks whether string is equal to other string.
 * @param self String to check.
 * @param rhs Other string to check.
 * @return Whether string is equal to other string.
 */
bool the_str_eq (const the_str_t self, const the_str_t rhs);

/**
 * Escapes all escapable characters in a string.
 * @param self String to escape.
 * @return Newly created string with escape characters escaped.
 */
the_str_t the_str_escape (const the_str_t self);

/**
 * Finds substring in a string.
 * @param self String to search in.
 * @param search String to search for.
 * @return Position of found string, -1 otherwise.
 */
int32_t the_str_find (const the_str_t self, const the_str_t search);

/**
 * Deallocates string.
 * @param self String to deallocate.
 */
void the_str_free (the_str_t self);

/**
 * Checks whether string is greater than or equal to right-hand string.
 * @param self String to compare.
 * @param rhs String to compare.
 * @return Whether string is greater or equal than right-hand string.
 */
bool the_str_ge (const the_str_t self, const the_str_t rhs);

/**
 * Checks whether string is greater than right-hand string.
 * @param self String to compare.
 * @param rhs String to compare.
 * @return Whether string is greater than right-hand string.
 */
bool the_str_gt (const the_str_t self, const the_str_t rhs);

/**
 * Checks whether string is less than or equal to right-hand string.
 * @param self String to compare.
 * @param rhs String to compare.
 * @return Whether string is less than or equal to right-hand string.
 */
bool the_str_le (const the_str_t self, const the_str_t rhs);

/**
 * Splits string by new line into array of strings.
 * @param self String to split into lines.
 * @param o1 Whether or not `keepLineBreaks` parameter is specified.
 * @param keepLineBreaks Whether to keep line breaks in resulting array.
 * @return Split by new line array of strings.
 */
the_arr_str_t the_str_lines (const the_str_t self, unsigned char o1, bool keepLineBreaks);

/**
 * Creates and returns representation of the string in lowercase.
 * @param self String to create representation for.
 * @return Representation of the string in lowercase.
 */
the_str_t the_str_lower (const the_str_t self);

/**
 * Creates and returns representation of the string with only first letter in lowercase.
 * @param self String to create representation for.
 * @return Representation of the string with only first letter in lowercase.
 */
the_str_t the_str_lowerFirst (const the_str_t self);

/**
 * Checks whether string is less than right-hand string.
 * @param self String to compare.
 * @param rhs String to compare.
 * @return Whether string is less than right-hand string.
 */
bool the_str_lt (const the_str_t self, const the_str_t rhs);

/**
 * Checks whether string is not empty.
 * @param self String to check.
 * @return Whether string is not empty.
 */
bool the_str_not (const the_str_t self);

/**
 * Reallocates string with right-hand string data.
 * @param self String to deallocate.
 * @param rhs String where to copy data from.
 * @return Newly reallocated string.
 */
the_str_t the_str_realloc (the_str_t self, const the_str_t rhs);

/**
 * Replaces search pattern with replacement in string provided.
 * @param self String to replace in.
 * @param search String to search for.
 * @param replacement String to replace with.
 * @param o3 Whether or not `count` parameter is specified.
 * @param count How many occurrences to replace. If less than or equal to zero - then it will act as if parameter was not passed.
 * @return String with replaced search pattern.
 */
the_str_t the_str_replace (const the_str_t self, const the_str_t search, const the_str_t replacement, unsigned char o3, int32_t count);

/**
 * Creates and returns slice of the string.
 * @param self String to take slice of.
 * @param o1 Whether or not `start` parameter is specified.
 * @param start Start of the slice.
 * @param o2 Whether or not `end` parameter is specified.
 * @param end End of the slice.
 * @return Slice of the string provided.
 */
the_str_t the_str_slice (const the_str_t self, unsigned char o1, int32_t start, unsigned char o2, int32_t end);

/**
 * Splits string into array of string by provided delimiter.
 * @param self String to take slice of.
 * @param o1 Whether or not `start` parameter is specified.
 * @param start Start of the slice.
 * @param o2 Whether or not `end` parameter is specified.
 * @param end End of the slice.
 * @return String split into array of string.
 */
the_arr_str_t the_str_split (const the_str_t self, unsigned char o1, const the_str_t delimiter);

/**
 * Converts string into float representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @return Float representation of the string.
 */
double the_str_toFloat (the_err_state_t *state, int line, int col, const the_str_t self);

/**
 * Converts string into f32 representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @return F32 representation of the string.
 */
float the_str_toF32 (the_err_state_t *state, int line, int col, const the_str_t self);

/**
 * Converts string into f64 representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @return F64 representation of the string.
 */
double the_str_toF64 (the_err_state_t *state, int line, int col, const the_str_t self);

/**
 * Converts string into isize representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @param radix Base in mathematical numeral systems of the string. Integer between 2 and 36.
 * @return Isize representation of the string.
 */
ptrdiff_t the_str_toIsize (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix);

/**
 * Converts string into i8 representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @param radix Base in mathematical numeral systems of the string. Integer between 2 and 36.
 * @return I8 representation of the string.
 */
int8_t the_str_toI8 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix);

/**
 * Converts string into i16 representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @param radix Base in mathematical numeral systems of the string. Integer between 2 and 36.
 * @return I16 representation of the string.
 */
int16_t the_str_toI16 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix);

/**
 * Converts string into i32 representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @param radix Base in mathematical numeral systems of the string. Integer between 2 and 36.
 * @return I32 representation of the string.
 */
int32_t the_str_toI32 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix);

/**
 * Converts string into i64 representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @param radix Base in mathematical numeral systems of the string. Integer between 2 and 36.
 * @return I64 representation of the string.
 */
int64_t the_str_toI64 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix);

/**
 * Converts string into usize representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @param radix Base in mathematical numeral systems of the string. Integer between 2 and 36.
 * @return Usize representation of the string.
 */
size_t the_str_toUsize (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix);

/**
 * Converts string into u8 representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @param radix Base in mathematical numeral systems of the string. Integer between 2 and 36.
 * @return U8 representation of the string.
 */
uint8_t the_str_toU8 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix);

/**
 * Converts string into u16 representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @param radix Base in mathematical numeral systems of the string. Integer between 2 and 36.
 * @return U16 representation of the string.
 */
uint16_t the_str_toU16 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix);

/**
 * Converts string into u32 representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @param radix Base in mathematical numeral systems of the string. Integer between 2 and 36.
 * @return U32 representation of the string.
 */
uint32_t the_str_toU32 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix);

/**
 * Converts string into u64 representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @param radix Base in mathematical numeral systems of the string. Integer between 2 and 36.
 * @return U64 representation of the string.
 */
uint64_t the_str_toU64 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix);

/**
 * Creates and returns string with whitespaces removed from both ends of the string provided.
 * @param self String to remove whitespace from.
 * @return String created in result of removing whitespaces.
 */
the_str_t the_str_trim (const the_str_t self);

/**
 * Creates and returns string with whitespaces removed from the end of the string provided.
 * @param self String to remove whitespace from.
 * @return String created in result of removing whitespaces.
 */
the_str_t the_str_trimEnd (const the_str_t self);

/**
 * Creates and returns string with whitespaces removed from the beginning of the string provided.
 * @param self String to remove whitespace from.
 * @return String created in result of removing whitespaces.
 */
the_str_t the_str_trimStart (const the_str_t self);

/**
 * Creates and returns representation of the string in uppercase.
 * @param self String to create representation for.
 * @return Representation of the string in uppercase.
 */
the_str_t the_str_upper (const the_str_t self);

/**
 * Creates and returns representation of the string with only first letter in uppercase.
 * @param self String to create representation for.
 * @return Representation of the string with only first letter in uppercase.
 */
the_str_t the_str_upperFirst (const the_str_t self);

#endif
