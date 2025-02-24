/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef SRC_ERROR_H
#define SRC_ERROR_H

#include "../include/d4/macro.h"
#include "../include/d4/error.h"

/**
 * Instantly reports error and quits the application. Used internally by safe_alloc, safe_realloc functions.
 * @param state Error state to generate stack from.
 * @param size Size that safe function failed to allocate.
 */
D4_NORETURN void d4_error_alloc (d4_err_state_t *state, size_t size);

/**
 * Populates stack field on the error state context from error state.
 * @param state Error state to perform action on.
 * @param err Error string to insert data into.
 * @param max_len Maximum length of string or zero if it should be allocated instead.
 */
void d4_error_stack_str (d4_err_state_t *state, d4_str_t *err, size_t max_len);

#endif
