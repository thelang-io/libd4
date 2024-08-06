/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef TEST_ANY_ERROR_H
#define TEST_ANY_ERROR_H

#include "../src/error.h"
#include "../src/safe.h"
#include "../src/string.h"

#define TYPE_CustomError 1

typedef struct {
  d4_str_t message;
  d4_str_t stack;
} CustomError_t;

static CustomError_t *d4_CustomError_alloc (d4_str_t message) {
  CustomError_t *err = d4_safe_alloc(sizeof(CustomError_t));
  err->message = d4_str_copy(message);
  err->stack = d4_str_empty_val;
  return err;
}

static void d4_CustomError_free (void *self) {
  CustomError_t *err = self;
  d4_str_free(err->message);
  d4_str_free(err->stack);
  d4_safe_free(self);
}

#endif
