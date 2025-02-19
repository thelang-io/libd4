/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_STRING_H
#define D4_STRING_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include "array-macro.h"

D4_ARRAY_DECLARE(str, d4_str_t)

/** Empty value that can be used when you need to initialize a string. */
extern d4_str_t d4_str_empty_val;

/**
 * Allocates string with format specifiers (similar to printf).
 * @param fmt String that contains text with format specifiers.
 * @param ... Arguments corresponding to the format specifiers.
 * @return Newly allocated string.
 */
d4_str_t d4_str_alloc (const wchar_t *fmt, ...);

/**
 * Allocates string from C string of specified size.
 * @param self String to copy data from.
 * @param length Length of string that needs to be copied from self string.
 * @return Newly allocated string.
 */
d4_str_t d4_str_calloc (const wchar_t *self, size_t length);

/**
 * Returns a wide character at specified position in string otherwise throws error if index more than string length.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self The string to find a character in.
 * @param index Character position to search for.
 * @return Found wide character in a specified string.
 */
wchar_t *d4_str_at (d4_err_state_t *state, int line, int col, const d4_str_t self, int32_t index);

/**
 * Concatenates two string into one.
 * @param self First string for concatenation.
 * @param other Second string for concatenation.
 * @return Resulting string of concatenation.
 */
d4_str_t d4_str_concat (const d4_str_t self, const d4_str_t other);

/**
 * Checks whether string contains search substring.
 * @param self String to check in contains substring.
 * @param search Substring to search for.
 * @return Whether string contains search substring.
 */
bool d4_str_contains (const d4_str_t self, const d4_str_t search);

/**
 * Creates deep copy of the string.
 * @param self String to create copy of.
 * @return Deep copy of the string.
 */
d4_str_t d4_str_copy (const d4_str_t self);

/**
 * Checks whether string is empty.
 * @param self String to check.
 * @return Whether string is empty.
 */
bool d4_str_empty (const d4_str_t self);

/**
 * Checks whether string ends with provided substring.
 * @param self String to check.
 * @param search Substring to search for.
 * @return Whether string ends with provided substring.
 */
bool d4_str_endsWith (const d4_str_t self, const d4_str_t search);

/**
 * Checks whether string is equal to other string.
 * @param self String to check.
 * @param rhs Other string to check.
 * @return Whether string is equal to other string.
 */
bool d4_str_eq (const d4_str_t self, const d4_str_t rhs);

/**
 * Escapes all escapable characters in a string.
 * @param self String to escape.
 * @return Newly created string with escape characters escaped.
 */
d4_str_t d4_str_escape (const d4_str_t self);

/**
 * Finds substring in a string.
 * @param self String to search in.
 * @param search String to search for.
 * @return Position of found string, -1 otherwise.
 */
int32_t d4_str_find (const d4_str_t self, const d4_str_t search);

/**
 * Deallocates string.
 * @param self String to deallocate.
 */
void d4_str_free (d4_str_t self);

/**
 * Checks whether string is greater than or equal to right-hand string.
 * @param self String to compare.
 * @param rhs String to compare.
 * @return Whether string is greater or equal than right-hand string.
 */
bool d4_str_ge (const d4_str_t self, const d4_str_t rhs);

/**
 * Checks whether string is greater than right-hand string.
 * @param self String to compare.
 * @param rhs String to compare.
 * @return Whether string is greater than right-hand string.
 */
bool d4_str_gt (const d4_str_t self, const d4_str_t rhs);

/**
 * Checks whether string is less than or equal to right-hand string.
 * @param self String to compare.
 * @param rhs String to compare.
 * @return Whether string is less than or equal to right-hand string.
 */
bool d4_str_le (const d4_str_t self, const d4_str_t rhs);

/**
 * Splits string by new line into array of strings.
 * @param self String to split into lines.
 * @param o1 Whether `keepLineBreaks` parameter is specified.
 * @param keepLineBreaks Whether to keep line breaks in resulting array.
 * @return Split by new line array of strings.
 */
d4_arr_str_t d4_str_lines (const d4_str_t self, unsigned char o1, bool keepLineBreaks);

