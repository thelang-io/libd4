/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <d4/array.h>
#include <d4/number.h>
#include <assert.h>
#include "./utils.h"

D4_ARRAY_DECLARE(int, int32_t)
D4_ARRAY_DEFINE(int, int32_t, int32_t, element, lhs_element == rhs_element, (void) element, d4_i32_str(element))

D4_ARRAY_DECLARE(arr_str, d4_arr_str_t)
D4_ARRAY_DEFINE(arr_str, d4_arr_str_t, d4_arr_str_t, d4_arr_str_copy(element), d4_arr_str_eq(lhs_element, rhs_element), d4_arr_str_free(element), d4_arr_str_str(element))

typedef struct {
  d4_str_t *var;
} foreach_ctx_t;

static bool filter_str (D4_UNUSED void *ctx, d4_fn_esFP3strFRboolFE_params_t *params) {
  return params->n0.len > 2;
}

static void *foreach_ctx_copy (const foreach_ctx_t *ctx) {
  foreach_ctx_t *result = d4_safe_alloc(sizeof(foreach_ctx_t));
  *result->var = d4_str_copy(*ctx->var);
  return result;
}

static void foreach_ctx_free (foreach_ctx_t *ctx) {
  d4_safe_free(ctx);
}

static void foreach_str (foreach_ctx_t *ctx, d4_fn_esFP3strFRboolFE_params_t *params) {
  d4_str_t t0;
  *ctx->var = d4_str_realloc(*ctx->var, t0 = d4_str_concat(*ctx->var, params->n0));
  d4_str_free(t0);
}

static int sort_asc_str (D4_UNUSED void *ctx, d4_fn_esFP3strFP3strFRintFE_params_t *params) {
  return d4_str_gt(params->n0, params->n1);
}

static int sort_desc_str (D4_UNUSED void *ctx, d4_fn_esFP3strFP3strFRintFE_params_t *params) {
  return d4_str_lt(params->n0, params->n1);
}

static void test_array_alloc (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");

  d4_arr_int_t a1 = d4_arr_int_alloc(1, 10);
  d4_arr_int_t a2 = d4_arr_int_alloc(2, 20, 30);
  d4_arr_str_t a3 = d4_arr_str_alloc(0);
  d4_arr_str_t a4 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a5 = d4_arr_str_alloc(2, v1, v2);

  assert(((void) "Creates int array with one element", a1.len == 1));
  assert(((void) "Creates int array with two elements", a2.len == 2));
  assert(((void) "Creates str array with zero elements", a3.len == 0));
  assert(((void) "Creates str array with one element", a4.len == 1));
  assert(((void) "Creates str array with two element", a5.len == 2));

  d4_arr_int_free(a1);
  d4_arr_int_free(a2);
  d4_arr_str_free(a3);
  d4_arr_str_free(a4);
  d4_arr_str_free(a5);

  d4_str_free(v1);
  d4_str_free(v2);
}

static void test_array_at (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v2, v1);

  d4_str_t *r;

  ASSERT_NO_THROW(AT1, {
    r = d4_arr_str_at(&d4_err_state, 0, 0, a2, 0);
    assert(((void) "Returns first element for one element array", d4_str_eq(*r, v1)));
    r = d4_arr_str_at(&d4_err_state, 0, 0, a3, 0);
    assert(((void) "Returns first element for two elements array", d4_str_eq(*r, v2)));
    r = d4_arr_str_at(&d4_err_state, 0, 0, a3, 1);
    assert(((void) "Returns second element for two elements array", d4_str_eq(*r, v1)));
    r = d4_arr_str_at(&d4_err_state, 0, 0, a2, -1);
    assert(((void) "Returns last element for one element array", d4_str_eq(*r, v1)));
    r = d4_arr_str_at(&d4_err_state, 0, 0, a3, -1);
    assert(((void) "Returns last element for two elements array", d4_str_eq(*r, v1)));
    r = d4_arr_str_at(&d4_err_state, 0, 0, a3, -2);
    assert(((void) "Returns first element for two elements array from back", d4_str_eq(*r, v2)));
  });

  ASSERT_THROW_WITH_MESSAGE(AT2, {
    r = d4_arr_str_at(&d4_err_state, 0, 0, a1, 10);
  }, L"index 10 out of array bounds");

  ASSERT_THROW_WITH_MESSAGE(AT3, {
    r = d4_arr_str_at(&d4_err_state, 0, 0, a1, -10);
  }, L"index -10 out of array bounds");

  ASSERT_THROW_WITH_MESSAGE(AT4, {
    r = d4_arr_str_at(&d4_err_state, 0, 0, a2, 10);
  }, L"index 10 out of array bounds");

  ASSERT_THROW_WITH_MESSAGE(AT5, {
    r = d4_arr_str_at(&d4_err_state, 0, 0, a3, -10);
  }, L"index -10 out of array bounds");

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);

  d4_str_free(v1);
  d4_str_free(v2);
}

static void test_array_clear (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v2, v1);

  d4_arr_str_clear(&a1);
  assert(((void) "Clears array with zero elements", a1.len == 0));
  d4_arr_str_clear(&a2);
  assert(((void) "Clears array with one element", a2.len == 0));
  d4_arr_str_clear(&a3);
  assert(((void) "Clears array with two elements", a3.len == 0));

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);

  d4_str_free(v1);
  d4_str_free(v2);
}

static void test_array_concat (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v2, v1);

  d4_arr_str_t r1 = d4_arr_str_concat(a1, a1);
  d4_arr_str_t r2 = d4_arr_str_concat(a2, a2);
  d4_arr_str_t r3 = d4_arr_str_concat(a3, a3);
  d4_arr_str_t r4 = d4_arr_str_concat(a1, a2);
  d4_arr_str_t r5 = d4_arr_str_concat(a1, a3);
  d4_arr_str_t r6 = d4_arr_str_concat(a2, a3);

  d4_arr_str_t cmp1 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp2 = d4_arr_str_alloc(2, v1, v1);
  d4_arr_str_t cmp3 = d4_arr_str_alloc(4, v2, v1, v2, v1);
  d4_arr_str_t cmp4 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t cmp5 = d4_arr_str_alloc(2, v2, v1);
  d4_arr_str_t cmp6 = d4_arr_str_alloc(3, v1, v2, v1);

  assert(((void) "Concatenates empty arrays", d4_arr_str_eq(r1, cmp1)));
  assert(((void) "Concatenates one element arrays", d4_arr_str_eq(r2, cmp2)));
  assert(((void) "Concatenates two elements arrays", d4_arr_str_eq(r3, cmp3)));
  assert(((void) "Concatenates empty with one element array", d4_arr_str_eq(r4, cmp4)));
  assert(((void) "Concatenates empty with two elements array", d4_arr_str_eq(r5, cmp5)));
  assert(((void) "Concatenates one element with two elements array", d4_arr_str_eq(r6, cmp6)));

  d4_arr_str_free(cmp1);
  d4_arr_str_free(cmp2);
  d4_arr_str_free(cmp3);
  d4_arr_str_free(cmp4);
  d4_arr_str_free(cmp5);
  d4_arr_str_free(cmp6);

  d4_arr_str_free(r1);
  d4_arr_str_free(r2);
  d4_arr_str_free(r3);
  d4_arr_str_free(r4);
  d4_arr_str_free(r5);
  d4_arr_str_free(r6);

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);

  d4_str_free(v1);
  d4_str_free(v2);
}

static void test_array_contains (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");
  d4_str_t v3 = d4_str_alloc(L"element3");
  d4_str_t v4 = d4_str_alloc(L"element4");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v2, v1);
  d4_arr_str_t a4 = d4_arr_str_alloc(3, v1, v2, v3);

  assert(((void) "Doesn't contain element in zero elements array", !d4_arr_str_contains(a1, v4)));
  assert(((void) "Doesn't contain element in one element array", !d4_arr_str_contains(a2, v4)));
  assert(((void) "Doesn't contain element in two elements array", !d4_arr_str_contains(a3, v4)));
  assert(((void) "Doesn't contain element in three elements array", !d4_arr_str_contains(a4, v4)));
  assert(((void) "Contains element in one element array", d4_arr_str_contains(a2, v1)));

  assert((
    (void) "Contains elements in two element array",
    (d4_arr_str_contains(a3, v1) && d4_arr_str_contains(a3, v2))
  ));

  assert((
    (void) "Contains elements in three element array",
    (d4_arr_str_contains(a4, v1) && d4_arr_str_contains(a4, v2) && d4_arr_str_contains(a4, v3))
  ));

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);
  d4_arr_str_free(a4);

  d4_str_free(v1);
  d4_str_free(v2);
  d4_str_free(v3);
  d4_str_free(v4);
}

