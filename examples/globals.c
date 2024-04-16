/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/globals.h>

// todo more examples

int main (void) {
  the_print.func(
    the_print.ctx,
    the_safe_calloc(
      &(the_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t) {
        the_arr_any_alloc(0),
        0, the_str_alloc(L""),
        0, the_str_alloc(L""),
        0, the_str_alloc(L"")
      },
      sizeof(the_fn_sFP4arr_anyFP1strFP1strFP1strFRvoidFE_params_t)
    )
  );

  return 0;
}
