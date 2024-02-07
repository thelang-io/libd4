/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/crypto.h>

int main () {
  unsigned char d[4];

  if (RAND_bytes(d, 4) != 1) {
    fprintf(strerr, "Failed to generate random bytes\n");
  }

  int num = (d[0] << 24) | (d[1] << 16) | (d[2] << 8) | d[3];
  printf("Random number: %d\n", num);

  return 0;
}
