/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <d4/number.h>
#include <d4/string.h>
#include <d4/union.h>

#define TYPE_int 1
#define TYPE_str 2

D4_UNION_DECLARE(intUSstr, {
  int32_t v1;
  d4_str_t v2;
})

D4_UNION_DEFINE(intUSstr, {
  if (self.type == TYPE_int) self.data.v1 = va_arg(args, int);
  if (self.type == TYPE_str) self.data.v2 = d4_str_copy(va_arg(args, d4_str_t));
}, {
  if (self.type == TYPE_int) result.data.v1 = self.data.v1;
  if (self.type == TYPE_str) result.data.v2 = d4_str_copy(self.data.v2);
}, {
  if (self.type == TYPE_int) return self.data.v1 == rhs.data.v1;
  if (self.type == TYPE_str) return d4_str_eq(self.data.v2, rhs.data.v2);
}, {
  if (self.type == TYPE_str) d4_str_free(self.data.v2);
}, {
  if (self.type == TYPE_int) return d4_i32_str(self.data.v1);
  if (self.type == TYPE_str) return d4_str_copy(self.data.v2);
})

int main (void) {
  d4_str_t s1 = d4_str_alloc(L"test");

  d4_union_intUSstrUE_t a1 = d4_union_intUSstrUE_alloc(0);
  d4_union_intUSstrUE_t a2 = d4_union_intUSstrUE_alloc(TYPE_int, 10);
  d4_union_intUSstrUE_t a3 = d4_union_intUSstrUE_alloc(TYPE_str, s1);
  d4_union_intUSstrUE_t a4 = d4_union_intUSstrUE_copy(a2);

  d4_str_t s2 = d4_union_intUSstrUE_str(a2);
  d4_str_t s3 = d4_union_intUSstrUE_str(a3);

  if (d4_union_intUSstrUE_eq(a2, a4)) {
    wprintf(L"a2 == a4\n");
  } else {
    wprintf(L"a2 != a4\n");
  }

  a4 = d4_union_intUSstrUE_realloc(a4, d4_union_intUSstrUE_copy(a3));

  if (d4_union_intUSstrUE_eq(a2, a4)) {
    wprintf(L"a2 == a4\n");
  } else {
    wprintf(L"a2 != a4\n");
  }

  wprintf(L"s2 = %ls\n", s2.data);
  wprintf(L"s3 = %ls\n", s3.data);

  d4_union_intUSstrUE_free(a1);
  d4_union_intUSstrUE_free(a2);
  d4_union_intUSstrUE_free(a3);
  d4_union_intUSstrUE_free(a4);

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);

  return 0;
}
