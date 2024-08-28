/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "globals.h"
#include <d4/array.h>
#include <d4/macro.h>
#include <stdio.h>
#include "string.h"

D4_ARRAY_DEFINE(any, d4_any_t, d4_any_t, d4_any_copy(element), d4_any_eq(lhs_element, rhs_element), d4_any_free(element), d4_any_str(element))
D4_FUNCTION_DEFINE_WITH_PARAMS(s, void, void, FP4arr_anyFP1strFP1strFP1str)

#if defined(D4_OS_WINDOWS)
  #define PRINT_FUNC_TERMINATOR L"\r\n"
  #define PRINT_FUNC_TERMINATOR_LEN 2
#else
  #define PRINT_FUNC_TERMINATOR L"\n"
  #define PRINT_FUNC_TERMINATOR_LEN 1
#endif

static void print_func (D4_UNUSED void *ctx, void *params) {
  d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t *p = params;
  d4_str_t separator = p->o1 == 0 ? (d4_str_t) {L" ", 1, true} : p->n1;
  d4_str_t terminator = p->o2 == 0 ? (d4_str_t) {PRINT_FUNC_TERMINATOR, PRINT_FUNC_TERMINATOR_LEN, true} : p->n2;
  FILE *stream = d4_str_eq(p->n3, (d4_str_t) {L"stderr", 6, true}) ? stderr : stdout;
  d4_str_t result = d4_str_empty_val;

  for (size_t i = 0; i < p->n0.len; i++) {
    d4_str_t param_str = d4_any_str(p->n0.data[i]);
    if (i != 0) result = d4_str_realloc(result, d4_str_concat(result, separator));
    result = d4_str_realloc(result, d4_str_concat(result, param_str));
  }

  result = d4_str_realloc(result, d4_str_concat(result, terminator));
  fwprintf(stream, result.data);
  d4_str_free(result);
}

d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_t d4_print = {
  {L"print", 4, true},
  NULL,
  NULL,
  NULL,
  print_func
};
