/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <d4/rand.h>
#include <stdio.h>
#include <wchar.h>

int main (void) {
  unsigned char d[4];
  int num;

  if (RAND_bytes(d, 4) != 1) {
    fwprintf(stderr, L"Failed to generate random bytes\n");
  }

  num = (d[0] << 24) | (d[1] << 16) | (d[2] << 8) | d[3];
  wprintf(L"Random number: %d\n", num);

  return 0;
}
