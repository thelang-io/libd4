/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <d4/number.h>
#include <d4/string.h>
#include <d4/union.h>
#include <assert.h>

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

static void test_union_alloc (void) {
  d4_str_t s1 = d4_str_alloc(L"string");

  d4_union_intUSstrUE_t u1 = d4_union_intUSstrUE_alloc(-1);
  d4_union_intUSstrUE_t u2 = d4_union_intUSstrUE_alloc(TYPE_int, 10);
  d4_union_intUSstrUE_t u3 = d4_union_intUSstrUE_alloc(TYPE_str, s1);

  assert(((void) "Union type is unset", u1.type == -1));
  assert(((void) "Union type is set to integer", u2.type == TYPE_int));
  assert(((void) "Union type is set to string", u3.type == TYPE_str));

  assert(((void) "Union value is correct integer", u2.data.v1 == 10));
  assert(((void) "Union value is correct string", d4_str_eq(u3.data.v2, s1)));

  d4_union_intUSstrUE_free(u1);
  d4_union_intUSstrUE_free(u2);
  d4_union_intUSstrUE_free(u3);

  d4_str_free(s1);
}

static void test_union_copy (void) {
  d4_str_t s1 = d4_str_alloc(L"string");

  d4_union_intUSstrUE_t u1 = d4_union_intUSstrUE_alloc(-1);
  d4_union_intUSstrUE_t u2 = d4_union_intUSstrUE_alloc(TYPE_int, 10);
  d4_union_intUSstrUE_t u3 = d4_union_intUSstrUE_alloc(TYPE_str, s1);

  d4_union_intUSstrUE_t u4 = d4_union_intUSstrUE_copy(u1);
  d4_union_intUSstrUE_t u5 = d4_union_intUSstrUE_copy(u2);
  d4_union_intUSstrUE_t u6 = d4_union_intUSstrUE_copy(u3);

  assert(((void) "Copies union with not set type", u4.type == -1));
  assert(((void) "Copies union with integer type", u5.type == TYPE_int));
  assert(((void) "Copies union with string type", u6.type == TYPE_str));

  assert(((void) "Copies union with integer value", u5.data.v1 == 10));
  assert(((void) "Copies union with string value", d4_str_eq(u6.data.v2, s1)));

  d4_union_intUSstrUE_free(u1);
  d4_union_intUSstrUE_free(u2);
  d4_union_intUSstrUE_free(u3);

  d4_union_intUSstrUE_free(u4);
  d4_union_intUSstrUE_free(u5);
  d4_union_intUSstrUE_free(u6);

  d4_str_free(s1);
}

static void test_union_eq (void) {
  d4_str_t s1 = d4_str_alloc(L"string");
  d4_str_t s2 = d4_str_alloc(L"string2");

  d4_union_intUSstrUE_t u1 = d4_union_intUSstrUE_alloc(-1);
  d4_union_intUSstrUE_t u2 = d4_union_intUSstrUE_alloc(TYPE_int, 10);
  d4_union_intUSstrUE_t u3 = d4_union_intUSstrUE_alloc(TYPE_str, s1);

  d4_union_intUSstrUE_t u4 = d4_union_intUSstrUE_alloc(-1);
  d4_union_intUSstrUE_t u5 = d4_union_intUSstrUE_alloc(TYPE_int, 10);
  d4_union_intUSstrUE_t u6 = d4_union_intUSstrUE_alloc(TYPE_str, s1);

  d4_union_intUSstrUE_t u7 = d4_union_intUSstrUE_alloc(TYPE_int, 11);
  d4_union_intUSstrUE_t u8 = d4_union_intUSstrUE_alloc(TYPE_str, s2);

  assert(((void) "Union equals with integer type", d4_union_intUSstrUE_eq(u2, u5)));
  assert(((void) "Union equals with string type", d4_union_intUSstrUE_eq(u3, u6)));

  assert(((void) "Union not equals without type", !d4_union_intUSstrUE_eq(u1, u4)));
  assert(((void) "Union not equals with different types", !d4_union_intUSstrUE_eq(u1, u2)));
  assert(((void) "Union not equals with different types 2", !d4_union_intUSstrUE_eq(u2, u3)));
  assert(((void) "Union not equals with different integer value", !d4_union_intUSstrUE_eq(u2, u7)));
  assert(((void) "Union not equals with different string value", !d4_union_intUSstrUE_eq(u3, u8)));

  d4_union_intUSstrUE_free(u1);
  d4_union_intUSstrUE_free(u2);
  d4_union_intUSstrUE_free(u3);

  d4_union_intUSstrUE_free(u4);
  d4_union_intUSstrUE_free(u5);
  d4_union_intUSstrUE_free(u6);

  d4_union_intUSstrUE_free(u7);
  d4_union_intUSstrUE_free(u8);

  d4_str_free(s1);
  d4_str_free(s2);
}

