/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_ENUM_H
#define THE_ENUM_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/string-type.h>

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
the_str_t the_enum_str (int self);

#endif
