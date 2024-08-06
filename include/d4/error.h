/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_ERROR_H
#define D4_ERROR_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include <d4/error-type.h>
#include <errno.h>

/** Type id representing generic error. */
#define TYPE_Error 0

/** Global error state accessible by all threads. */
extern d4_err_state_t d4_err_state;

/**
 * Populates all required fields on error state from specified information.
 * @param state Error state to perform action on.
 * @param line Line where error appeared.
 * @param col Line column where error appeared.
 * @param id Type of the error.
 * @param ctx Context of the error.
 * @param free_cb Callback that is being called to deallocate the error object.
 */
void d4_error_assign (d4_err_state_t *state, int line, int col, int id, void *ctx, d4_err_state_free_cb free_cb);

/**
 * Populates all required fields as generic error on error state from specified information.
 * @param state Error state to perform action on.
 * @param line Line where error appeared.
 * @param col Line column where error appeared.
 * @param message Message of the generic error.
 */
void d4_error_assign_generic (d4_err_state_t *state, int line, int col, d4_str_t message);

/**
 * Decreases error state buffer by one.
 * @param state Error state to perform action on.
 */
void d4_error_buf_decrease (d4_err_state_t *state);

/**
 * Increases error state buffer by one.
 * @param state Error state to perform action on.
 */
d4_err_buf_t *d4_error_buf_increase (d4_err_state_t *state);

/**
 * Removes last item from error state stack.
 * @param state Error state to perform action on.
 */
void d4_error_stack_pop (d4_err_state_t *state);

/**
 * Inserts new item to error state stack.
 * @param state Error state to perform action on.
 * @param file File of the error.
 * @param name Name of function where error happened.
 * @param line Line of the error.
 * @param col Line column of the error.
 */
void d4_error_stack_push (d4_err_state_t *state, const wchar_t *file, const wchar_t *name, int line, int col);

/**
 * Unsets previously set error on the error state.
 * @param state Error state to perform action on.
 */
void d4_error_unset (d4_err_state_t *state);

/**
 * Allocates error object.
 * @param message Message of the error object.
 */
d4_Error_t *d4_Error_alloc (d4_str_t message);

/**
 * Deallocates error object.
 * @param self Pointer to an error object to deallocate.
 */
void d4_Error_free (void *self);

#endif