static void test_array_copy (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v1, v2);
  d4_arr_str_t a4 = d4_arr_str_copy(a1);
  d4_arr_str_t a5 = d4_arr_str_copy(a2);
  d4_arr_str_t a6 = d4_arr_str_copy(a3);

  assert(((void) "Copies empty array", a4.len == 0));
  assert(((void) "Copies one element array", a5.len == 1));
  assert(((void) "Copies two elements array", a6.len == 2));

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);
  d4_arr_str_free(a4);
  d4_arr_str_free(a5);
  d4_arr_str_free(a6);

  d4_str_free(v1);
  d4_str_free(v2);
}

static void test_array_empty (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v1, v2);

  assert(((void) "Checks empty on array with zero elements", d4_arr_str_empty(a1)));
  assert(((void) "Checks empty on array with one element", !d4_arr_str_empty(a2)));
  assert(((void) "Checks empty on array with two elements", !d4_arr_str_empty(a3)));

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);

  d4_str_free(v1);
  d4_str_free(v2);
}

static void test_array_eq (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");
  d4_str_t v3 = d4_str_alloc(L"element3");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(0);
  d4_arr_str_t a3 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a4 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a5 = d4_arr_str_alloc(2, v1, v2);
  d4_arr_str_t a6 = d4_arr_str_alloc(2, v1, v2);
  d4_arr_str_t a7 = d4_arr_str_alloc(2, v2, v1);
  d4_arr_str_t a8 = d4_arr_str_alloc(2, v2, v3);

  assert(((void) "Equals arrays with zero elements", d4_arr_str_eq(a1, a2)));
  assert(((void) "Equals arrays with one element", d4_arr_str_eq(a3, a4)));
  assert(((void) "Equals arrays with two elements", d4_arr_str_eq(a5, a6)));
  assert(((void) "Not equals arrays with different amount of elements", !d4_arr_str_eq(a1, a3)));
  assert(((void) "Not equals arrays with different amount of elements 2", !d4_arr_str_eq(a3, a5)));
  assert(((void) "Not equals arrays with different elements", !d4_arr_str_eq(a7, a8)));

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);
  d4_arr_str_free(a4);
  d4_arr_str_free(a5);
  d4_arr_str_free(a6);
  d4_arr_str_free(a7);
  d4_arr_str_free(a8);

  d4_str_free(v1);
  d4_str_free(v2);
  d4_str_free(v3);
}

static void test_array_filter (void) {
  d4_str_t filter_name = d4_str_alloc(L"filter");
  d4_fn_esFP3strFRboolFE_t filter = d4_fn_esFP3strFRboolFE_alloc(filter_name, NULL, NULL, NULL, (bool (*) (void *, void *)) filter_str);

  d4_str_t v1 = d4_str_alloc(L"");
  d4_str_t v2 = d4_str_alloc(L"a");
  d4_str_t v3 = d4_str_alloc(L"orange");
  d4_str_t v4 = d4_str_alloc(L"lorem ipsum dolor sit amet");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v1, v2);
  d4_arr_str_t a4 = d4_arr_str_alloc(3, v1, v2, v3);
  d4_arr_str_t a5 = d4_arr_str_alloc(4, v1, v2, v3, v4);

  d4_arr_str_t cmp1 = d4_arr_str_alloc(1, v3);
  d4_arr_str_t cmp2 = d4_arr_str_alloc(2, v3, v4);

  ASSERT_NO_THROW(FILTER1, {
    d4_arr_str_t r1 = d4_arr_str_filter(&d4_err_state, 0, 0, a1, filter);
    d4_arr_str_t r2 = d4_arr_str_filter(&d4_err_state, 0, 0, a2, filter);
    d4_arr_str_t r3 = d4_arr_str_filter(&d4_err_state, 0, 0, a3, filter);
    d4_arr_str_t r4 = d4_arr_str_filter(&d4_err_state, 0, 0, a4, filter);
    d4_arr_str_t r5 = d4_arr_str_filter(&d4_err_state, 0, 0, a5, filter);

    assert(((void) "Filters empty array", d4_arr_str_eq(r1, a1)));
    assert(((void) "Filters array with one element", d4_arr_str_eq(r2, a1)));
    assert(((void) "Filters array with two elements", d4_arr_str_eq(r3, a1)));
    assert(((void) "Filters array with three elements", d4_arr_str_eq(r4, cmp1)));
    assert(((void) "Filters array with four elements", d4_arr_str_eq(r5, cmp2)));

    d4_arr_str_free(r1);
    d4_arr_str_free(r2);
    d4_arr_str_free(r3);
    d4_arr_str_free(r4);
    d4_arr_str_free(r5);
  });

  d4_arr_str_free(cmp1);
  d4_arr_str_free(cmp2);

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);
  d4_arr_str_free(a4);
  d4_arr_str_free(a5);

  d4_str_free(v1);
  d4_str_free(v2);
  d4_str_free(v3);
  d4_str_free(v4);

  d4_fn_esFP3strFRboolFE_free(filter);
  d4_str_free(filter_name);
}

static void test_array_first (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v2, v1);

  ASSERT_NO_THROW(FIRST1, {
    d4_str_t *f1 = d4_arr_str_first(&d4_err_state, 0, 0, &a2);
    d4_str_t *f2 = d4_arr_str_first(&d4_err_state, 0, 0, &a3);

    assert(((void) "Gets first from array with one element", d4_str_eq(v1, *f1)));
    assert(((void) "Gets first from array with two elements", d4_str_eq(v2, *f2)));
  });

  ASSERT_THROW_WITH_MESSAGE(FIRST2, {
    d4_arr_str_first(&d4_err_state, 0, 0, &a1);
  }, L"tried getting first element of empty array");

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);

  d4_str_free(v1);
  d4_str_free(v2);
}

static void test_array_forEach (void) {
  d4_str_t foreach_name = d4_str_alloc(L"foreach");

  d4_str_t r1 = d4_str_alloc(L"");
  d4_str_t r2 = d4_str_alloc(L"");
  d4_str_t r3 = d4_str_alloc(L"");
  d4_str_t r4 = d4_str_alloc(L"");

  d4_fn_esFP3strFP3intFRvoidFE_t foreach1 = d4_fn_esFP3strFP3intFRvoidFE_alloc(
    foreach_name,
    d4_safe_calloc(&(foreach_ctx_t) {&r1}, sizeof(foreach_ctx_t)),
    (void *(*) (const void *)) foreach_ctx_copy,
    (void (*) (void *)) foreach_ctx_free,
    (void (*) (void *, void *)) foreach_str
  );

  d4_fn_esFP3strFP3intFRvoidFE_t foreach2 = d4_fn_esFP3strFP3intFRvoidFE_alloc(
    foreach_name,
    d4_safe_calloc(&(foreach_ctx_t) {&r2}, sizeof(foreach_ctx_t)),
    (void *(*) (const void *)) foreach_ctx_copy,
    (void (*) (void *)) foreach_ctx_free,
    (void (*) (void *, void *)) foreach_str
  );

  d4_fn_esFP3strFP3intFRvoidFE_t foreach3 = d4_fn_esFP3strFP3intFRvoidFE_alloc(
    foreach_name,
    d4_safe_calloc(&(foreach_ctx_t) {&r3}, sizeof(foreach_ctx_t)),
    (void *(*) (const void *)) foreach_ctx_copy,
    (void (*) (void *)) foreach_ctx_free,
    (void (*) (void *, void *)) foreach_str
  );

  d4_fn_esFP3strFP3intFRvoidFE_t foreach4 = d4_fn_esFP3strFP3intFRvoidFE_alloc(
    foreach_name,
    d4_safe_calloc(&(foreach_ctx_t) {&r4}, sizeof(foreach_ctx_t)),
    (void *(*) (const void *)) foreach_ctx_copy,
    (void (*) (void *)) foreach_ctx_free,
    (void (*) (void *, void *)) foreach_str
  );

  d4_str_t v1 = d4_str_alloc(L"");
  d4_str_t v2 = d4_str_alloc(L"a");
  d4_str_t v3 = d4_str_alloc(L"orange");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v1, v2);
  d4_arr_str_t a4 = d4_arr_str_alloc(3, v1, v2, v3);

  d4_str_t cmp1 = d4_str_alloc(L"");
  d4_str_t cmp2 = d4_str_alloc(L"");
  d4_str_t cmp3 = d4_str_alloc(L"a");
  d4_str_t cmp4 = d4_str_alloc(L"aorange");

  ASSERT_NO_THROW(FOREACH1, {
    d4_arr_str_forEach(&d4_err_state, 0, 0, a1, foreach1);
    d4_arr_str_forEach(&d4_err_state, 0, 0, a2, foreach2);
    d4_arr_str_forEach(&d4_err_state, 0, 0, a3, foreach3);
    d4_arr_str_forEach(&d4_err_state, 0, 0, a4, foreach4);

    assert(((void) "ForEach works with empty array", d4_str_eq(r1, cmp1)));
    assert(((void) "ForEach works with one element array", d4_str_eq(r2, cmp2)));
    assert(((void) "ForEach works with two elements array", d4_str_eq(r3, cmp3)));
    assert(((void) "ForEach works with three elements array", d4_str_eq(r4, cmp4)));
  });

  d4_str_free(cmp1);
  d4_str_free(cmp2);
  d4_str_free(cmp3);
  d4_str_free(cmp4);

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);
  d4_arr_str_free(a4);

  d4_str_free(v1);
  d4_str_free(v2);
  d4_str_free(v3);

  d4_fn_esFP3strFP3intFRvoidFE_free(foreach1);
  d4_fn_esFP3strFP3intFRvoidFE_free(foreach2);
  d4_fn_esFP3strFP3intFRvoidFE_free(foreach3);
  d4_fn_esFP3strFP3intFRvoidFE_free(foreach4);

  d4_str_free(r1);
  d4_str_free(r2);
  d4_str_free(r3);
  d4_str_free(r4);

  d4_str_free(foreach_name);
}

