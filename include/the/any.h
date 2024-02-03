/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_ANY_H
#define THE_ANY_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/string-type.h>
#include <stdbool.h>

/** Structure representing any object. */
typedef struct the_any_s the_any_t;

/** todo */
the_any_t the_any_copy (const the_any_t self);

/** todo */
bool the_any_eq (const the_any_t self, const the_any_t rhs);

/** todo */
void the_any_free (the_any_t self);

/** todo */
bool the_any_ne (const the_any_t self, const the_any_t rhs);

/** todo */
the_any_t the_any_realloc (the_any_t self, const the_any_t n);

/** todo */
the_str_t the_any_str (const the_any_t self);

#endif
