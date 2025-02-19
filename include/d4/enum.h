/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_ENUM_H
#define D4_ENUM_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include "string-type.h"

/**
 * Generates string representation of the object.
 * @param self Object to generate string representation for.
 * @return String representation of the object.
 */
d4_str_t d4_enum_str (int self);

#endif
