/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef SRC_ERROR_H
#define SRC_ERROR_H

#include <the/error.h>
#include <setjmp.h>
#include "string.h"

struct the_err_buf_s {
  jmp_buf buf;
  struct the_err_buf_s *next;
  struct the_err_buf_s *prev;
};

struct the_err_stack_s {
  const wchar_t *file;
  const wchar_t *name;
  int line;
  int col;
  struct the_err_stack_s *next;
  struct the_err_stack_s *prev;
};

struct the_err_state_s {
  int id;
  void *ctx;
  the_err_buf_t *buf_first;
  the_err_buf_t *buf_last;
  the_err_stack_t *stack_first;
  the_err_stack_t *stack_last;
  void (*_free) (void *);
};

struct the_Error_s {
  the_str_t message;
  the_str_t stack;
};

#endif
