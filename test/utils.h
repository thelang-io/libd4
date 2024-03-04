/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "../src/error.h"

#define ASSERT_NO_THROW(errorId, block) \
  do { \
    the_error_stack_push(&the_err_state, L"test.c", L"main", 0, 0); \
    if (setjmp(the_error_buf_increase(&the_err_state)->buf) != 0) goto L##errorId; \
    block \
L##errorId: \
    the_error_stack_pop(&the_err_state); \
    assert(((void) "Throws no errors", the_err_state.id == -1)); \
  } while (0)

#define ASSERT_THROW_WITH_MESSAGE(errorId, block, err) \
  do { \
    the_Error_t *error; \
    the_error_stack_push(&the_err_state, L"test.c", L"main", 0, 0); \
    if (setjmp(the_error_buf_increase(&the_err_state)->buf) != 0) goto L##errorId; \
    block \
L##errorId: \
    the_error_stack_pop(&the_err_state); \
    assert(((void) "Throws error", the_err_state.id != -1)); \
    error = the_err_state.ctx; \
    assert(((void) "Error message matches", wcscmp(err, error->message.data) == 0)); \
    the_err_state.free_cb(the_err_state.ctx); \
    the_error_unset(&the_err_state); \
  } while (0)

#endif