static void test_union_free (void) {
  d4_str_t s1 = d4_str_alloc(L"string");

  d4_union_intUSstrUE_t u1 = d4_union_intUSstrUE_alloc(-1);
  d4_union_intUSstrUE_t u2 = d4_union_intUSstrUE_alloc(TYPE_int, 10);
  d4_union_intUSstrUE_t u3 = d4_union_intUSstrUE_alloc(TYPE_str, s1);

  d4_union_intUSstrUE_free(u1);
  d4_union_intUSstrUE_free(u2);
  d4_union_intUSstrUE_free(u3);

  d4_str_free(s1);
}

static void test_union_realloc (void) {
  d4_str_t s1 = d4_str_alloc(L"string");

  d4_union_intUSstrUE_t u1 = d4_union_intUSstrUE_alloc(-1);
  d4_union_intUSstrUE_t u2 = d4_union_intUSstrUE_alloc(TYPE_int, 10);
  d4_union_intUSstrUE_t u3 = d4_union_intUSstrUE_alloc(TYPE_str, s1);
  d4_union_intUSstrUE_t u4 = d4_union_intUSstrUE_copy(u1);

  u4 = d4_union_intUSstrUE_realloc(u4, u2);
  assert(((void) "Union reallocates to integer type", d4_union_intUSstrUE_eq(u4, u2)));
  u4 = d4_union_intUSstrUE_realloc(u4, u3);
  assert(((void) "Union reallocates to string type", d4_union_intUSstrUE_eq(u4, u3)));
  u4 = d4_union_intUSstrUE_realloc(u4, u1);
  assert(((void) "Union reallocates to no type", u4.type == -1));

  d4_union_intUSstrUE_free(u1);
  d4_union_intUSstrUE_free(u2);
  d4_union_intUSstrUE_free(u3);
  d4_union_intUSstrUE_free(u4);

  d4_str_free(s1);
}

static void test_union_str (void) {
  d4_str_t v1 = d4_str_alloc(L"string");

  d4_union_intUSstrUE_t u1 = d4_union_intUSstrUE_alloc(-1);
  d4_union_intUSstrUE_t u2 = d4_union_intUSstrUE_alloc(TYPE_int, 10);
  d4_union_intUSstrUE_t u3 = d4_union_intUSstrUE_alloc(TYPE_str, v1);

  d4_str_t r1 = d4_str_alloc(L"");
  d4_str_t r2 = d4_str_alloc(L"10");
  d4_str_t r3 = d4_str_alloc(L"string");

  d4_str_t s1 = d4_union_intUSstrUE_str(u1);
  d4_str_t s2 = d4_union_intUSstrUE_str(u2);
  d4_str_t s3 = d4_union_intUSstrUE_str(u3);

  assert(((void) "Union stringifies without type", d4_str_eq(s1, r1)));
  assert(((void) "Union stringifies with integer type", d4_str_eq(s2, r2)));
  assert(((void) "Union stringifies with string type", d4_str_eq(s3, r3)));

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);

  d4_str_free(r1);
  d4_str_free(r2);
  d4_str_free(r3);

  d4_union_intUSstrUE_free(u1);
  d4_union_intUSstrUE_free(u2);
  d4_union_intUSstrUE_free(u3);

  d4_str_free(v1);
}

int main (void) {
  test_union_alloc();
  test_union_copy();
  test_union_eq();
  test_union_free();
  test_union_realloc();
  test_union_str();
}
