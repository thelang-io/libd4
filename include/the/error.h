/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_ERROR_H
#define THE_ERROR_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/error-type.h>

/** Type id representing generic error. */
#define TYPE_Error 0

/** Global error state accessible by all threads. */
extern the_err_state_t the_err_state;

/**
 * Populates all required fields on error state from specified information.
 * @param state Error state to perform action on.
 * @param line Line where error appeared.
 * @param col Line column where error appeared.
 * @param id Type of the error.
 * @param ctx Context of the error.
 * @param free_cb Callback that is being called to deallocate the error object.
 */
void the_error_assign (the_err_state_t *state, int line, int col, int id, void *ctx, the_err_state_free_cb free_cb);

/**
 * Populates all required fields as generic error on error state from specified information.
 * @param state Error state to perform action on.
 * @param line Line where error appeared.
 * @param col Line column where error appeared.
 * @param message Message of the generic error.
 */
void the_error_assign_generic (the_err_state_t *state, int line, int col, the_str_t message);

/**
 * Decreases error state buffer by one.
 * @param state Error state to perform action on.
 */
void the_error_buf_decrease (the_err_state_t *state);

/**
 * Increases error state buffer by one.
 * @param state Error state to perform action on.
 */
the_err_buf_t *the_error_buf_increase (the_err_state_t *state);

/**
 * Removes last item from error state stack.
 * @param state Error state to perform action on.
 */
void the_error_stack_pop (the_err_state_t *state);

/**
 * Inserts new item to error state stack.
 * @param state Error state to perform action on.
 * @param file File of the error.
 * @param name Name of function where error happened.
 * @param line Line of the error.
 * @param col Line column of the error.
 */
void the_error_stack_push (the_err_state_t *state, const wchar_t *file, const wchar_t *name, int line, int col);

/**
 * Unsets previously set error on the error state.
 * @param state Error state to perform action on.
 */
void the_error_unset (the_err_state_t *state);

/**
 * Allocates error object.
 * @param message Message of the error object.
 */
the_Error_t *the_Error_alloc (the_str_t message);

/**
 * Deallocates error object.
 * @param self Pointer to an error object to deallocate.
 */
void the_Error_free (void *self);

#endif
