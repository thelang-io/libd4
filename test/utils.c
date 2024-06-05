/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/safe.h>
#include <the/string.h>
#include "utils.h"

static int unicode_len (unsigned char code) {
  if (code < 0x80) {
    return 1;
  } else if (code < 0xE0) {
    return 2;
  } else if (code < 0xF0) {
    return 3;
  } else {
    return 4;
  }
}

static unsigned char unicode_mask (unsigned char code) {
  if (code < 0x80) {
    return 0x00;
  } else if (code < 0xE0) {
    return 0xC0;
  } else if (code < 0xF0) {
    return 0xE0;
  } else {
    return 0xF0;
  }
}

the_str_t read_unicode_file (const char *path) {
  FILE *f = fopen(path, "rb");
  char *buf = NULL;
  size_t buf_len;
  wchar_t *data = NULL;
  size_t len = 0;

  if (f != NULL) {
    fseek(f, 0, SEEK_END);
    buf_len = ftell(f);
    fseek(f, 0, SEEK_SET);
    buf = the_safe_alloc(buf_len);
    fread(buf, 1, buf_len, f);
    fclose(f);
  }

  if (buf == NULL) {
    return the_str_empty_val;
  }

  data = the_safe_alloc((buf_len + 1) * sizeof(wchar_t));

  for (size_t i = 0; i < buf_len; len++) {
    unsigned char code = buf[i++];
    data[len] = code ^ unicode_mask(code);

    for (int j = unicode_len(code); j > 1; j--) {
      data[len] <<= 6;
      data[len] |= buf[i++] & 0x3F;
    }
  }

  data[len] = L'\0';
  return (the_str_t) {data, len, false};
}
