/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/number.h>
#include <the/string.h>
#include <the/union.h>

#define TYPE_int 1
#define TYPE_str 2

THE_UNION_DECLARE(intUSstr, {
  int32_t v1;
  the_str_t v2;
})

THE_UNION_DEFINE(intUSstr, {
  if (self.type == TYPE_int) self.data.v1 = va_arg(args, int);
  if (self.type == TYPE_str) self.data.v2 = the_str_copy(va_arg(args, the_str_t));
}, {
  if (self.type == TYPE_int) result.data.v1 = self.data.v1;
  if (self.type == TYPE_str) result.data.v2 = the_str_copy(self.data.v2);
}, {
  if (self.type == TYPE_int) return self.data.v1 == rhs.data.v1;
  if (self.type == TYPE_str) return the_str_eq(self.data.v2, rhs.data.v2);
}, {
  if (self.type == TYPE_str) the_str_free(self.data.v2);
}, {
  if (self.type == TYPE_int) return the_i32_str(self.data.v1);
  if (self.type == TYPE_str) return the_str_copy(self.data.v2);
})

int main (void) {
  the_str_t s1 = the_str_alloc(L"test");

  the_union_intUSstrUE_t a1 = the_union_intUSstrUE_alloc(0);
  the_union_intUSstrUE_t a2 = the_union_intUSstrUE_alloc(TYPE_int, 10);
  the_union_intUSstrUE_t a3 = the_union_intUSstrUE_alloc(TYPE_str, s1);
  the_union_intUSstrUE_t a4 = the_union_intUSstrUE_copy(a2);

  the_str_t s2 = the_union_intUSstrUE_str(a2);
  the_str_t s3 = the_union_intUSstrUE_str(a3);

  if (the_union_intUSstrUE_eq(a2, a4)) {
    wprintf(L"a2 == a4\n");
  } else {
    wprintf(L"a2 != a4\n");
  }

  a4 = the_union_intUSstrUE_realloc(a4, the_union_intUSstrUE_copy(a3));

  if (the_union_intUSstrUE_eq(a2, a4)) {
    wprintf(L"a2 == a4\n");
  } else {
    wprintf(L"a2 != a4\n");
  }

  wprintf(L"s2 = %ls\n", s2.data);
  wprintf(L"s3 = %ls\n", s3.data);

  the_union_intUSstrUE_free(a1);
  the_union_intUSstrUE_free(a2);
  the_union_intUSstrUE_free(a3);
  the_union_intUSstrUE_free(a4);

  the_str_free(s1);
  the_str_free(s2);
  the_str_free(s3);

  return 0;
}
