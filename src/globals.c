/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <d4/macro.h>
#include "globals.h"
#include <d4/array.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#if defined(D4_OS_WINDOWS)
  #include <fcntl.h>
  #include <io.h>
#else
  #include <unistd.h>
#endif

D4_ARRAY_DEFINE(any, d4_any_t, d4_any_t, d4_any_copy(element), d4_any_eq(lhs_element, rhs_element), d4_any_free(element), d4_any_str(element))
D4_FUNCTION_DEFINE_WITH_PARAMS(s, void, void, FP4arr_anyFP1strFP1strFP1str)

static void print_func (D4_UNUSED void *ctx, void *params) {
  d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t *p = params;
  d4_str_t separator = p->o1 == 0 ? (d4_str_t) {L" ", 1, true} : p->n1;
  d4_str_t terminator = p->o2 == 0 ? (d4_str_t) {D4_EOL, D4_EOL_LEN, true} : p->n2;
  FILE *stream = d4_str_eq(p->n3, (d4_str_t) {L"stderr", 6, true}) ? stderr : stdout;
  int stream_fd = fileno(stream);
  d4_str_t result = d4_str_empty_val;
  d4_str_t t1;
  size_t buf_len;
  char *buf;

  for (size_t i = 0; i < p->n0.len; i++) {
    d4_str_t param_str = d4_any_str(p->n0.data[i]);
    if (i != 0) {
      result = d4_str_realloc(result, t1 = d4_str_concat(result, separator));
      d4_str_free(t1);
    }
    result = d4_str_realloc(result, t1 = d4_str_concat(result, param_str));
    d4_str_free(t1);
    d4_str_free(param_str);
  }

  result = d4_str_realloc(result, t1 = d4_str_concat(result, terminator));
  d4_str_free(t1);

  buf_len = wcstombs(NULL, result.data, 0) + 1;
  buf = d4_safe_alloc(buf_len);
  wcstombs(buf, result.data, buf_len);

  #if defined(D4_OS_WINDOWS)
    _setmode(stream_fd, _O_BINARY);
    _write(stream_fd, buf, result.len);
    _setmode(stream_fd, _O_TEXT);
  #else
    write(stream_fd, buf, result.len);
  #endif

  d4_safe_free(buf);
  d4_str_free(result);
}

d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_t d4_print = {
  {L"print", 4, true},
  NULL,
  NULL,
  NULL,
  print_func
};
