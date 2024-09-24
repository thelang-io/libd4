/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <d4/macro.h>
#include <d4/number.h>
#include <assert.h>
#include <stdio.h>
#include "../src/globals.h"
#include "utils.h"

#define TYPE_int 1
#define TYPE_str 2

D4_ANY_DECLARE(int, int32_t)
D4_ANY_DEFINE(TYPE_int, int, int32_t, val, lhs_val == rhs_val, (void) val, d4_i32_str(val))

D4_ANY_DECLARE(str, d4_str_t)
D4_ANY_DEFINE(TYPE_str, str, d4_str_t, d4_str_copy(val), d4_str_eq(lhs_val, rhs_val), d4_str_free(val), d4_str_copy(val))

static void test_globals_print (void) {
  char *path = "globals-test.txt";
  d4_str_t file_content;

  d4_str_t s_e = d4_str_alloc(L"");
  d4_str_t s_comma = d4_str_alloc(L",");
  d4_str_t s_stdout = d4_str_alloc(L"stdout");
  d4_str_t s_stderr = d4_str_alloc(L"stderr");
  d4_str_t s_string = d4_str_alloc(L"string");
  d4_str_t result = d4_str_alloc(D4_EOL L"10 string" D4_EOL L"10,string");

  d4_any_t i1 = d4_any_int_alloc(10);
  d4_any_t i2 = d4_any_str_alloc(s_string);

  d4_arr_any_t items1 = d4_arr_any_alloc(0);
  d4_arr_any_t items2 = d4_arr_any_alloc(2, i1, i2);

  FILE *f = freopen(path, "w", stdout);
  void *params;

  d4_print.func(
    d4_print.ctx,
    params = d4_safe_calloc(
      &(d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t) {
        items1,
        0, s_e,
        0, s_e,
        0, s_e
      },
      sizeof(d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t)
    )
  );

  d4_safe_free(params);

  d4_print.func(
    d4_print.ctx,
    params = d4_safe_calloc(
      &(d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t) {
        items2,
        0, s_e,
        0, s_e,
        0, s_e
      },
      sizeof(d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t)
    )
  );

  d4_safe_free(params);

  d4_print.func(
    d4_print.ctx,
    params = d4_safe_calloc(
      &(d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t) {
        items2,
        1, s_comma,
        1, s_e,
        1, s_stdout
      },
      sizeof(d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t)
    )
  );

  d4_safe_free(params);

  fclose(f);
  file_content = read_unicode_file(path);
  remove(path);
  assert(((void) "Output is correct for stdout", d4_str_eq(file_content, result)));
  d4_str_free(file_content);

  f = freopen(path, "w", stderr);

  d4_print.func(
    d4_print.ctx,
    params = d4_safe_calloc(
      &(d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t) {
        items1,
        0, s_e,
        0, s_e,
        1, s_stderr
      },
      sizeof(d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t)
    )
  );

  d4_safe_free(params);

  d4_print.func(
    d4_print.ctx,
    params = d4_safe_calloc(
      &(d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t) {
        items2,
        0, s_e,
        0, s_e,
        1, s_stderr
      },
      sizeof(d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t)
    )
  );

  d4_safe_free(params);

  d4_print.func(
    d4_print.ctx,
    params = d4_safe_calloc(
      &(d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t) {
        items2,
        1, s_comma,
        1, s_e,
        1, s_stderr
      },
      sizeof(d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t)
    )
  );

  d4_safe_free(params);

  fclose(f);
  file_content = read_unicode_file(path);
  remove(path);
  assert(((void) "Output is correct for stderr", d4_str_eq(file_content, result)));
  d4_str_free(file_content);

  d4_arr_any_free(items1);
  d4_arr_any_free(items2);

  d4_any_free(i1);
  d4_any_free(i2);

  d4_str_free(s_comma);
  d4_str_free(s_stderr);
  d4_str_free(s_stdout);
  d4_str_free(s_string);
  d4_str_free(s_e);

  d4_str_free(result);
}

static void print_custom (void) {
}

static void test_globals_print_custom (void) {
  d4_str_t print_name = d4_str_alloc(L"print");

  d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_t print = d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_alloc(
    print_name,
    NULL,
    NULL,
    NULL,
    (void (*)(void *, void *)) print_custom
  );

  d4_str_t print_str = d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_str(print);

  d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_t print2 = d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_copy(print);
  print2 = d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_realloc(print2, print);

  assert(((void) "Custom print functions are equal", d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_eq(print, print2)));
  assert(((void) "Custom print str is its name", d4_str_eq(print_str, print_name)));

  d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_free(print);
  d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_free(print2);

  d4_str_free(print_name);
  d4_str_free(print_str);
}

int main (void) {
  test_globals_print();
  test_globals_print_custom();
}
