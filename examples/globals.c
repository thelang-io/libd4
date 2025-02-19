/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "../include/d4/globals.h"
#include "../include/d4/number.h"

#define TYPE_int 1
#define TYPE_str 2

D4_ANY_DECLARE(int, int32_t)
D4_ANY_DEFINE(TYPE_int, int, int32_t, val, lhs_val == rhs_val, (void) val, d4_i32_str(val))

D4_ANY_DECLARE(str, d4_str_t)
D4_ANY_DEFINE(TYPE_str, str, d4_str_t, d4_str_copy(val), d4_str_eq(lhs_val, rhs_val), d4_str_free(val), d4_str_copy(val))

int main (void) {
  d4_str_t s_e = d4_str_alloc(L"");
  d4_str_t s_comma = d4_str_alloc(L",");
  d4_str_t s_stdout = d4_str_alloc(L"stdout");
  d4_str_t s_stderr = d4_str_alloc(L"stderr");
  d4_str_t s_string = d4_str_alloc(L"string");

  d4_any_t i1 = d4_any_int_alloc(10);
  d4_any_t i2 = d4_any_str_alloc(s_string);

  d4_arr_any_t items1 = d4_arr_any_alloc(0);
  d4_arr_any_t items2 = d4_arr_any_alloc(2, i1, i2);

  d4_print.func(
    d4_print.ctx,
    d4_safe_calloc(
      &(d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t) {
        items1,
        0, s_e,
        0, s_e,
        0, s_e
      },
      sizeof(d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t)
    )
  );

  d4_print.func(
    d4_print.ctx,
    d4_safe_calloc(
      &(d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t) {
        items2,
        1, s_comma,
        1, s_e,
        1, s_stderr
      },
      sizeof(d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t)
    )
  );

  d4_arr_any_free(items1);
  d4_arr_any_free(items2);

  d4_any_free(i1);
  d4_any_free(i2);

  d4_str_free(s_comma);
  d4_str_free(s_stderr);
  d4_str_free(s_stdout);
  d4_str_free(s_e);

  return 0;
}
