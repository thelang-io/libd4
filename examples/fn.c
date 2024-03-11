/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/fn.h>
#include <stdio.h>

THE_FUNCTION_DECLARE(fn_sFRintFE, int)

THE_FUNCTION_DECLARE_WITH_PARAMS(fn_sFPintFRintFE, int, {
  int b;
})

THE_FUNCTION_DEFINE(fn_sFRintFE, int)
THE_FUNCTION_DEFINE(fn_sFPintFRintFE, int)

typedef struct {
  int *a;
} job_ctx_t;

static void *job_ctx_copy (const job_ctx_t *ctx) {
  job_ctx_t *result = the_safe_alloc(sizeof(job_ctx_t));
  result->a = ctx->a;
  return result;
}

static void job_ctx_free (job_ctx_t *ctx) {
  the_safe_free(ctx);
}

static int job (job_ctx_t *ctx, the_fn_sFPintFRintFE_params_t *params) {
  printf("Context a: %d, Params: b: %d\n", *ctx->a, params->b);
  *ctx->a += params->b;
  return *ctx->a;
}

static int job2 (THE_UNUSED void *ctx, the_fn_sFPintFRintFE_params_t *params) {
  printf("Params: b: %d\n", params->b);
  return params->b;
}

int main (void) {
  int a = 2;

  the_fn_sFPintFRintFE_t a1 = the_fn_sFPintFRintFE_alloc(
    the_str_alloc(L"job"),
    the_safe_calloc(&(job_ctx_t) {&a}, sizeof(job_ctx_t)),
    (void *(*) (const void *)) job_ctx_copy,
    (void (*) (void *)) job_ctx_free,
    (int (*) (void *, void *)) job
  );

  the_fn_sFPintFRintFE_t a2 = the_fn_sFPintFRintFE_alloc(
    the_str_alloc(L"job2"),
    NULL,
    NULL,
    NULL,
    (int (*) (void *, void *)) job2
  );

  int result1;
  int result2;
  the_str_t s1 = the_fn_sFPintFRintFE_str(a1);
  the_str_t s2 = the_fn_sFPintFRintFE_str(a2);

  printf("a1: %ls\n", s1.data);
  printf("a2: %ls\n", s2.data);

  if (the_fn_sFPintFRintFE_eq(a1, a2)) {
    printf("a1 == a2\n");
  } else {
    printf("a1 != a2\n");
  }

  result1 = a1.func(a1.ctx, the_safe_calloc(&(the_fn_sFPintFRintFE_params_t) {10}, sizeof(the_fn_sFPintFRintFE_params_t)));
  printf("Result: %d\n", result1);
  result2 = a2.func(a1.ctx, the_safe_calloc(&(the_fn_sFPintFRintFE_params_t) {2}, sizeof(the_fn_sFPintFRintFE_params_t)));
  printf("Result: %d\n", result2);

  the_str_free(s1);
  the_str_free(s2);
  a2 = the_fn_sFPintFRintFE_realloc(a2, a1);

  s1 = the_fn_sFPintFRintFE_str(a1);
  s2 = the_fn_sFPintFRintFE_str(a2);

  printf("a1: %ls\n", s1.data);
  printf("a2: %ls\n", s2.data);

  if (the_fn_sFPintFRintFE_eq(a1, a2)) {
    printf("a1 == a2\n");
  } else {
    printf("a1 != a2\n");
  }

  result2 = a2.func(a1.ctx, the_safe_calloc(&(the_fn_sFPintFRintFE_params_t) {2}, sizeof(the_fn_sFPintFRintFE_params_t)));
  printf("Result: %d\n", result2);

  the_str_free(s1);
  the_str_free(s2);

  the_fn_sFPintFRintFE_free(a1);
  the_fn_sFPintFRintFE_free(a2);

  return 0;
}
