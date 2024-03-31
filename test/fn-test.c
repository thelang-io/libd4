/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/fn.h>
#include <the/macro.h>
#include <the/number.h>
#include <assert.h>

THE_FUNCTION_DECLARE(s, u32, uint32_t)
THE_FUNCTION_DEFINE(s, u32, uint32_t)

THE_FUNCTION_DECLARE_WITH_PARAMS(s, u32, uint32_t, FP3int, {
  int32_t n0;
})

THE_FUNCTION_DEFINE_WITH_PARAMS(s, u32, uint32_t, FP3int)

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

static uint32_t job1 (THE_UNUSED void *ctx, THE_UNUSED void *params) {
  return 10;
}

static uint32_t job2 (THE_UNUSED void *ctx, the_fn_sFP3intFRu32FE_params_t *params) {
  return params->n0 + 20;
}

static uint32_t job3 (job_ctx_t *ctx, THE_UNUSED void *params) {
  return *ctx->a + 30;
}

static uint32_t job4 (job_ctx_t *ctx, the_fn_sFP3intFRu32FE_params_t *params) {
  return *ctx->a + params->n0 + 40;
}

static void test_fn_alloc (void) {
  int int_var = 5;

  the_str_t name1 = the_str_alloc(L"job1");
  the_str_t name2 = the_str_alloc(L"job2");
  the_str_t name3 = the_str_alloc(L"job3");
  the_str_t name4 = the_str_alloc(L"job4");

  the_fn_sFRu32FE_t a = the_fn_sFRu32FE_alloc(
    name1,
    NULL,
    NULL,
    NULL,
    (uint32_t (*) (void *, void *)) job1
  );

  the_fn_sFP3intFRu32FE_t b = the_fn_sFP3intFRu32FE_alloc(
    name2,
    NULL,
    NULL,
    NULL,
    (uint32_t (*) (void *, void *)) job2
  );

  the_fn_sFRu32FE_t c = the_fn_sFRu32FE_alloc(
    name3,
    the_safe_calloc(&(job_ctx_t) {&int_var}, sizeof(job_ctx_t)),
    (void *(*) (const void *)) job_ctx_copy,
    (void (*) (void *)) job_ctx_free,
    (uint32_t (*) (void *, void *)) job3
  );

  the_fn_sFP3intFRu32FE_t d = the_fn_sFP3intFRu32FE_alloc(
    name4,
    the_safe_calloc(&(job_ctx_t) {&int_var}, sizeof(job_ctx_t)),
    (void *(*) (const void *)) job_ctx_copy,
    (void (*) (void *)) job_ctx_free,
    (uint32_t (*) (void *, void *)) job4
  );

  assert(((void) "Function name is set without ctx and params", the_str_eq(a.name, name1)));
  assert(((void) "Function name is set without ctx", the_str_eq(b.name, name2)));
  assert(((void) "Function name is set without params", the_str_eq(c.name, name3)));
  assert(((void) "Function name is set with ctx and params", the_str_eq(d.name, name4)));

  assert(((void) "Function name is set without ctx and params", a.func != NULL));
  assert(((void) "Function name is set without ctx", b.func != NULL));
  assert(((void) "Function name is set without params", c.func != NULL));
  assert(((void) "Function name is set with ctx and params", d.func != NULL));

  the_fn_sFRu32FE_free(a);
  the_fn_sFP3intFRu32FE_free(b);
  the_fn_sFRu32FE_free(c);
  the_fn_sFP3intFRu32FE_free(d);

  the_str_free(name1);
  the_str_free(name2);
  the_str_free(name3);
  the_str_free(name4);
}

