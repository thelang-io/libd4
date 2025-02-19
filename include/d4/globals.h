/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef D4_GLOBALS_H
#define D4_GLOBALS_H

/* See https://github.com/thelang-io/libd4 for reference. */

#include "any.h"
#include "fn.h"

D4_ARRAY_DECLARE(any, d4_any_t)

D4_FUNCTION_DECLARE_WITH_PARAMS(s, void, void, FP4arr_anyFP1strFP1strFP1str, {
  d4_arr_any_t n0;
  unsigned char o1;
  d4_str_t n1;
  unsigned char o2;
  d4_str_t n2;
  unsigned char o3;
  d4_str_t n3;
})

/**
 * Global function that writes the textual representations of the given items into the given output stream.
 * @param items Items to print.
 * @param separator String separating items. The default is empty string.
 * @param terminator String terminating items. The default is `os_EOL`.
 * @param to Output where to write items. Can be `stdout` or `stderr`. The default is `stdout`.
 */
extern d4_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_t d4_print;

#endif
