/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <stdint.h>
#include <wchar.h>
#include "../include/d4/reference.h"

D4_REFERENCE_DECLARE(int, int32_t)

int main (void) {
  int32_t a = 2;
  d4_ref_int_t ref_a = &a;

  wprintf(L"a: %p", ref_a);

  return 0;
}
