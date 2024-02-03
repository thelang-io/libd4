/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef SRC_ANY_H
#define SRC_ANY_H

#include <the/any.h>
#include <the/string-type.h>

struct the_any_s {
  int t;
  void *d;
  struct the_any_s (*_copy) (const struct the_any_s);
  bool (*_eq) (const struct the_any_s, const struct the_any_s);
  bool (*_ne) (const struct the_any_s, const struct the_any_s);
  void (*_free) (struct the_any_s);
  the_str_t (*_str) (const struct the_any_s);
};

#endif
