/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef SRC_ERROR_H
#define SRC_ERROR_H

#include <the/error.h>
#include <the/macro.h>

/**
 * Instantly reports error and quits the application. Used internally by safe_alloc, safe_realloc functions.
 * @param state Error state to generate stack from.
 * @param size Size that safe function failed to allocate.
 */
THE_NORETURN void the_error_alloc (the_err_state_t *state, size_t size);

/**
 * Populates stack field on the error state context from error state.
 * @param state Error state to perform action on.
 * @param err Error string to insert data into.
 * @param max_len Maximum length of string or zero if it should be allocated instead.
 */
void the_error_stack_str (the_err_state_t *state, the_str_t *err, size_t max_len);

#endif
