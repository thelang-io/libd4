/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef SRC_STRING_H
#define SRC_STRING_H

#include <the/string.h>

int snwprintf (const wchar_t *, ...);
int vsnwprintf (const wchar_t *, va_list);

extern the_str_t empty_str_value;

#endif
