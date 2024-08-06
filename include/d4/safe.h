/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_SAFE_H
#define D4_SAFE_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include <stddef.h>

/**
 * Safely allocates X amount of bytes. Sets the error in case allocation fails.
 * @param size Amount of bytes to allocate.
 * @return Pointer to address in memory where allocated bytes reside.
 */
void *d4_safe_alloc (size_t size);

/**
 * Safely allocates X amount of bytes and copies pointer. Sets the error in case allocation fails.
 * @param ptr Amount of bytes to allocate.
 * @param size Size of the pointer.
 * @return Pointer to address in memory where allocated bytes reside.
 */
void *d4_safe_calloc (const void *ptr, size_t size);

/**
 * Safely deallocates pointer.
 * @param self Pointer to deallocate.
 */
void d4_safe_free (void *self);

/**
 * Safely reallocates pointer with X amount of bytes. Sets the error in case reallocation fails.
 * @param self Pointer to reallocate.
 * @param size Amount of bytes to reallocate.
 * @return Pointer to address in memory where reallocated bytes reside.
 */
void *d4_safe_realloc (void *self, size_t size);

/**
 * Safely swaps two pointers.
 * @param a First pointer to make a swap for.
 * @param b Second pointer to make a swap for.
 * @param size Size of pointer `a`. Both pointers `a` and `b` should have same size.
 */
void d4_safe_swap (void *a, void *b, size_t size);

#endif
