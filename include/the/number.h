/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_NUMBER_H
#define THE_NUMBER_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/string-type.h>
#include <stddef.h>
#include <stdint.h>

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
the_str_t the_f32_str (float self);

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
the_str_t the_f64_str (double self);

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
the_str_t the_float_str (double self);

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
the_str_t the_i8_str (int8_t self);

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
the_str_t the_i16_str (int16_t self);

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
the_str_t the_i32_str (int32_t self);

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
the_str_t the_i64_str (int64_t self);

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
the_str_t the_int_str (int32_t self);

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
the_str_t the_isize_str (ptrdiff_t self);

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
the_str_t the_u8_str (uint8_t self);

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
the_str_t the_u16_str (uint16_t self);

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
the_str_t the_u32_str (uint32_t self);

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
the_str_t the_u64_str (uint64_t self);

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
the_str_t the_usize_str (size_t self);

#endif
