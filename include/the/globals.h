/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_GLOBALS_H
#define THE_GLOBALS_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/any.h>
#include <the/fn.h>

THE_ARRAY_DECLARE(any, the_any_t)

THE_FUNCTION_DECLARE_WITH_PARAMS(s, void, void, FP4arr_anyFP1strFP1strFP1str, {
  the_arr_any_t n0;
  unsigned char o1;
  the_str_t n1;
  unsigned char o2;
  the_str_t n2;
  unsigned char o3;
  the_str_t n3;
})

// todo test
// todo documentation
extern the_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_t the_print;

#endif
