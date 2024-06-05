/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/macro.h>
#include <the/number.h>
#include <assert.h>
#include "../src/globals.h"
#include "utils.h"

#define TYPE_int 1
#define TYPE_str 2

THE_ANY_DECLARE(int, int32_t)
THE_ANY_DEFINE(TYPE_int, int, int32_t, val, lhs_val == rhs_val, (void) val, the_i32_str(val))

THE_ANY_DECLARE(str, the_str_t)
THE_ANY_DEFINE(TYPE_str, str, the_str_t, the_str_copy(val), the_str_eq(lhs_val, rhs_val), the_str_free(val), the_str_copy(val))

static void test_globals_print (void) {
  char *path = "globals-test.txt";
  the_str_t file_content;

  the_str_t s_e = the_str_alloc(L"");
  the_str_t s_comma = the_str_alloc(L",");
  the_str_t s_stdout = the_str_alloc(L"stdout");
  the_str_t s_stderr = the_str_alloc(L"stderr");
  the_str_t s_string = the_str_alloc(L"string");
  the_str_t result = the_str_alloc(THE_EOL L"10 string" THE_EOL L"10,string");

  the_any_t i1 = the_any_int_alloc(10);
  the_any_t i2 = the_any_str_alloc(s_string);

  the_arr_any_t items1 = the_arr_any_alloc(0);
  the_arr_any_t items2 = the_arr_any_alloc(2, i1, i2);

  FILE *f = freopen(path, "w", stdout);

  the_print.func(
    the_print.ctx,
    the_safe_calloc(
      &(the_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t) {
        items1,
        0, s_e,
        0, s_e,
        0, s_e
      },
      sizeof(the_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t)
    )
  );

  the_print.func(
    the_print.ctx,
    the_safe_calloc(
      &(the_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t) {
        items2,
        0, s_e,
        0, s_e,
        0, s_e
      },
      sizeof(the_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t)
    )
  );

  the_print.func(
    the_print.ctx,
    the_safe_calloc(
      &(the_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t) {
        items2,
        1, s_comma,
        1, s_e,
        1, s_stdout
      },
      sizeof(the_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t)
    )
  );

  fclose(f);
  file_content = read_unicode_file(path);
  remove(path);
  assert(((void) "Output is correct for stdout", the_str_eq(file_content, result)));
  the_str_free(file_content);

  f = freopen(path, "w", stderr);

  the_print.func(
    the_print.ctx,
    the_safe_calloc(
      &(the_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t) {
        items1,
        0, s_e,
        0, s_e,
        1, s_stderr
      },
      sizeof(the_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t)
    )
  );

  the_print.func(
    the_print.ctx,
    the_safe_calloc(
      &(the_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t) {
        items2,
        0, s_e,
        0, s_e,
        1, s_stderr
      },
      sizeof(the_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t)
    )
  );

  the_print.func(
    the_print.ctx,
    the_safe_calloc(
      &(the_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t) {
        items2,
        1, s_comma,
        1, s_e,
        1, s_stderr
      },
      sizeof(the_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t)
    )
  );

  fclose(f);
  file_content = read_unicode_file(path);
  remove(path);
  assert(((void) "Output is correct for stderr", the_str_eq(file_content, result)));
  the_str_free(file_content);

  the_arr_any_free(items1);
  the_arr_any_free(items2);

  the_any_free(i1);
  the_any_free(i2);

  the_str_free(s_comma);
  the_str_free(s_stderr);
  the_str_free(s_stdout);
  the_str_free(s_e);

  the_str_free(result);
}

int main (void) {
  test_globals_print();
}
