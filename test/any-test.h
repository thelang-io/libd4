/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef TEST_ANY_TEST_H
#define TEST_ANY_TEST_H

#include "../src/any.h"
#include "../src/number.h"
#include "../src/safe.h"

#define TYPE_u32 1
#define TYPE_u64 2

THE_ANY_DECLARE(u32, uint32_t)
THE_ANY_DEFINE(TYPE_u32, u32, uint32_t, val, lhs_val == rhs_val, (void) val, the_u32_str(val))

THE_ANY_DECLARE(u64, uint64_t)
THE_ANY_DEFINE(TYPE_u64, u64, uint64_t, val, lhs_val == rhs_val, (void) val, the_u64_str(val))

#endif