static void test_array_free (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v1, v2);
  d4_arr_int_t a4 = d4_arr_int_alloc(0);
  d4_arr_int_t a5 = d4_arr_int_alloc(1, 10);
  d4_arr_int_t a6 = d4_arr_int_alloc(2, 20, 30);
  d4_arr_arr_str_t a7 = d4_arr_arr_str_alloc(0);
  d4_arr_arr_str_t a8 = d4_arr_arr_str_alloc(1, a2);
  d4_arr_arr_str_t a9 = d4_arr_arr_str_alloc(2, a2, a3);

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);
  d4_arr_int_free(a4);
  d4_arr_int_free(a5);
  d4_arr_int_free(a6);
  d4_arr_arr_str_free(a7);
  d4_arr_arr_str_free(a8);
  d4_arr_arr_str_free(a9);

  d4_str_free(v1);
  d4_str_free(v2);
}

static void test_array_join (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");
  d4_str_t v3 = d4_str_alloc(L"a");
  d4_str_t v4 = d4_str_alloc(L"");

  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L",");
  d4_str_t s3 = d4_str_alloc(L" string ");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v2, v1);
  d4_arr_str_t a4 = d4_arr_str_alloc(3, v1, v2, v3);
  d4_arr_str_t a5 = d4_arr_str_alloc(4, v1, v2, v3, v4);

  d4_str_t r10 = d4_arr_str_join(a1, 0, d4_str_empty_val);
  d4_str_t r11 = d4_arr_str_join(a2, 0, d4_str_empty_val);
  d4_str_t r12 = d4_arr_str_join(a3, 0, d4_str_empty_val);
  d4_str_t r13 = d4_arr_str_join(a4, 0, d4_str_empty_val);
  d4_str_t r14 = d4_arr_str_join(a5, 0, d4_str_empty_val);
  d4_str_t r15 = d4_arr_str_join(a1, 1, s1);
  d4_str_t r16 = d4_arr_str_join(a2, 1, s1);
  d4_str_t r17 = d4_arr_str_join(a3, 1, s1);
  d4_str_t r18 = d4_arr_str_join(a4, 1, s1);
  d4_str_t r19 = d4_arr_str_join(a5, 1, s1);
  d4_str_t r20 = d4_arr_str_join(a1, 1, s2);
  d4_str_t r21 = d4_arr_str_join(a2, 1, s2);
  d4_str_t r22 = d4_arr_str_join(a3, 1, s2);
  d4_str_t r23 = d4_arr_str_join(a4, 1, s2);
  d4_str_t r24 = d4_arr_str_join(a5, 1, s2);
  d4_str_t r25 = d4_arr_str_join(a1, 1, s3);
  d4_str_t r26 = d4_arr_str_join(a2, 1, s3);
  d4_str_t r27 = d4_arr_str_join(a3, 1, s3);
  d4_str_t r28 = d4_arr_str_join(a4, 1, s3);
  d4_str_t r29 = d4_arr_str_join(a5, 1, s3);

  d4_str_t cmp10 = d4_str_alloc(L"");
  d4_str_t cmp11 = d4_str_alloc(L"element1");
  d4_str_t cmp12 = d4_str_alloc(L"element2,element1");
  d4_str_t cmp13 = d4_str_alloc(L"element1,element2,a");
  d4_str_t cmp14 = d4_str_alloc(L"element1,element2,a,");
  d4_str_t cmp15 = d4_str_alloc(L"");
  d4_str_t cmp16 = d4_str_alloc(L"element1");
  d4_str_t cmp17 = d4_str_alloc(L"element2element1");
  d4_str_t cmp18 = d4_str_alloc(L"element1element2a");
  d4_str_t cmp19 = d4_str_alloc(L"element1element2a");
  d4_str_t cmp20 = d4_str_alloc(L"");
  d4_str_t cmp21 = d4_str_alloc(L"element1");
  d4_str_t cmp22 = d4_str_alloc(L"element2,element1");
  d4_str_t cmp23 = d4_str_alloc(L"element1,element2,a");
  d4_str_t cmp24 = d4_str_alloc(L"element1,element2,a,");
  d4_str_t cmp25 = d4_str_alloc(L"");
  d4_str_t cmp26 = d4_str_alloc(L"element1");
  d4_str_t cmp27 = d4_str_alloc(L"element2 string element1");
  d4_str_t cmp28 = d4_str_alloc(L"element1 string element2 string a");
  d4_str_t cmp29 = d4_str_alloc(L"element1 string element2 string a string ");

  assert(((void) "Joins without arguments on zero elements array", d4_str_eq(r10, cmp10)));
  assert(((void) "Joins without arguments on one element array", d4_str_eq(r11, cmp11)));
  assert(((void) "Joins without arguments on two elements array", d4_str_eq(r12, cmp12)));
  assert(((void) "Joins without arguments on three elements array", d4_str_eq(r13, cmp13)));
  assert(((void) "Joins without arguments on four elements array", d4_str_eq(r14, cmp14)));
  assert(((void) "Joins by empty on zero elements array", d4_str_eq(r15, cmp15)));
  assert(((void) "Joins by empty on one element array", d4_str_eq(r16, cmp16)));
  assert(((void) "Joins by empty on two elements array", d4_str_eq(r17, cmp17)));
  assert(((void) "Joins by empty on three elements array", d4_str_eq(r18, cmp18)));
  assert(((void) "Joins by empty on four elements array", d4_str_eq(r19, cmp19)));
  assert(((void) "Joins by comma on zero elements array", d4_str_eq(r20, cmp20)));
  assert(((void) "Joins by comma on one element array", d4_str_eq(r21, cmp21)));
  assert(((void) "Joins by comma on two elements array", d4_str_eq(r22, cmp22)));
  assert(((void) "Joins by comma on three elements array", d4_str_eq(r23, cmp23)));
  assert(((void) "Joins by comma on four elements array", d4_str_eq(r24, cmp24)));
  assert(((void) "Joins by word on zero elements array", d4_str_eq(r25, cmp25)));
  assert(((void) "Joins by word on one element array", d4_str_eq(r26, cmp26)));
  assert(((void) "Joins by word on two elements array", d4_str_eq(r27, cmp27)));
  assert(((void) "Joins by word on three elements array", d4_str_eq(r28, cmp28)));
  assert(((void) "Joins by word on four elements array", d4_str_eq(r29, cmp29)));

  d4_str_free(v1);
  d4_str_free(v2);
  d4_str_free(v3);
  d4_str_free(v4);

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);
  d4_arr_str_free(a4);
  d4_arr_str_free(a5);

  d4_str_free(r10);
  d4_str_free(r11);
  d4_str_free(r12);
  d4_str_free(r13);
  d4_str_free(r14);
  d4_str_free(r15);
  d4_str_free(r16);
  d4_str_free(r17);
  d4_str_free(r18);
  d4_str_free(r19);
  d4_str_free(r20);
  d4_str_free(r21);
  d4_str_free(r22);
  d4_str_free(r23);
  d4_str_free(r24);
  d4_str_free(r25);
  d4_str_free(r26);
  d4_str_free(r27);
  d4_str_free(r28);
  d4_str_free(r29);

  d4_str_free(cmp10);
  d4_str_free(cmp11);
  d4_str_free(cmp12);
  d4_str_free(cmp13);
  d4_str_free(cmp14);
  d4_str_free(cmp15);
  d4_str_free(cmp16);
  d4_str_free(cmp17);
  d4_str_free(cmp18);
  d4_str_free(cmp19);
  d4_str_free(cmp20);
  d4_str_free(cmp21);
  d4_str_free(cmp22);
  d4_str_free(cmp23);
  d4_str_free(cmp24);
  d4_str_free(cmp25);
  d4_str_free(cmp26);
  d4_str_free(cmp27);
  d4_str_free(cmp28);
  d4_str_free(cmp29);
}

