/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_SAFE_H
#define THE_SAFE_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <stddef.h>

/**
 * todo.
 * @param size How many bytes to allocate
 * @return todo
 */
void *the_safe_alloc (size_t size);

/** todo */
void *the_safe_realloc (void *self, size_t size);

/** todo */
void the_safe_swap (void *a, void *b, size_t size);

#endif
