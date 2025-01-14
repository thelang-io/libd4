/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "../src/error.h"
#include <stdio.h>

#define ASSERT_NO_THROW(error_id, block) \
  do { \
    d4_Error_t *error; \
    d4_error_stack_push(&d4_err_state, L"test.c", L"main", 0, 0); \
    if (setjmp(d4_error_buf_increase(&d4_err_state)->buf) != 0) goto L##error_id; \
    block \
L##error_id: \
    d4_error_buf_decrease(&d4_err_state); \
    d4_error_stack_pop(&d4_err_state); \
    if (d4_err_state.id == -1) continue; \
    error = d4_err_state.ctx; \
    fprintf(stderr, "%ls\n", error->message.data); \
    assert(((void) "Throws no errors", d4_err_state.id == -1)); \
  } while (0)

#define ASSERT_THROW_WITH_MESSAGE(error_id, block, err) \
  do { \
    d4_Error_t *error; \
    d4_error_stack_push(&d4_err_state, L"test.c", L"main", 0, 0); \
    if (setjmp(d4_error_buf_increase(&d4_err_state)->buf) != 0) goto L##error_id; \
    block \
L##error_id: \
    d4_error_buf_decrease(&d4_err_state); \
    d4_error_stack_pop(&d4_err_state); \
    assert(((void) "Throws error", d4_err_state.id != -1)); \
    error = d4_err_state.ctx; \
    assert(((void) "Error message matches", wcscmp(err, error->message.data) == 0)); \
    d4_err_state.free_cb(d4_err_state.ctx); \
    d4_error_unset(&d4_err_state); \
  } while (0)

d4_str_t read_unicode_file (const char *path);

#endif