static void test_array_last (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v1, v2);

  ASSERT_NO_THROW(LAST1, {
    d4_str_t *l1 = d4_arr_str_last(&d4_err_state, 0, 0, &a2);
    d4_str_t *l2 = d4_arr_str_last(&d4_err_state, 0, 0, &a3);

    assert(((void) "Gets last from array with one element", d4_str_eq(v1, *l1)));
    assert(((void) "Gets last from array with two elements", d4_str_eq(v2, *l2)));
  });

  ASSERT_THROW_WITH_MESSAGE(LAST2, {
    d4_arr_str_last(&d4_err_state, 0, 0, &a1);
  }, L"tried getting last element of empty array");

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);

  d4_str_free(v1);
  d4_str_free(v2);
}

static void test_array_merge (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v2, v1);

  d4_arr_str_t r1 = d4_arr_str_alloc(0);
  d4_arr_str_t r2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t r3 = d4_arr_str_alloc(2, v2, v1);

  d4_arr_str_merge(&r1, a1);
  assert(((void) "Merges zero elements into zero elements array", r1.len == 0));
  d4_arr_str_merge(&r1, a2);
  assert(((void) "Merges one element into zero elements array", r1.len == 1));
  d4_arr_str_merge(&r1, a3);
  assert(((void) "Merges two elements into one element array", r1.len == 3));

  d4_arr_str_merge(&r2, a1);
  assert(((void) "Merges zero elements into one element array", r2.len == 1));
  d4_arr_str_merge(&r2, a2);
  assert(((void) "Merges one element into one element array", r2.len == 2));
  d4_arr_str_merge(&r2, a3);
  assert(((void) "Merges two elements into two elements array", r2.len == 4));

  d4_arr_str_merge(&r3, a1);
  assert(((void) "Merges zero elements into two elements array", r3.len == 2));
  d4_arr_str_merge(&r3, a2);
  assert(((void) "Merges one element into two elements array", r3.len == 3));
  d4_arr_str_merge(&r3, a3);
  assert(((void) "Merges two elements into three elements array", r3.len == 5));

  d4_arr_str_free(r1);
  d4_arr_str_free(r2);
  d4_arr_str_free(r3);

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);

  d4_str_free(v1);
  d4_str_free(v2);
}

static void test_array_pop (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");
  d4_str_t v3;
  d4_str_t v4;
  d4_str_t v5;

  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v1, v2);

  v3 = d4_arr_str_pop(&a2);
  assert(((void) "Pops from array with one element", (a2.len == 0 && d4_str_eq(v3, v1))));
  v4 = d4_arr_str_pop(&a3);
  assert(((void) "Pops from array with two elements", (a3.len == 1 && d4_str_eq(v4, v2))));
  v5 = d4_arr_str_pop(&a3);
  assert(((void) "Pops from array with previously two elements", (a3.len == 0 && d4_str_eq(v5, v1))));

  d4_arr_str_free(a2);
  d4_arr_str_free(a3);

  d4_str_free(v1);
  d4_str_free(v2);
  d4_str_free(v3);
  d4_str_free(v4);
  d4_str_free(v5);
}

static void test_array_push (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v2, v1);

  d4_arr_str_t r1 = d4_arr_str_alloc(0);
  d4_arr_str_t r2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t r3 = d4_arr_str_alloc(2, v2, v1);

  d4_arr_str_push(&r1, a1);
  assert(((void) "Pushes zero elements into zero elements array", r1.len == 0));
  d4_arr_str_push(&r1, a2);
  assert(((void) "Pushes one element into zero elements array", r1.len == 1));
  d4_arr_str_push(&r1, a3);
  assert(((void) "Pushes two elements into one element array", r1.len == 3));

  d4_arr_str_push(&r2, a1);
  assert(((void) "Pushes zero elements into one element array", r2.len == 1));
  d4_arr_str_push(&r2, a2);
  assert(((void) "Pushes one element into one element array", r2.len == 2));
  d4_arr_str_push(&r2, a3);
  assert(((void) "Pushes two elements into two elements array", r2.len == 4));

  d4_arr_str_push(&r3, a1);
  assert(((void) "Pushes zero elements into two elements array", r3.len == 2));
  d4_arr_str_push(&r3, a2);
  assert(((void) "Pushes one element into two elements array", r3.len == 3));
  d4_arr_str_push(&r3, a3);
  assert(((void) "Pushes two elements into three elements array", r3.len == 5));

  d4_arr_str_free(r1);
  d4_arr_str_free(r2);
  d4_arr_str_free(r3);

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);

  d4_str_free(v1);
  d4_str_free(v2);
}

static void test_array_realloc (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v1, v2);
  d4_arr_str_t a4 = d4_arr_str_alloc(0);

  a4 = d4_arr_str_realloc(a4, a1);
  assert(((void) "Re-allocates empty array with empty array", a4.len == 0));
  a4 = d4_arr_str_realloc(a4, a2);
  assert(((void) "Re-allocates empty array with one element array", a4.len == 1));
  a4 = d4_arr_str_realloc(a4, a1);
  assert(((void) "Re-allocates one element array with empty array", a4.len == 0));
  a4 = d4_arr_str_realloc(a4, a3);
  assert(((void) "Re-allocates empty array with two elements array", a4.len == 2));
  a4 = d4_arr_str_realloc(a4, a1);
  assert(((void) "Re-allocates two elements array with empty array", a4.len == 0));

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);
  d4_arr_str_free(a4);

  d4_str_free(v1);
  d4_str_free(v2);
}

static void test_array_remove (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");
  d4_str_t v3 = d4_str_alloc(L"element3");
  d4_str_t v4 = d4_str_alloc(L"element4");
  d4_str_t v5 = d4_str_alloc(L"element5");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v1, v2);
  d4_arr_str_t a4 = d4_arr_str_alloc(5, v1, v2, v3, v4, v5);

  ASSERT_THROW_WITH_MESSAGE(REMOVE1, {
    d4_arr_str_remove(&d4_err_state, 0, 0, &a3, 10);
  }, L"index 10 out of array bounds");

  ASSERT_NO_THROW(REMOVE2, {
    d4_arr_str_remove(&d4_err_state, 0, 0, &a2, 0);
    assert(((void) "Removes first element from one element array", a2.len == 0));
    d4_arr_str_remove(&d4_err_state, 0, 0, &a3, 1);
    assert(((void) "Removes seconds element from two elements array", a3.len == 1));
    d4_arr_str_remove(&d4_err_state, 0, 0, &a3, 0);
    assert(((void) "Removes first element from two elements array", a3.len == 0));
    d4_arr_str_remove(&d4_err_state, 0, 0, &a4, 2);
    assert(((void) "Removes middle element from five elements array", a4.len == 4));
    d4_arr_str_remove(&d4_err_state, 0, 0, &a4, -1);
    assert(((void) "Removes last element from five elements array", a4.len == 3));
  });

  ASSERT_THROW_WITH_MESSAGE(REMOVE3, {
    d4_arr_str_remove(&d4_err_state, 0, 0, &a1, 0);
  }, L"index 0 out of array bounds");

  ASSERT_THROW_WITH_MESSAGE(REMOVE4, {
    d4_arr_str_remove(&d4_err_state, 0, 0, &a4, -10);
  }, L"index -10 out of array bounds");

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);
  d4_arr_str_free(a4);

  d4_str_free(v1);
  d4_str_free(v2);
  d4_str_free(v3);
  d4_str_free(v4);
  d4_str_free(v5);
}