static void test_fn_copy (void) {
  the_str_t name1 = the_str_alloc(L"job1");
  the_str_t name2 = the_str_alloc(L"job2");

  the_fn_sFRu32FE_t a = the_fn_sFRu32FE_alloc(name1, NULL, NULL, NULL, (uint32_t (*) (void *, void *)) job1);
  the_fn_sFP3intFRu32FE_t b = the_fn_sFP3intFRu32FE_alloc(name2, NULL, NULL, NULL, (uint32_t (*) (void *, void *)) job2);
  the_fn_sFRu32FE_t c = the_fn_sFRu32FE_copy(a);
  the_fn_sFP3intFRu32FE_t d = the_fn_sFP3intFRu32FE_copy(b);

  assert(((void) "Function copies without ctx and params", the_fn_sFRu32FE_eq(a, c)));
  assert(((void) "Function copies without ctx", the_fn_sFP3intFRu32FE_eq(b, d)));

  the_fn_sFRu32FE_free(a);
  the_fn_sFP3intFRu32FE_free(b);
  the_fn_sFRu32FE_free(c);
  the_fn_sFP3intFRu32FE_free(d);

  the_str_free(name1);
  the_str_free(name2);
}

static void test_fn_eq (void) {
  the_str_t name1 = the_str_alloc(L"job1");
  the_str_t name2 = the_str_alloc(L"job2");

  the_fn_sFRu32FE_t a = the_fn_sFRu32FE_alloc(name1, NULL, NULL, NULL, (uint32_t (*) (void *, void *)) job1);
  the_fn_sFP3intFRu32FE_t b = the_fn_sFP3intFRu32FE_alloc(name2, NULL, NULL, NULL, (uint32_t (*) (void *, void *)) job2);
  the_fn_sFRu32FE_t c = the_fn_sFRu32FE_alloc(name1, NULL, NULL, NULL, (uint32_t (*) (void *, void *)) job1);
  the_fn_sFP3intFRu32FE_t d = the_fn_sFP3intFRu32FE_alloc(name2, NULL, NULL, NULL, (uint32_t (*) (void *, void *)) job2);

  assert(((void) "Function equals without ctx and params", the_fn_sFRu32FE_eq(a, c)));
  assert(((void) "Function copies without ctx", the_fn_sFP3intFRu32FE_eq(b, d)));

  the_fn_sFRu32FE_free(a);
  the_fn_sFP3intFRu32FE_free(b);
  the_fn_sFRu32FE_free(c);
  the_fn_sFP3intFRu32FE_free(d);

  the_str_free(name1);
  the_str_free(name2);
}

static void test_fn_exec (void) {
  int int_var = 5;

  the_str_t name1 = the_str_alloc(L"job1");
  the_str_t name2 = the_str_alloc(L"job2");
  the_str_t name3 = the_str_alloc(L"job3");
  the_str_t name4 = the_str_alloc(L"job4");

  the_fn_sFRu32FE_t a = the_fn_sFRu32FE_alloc(
    name1,
    NULL,
    NULL,
    NULL,
    (uint32_t (*) (void *, void *)) job1
  );

  the_fn_sFP3intFRu32FE_t b = the_fn_sFP3intFRu32FE_alloc(
    name2,
    NULL,
    NULL,
    NULL,
    (uint32_t (*) (void *, void *)) job2
  );

  the_fn_sFRu32FE_t c = the_fn_sFRu32FE_alloc(
    name3,
    the_safe_calloc(&(job_ctx_t) {&int_var}, sizeof(job_ctx_t)),
    (void *(*) (const void *)) job_ctx_copy,
    (void (*) (void *)) job_ctx_free,
    (uint32_t (*) (void *, void *)) job3
  );

  the_fn_sFP3intFRu32FE_t d = the_fn_sFP3intFRu32FE_alloc(
    name4,
    the_safe_calloc(&(job_ctx_t) {&int_var}, sizeof(job_ctx_t)),
    (void *(*) (const void *)) job_ctx_copy,
    (void (*) (void *)) job_ctx_free,
    (uint32_t (*) (void *, void *)) job4
  );

  assert(((void) "Function name is set without ctx and params", a.func(a.ctx, NULL) == 10));
  assert(((void) "Function name is set without ctx", b.func(b.ctx, the_safe_calloc(&(the_fn_sFP3intFRu32FE_params_t) {5}, sizeof(the_fn_sFP3intFRu32FE_params_t))) == 25));
  assert(((void) "Function name is set without params", c.func(c.ctx, NULL) == 35));
  assert(((void) "Function name is set with ctx and params", d.func(d.ctx, the_safe_calloc(&(the_fn_sFP3intFRu32FE_params_t) {10}, sizeof(the_fn_sFP3intFRu32FE_params_t))) == 55));

  the_fn_sFRu32FE_free(a);
  the_fn_sFP3intFRu32FE_free(b);
  the_fn_sFRu32FE_free(c);
  the_fn_sFP3intFRu32FE_free(d);

  the_str_free(name1);
  the_str_free(name2);
  the_str_free(name3);
  the_str_free(name4);
}

