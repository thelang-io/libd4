/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "error.h"
#include <the/safe.h>
#include <the/string.h>
#include <stdlib.h>

the_err_state_t the_err_state = {-1, NULL, NULL, NULL, NULL, NULL, NULL};

void the_error_alloc (const the_err_state_t *state, size_t size) {
  wchar_t d[4096];
  size_t l = 0;

  for (the_err_stack_t *it = state->stack_last; it != NULL; it = it->prev) {
    wchar_t *fmt;
    size_t z;

    if (it->col == 0 && it->line == 0) {
      fmt = THE_EOL L"  at %s (%s)";
      z = (size_t) swprintf(NULL, 0, fmt, it->name, it->file);
    } else if (it->col == 0) {
      fmt = THE_EOL L"  at %s (%s:%d)";
      z = (size_t) swprintf(NULL, 0, fmt, it->name, it->file, it->line);
    } else {
      fmt = THE_EOL L"  at %s (%s:%d:%d)";
      z = (size_t) swprintf(NULL, 0, fmt, it->name, it->file, it->line, it->col);
    }

    if (l + z >= 4096) break;

    if (it->col == 0 && it->line == 0) {
      swprintf(&d[l], z, fmt, it->name, it->file);
    } else if (it->col == 0) {
      swprintf(&d[l], z, fmt, it->name, it->file, it->line);
    } else {
      swprintf(&d[l], z, fmt, it->name, it->file, it->line, it->col);
    }

    l += z;
  }

  fwprintf(stderr, L"Allocation Error: failed to allocate %zu bytes%s" THE_EOL, size, d);
  exit(EXIT_FAILURE);
}

void the_error_assign (the_err_state_t *state, int line, int col, int id, void *ctx, the_err_state_free_cb free_cb) {
  state->id = id;
  state->ctx = ctx;
  state->free_cb = free_cb;
  if (line != 0) state->stack_last->line = line;
  if (col != 0) state->stack_last->col = col;
  the_error_stack_str(state);
}

void the_error_assign_generic (the_err_state_t *state, int line, int col, the_str_t message) {
  the_error_assign(state, line, col, TYPE_Error, the_Error_alloc(message), the_Error_free);
}

void the_error_buf_decrease (the_err_state_t *state) {
  the_err_buf_t *buf = state->buf_last;
  state->buf_last = buf->prev;
  the_safe_free(buf);
}

the_err_buf_t *the_error_buf_increase (the_err_state_t *state) {
  the_err_buf_t *buf = the_safe_alloc(sizeof(the_err_buf_t));
  buf->next = NULL;
  buf->prev = state->buf_last;
  if (state->buf_first == NULL) state->buf_first = buf;
  if (state->buf_last != NULL) state->buf_last->next = buf;
  state->buf_last = buf;
  return state->buf_last;
}

void the_error_stack_pop (the_err_state_t *state) {
  the_err_stack_t *stack = state->stack_last;
  state->stack_last = stack->prev;
  the_safe_free(stack);
}

void the_error_stack_push (the_err_state_t *state, const wchar_t *file, const wchar_t *name, int line, int col) {
  the_err_stack_t *stack;
  if (line != 0) state->stack_last->line = line;
  if (col != 0) state->stack_last->col = col;
  stack = the_safe_alloc(sizeof(the_err_stack_t));
  stack->file = file;
  stack->name = name;
  stack->next = NULL;
  stack->prev = state->stack_last;
  if (state->stack_first == NULL) state->stack_first = stack;
  if (state->stack_last != NULL) state->stack_last->next = stack;
  state->stack_last = stack;
}

void the_error_stack_str (the_err_state_t *state) {
  the_Error_t *err = state->ctx;
  err->stack = the_str_realloc(err->stack, err->message);

  for (the_err_stack_t *it = state->stack_last; it != NULL; it = it->prev) {
    wchar_t *fmt;
    size_t z;

    if (it->col == 0 && it->line == 0) {
      fmt = THE_EOL L"  at %s (%s)";
      z = (size_t) swprintf(NULL, 0, fmt, it->name, it->file);
    } else if (it->col == 0) {
      fmt = THE_EOL L"  at %s (%s:%d)";
      z = (size_t) swprintf(NULL, 0, fmt, it->name, it->file, it->line);
    } else {
      fmt = THE_EOL L"  at %s (%s:%d:%d)";
      z = (size_t) swprintf(NULL, 0, fmt, it->name, it->file, it->line, it->col);
    }

    err->stack.data = the_safe_realloc(err->stack.data, (err->stack.len + z + 1) * sizeof(wchar_t));

    if (it->col == 0 && it->line == 0) {
      swprintf(&err->stack.data[err->stack.len], z, fmt, it->name, it->file);
    } else if (it->col == 0) {
      swprintf(&err->stack.data[err->stack.len], z, fmt, it->name, it->file, it->line);
    } else {
      swprintf(&err->stack.data[err->stack.len], z, fmt, it->name, it->file, it->line, it->col);
    }

    err->stack.len += z;
  }
}

void the_error_unset (the_err_state_t *state) {
  state->id = -1;
  state->free_cb = NULL;
}

the_Error_t *the_Error_alloc (the_str_t message) {
  the_Error_t *err = the_safe_alloc(sizeof(the_Error_t));
  err->message = the_str_copy(message);
  err->stack = the_str_alloc(L"");
  return err;
}

void the_Error_free (void *self) {
  the_Error_t *err = self;
  the_str_free(err->message);
  the_str_free(err->stack);
  the_safe_free(self);
}