static void test_array_reverse (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v1, v2);
  d4_arr_str_t a4 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a5 = d4_arr_str_alloc(2, v2, v1);

  d4_arr_str_t r1 = d4_arr_str_reverse(a1);
  d4_arr_str_t r2 = d4_arr_str_reverse(a2);
  d4_arr_str_t r3 = d4_arr_str_reverse(a3);

  assert(((void) "Reverses empty array", d4_arr_str_eq(r1, a1)));
  assert(((void) "Reverses array with one element", d4_arr_str_eq(r2, a4)));
  assert(((void) "Reverses array with two elements", d4_arr_str_eq(r3, a5)));

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);
  d4_arr_str_free(a4);
  d4_arr_str_free(a5);

  d4_arr_str_free(r1);
  d4_arr_str_free(r2);
  d4_arr_str_free(r3);

  d4_str_free(v1);
  d4_str_free(v2);
}

static void test_array_slice (void) {
  d4_str_t v1 = d4_str_alloc(L"");
  d4_str_t v2 = d4_str_alloc(L"a");
  d4_str_t v3 = d4_str_alloc(L"lorem ipsum dolor sit amet");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v2, v1);
  d4_arr_str_t a4 = d4_arr_str_alloc(3, v1, v2, v3);

  d4_arr_str_t r10 = d4_arr_str_slice(a1, 0, 0, 0, 0);
  d4_arr_str_t r11 = d4_arr_str_slice(a1, 1, 1, 0, 0);
  d4_arr_str_t r12 = d4_arr_str_slice(a1, 1, 3, 0, 0);
  d4_arr_str_t r13 = d4_arr_str_slice(a1, 1, 10, 0, 0);
  d4_arr_str_t r14 = d4_arr_str_slice(a1, 1, -1, 0, 0);
  d4_arr_str_t r15 = d4_arr_str_slice(a1, 1, -3, 0, 0);
  d4_arr_str_t r16 = d4_arr_str_slice(a1, 1, -10, 0, 0);
  d4_arr_str_t r17 = d4_arr_str_slice(a1, 0, 0, 1, 1);
  d4_arr_str_t r18 = d4_arr_str_slice(a1, 0, 0, 1, 3);
  d4_arr_str_t r19 = d4_arr_str_slice(a1, 0, 0, 1, 10);
  d4_arr_str_t r20 = d4_arr_str_slice(a1, 0, 0, 1, -1);
  d4_arr_str_t r21 = d4_arr_str_slice(a1, 0, 0, 1, -3);
  d4_arr_str_t r22 = d4_arr_str_slice(a1, 0, 0, 1, -10);
  d4_arr_str_t r23 = d4_arr_str_slice(a1, 1, 0, 1, 1);
  d4_arr_str_t r24 = d4_arr_str_slice(a1, 1, 1, 1, 3);
  d4_arr_str_t r25 = d4_arr_str_slice(a1, 1, 3, 1, 10);
  d4_arr_str_t r26 = d4_arr_str_slice(a1, 1, 0, 1, -1);
  d4_arr_str_t r27 = d4_arr_str_slice(a1, 1, -3, 1, -1);
  d4_arr_str_t r28 = d4_arr_str_slice(a1, 1, -10, 1, -3);

  d4_arr_str_t r30 = d4_arr_str_slice(a2, 0, 0, 0, 0);
  d4_arr_str_t r31 = d4_arr_str_slice(a2, 1, 1, 0, 0);
  d4_arr_str_t r32 = d4_arr_str_slice(a2, 1, 3, 0, 0);
  d4_arr_str_t r33 = d4_arr_str_slice(a2, 1, 10, 0, 0);
  d4_arr_str_t r34 = d4_arr_str_slice(a2, 1, -1, 0, 0);
  d4_arr_str_t r35 = d4_arr_str_slice(a2, 1, -3, 0, 0);
  d4_arr_str_t r36 = d4_arr_str_slice(a2, 1, -10, 0, 0);
  d4_arr_str_t r37 = d4_arr_str_slice(a2, 0, 0, 1, 1);
  d4_arr_str_t r38 = d4_arr_str_slice(a2, 0, 0, 1, 3);
  d4_arr_str_t r39 = d4_arr_str_slice(a2, 0, 0, 1, 10);
  d4_arr_str_t r40 = d4_arr_str_slice(a2, 0, 0, 1, -1);
  d4_arr_str_t r41 = d4_arr_str_slice(a2, 0, 0, 1, -3);
  d4_arr_str_t r42 = d4_arr_str_slice(a2, 0, 0, 1, -10);
  d4_arr_str_t r43 = d4_arr_str_slice(a2, 1, 0, 1, 1);
  d4_arr_str_t r44 = d4_arr_str_slice(a2, 1, 1, 1, 3);
  d4_arr_str_t r45 = d4_arr_str_slice(a2, 1, 3, 1, 10);
  d4_arr_str_t r46 = d4_arr_str_slice(a2, 1, 0, 1, -1);
  d4_arr_str_t r47 = d4_arr_str_slice(a2, 1, -3, 1, -1);
  d4_arr_str_t r48 = d4_arr_str_slice(a2, 1, -10, 1, -3);

  d4_arr_str_t r50 = d4_arr_str_slice(a3, 0, 0, 0, 0);
  d4_arr_str_t r51 = d4_arr_str_slice(a3, 1, 1, 0, 0);
  d4_arr_str_t r52 = d4_arr_str_slice(a3, 1, 3, 0, 0);
  d4_arr_str_t r53 = d4_arr_str_slice(a3, 1, 10, 0, 0);
  d4_arr_str_t r54 = d4_arr_str_slice(a3, 1, -1, 0, 0);
  d4_arr_str_t r55 = d4_arr_str_slice(a3, 1, -3, 0, 0);
  d4_arr_str_t r56 = d4_arr_str_slice(a3, 1, -10, 0, 0);
  d4_arr_str_t r57 = d4_arr_str_slice(a3, 0, 0, 1, 1);
  d4_arr_str_t r58 = d4_arr_str_slice(a3, 0, 0, 1, 3);
  d4_arr_str_t r59 = d4_arr_str_slice(a3, 0, 0, 1, 10);
  d4_arr_str_t r60 = d4_arr_str_slice(a3, 0, 0, 1, -1);
  d4_arr_str_t r61 = d4_arr_str_slice(a3, 0, 0, 1, -3);
  d4_arr_str_t r62 = d4_arr_str_slice(a3, 0, 0, 1, -10);
  d4_arr_str_t r63 = d4_arr_str_slice(a3, 1, 0, 1, 1);
  d4_arr_str_t r64 = d4_arr_str_slice(a3, 1, 1, 1, 3);
  d4_arr_str_t r65 = d4_arr_str_slice(a3, 1, 3, 1, 10);
  d4_arr_str_t r66 = d4_arr_str_slice(a3, 1, 0, 1, -1);
  d4_arr_str_t r67 = d4_arr_str_slice(a3, 1, -3, 1, -1);
  d4_arr_str_t r68 = d4_arr_str_slice(a3, 1, -10, 1, -3);

  d4_arr_str_t r70 = d4_arr_str_slice(a4, 0, 0, 0, 0);
  d4_arr_str_t r71 = d4_arr_str_slice(a4, 1, 1, 0, 0);
  d4_arr_str_t r72 = d4_arr_str_slice(a4, 1, 3, 0, 0);
  d4_arr_str_t r73 = d4_arr_str_slice(a4, 1, 10, 0, 0);
  d4_arr_str_t r74 = d4_arr_str_slice(a4, 1, -1, 0, 0);
  d4_arr_str_t r75 = d4_arr_str_slice(a4, 1, -3, 0, 0);
  d4_arr_str_t r76 = d4_arr_str_slice(a4, 1, -10, 0, 0);
  d4_arr_str_t r77 = d4_arr_str_slice(a4, 0, 0, 1, 1);
  d4_arr_str_t r78 = d4_arr_str_slice(a4, 0, 0, 1, 3);
  d4_arr_str_t r79 = d4_arr_str_slice(a4, 0, 0, 1, 10);
  d4_arr_str_t r80 = d4_arr_str_slice(a4, 0, 0, 1, -1);
  d4_arr_str_t r81 = d4_arr_str_slice(a4, 0, 0, 1, -3);
  d4_arr_str_t r82 = d4_arr_str_slice(a4, 0, 0, 1, -10);
  d4_arr_str_t r83 = d4_arr_str_slice(a4, 1, 0, 1, 1);
  d4_arr_str_t r84 = d4_arr_str_slice(a4, 1, 1, 1, 3);
  d4_arr_str_t r85 = d4_arr_str_slice(a4, 1, 3, 1, 10);
  d4_arr_str_t r86 = d4_arr_str_slice(a4, 1, 0, 1, -1);
  d4_arr_str_t r87 = d4_arr_str_slice(a4, 1, -3, 1, -1);
  d4_arr_str_t r88 = d4_arr_str_slice(a4, 1, -10, 1, -3);

  d4_arr_str_t cmp10 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp11 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp12 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp13 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp14 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp15 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp16 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp17 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp18 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp19 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp20 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp21 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp22 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp23 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp24 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp25 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp26 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp27 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp28 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp30 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t cmp31 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp32 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp33 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp34 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t cmp35 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t cmp36 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t cmp37 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t cmp38 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t cmp39 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t cmp40 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp41 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp42 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp43 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t cmp44 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp45 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp46 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp47 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp48 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp50 = d4_arr_str_alloc(2, v2, v1);
  d4_arr_str_t cmp51 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t cmp52 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp53 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp54 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t cmp55 = d4_arr_str_alloc(2, v2, v1);
  d4_arr_str_t cmp56 = d4_arr_str_alloc(2, v2, v1);
  d4_arr_str_t cmp57 = d4_arr_str_alloc(1, v2);
  d4_arr_str_t cmp58 = d4_arr_str_alloc(2, v2, v1);
  d4_arr_str_t cmp59 = d4_arr_str_alloc(2, v2, v1);
  d4_arr_str_t cmp60 = d4_arr_str_alloc(1, v2);
  d4_arr_str_t cmp61 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp62 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp63 = d4_arr_str_alloc(1, v2);
  d4_arr_str_t cmp64 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t cmp65 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp66 = d4_arr_str_alloc(1, v2);
  d4_arr_str_t cmp67 = d4_arr_str_alloc(1, v2);
  d4_arr_str_t cmp68 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp70 = d4_arr_str_alloc(3, v1, v2, v3);
  d4_arr_str_t cmp71 = d4_arr_str_alloc(2, v2, v3);
  d4_arr_str_t cmp72 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp73 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp74 = d4_arr_str_alloc(1, v3);
  d4_arr_str_t cmp75 = d4_arr_str_alloc(3, v1, v2, v3);
  d4_arr_str_t cmp76 = d4_arr_str_alloc(3, v1, v2, v3);
  d4_arr_str_t cmp77 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t cmp78 = d4_arr_str_alloc(3, v1, v2, v3);
  d4_arr_str_t cmp79 = d4_arr_str_alloc(3, v1, v2, v3);
  d4_arr_str_t cmp80 = d4_arr_str_alloc(2, v1, v2);
  d4_arr_str_t cmp81 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp82 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp83 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t cmp84 = d4_arr_str_alloc(2, v2, v3);
  d4_arr_str_t cmp85 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp86 = d4_arr_str_alloc(2, v1, v2);
  d4_arr_str_t cmp87 = d4_arr_str_alloc(2, v1, v2);
  d4_arr_str_t cmp88 = d4_arr_str_alloc(0);

  assert(((void) "Slices zero elements array without arguments", d4_arr_str_eq(r10, cmp10)));
  assert(((void) "Slices zero elements array with start 1", d4_arr_str_eq(r11, cmp11)));
  assert(((void) "Slices zero elements array with start 3", d4_arr_str_eq(r12, cmp12)));
  assert(((void) "Slices zero elements array with start 10", d4_arr_str_eq(r13, cmp13)));
  assert(((void) "Slices zero elements array with start -1", d4_arr_str_eq(r14, cmp14)));
  assert(((void) "Slices zero elements array with start -3", d4_arr_str_eq(r15, cmp15)));
  assert(((void) "Slices zero elements array with start -10", d4_arr_str_eq(r16, cmp16)));
  assert(((void) "Slices zero elements array with end 1", d4_arr_str_eq(r17, cmp17)));
  assert(((void) "Slices zero elements array with end 3", d4_arr_str_eq(r18, cmp18)));
  assert(((void) "Slices zero elements array with end 10", d4_arr_str_eq(r19, cmp19)));
  assert(((void) "Slices zero elements array with end -1", d4_arr_str_eq(r20, cmp20)));
  assert(((void) "Slices zero elements array with end -3", d4_arr_str_eq(r21, cmp21)));
  assert(((void) "Slices zero elements array with end -10", d4_arr_str_eq(r22, cmp22)));
  assert(((void) "Slices zero elements array with start 0 and end 1", d4_arr_str_eq(r23, cmp23)));
  assert(((void) "Slices zero elements array with start 1 and end 3", d4_arr_str_eq(r24, cmp24)));
  assert(((void) "Slices zero elements array with start 3 and end 10", d4_arr_str_eq(r25, cmp25)));
  assert(((void) "Slices zero elements array with start 0 and end -1", d4_arr_str_eq(r26, cmp26)));
  assert(((void) "Slices zero elements array with start -3 and end -1", d4_arr_str_eq(r27, cmp27)));
  assert(((void) "Slices zero elements array with start -10 and end -3", d4_arr_str_eq(r28, cmp28)));
  assert(((void) "Slices one element array without arguments", d4_arr_str_eq(r30, cmp30)));
  assert(((void) "Slices one element array with start 1", d4_arr_str_eq(r31, cmp31)));
  assert(((void) "Slices one element array with start 3", d4_arr_str_eq(r32, cmp32)));
  assert(((void) "Slices one element array with start 10", d4_arr_str_eq(r33, cmp33)));
  assert(((void) "Slices one element array with start -1", d4_arr_str_eq(r34, cmp34)));
  assert(((void) "Slices one element array with start -3", d4_arr_str_eq(r35, cmp35)));
  assert(((void) "Slices one element array with start -10", d4_arr_str_eq(r36, cmp36)));
  assert(((void) "Slices one element array with end 1", d4_arr_str_eq(r37, cmp37)));
  assert(((void) "Slices one element array with end 3", d4_arr_str_eq(r38, cmp38)));
  assert(((void) "Slices one element array with end 10", d4_arr_str_eq(r39, cmp39)));
  assert(((void) "Slices one element array with end -1", d4_arr_str_eq(r40, cmp40)));
  assert(((void) "Slices one element array with end -3", d4_arr_str_eq(r41, cmp41)));
  assert(((void) "Slices one element array with end -10", d4_arr_str_eq(r42, cmp42)));
  assert(((void) "Slices one element array with start 0 and end 1", d4_arr_str_eq(r43, cmp43)));
  assert(((void) "Slices one element array with start 1 and end 3", d4_arr_str_eq(r44, cmp44)));
  assert(((void) "Slices one element array with start 3 and end 10", d4_arr_str_eq(r45, cmp45)));
  assert(((void) "Slices one element array with start 0 and end -1", d4_arr_str_eq(r46, cmp46)));
  assert(((void) "Slices one element array with start -3 and end -1", d4_arr_str_eq(r47, cmp47)));
  assert(((void) "Slices one element array with start -10 and end -3", d4_arr_str_eq(r48, cmp48)));
  assert(((void) "Slices two elements array without arguments", d4_arr_str_eq(r50, cmp50)));
  assert(((void) "Slices two elements array with start 1", d4_arr_str_eq(r51, cmp51)));
  assert(((void) "Slices two elements array with start 3", d4_arr_str_eq(r52, cmp52)));
  assert(((void) "Slices two elements array with start 10", d4_arr_str_eq(r53, cmp53)));
  assert(((void) "Slices two elements array with start -1", d4_arr_str_eq(r54, cmp54)));
  assert(((void) "Slices two elements array with start -3", d4_arr_str_eq(r55, cmp55)));
  assert(((void) "Slices two elements array with start -10", d4_arr_str_eq(r56, cmp56)));
  assert(((void) "Slices two elements array with end 1", d4_arr_str_eq(r57, cmp57)));
  assert(((void) "Slices two elements array with end 3", d4_arr_str_eq(r58, cmp58)));
  assert(((void) "Slices two elements array with end 10", d4_arr_str_eq(r59, cmp59)));
  assert(((void) "Slices two elements array with end -1", d4_arr_str_eq(r60, cmp60)));
  assert(((void) "Slices two elements array with end -3", d4_arr_str_eq(r61, cmp61)));
  assert(((void) "Slices two elements array with end -10", d4_arr_str_eq(r62, cmp62)));
  assert(((void) "Slices two elements array with start 0 and end 1", d4_arr_str_eq(r63, cmp63)));
  assert(((void) "Slices two elements array with start 1 and end 3", d4_arr_str_eq(r64, cmp64)));
  assert(((void) "Slices two elements array with start 3 and end 10", d4_arr_str_eq(r65, cmp65)));
  assert(((void) "Slices two elements array with start 0 and end -1", d4_arr_str_eq(r66, cmp66)));
  assert(((void) "Slices two elements array with start -3 and end -1", d4_arr_str_eq(r67, cmp67)));
  assert(((void) "Slices two elements array with start -10 and end -3", d4_arr_str_eq(r68, cmp68)));
  assert(((void) "Slices three elements array without arguments", d4_arr_str_eq(r70, cmp70)));
  assert(((void) "Slices three elements array with start 1", d4_arr_str_eq(r71, cmp71)));
  assert(((void) "Slices three elements array with start 3", d4_arr_str_eq(r72, cmp72)));
  assert(((void) "Slices three elements array with start 10", d4_arr_str_eq(r73, cmp73)));
  assert(((void) "Slices three elements array with start -1", d4_arr_str_eq(r74, cmp74)));
  assert(((void) "Slices three elements array with start -3", d4_arr_str_eq(r75, cmp75)));
  assert(((void) "Slices three elements array with start -10", d4_arr_str_eq(r76, cmp76)));
  assert(((void) "Slices three elements array with end 1", d4_arr_str_eq(r77, cmp77)));
  assert(((void) "Slices three elements array with end 3", d4_arr_str_eq(r78, cmp78)));
  assert(((void) "Slices three elements array with end 10", d4_arr_str_eq(r79, cmp79)));
  assert(((void) "Slices three elements array with end -1", d4_arr_str_eq(r80, cmp80)));
  assert(((void) "Slices three elements array with end -3", d4_arr_str_eq(r81, cmp81)));
  assert(((void) "Slices three elements array with end -10", d4_arr_str_eq(r82, cmp82)));
  assert(((void) "Slices three elements array with start 0 and end 1", d4_arr_str_eq(r83, cmp83)));
  assert(((void) "Slices three elements array with start 1 and end 3", d4_arr_str_eq(r84, cmp84)));
  assert(((void) "Slices three elements array with start 3 and end 10", d4_arr_str_eq(r85, cmp85)));
  assert(((void) "Slices three elements array with start 0 and end -1", d4_arr_str_eq(r86, cmp86)));
  assert(((void) "Slices three elements array with start -3 and end -1", d4_arr_str_eq(r87, cmp87)));
  assert(((void) "Slices three elements array with start -10 and end -3", d4_arr_str_eq(r88, cmp88)));

  d4_str_free(v1);
  d4_str_free(v2);
  d4_str_free(v3);

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);
  d4_arr_str_free(a4);

  d4_arr_str_free(r10);
  d4_arr_str_free(r11);
  d4_arr_str_free(r12);
  d4_arr_str_free(r13);
  d4_arr_str_free(r14);
  d4_arr_str_free(r15);
  d4_arr_str_free(r16);
  d4_arr_str_free(r17);
  d4_arr_str_free(r18);
  d4_arr_str_free(r19);
  d4_arr_str_free(r20);
  d4_arr_str_free(r21);
  d4_arr_str_free(r22);
  d4_arr_str_free(r23);
  d4_arr_str_free(r24);
  d4_arr_str_free(r25);
  d4_arr_str_free(r26);
  d4_arr_str_free(r27);
  d4_arr_str_free(r28);
  d4_arr_str_free(r30);
  d4_arr_str_free(r31);
  d4_arr_str_free(r32);
  d4_arr_str_free(r33);
  d4_arr_str_free(r34);
  d4_arr_str_free(r35);
  d4_arr_str_free(r36);
  d4_arr_str_free(r37);
  d4_arr_str_free(r38);
  d4_arr_str_free(r39);
  d4_arr_str_free(r40);
  d4_arr_str_free(r41);
  d4_arr_str_free(r42);
  d4_arr_str_free(r43);
  d4_arr_str_free(r44);
  d4_arr_str_free(r45);
  d4_arr_str_free(r46);
  d4_arr_str_free(r47);
  d4_arr_str_free(r48);
  d4_arr_str_free(r50);
  d4_arr_str_free(r51);
  d4_arr_str_free(r52);
  d4_arr_str_free(r53);
  d4_arr_str_free(r54);
  d4_arr_str_free(r55);
  d4_arr_str_free(r56);
  d4_arr_str_free(r57);
  d4_arr_str_free(r58);
  d4_arr_str_free(r59);
  d4_arr_str_free(r60);
  d4_arr_str_free(r61);
  d4_arr_str_free(r62);
  d4_arr_str_free(r63);
  d4_arr_str_free(r64);
  d4_arr_str_free(r65);
  d4_arr_str_free(r66);
  d4_arr_str_free(r67);
  d4_arr_str_free(r68);
  d4_arr_str_free(r70);
  d4_arr_str_free(r71);
  d4_arr_str_free(r72);
  d4_arr_str_free(r73);
  d4_arr_str_free(r74);
  d4_arr_str_free(r75);
  d4_arr_str_free(r76);
  d4_arr_str_free(r77);
  d4_arr_str_free(r78);
  d4_arr_str_free(r79);
  d4_arr_str_free(r80);
  d4_arr_str_free(r81);
  d4_arr_str_free(r82);
  d4_arr_str_free(r83);
  d4_arr_str_free(r84);
  d4_arr_str_free(r85);
  d4_arr_str_free(r86);
  d4_arr_str_free(r87);
  d4_arr_str_free(r88);

  d4_arr_str_free(cmp10);
  d4_arr_str_free(cmp11);
  d4_arr_str_free(cmp12);
  d4_arr_str_free(cmp13);
  d4_arr_str_free(cmp14);
  d4_arr_str_free(cmp15);
  d4_arr_str_free(cmp16);
  d4_arr_str_free(cmp17);
  d4_arr_str_free(cmp18);
  d4_arr_str_free(cmp19);
  d4_arr_str_free(cmp20);
  d4_arr_str_free(cmp21);
  d4_arr_str_free(cmp22);
  d4_arr_str_free(cmp23);
  d4_arr_str_free(cmp24);
  d4_arr_str_free(cmp25);
  d4_arr_str_free(cmp26);
  d4_arr_str_free(cmp27);
  d4_arr_str_free(cmp28);
  d4_arr_str_free(cmp30);
  d4_arr_str_free(cmp31);
  d4_arr_str_free(cmp32);
  d4_arr_str_free(cmp33);
  d4_arr_str_free(cmp34);
  d4_arr_str_free(cmp35);
  d4_arr_str_free(cmp36);
  d4_arr_str_free(cmp37);
  d4_arr_str_free(cmp38);
  d4_arr_str_free(cmp39);
  d4_arr_str_free(cmp40);
  d4_arr_str_free(cmp41);
  d4_arr_str_free(cmp42);
  d4_arr_str_free(cmp43);
  d4_arr_str_free(cmp44);
  d4_arr_str_free(cmp45);
  d4_arr_str_free(cmp46);
  d4_arr_str_free(cmp47);
  d4_arr_str_free(cmp48);
  d4_arr_str_free(cmp50);
  d4_arr_str_free(cmp51);
  d4_arr_str_free(cmp52);
  d4_arr_str_free(cmp53);
  d4_arr_str_free(cmp54);
  d4_arr_str_free(cmp55);
  d4_arr_str_free(cmp56);
  d4_arr_str_free(cmp57);
  d4_arr_str_free(cmp58);
  d4_arr_str_free(cmp59);
  d4_arr_str_free(cmp60);
  d4_arr_str_free(cmp61);
  d4_arr_str_free(cmp62);
  d4_arr_str_free(cmp63);
  d4_arr_str_free(cmp64);
  d4_arr_str_free(cmp65);
  d4_arr_str_free(cmp66);
  d4_arr_str_free(cmp67);
  d4_arr_str_free(cmp68);
  d4_arr_str_free(cmp70);
  d4_arr_str_free(cmp71);
  d4_arr_str_free(cmp72);
  d4_arr_str_free(cmp73);
  d4_arr_str_free(cmp74);
  d4_arr_str_free(cmp75);
  d4_arr_str_free(cmp76);
  d4_arr_str_free(cmp77);
  d4_arr_str_free(cmp78);
  d4_arr_str_free(cmp79);
  d4_arr_str_free(cmp80);
  d4_arr_str_free(cmp81);
  d4_arr_str_free(cmp82);
  d4_arr_str_free(cmp83);
  d4_arr_str_free(cmp84);
  d4_arr_str_free(cmp85);
  d4_arr_str_free(cmp86);
  d4_arr_str_free(cmp87);
  d4_arr_str_free(cmp88);
}

