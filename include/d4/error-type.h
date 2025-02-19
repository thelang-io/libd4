/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_ERROR_TYPE_H
#define D4_ERROR_TYPE_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include <setjmp.h>
#include "string-type.h"

/**
 * Callback that is used as a property of d4_err_state__t object to free the object.
 * @param ctx Context of the object to copy.
 * @return Newly copied object.
 */
typedef void (*d4_err_state_free_cb) (void *ctx);

/** Structure representing d4_err_buf_t linked list. */
typedef struct d4_err_buf_s {
  /** Jump buffer. */
  jmp_buf buf;

  /** Next item in a chain. */
  struct d4_err_buf_s *next;

  /** Previous item in a chain. */
  struct d4_err_buf_s *prev;
} d4_err_buf_t;

/** Structure representing d4_err_stack_t linked list. */
typedef struct d4_err_stack_s {
  /** Stack file path. */
  const wchar_t *file;

  /** Stack function name. */
  const wchar_t *name;

  /** Stack line number. */
  int line;

  /** Stack line column. */
  int col;

  /** Next item in a chain. */
  struct d4_err_stack_s *next;

  /** Previous item in a chain. */
  struct d4_err_stack_s *prev;
} d4_err_stack_t;

/** Structure representing d4_err_state_t object. */
typedef struct {
  /** Type of the error. */
  int id;

  /** Context of the error object. */
  void *ctx;

  /** Pointer to a first item of buffer. */
  d4_err_buf_t *buf_first;

  /** Pointer to a last item of buffer. */
  d4_err_buf_t *buf_last;

  /** Pointer to a first item of stack. */
  d4_err_stack_t *stack_first;

  /** Pointer to a last item of stack. */
  d4_err_stack_t *stack_last;

  /** Callback of d4_err_state_t object used to free the context. */
  d4_err_state_free_cb free_cb;
} d4_err_state_t;

/** Structure representing generic Error object. */
typedef struct {
  /** Message of the error. */
  d4_str_t message;

  /** Stack of the error. */
  d4_str_t stack;
} d4_Error_t;

#endif
