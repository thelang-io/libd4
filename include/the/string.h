/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_STRING_H
#define THE_STRING_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/error-type.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/** Structure representing array of string objects. */
typedef struct {
  /** Pointer to a first element of the array object. */
  the_str_t *data;

  /** Length of array object. */
  size_t len;
} the_arr_str_t;

/**
 * Allocates string with format specifiers (similar to printf).
 * @param fmt String that contains text with format specifiers.
 * @return Newly allocated string.
 */
the_str_t the_str_alloc (const wchar_t *fmt, ...);

/**
 * Allocates string from C string of specified size.
 * @param self String to copy data from.
 * @param size Size that needs to be copied from self string.
 * @return Newly allocated string.
 */
the_str_t the_str_calloc (const wchar_t *self, size_t size);

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

/** todo */
the_str_t the_str_escape (const the_str_t self);

/** todo */
int32_t the_str_find (const the_str_t self, const the_str_t search);

/** todo */
void the_str_free (the_str_t self);

/** todo */
bool the_str_ge (const the_str_t self, const the_str_t rhs);

/** todo */
bool the_str_gt (const the_str_t self, const the_str_t rhs);

/** todo */
bool the_str_le (const the_str_t self, const the_str_t rhs);

/** todo */
bool the_str_lt (const the_str_t self, const the_str_t rhs);

/** todo */
bool the_str_ne (const the_str_t self, const the_str_t rhs);

/** todo */
the_str_t the_str_realloc (the_str_t self, const the_str_t rhs);

/** todo */
the_arr_str_t the_str_lines (const the_str_t self, unsigned char o1, bool keepLineBreaks);

/** todo */
the_str_t the_str_lower (const the_str_t self);

/** todo */
the_str_t the_str_lowerFirst (const the_str_t self);

/** todo */
bool the_str_not (const the_str_t self);

/** todo */
the_str_t the_str_replace (const the_str_t self, const the_str_t search, const the_str_t replacement, unsigned char o3, int32_t count);

/** todo */
the_str_t the_str_slice (const the_str_t self, unsigned char o1, int32_t start, unsigned char o2, int32_t end);

/** todo */
the_arr_str_t the_str_split (const the_str_t self, unsigned char o1, const the_str_t delimiter);

/** todo */
double the_str_toFloat (the_err_state_t *state, int line, int col, const the_str_t self);

/** todo */
float the_str_toF32 (the_err_state_t *state, int line, int col, const the_str_t self);

/** todo */
double the_str_toF64 (the_err_state_t *state, int line, int col, const the_str_t self);

/** todo */
ptrdiff_t the_str_toIsize (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix);

/** todo */
int8_t the_str_toI8 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix);

/** todo */
int16_t the_str_toI16 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix);

/** todo */
int32_t the_str_toI32 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix);

/** todo */
int64_t the_str_toI64 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix);

/** todo */
size_t the_str_toUsize (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix);

/** todo */
uint8_t the_str_toU8 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix);

/** todo */
uint16_t the_str_toU16 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix);

/** todo */
uint32_t the_str_toU32 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix);

/** todo */
uint64_t the_str_toU64 (the_err_state_t *state, int line, int col, const the_str_t self, unsigned char o1, int32_t radix);

/** todo */
the_str_t the_str_trim (const the_str_t self);

/** todo */
the_str_t the_str_trimEnd (const the_str_t self);

/** todo */
the_str_t the_str_trimStart (const the_str_t self);

/** todo */
the_str_t the_str_upper (const the_str_t self);

/** todo */
the_str_t the_str_upperFirst (const the_str_t self);

#endif
