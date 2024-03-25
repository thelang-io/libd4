/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/reference.h>
#include <stdint.h>
#include <wchar.h>

THE_REFERENCE_DECLARE(int, int32_t)

int main (void) {
  int32_t a = 2;
  the_ref_int_t ref_a = &a;

  wprintf(L"a: %p", ref_a);

  return 0;
}
