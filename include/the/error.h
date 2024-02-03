/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_ERROR_H
#define THE_ERROR_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/error-type.h>
#include <the/string-type.h>
#include <wchar.h>

/** todo */
#define TYPE_Error 1

/** todo */
extern the_err_state_t the_err_state;

/** todo */
__attribute__((noreturn)) void the_error_alloc (const the_err_state_t *state, size_t size);

/** todo */
void the_error_assign (the_err_state_t *state, int line, int col, int id, void *ctx, void (*free) (void *));

/** todo */
void the_error_assign_builtin (the_err_state_t *state, int line, int col, the_str_t message);

/** todo */
void the_error_buf_decrease (the_err_state_t *state);

/** todo */
the_err_buf_t *the_error_buf_increase (the_err_state_t *state);

/** todo */
void the_error_stack_pop (the_err_state_t *state);

/** todo */
void the_error_stack_pos (the_err_state_t *state, int line, int col);

/** todo */
void the_error_stack_push (the_err_state_t *state, const wchar_t *file, const wchar_t *name, int line, int col);

/** todo */
void the_error_stack_str (the_err_state_t *state);

/** todo */
void the_error_unset (the_err_state_t *state);

/** todo */
the_Error_t *the_Error_alloc (the_str_t message);

/** todo */
void the_Error_free (void *self);

#endif