/**
 * Creates and returns representation of the string in lowercase.
 * @param self String to create representation for.
 * @return Representation of the string in lowercase.
 */
d4_str_t d4_str_lower (const d4_str_t self);

/**
 * Creates and returns representation of the string with only first letter in lowercase.
 * @param self String to create representation for.
 * @return Representation of the string with only first letter in lowercase.
 */
d4_str_t d4_str_lowerFirst (const d4_str_t self);

/**
 * Checks whether string is less than right-hand string.
 * @param self String to compare.
 * @param rhs String to compare.
 * @return Whether string is less than right-hand string.
 */
bool d4_str_lt (const d4_str_t self, const d4_str_t rhs);

/**
 * Checks whether string is not empty.
 * @param self String to check.
 * @return Whether string is not empty.
 */
bool d4_str_not (const d4_str_t self);

/**
 * Puts string into double quotes and escapes characters inside of it.
 * @param self String to quote.
 * @return Quoted string.
 */
d4_str_t d4_str_quoted_escape (d4_str_t self);

/**
 * Reallocates string with right-hand string data.
 * @param self String to deallocate.
 * @param rhs String where to copy data from.
 * @return Newly reallocated string.
 */
d4_str_t d4_str_realloc (d4_str_t self, const d4_str_t rhs);

/**
 * Replaces search pattern with replacement in string provided.
 * @param self String to replace in.
 * @param search String to search for.
 * @param replacement String to replace with.
 * @param o3 Whether `count` parameter is specified.
 * @param count How many occurrences to replace. If less than or equal to zero - then it will act as if parameter was not passed.
 * @return String with replaced search pattern.
 */
d4_str_t d4_str_replace (const d4_str_t self, const d4_str_t search, const d4_str_t replacement, unsigned char o3, int32_t count);

/**
 * Creates and returns slice of the string.
 * @param self String to take slice of.
 * @param o1 Whether `start` parameter is specified.
 * @param start Start of the slice.
 * @param o2 Whether `end` parameter is specified.
 * @param end End of the slice.
 * @return Slice of the string provided.
 */
d4_str_t d4_str_slice (const d4_str_t self, unsigned char o1, int32_t start, unsigned char o2, int32_t end);

/**
 * Splits string into array of string by provided delimiter.
 * @param self String to take slice of.
 * @param o1 Whether `delimiter` parameter is specified.
 * @param delimiter Delimiter substring to split string by.
 * @return String split into array of string.
 */
d4_arr_str_t d4_str_split (const d4_str_t self, unsigned char o1, const d4_str_t delimiter);

/**
 * Checks whether string starts with provided substring.
 * @param self String to check.
 * @param search Substring to search for.
 * @return Whether string starts with provided substring.
 */
bool d4_str_startsWith (const d4_str_t self, const d4_str_t search);

/**
 * Converts string into float representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @return Float representation of the string.
 */
double d4_str_toFloat (d4_err_state_t *state, int line, int col, const d4_str_t self);

/**
 * Converts string into f32 representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @return F32 representation of the string.
 */
float d4_str_toF32 (d4_err_state_t *state, int line, int col, const d4_str_t self);

/**
 * Converts string into f64 representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @return F64 representation of the string.
 */
double d4_str_toF64 (d4_err_state_t *state, int line, int col, const d4_str_t self);

/**
 * Converts string into isize representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @param o1 Whether radix parameter is present.
 * @param radix Base in mathematical numeral systems of the string. Integer between 2 and 36.
 * @return Isize representation of the string.
 */
ptrdiff_t d4_str_toIsize (d4_err_state_t *state, int line, int col, const d4_str_t self, unsigned char o1, int32_t radix);

/**
 * Converts string into i8 representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @param o1 Whether radix parameter is present.
 * @param radix Base in mathematical numeral systems of the string. Integer between 2 and 36.
 * @return I8 representation of the string.
 */
int8_t d4_str_toI8 (d4_err_state_t *state, int line, int col, const d4_str_t self, unsigned char o1, int32_t radix);

