/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "error.h"
#include <d4/safe.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

d4_err_state_t d4_err_state = {-1, NULL, NULL, NULL, NULL, NULL, NULL};

// LCOV_EXCL_START
void d4_error_alloc (d4_err_state_t *state, size_t size) {
  wchar_t d[4096];
  d4_str_t stack = (d4_str_t) {d, sizeof(d) / sizeof(d[0]), true};
  d4_error_stack_str(state, &stack, stack.len);
  fwprintf(stderr, L"Allocation Error: failed to allocate %zu bytes%s" D4_EOL, size, d);
  exit(EXIT_FAILURE);
}
// LCOV_EXCL_STOP

void d4_error_assign (d4_err_state_t *state, int line, int col, int id, void *ctx, d4_err_state_free_cb free_cb) {
  d4_Error_t *err = (d4_Error_t *) ctx;

  state->id = id;
  state->ctx = ctx;
  state->free_cb = free_cb;
  if (line != 0) state->stack_last->line = line;
  if (col != 0) state->stack_last->col = col;

  err->stack = d4_str_realloc(err->stack, err->message);
  d4_error_stack_str(state, &err->stack, 0);
}

void d4_error_assign_generic (d4_err_state_t *state, int line, int col, d4_str_t message) {
  d4_error_assign(state, line, col, TYPE_Error, d4_Error_alloc(message), d4_Error_free);
}

void d4_error_buf_decrease (d4_err_state_t *state) {
  d4_err_buf_t *buf = state->buf_last;
  state->buf_last = buf->prev;

  if (state->buf_last == NULL) {
    state->buf_first = NULL;
  }

  d4_safe_free(buf);
}

d4_err_buf_t *d4_error_buf_increase (d4_err_state_t *state) {
  d4_err_buf_t *buf = d4_safe_alloc(sizeof(d4_err_buf_t));
  buf->next = NULL;
  buf->prev = state->buf_last;
  if (state->buf_first == NULL) state->buf_first = buf;
  if (state->buf_last != NULL) state->buf_last->next = buf;
  state->buf_last = buf;
  return state->buf_last;
}

void d4_error_stack_pop (d4_err_state_t *state) {
  d4_err_stack_t *stack = state->stack_last;
  bool was_last = state->stack_last == state->stack_first;

  state->stack_last = stack->prev;
  d4_safe_free(stack);

  if (was_last) {
    state->stack_first = NULL;
    state->stack_last = NULL;
  }
}

void d4_error_stack_push (d4_err_state_t *state, const wchar_t *file, const wchar_t *name, int line, int col) {
  d4_err_stack_t *stack;
  if (line != 0) state->stack_last->line = line;
  if (col != 0) state->stack_last->col = col;
  stack = d4_safe_alloc(sizeof(d4_err_stack_t));
  stack->file = file;
  stack->name = name;
  stack->line = 0;
  stack->col = 0;
  stack->next = NULL;
  stack->prev = state->stack_last;
  if (state->stack_first == NULL) state->stack_first = stack;
  if (state->stack_last != NULL) state->stack_last->next = stack;
  state->stack_last = stack;
}

void d4_error_stack_str (d4_err_state_t *state, d4_str_t *err, size_t max_len) {
  for (d4_err_stack_t *it = state->stack_last; it != NULL; it = it->prev) {
    wchar_t *fmt;
    size_t z;

    if (it->col == 0 && it->line == 0) {
      fmt = D4_EOL L"  at %ls (%ls)";
      z = (size_t) snwprintf(fmt, it->name, it->file);
    } else if (it->col == 0) {
      fmt = D4_EOL L"  at %ls (%ls:%d)";
      z = (size_t) snwprintf(fmt, it->name, it->file, it->line);
    } else {
      fmt = D4_EOL L"  at %ls (%ls:%d:%d)";
      z = (size_t) snwprintf(fmt, it->name, it->file, it->line, it->col);
    }

    if (max_len == 0) {
      err->data = d4_safe_realloc(err->data, (err->len + z + 1) * sizeof(wchar_t));
    } else if (err->len + z >= max_len) {
      break; // LCOV_EXCL_LINE
    }

    if (it->col == 0 && it->line == 0) {
      swprintf(&err->data[err->len], z + 1, fmt, it->name, it->file);
    } else if (it->col == 0) {
      swprintf(&err->data[err->len], z + 1, fmt, it->name, it->file, it->line);
    } else {
      swprintf(&err->data[err->len], z + 1, fmt, it->name, it->file, it->line, it->col);
    }

    err->len += z;
  }
}

void d4_error_unset (d4_err_state_t *state) {
  state->id = -1;
  state->free_cb = NULL;
}

d4_Error_t *d4_Error_alloc (d4_str_t message) {
  d4_Error_t *err = d4_safe_alloc(sizeof(d4_Error_t));
  err->message = d4_str_copy(message);
  err->stack = d4_str_empty_val;
  return err;
}

void d4_Error_free (void *self) {
  d4_Error_t *err = self;
  d4_str_free(err->message);
  d4_str_free(err->stack);
  d4_safe_free(self);
}