static void test_array_sort (void) {
  d4_str_t sort_asc_name = d4_str_alloc(L"asc");
  d4_str_t sort_desc_name = d4_str_alloc(L"desc");

  d4_fn_esFP3strFP3strFRintFE_t sort_asc = d4_fn_esFP3strFP3strFRintFE_alloc(
    sort_asc_name,
    NULL,
    NULL,
    NULL,
    (int32_t (*) (void *, void *)) sort_asc_str
  );

  d4_fn_esFP3strFP3strFRintFE_t sort_desc = d4_fn_esFP3strFP3strFRintFE_alloc(
    sort_desc_name,
    NULL,
    NULL,
    NULL,
    (int32_t (*) (void *, void *)) sort_desc_str
  );

  d4_str_t v1 = d4_str_alloc(L"");
  d4_str_t v2 = d4_str_alloc(L"a");
  d4_str_t v3 = d4_str_alloc(L"orange");
  d4_str_t v4 = d4_str_alloc(L"lorem ipsum dolor sit amet");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_str_t a2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a3 = d4_arr_str_alloc(2, v1, v2);
  d4_arr_str_t a4 = d4_arr_str_alloc(3, v1, v3, v2);
  d4_arr_str_t a5 = d4_arr_str_alloc(4, v1, v3, v4, v2);
  d4_arr_str_t a6 = d4_arr_str_alloc(8, v4, v1, v2, v3, v3, v2, v4, v1);

  d4_arr_str_t cmp1 = d4_arr_str_alloc(0);
  d4_arr_str_t cmp2 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t cmp3 = d4_arr_str_alloc(2, v1, v2);
  d4_arr_str_t cmp4 = d4_arr_str_alloc(3, v1, v2, v3);
  d4_arr_str_t cmp5 = d4_arr_str_alloc(4, v1, v2, v4, v3);
  d4_arr_str_t cmp6 = d4_arr_str_alloc(8, v1, v1, v2, v2, v4, v4, v3, v3);
  d4_arr_str_t cmp7 = d4_arr_str_alloc(2, v2, v1);
  d4_arr_str_t cmp8 = d4_arr_str_alloc(3, v3, v2, v1);
  d4_arr_str_t cmp9 = d4_arr_str_alloc(4, v3, v4, v2, v1);
  d4_arr_str_t cmp10 = d4_arr_str_alloc(8, v3, v3, v4, v4, v2, v2, v1, v1);

  ASSERT_NO_THROW(FOREACH1, {
    d4_arr_str_sort(&d4_err_state, 0, 0, &a1, sort_asc);
    d4_arr_str_sort(&d4_err_state, 0, 0, &a2, sort_asc);
    d4_arr_str_sort(&d4_err_state, 0, 0, &a3, sort_asc);
    d4_arr_str_sort(&d4_err_state, 0, 0, &a4, sort_asc);
    d4_arr_str_sort(&d4_err_state, 0, 0, &a5, sort_asc);
    d4_arr_str_sort(&d4_err_state, 0, 0, &a6, sort_asc);

    assert(((void) "Sorts ASC empty array", d4_arr_str_eq(a1, cmp1)));
    assert(((void) "Sorts ASC one element array", d4_arr_str_eq(a2, cmp2)));
    assert(((void) "Sorts ASC two elements array", d4_arr_str_eq(a3, cmp3)));
    assert(((void) "Sorts ASC three elements array", d4_arr_str_eq(a4, cmp4)));
    assert(((void) "Sorts ASC four elements array", d4_arr_str_eq(a5, cmp5)));
    assert(((void) "Sorts ASC eight elements array", d4_arr_str_eq(a6, cmp6)));

    d4_arr_str_sort(&d4_err_state, 0, 0, &a1, sort_desc);
    d4_arr_str_sort(&d4_err_state, 0, 0, &a2, sort_desc);
    d4_arr_str_sort(&d4_err_state, 0, 0, &a3, sort_desc);
    d4_arr_str_sort(&d4_err_state, 0, 0, &a4, sort_desc);
    d4_arr_str_sort(&d4_err_state, 0, 0, &a5, sort_desc);
    d4_arr_str_sort(&d4_err_state, 0, 0, &a6, sort_desc);

    assert(((void) "Sorts DESC empty array", d4_arr_str_eq(a1, cmp1)));
    assert(((void) "Sorts DESC one element array", d4_arr_str_eq(a2, cmp2)));
    assert(((void) "Sorts DESC two elements array", d4_arr_str_eq(a3, cmp7)));
    assert(((void) "Sorts DESC three elements array", d4_arr_str_eq(a4, cmp8)));
    assert(((void) "Sorts DESC four elements array", d4_arr_str_eq(a5, cmp9)));
    assert(((void) "Sorts DESC eight elements array", d4_arr_str_eq(a6, cmp10)));
  });

  d4_str_free(sort_asc_name);
  d4_str_free(sort_desc_name);

  d4_fn_esFP3strFP3strFRintFE_free(sort_asc);
  d4_fn_esFP3strFP3strFRintFE_free(sort_desc);

  d4_str_free(v1);
  d4_str_free(v2);
  d4_str_free(v3);
  d4_str_free(v4);

  d4_arr_str_free(a1);
  d4_arr_str_free(a2);
  d4_arr_str_free(a3);
  d4_arr_str_free(a4);
  d4_arr_str_free(a5);
  d4_arr_str_free(a6);

  d4_arr_str_free(cmp1);
  d4_arr_str_free(cmp2);
  d4_arr_str_free(cmp3);
  d4_arr_str_free(cmp4);
  d4_arr_str_free(cmp5);
  d4_arr_str_free(cmp6);
  d4_arr_str_free(cmp7);
  d4_arr_str_free(cmp8);
  d4_arr_str_free(cmp9);
  d4_arr_str_free(cmp10);
}

