/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "globals.h"
#include <the/array.h>
#include <the/macro.h>
#include <stdio.h>
#include "string.h"

THE_ARRAY_DEFINE(any, the_any_t, the_any_t, the_any_copy(element), the_any_eq(lhs_element, rhs_element), the_any_free(element), the_any_str(element))
THE_FUNCTION_DEFINE_WITH_PARAMS(s, void, void, FP4arr_anyFP1strFP1strFP1str)

#if defined(THE_OS_WINDOWS)
  #define PRINT_FUNC_TERMINATOR L"\r\n"
  #define PRINT_FUNC_TERMINATOR_LEN 2
#else
  #define PRINT_FUNC_TERMINATOR L"\n"
  #define PRINT_FUNC_TERMINATOR_LEN 1
#endif

static void print_func (THE_UNUSED void *ctx, void *params) {
  the_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t *p = params;
  the_str_t separator = p->o1 == 0 ? (the_str_t) {L" ", 1, true} : p->n1;
  the_str_t terminator = p->o2 == 0 ? (the_str_t) {PRINT_FUNC_TERMINATOR, PRINT_FUNC_TERMINATOR_LEN, true} : p->n2;
  FILE *stream = the_str_eq(p->n3, (the_str_t) {L"stderr", 6, true}) ? stderr : stdout;
  the_str_t result = the_str_empty_val;

  for (size_t i = 0; i < p->n0.len; i++) {
    the_str_t param_str = the_any_str(p->n0.data[i]);
    if (i != 0) result = the_str_realloc(result, the_str_concat(result, separator));
    result = the_str_realloc(result, the_str_concat(result, param_str));
  }

  result = the_str_realloc(result, the_str_concat(result, terminator));
  the_str_free(separator);
  the_str_free(terminator);
  fwprintf(stream, result.data);
  the_str_free(result);
}

the_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_t the_print = {
  (the_str_t) {L"print", 4, true},
  NULL,
  NULL,
  NULL,
  print_func
};