/**
 * Converts string into i16 representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @param o1 Whether radix parameter is present.
 * @param radix Base in mathematical numeral systems of the string. Integer between 2 and 36.
 * @return I16 representation of the string.
 */
int16_t d4_str_toI16 (d4_err_state_t *state, int line, int col, const d4_str_t self, unsigned char o1, int32_t radix);

/**
 * Converts string into i32 representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @param o1 Whether radix parameter is present.
 * @param radix Base in mathematical numeral systems of the string. Integer between 2 and 36.
 * @return I32 representation of the string.
 */
int32_t d4_str_toI32 (d4_err_state_t *state, int line, int col, const d4_str_t self, unsigned char o1, int32_t radix);

/**
 * Converts string into i64 representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @param o1 Whether radix parameter is present.
 * @param radix Base in mathematical numeral systems of the string. Integer between 2 and 36.
 * @return I64 representation of the string.
 */
int64_t d4_str_toI64 (d4_err_state_t *state, int line, int col, const d4_str_t self, unsigned char o1, int32_t radix);

/**
 * Converts string into usize representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @param o1 Whether radix parameter is present.
 * @param radix Base in mathematical numeral systems of the string. Integer between 2 and 36.
 * @return Usize representation of the string.
 */
size_t d4_str_toUsize (d4_err_state_t *state, int line, int col, const d4_str_t self, unsigned char o1, int32_t radix);

/**
 * Converts string into u8 representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @param o1 Whether radix parameter is present.
 * @param radix Base in mathematical numeral systems of the string. Integer between 2 and 36.
 * @return U8 representation of the string.
 */
uint8_t d4_str_toU8 (d4_err_state_t *state, int line, int col, const d4_str_t self, unsigned char o1, int32_t radix);

/**
 * Converts string into u16 representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @param o1 Whether radix parameter is present.
 * @param radix Base in mathematical numeral systems of the string. Integer between 2 and 36.
 * @return U16 representation of the string.
 */
uint16_t d4_str_toU16 (d4_err_state_t *state, int line, int col, const d4_str_t self, unsigned char o1, int32_t radix);

/**
 * Converts string into u32 representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @param o1 Whether radix parameter is present.
 * @param radix Base in mathematical numeral systems of the string. Integer between 2 and 36.
 * @return U32 representation of the string.
 */
uint32_t d4_str_toU32 (d4_err_state_t *state, int line, int col, const d4_str_t self, unsigned char o1, int32_t radix);

/**
 * Converts string into u64 representation.
 * @param state Error state to assign error to.
 * @param line Source line number.
 * @param col Source line column.
 * @param self String to convert.
 * @param o1 Whether radix parameter is present.
 * @param radix Base in mathematical numeral systems of the string. Integer between 2 and 36.
 * @return U64 representation of the string.
 */
uint64_t d4_str_toU64 (d4_err_state_t *state, int line, int col, const d4_str_t self, unsigned char o1, int32_t radix);

/**
 * Creates and returns string with whitespaces removed from both ends of the string provided.
 * @param self String to remove whitespace from.
 * @return String created in result of removing whitespaces.
 */
d4_str_t d4_str_trim (const d4_str_t self);

/**
 * Creates and returns string with whitespaces removed from the end of the string provided.
 * @param self String to remove whitespace from.
 * @return String created in result of removing whitespaces.
 */
d4_str_t d4_str_trimEnd (const d4_str_t self);

/**
 * Creates and returns string with whitespaces removed from the beginning of the string provided.
 * @param self String to remove whitespace from.
 * @return String created in result of removing whitespaces.
 */
d4_str_t d4_str_trimStart (const d4_str_t self);

/**
 * Creates and returns representation of the string in uppercase.
 * @param self String to create representation for.
 * @return Representation of the string in uppercase.
 */
d4_str_t d4_str_upper (const d4_str_t self);

/**
 * Creates and returns representation of the string with only first letter in uppercase.
 * @param self String to create representation for.
 * @return Representation of the string with only first letter in uppercase.
 */
d4_str_t d4_str_upperFirst (const d4_str_t self);

#endif