static void test_array_str (void) {
  d4_str_t v1 = d4_str_alloc(L"element1");
  d4_str_t v2 = d4_str_alloc(L"element2");

  d4_arr_str_t a1 = d4_arr_str_alloc(0);
  d4_arr_int_t a2 = d4_arr_int_alloc(1, 10);
  d4_arr_int_t a3 = d4_arr_int_alloc(2, 20, 30);
  d4_arr_str_t a4 = d4_arr_str_alloc(1, v1);
  d4_arr_str_t a5 = d4_arr_str_alloc(2, v1, v2);

  d4_str_t r1 = d4_arr_str_str(a1);
  d4_str_t r2 = d4_arr_int_str(a2);
  d4_str_t r3 = d4_arr_int_str(a3);
  d4_str_t r4 = d4_arr_str_str(a4);
  d4_str_t r5 = d4_arr_str_str(a5);

  d4_str_t cmp1 = d4_str_alloc(L"[]");
  d4_str_t cmp2 = d4_str_alloc(L"[10]");
  d4_str_t cmp3 = d4_str_alloc(L"[20, 30]");
  d4_str_t cmp4 = d4_str_alloc(L"[element1]");
  d4_str_t cmp5 = d4_str_alloc(L"[element1, element2]");

  assert(((void) "Stringifies string array with zero elements", d4_str_eq(r1, cmp1)));
  assert(((void) "Stringifies int array with one element", d4_str_eq(r2, cmp2)));
  assert(((void) "Stringifies int array with two elements", d4_str_eq(r3, cmp3)));
  assert(((void) "Stringifies string array with one element", d4_str_eq(r4, cmp4)));
  assert(((void) "Stringifies string array with two elements", d4_str_eq(r5, cmp5)));

  d4_str_free(cmp1);
  d4_str_free(cmp2);
  d4_str_free(cmp3);
  d4_str_free(cmp4);
  d4_str_free(cmp5);

  d4_str_free(r1);
  d4_str_free(r2);
  d4_str_free(r3);
  d4_str_free(r4);
  d4_str_free(r5);

  d4_arr_str_free(a1);
  d4_arr_int_free(a2);
  d4_arr_int_free(a3);
  d4_arr_str_free(a4);
  d4_arr_str_free(a5);

  d4_str_free(v1);
  d4_str_free(v2);
}

int main (void) {
  test_array_alloc();
  test_array_at();
  test_array_clear();
  test_array_concat();
  test_array_contains();
  test_array_copy();
  test_array_empty();
  test_array_eq();
  test_array_filter();
  test_array_first();
  test_array_forEach();
  test_array_free();
  test_array_join();
  test_array_last();
  test_array_merge();
  test_array_pop();
  test_array_push();
  test_array_realloc();
  test_array_remove();
  test_array_reverse();
  test_array_slice();
  test_array_sort();
  test_array_str();
}
