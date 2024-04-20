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
  the_str_t message;
  the_str_t stack;
} CustomError_t;

static CustomError_t *the_CustomError_alloc (the_str_t message) {
  CustomError_t *err = the_safe_alloc(sizeof(CustomError_t));
  err->message = the_str_copy(message);
  err->stack = the_str_empty_val;
  return err;
}

static void the_CustomError_free (void *self) {
  CustomError_t *err = self;
  the_str_free(err->message);
  the_str_free(err->stack);
  the_safe_free(self);
}

#endif