static void test_fn_free (void) {
  the_str_t name1 = the_str_alloc(L"job1");
  the_str_t name2 = the_str_alloc(L"job2");

  the_fn_sFRu32FE_t a = the_fn_sFRu32FE_alloc(name1, NULL, NULL, NULL, (uint32_t (*) (void *, void *)) job1);
  the_fn_sFP3intFRu32FE_t b = the_fn_sFP3intFRu32FE_alloc(name2, NULL, NULL, NULL, (uint32_t (*) (void *, void *)) job2);

  the_fn_sFRu32FE_free(a);
  the_fn_sFP3intFRu32FE_free(b);

  the_str_free(name1);
  the_str_free(name2);
}

static void test_fn_realloc (void) {
  the_str_t name1 = the_str_alloc(L"job1");
  the_str_t name2 = the_str_alloc(L"job2");

  the_fn_sFRu32FE_t a = the_fn_sFRu32FE_alloc(name1, NULL, NULL, NULL, (uint32_t (*) (void *, void *)) job1);
  the_fn_sFP3intFRu32FE_t b = the_fn_sFP3intFRu32FE_alloc(name2, NULL, NULL, NULL, (uint32_t (*) (void *, void *)) job2);
  the_fn_sFRu32FE_t c = the_fn_sFRu32FE_alloc(name1, NULL, NULL, NULL, (uint32_t (*) (void *, void *)) job1);
  the_fn_sFP3intFRu32FE_t d = the_fn_sFP3intFRu32FE_alloc(name2, NULL, NULL, NULL, (uint32_t (*) (void *, void *)) job2);

  c = the_fn_sFRu32FE_realloc(c, a);
  d = the_fn_sFP3intFRu32FE_realloc(d, b);

  assert(((void) "Function reallocates without ctx and params", the_fn_sFRu32FE_eq(a, c)));
  assert(((void) "Function reallocates without ctx", the_fn_sFP3intFRu32FE_eq(b, d)));

  the_fn_sFRu32FE_free(a);
  the_fn_sFP3intFRu32FE_free(b);
  the_fn_sFRu32FE_free(c);
  the_fn_sFP3intFRu32FE_free(d);

  the_str_free(name1);
  the_str_free(name2);
}

static void test_fn_str (void) {
  the_str_t name1 = the_str_alloc(L"job1");
  the_str_t name2 = the_str_alloc(L"job2");

  the_fn_sFRu32FE_t a = the_fn_sFRu32FE_alloc(name1, NULL, NULL, NULL, (uint32_t (*) (void *, void *)) job1);
  the_fn_sFP3intFRu32FE_t b = the_fn_sFP3intFRu32FE_alloc(name2, NULL, NULL, NULL, (uint32_t (*) (void *, void *)) job2);

  the_str_t s1 = the_fn_sFRu32FE_str(a);
  the_str_t s2 = the_fn_sFP3intFRu32FE_str(b);

  assert(((void) "Function stringifies without ctx and params", the_str_eq(s1, name1)));
  assert(((void) "Function stringifies without ctx", the_str_eq(s2, name2)));

  the_str_free(s1);
  the_str_free(s2);

  the_fn_sFRu32FE_free(a);
  the_fn_sFP3intFRu32FE_free(b);

  the_str_free(name1);
  the_str_free(name2);
}

int main (void) {
  test_fn_alloc();
  test_fn_copy();
  test_fn_eq();
  test_fn_exec();
  test_fn_free();
  test_fn_realloc();
  test_fn_str();
}
