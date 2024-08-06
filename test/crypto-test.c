/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <d4/crypto.h>
#include <d4/safe.h>
#include <assert.h>
#include <string.h>
#include "../src/string.h"

static d4_str_t convert_byte_array_to_str (const char *buf, unsigned int len) {
  const unsigned char hex[] = "0123456789ABCDEF";
  wchar_t *wide_buf = d4_safe_alloc((len * 2 + 1) * sizeof(wchar_t));
  d4_str_t result;

  for (unsigned int i = 0; i < len; i++) {
    wide_buf[i * 2] = hex[(buf[i] >> 4) & 0xF];
    wide_buf[i * 2 + 1] = hex[buf[i] & 0xF];
  }

  wide_buf[len * 2] = '\0';
  result = d4_str_alloc(wide_buf);
  d4_safe_free(wide_buf);

  return result;
}

static d4_str_t crypto_sha256 (const char *msg) {
  char *buf;
  unsigned int len;
  d4_str_t result;

  EVP_MD_CTX *ctx = EVP_MD_CTX_new();
  EVP_MD *sha256 = EVP_MD_fetch(NULL, "SHA256", NULL);

  EVP_DigestInit_ex(ctx, sha256, NULL);
  EVP_DigestUpdate(ctx, msg, strlen(msg));

  buf = d4_safe_alloc(EVP_MD_get_size(sha256));
  EVP_DigestFinal_ex(ctx, (void *) buf, &len);
  result = convert_byte_array_to_str(buf, len);

  d4_safe_free(buf);
  EVP_MD_free(sha256);
  EVP_MD_CTX_free(ctx);

  return result;
}

static void test_crypto (void) {
  d4_str_t s = crypto_sha256("Aaron");
  d4_str_t s_cmp = d4_str_alloc(L"324A17D21917A99CF2AC6EA468B73ECE5685161D414E9416C16DF0018D3C6DB5");

  assert(((void) "SHA256 works", d4_str_eq(s, s_cmp)));

  d4_str_free(s);
  d4_str_free(s_cmp);
}

int main (void) {
  test_crypto();
}
