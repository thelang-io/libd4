/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <d4/reference.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>

D4_REFERENCE_DECLARE(u32, uint32_t)

static void test_reference_creates (void) {
  uint32_t a = 1;
  d4_ref_u32_t ref_a = &a;

  assert(((void) "Reference is not NULL", ref_a != NULL));
}

int main (void) {
  test_reference_creates();
}
