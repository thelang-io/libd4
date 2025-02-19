/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <wchar.h>
#include "../include/d4/crypto.h"
#include "../include/d4/safe.h"

int main (void) {
  unsigned char *out_digest;
  const unsigned char msg[] = {49, 50, 51, 52};
  unsigned int len;

  EVP_MD_CTX *ctx = EVP_MD_CTX_new();
  EVP_MD *sha256 = EVP_MD_fetch(NULL, "SHA256", NULL);

  EVP_DigestInit_ex(ctx, sha256, NULL);
  EVP_DigestUpdate(ctx, msg, sizeof(msg));
  out_digest = d4_safe_alloc(EVP_MD_get_size(sha256));
  EVP_DigestFinal_ex(ctx, out_digest, &len);

  for (unsigned int i = 0; i < len; i++) {
    wprintf(L"%02X", out_digest[i]);
  }

  d4_safe_free(out_digest);
  EVP_MD_free(sha256);
  EVP_MD_CTX_free(ctx);

  return 0;
}
