/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "array.h"
#include <the/string.h>

THE_DEFINE_ARRAY(arr_str, the_str_t, the_str_copy(self.data[i]), the_str_free(self.data[i]))
