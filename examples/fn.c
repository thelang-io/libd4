/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/fn.h>
#include <stdio.h>

THE_FUNCTION_DECLARE(fn_fFPintFRvoidFE, int)

THE_FUNCTION_DEFINE(fn_fFPintFRvoidFE, int)

typedef struct {
  int b;
} the_fn_fFPintFRvoidFE_params_t;

typedef struct {
  int *a;
} job_ctx_t;

static int job (job_ctx_t *ctx, the_fn_fFPintFRvoidFE_params_t *params) {
  printf("Context a: %d, Params: b: %d\n", *ctx->a, params->b);
  return *ctx->a + params->b;
}

static void *job_ctx_copy (const job_ctx_t *ctx) {
  job_ctx_t *result = the_safe_alloc(sizeof(job_ctx_t));
  result->a = ctx->a;
  return result;
}

// todo finish
int main (void) {
  int a = 2;
  the_str_t a1_name = the_str_alloc(L"job");

  the_fn_fFPintFRvoidFE_t a1 = the_fn_fFPintFRvoidFE_alloc(
    a1_name,
    (int (*) (void *, void *)) job,
    the_safe_calloc(&(job_ctx_t) {&a}, sizeof(job_ctx_t)),
    (void *(*) (const void *)) job_ctx_copy,
    the_fn_ctx_free_generic
  );

  int result = a1.func(a1.ctx, the_safe_calloc(&(the_fn_fFPintFRvoidFE_params_t) {10}, sizeof(the_fn_fFPintFRvoidFE_params_t)));
  printf("Result: %d\n", result);

  the_fn_fFPintFRvoidFE_free(a1);

  return 0;
}
