/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <assert.h>
#include "../include/d4/rand.h"

static int rand_int (void) {
  unsigned char d[4];
  RAND_bytes(d, 4);
  return (d[0] << 24) | (d[1] << 16) | (d[2] << 8) | d[3];
}

static void test_rand (void) {
  int num1 = rand_int();
  int num2 = rand_int();

  assert(((void) "Two random numbers are not equal", num1 != num2));
}

int main (void) {
  test_rand();
}
