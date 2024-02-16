/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef SRC_ERROR_H
#define SRC_ERROR_H

#include <the/error.h>

/**
 * Instantly reports error and exists the application. Used internally by safe_alloc, safe_realloc functions.
 * @param state Error state to generate stack from.
 * @param size Size that safe function failed to allocate.
 */
THE_NORETURN void the_error_alloc (const the_err_state_t *state, size_t size);

/**
 * Populates stack field on the error state context from error state.
 * @param state Error state to perform action on.
 */
void the_error_stack_str (the_err_state_t *state);

#endif
