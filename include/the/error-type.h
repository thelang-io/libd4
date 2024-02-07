/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_ERROR_TYPE_H
#define THE_ERROR_TYPE_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/string-type.h>
#include <setjmp.h>

/**
 * Callback that is used as a property of the_err_state__t object to free the object.
 * @param ctx Context of the object to copy.
 * @return Newly copied object.
 */
typedef void (*the_err_state_free_cb) (void *);

/** Structure representing the_err_buf_t linked list. */
typedef struct the_err_buf_s {
  /** Jump buffer. */
  jmp_buf buf;

  /** Next item in a chain. */
  struct the_err_buf_s *next;

  /** Previous item in a chain. */
  struct the_err_buf_s *prev;
} the_err_buf_t;

/** Structure representing the_err_stack_t linked list. */
typedef struct the_err_stack_s {
  /** todo */
  const wchar_t *file;

  /** todo */
  const wchar_t *name;

  /** todo */
  int line;

  /** todo */
  int col;

  /** Next item in a chain. */
  struct the_err_stack_s *next;

  /** Previous item in a chain. */
  struct the_err_stack_s *prev;
} the_err_stack_t;

/** Structure representing the_err_state_t object. */
typedef struct {
  /** Type of the error. */
  int id;

  /** Context of the error object. */
  void *ctx;

  /** Pointer to a first item of buffer. */
  the_err_buf_t *buf_first;

  /** Pointer to a last item of buffer. */
  the_err_buf_t *buf_last;

  /** Pointer to a first item of stack. */
  the_err_stack_t *stack_first;

  /** Pointer to a last item of stack. */
  the_err_stack_t *stack_last;

  /** Callback of the_err_state_t object used to free the context. */
  the_err_state_free_cb free_cb;
} the_err_state_t;

/** Structure representing generic Error object. */
typedef struct {
  /** Message of the error. */
  the_str_t message;

  /** Stack of the error. */
  the_str_t stack;
} the_Error_t;

#endif
