/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <assert.h>
#include <limits.h>
#include "../src/number.h"
#include "../src/string.h"

static void test_f32_str (void) {
  the_str_t a1 = the_f32_str(0.0f);
  the_str_t a2 = the_f32_str(12.34f);

  the_str_t s1_cmp = the_str_alloc(L"0.0");
  the_str_t s2_cmp = the_str_alloc(L"12.34");

  assert(((void) "Stringifies 0.0", the_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 12.34", the_str_eq(a2, s2_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);

  the_str_free(a1);
  the_str_free(a2);
}

static void test_f64_str (void) {
  the_str_t a1 = the_f64_str(0.0);
  the_str_t a2 = the_f64_str(12.34);

  the_str_t s1_cmp = the_str_alloc(L"0.0");
  the_str_t s2_cmp = the_str_alloc(L"12.34");

  assert(((void) "Stringifies 0.0", the_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 12.34", the_str_eq(a2, s2_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);

  the_str_free(a1);
  the_str_free(a2);
}

static void test_float_str (void) {
  the_str_t a1 = the_float_str(0.0);
  the_str_t a2 = the_float_str(12.34);

  the_str_t s1_cmp = the_str_alloc(L"0.0");
  the_str_t s2_cmp = the_str_alloc(L"12.34");

  assert(((void) "Stringifies 0.0", the_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 12.34", the_str_eq(a2, s2_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);

  the_str_free(a1);
  the_str_free(a2);
}

static void test_i8_str (void) {
  the_str_t a1 = the_i8_str(INT8_MIN);
  the_str_t a2 = the_i8_str(0);
  the_str_t a3 = the_i8_str(INT8_MAX);

  the_str_t s1_cmp = the_str_alloc(L"-128");
  the_str_t s2_cmp = the_str_alloc(L"0");
  the_str_t s3_cmp = the_str_alloc(L"127");

  assert(((void) "Stringifies -128", the_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 0", the_str_eq(a2, s2_cmp)));
  assert(((void) "Stringifies 127", the_str_eq(a3, s3_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);
  the_str_free(s3_cmp);

  the_str_free(a1);
  the_str_free(a2);
  the_str_free(a3);
}

static void test_i16_str (void) {
  the_str_t a1 = the_i16_str(INT16_MIN);
  the_str_t a2 = the_i16_str(0);
  the_str_t a3 = the_i16_str(INT16_MAX);

  the_str_t s1_cmp = the_str_alloc(L"-32768");
  the_str_t s2_cmp = the_str_alloc(L"0");
  the_str_t s3_cmp = the_str_alloc(L"32767");

  assert(((void) "Stringifies -32768", the_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 0", the_str_eq(a2, s2_cmp)));
  assert(((void) "Stringifies 32767", the_str_eq(a3, s3_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);
  the_str_free(s3_cmp);

  the_str_free(a1);
  the_str_free(a2);
  the_str_free(a3);
}

static void test_i32_str (void) {
  the_str_t a1 = the_i32_str(INT32_MIN);
  the_str_t a2 = the_i32_str(0);
  the_str_t a3 = the_i32_str(INT32_MAX);

  the_str_t s1_cmp = the_str_alloc(L"-2147483648");
  the_str_t s2_cmp = the_str_alloc(L"0");
  the_str_t s3_cmp = the_str_alloc(L"2147483647");

  assert(((void) "Stringifies -2147483648", the_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 0", the_str_eq(a2, s2_cmp)));
  assert(((void) "Stringifies 2147483647", the_str_eq(a3, s3_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);
  the_str_free(s3_cmp);

  the_str_free(a1);
  the_str_free(a2);
  the_str_free(a3);
}

static void test_i64_str (void) {
  the_str_t a1 = the_i64_str(INT64_MIN);
  the_str_t a2 = the_i64_str(0);
  the_str_t a3 = the_i64_str(INT64_MAX);

  the_str_t s1_cmp = the_str_alloc(L"-9223372036854775808");
  the_str_t s2_cmp = the_str_alloc(L"0");
  the_str_t s3_cmp = the_str_alloc(L"9223372036854775807");

  assert(((void) "Stringifies -9223372036854775808", the_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 0", the_str_eq(a2, s2_cmp)));
  assert(((void) "Stringifies 9223372036854775807", the_str_eq(a3, s3_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);
  the_str_free(s3_cmp);

  the_str_free(a1);
  the_str_free(a2);
  the_str_free(a3);
}

static void test_int_str (void) {
  the_str_t a1 = the_int_str(INT32_MIN);
  the_str_t a2 = the_int_str(0);
  the_str_t a3 = the_int_str(INT32_MAX);

  the_str_t s1_cmp = the_str_alloc(L"-2147483648");
  the_str_t s2_cmp = the_str_alloc(L"0");
  the_str_t s3_cmp = the_str_alloc(L"2147483647");

  assert(((void) "Stringifies -2147483648", the_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 0", the_str_eq(a2, s2_cmp)));
  assert(((void) "Stringifies 2147483647", the_str_eq(a3, s3_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);
  the_str_free(s3_cmp);

  the_str_free(a1);
  the_str_free(a2);
  the_str_free(a3);
}

static void test_isize_str (void) {
  the_str_t a1 = the_isize_str(PTRDIFF_MIN);
  the_str_t a2 = the_isize_str(0);
  the_str_t a3 = the_isize_str(PTRDIFF_MAX);

  the_str_t s1_cmp = the_str_alloc(L"-9223372036854775808");
  the_str_t s2_cmp = the_str_alloc(L"0");
  the_str_t s3_cmp = the_str_alloc(L"9223372036854775807");

  assert(((void) "Stringifies -9223372036854775808", the_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 0", the_str_eq(a2, s2_cmp)));
  assert(((void) "Stringifies 9223372036854775807", the_str_eq(a3, s3_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);
  the_str_free(s3_cmp);

  the_str_free(a1);
  the_str_free(a2);
  the_str_free(a3);
}

static void test_u8_str (void) {
  the_str_t a1 = the_u8_str(0);
  the_str_t a2 = the_u8_str(UINT8_MAX);

  the_str_t s1_cmp = the_str_alloc(L"0");
  the_str_t s2_cmp = the_str_alloc(L"255");

  assert(((void) "Stringifies 0", the_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 255", the_str_eq(a2, s2_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);

  the_str_free(a1);
  the_str_free(a2);
}

static void test_u16_str (void) {
  the_str_t a1 = the_u16_str(0);
  the_str_t a2 = the_u16_str(UINT16_MAX);

  the_str_t s1_cmp = the_str_alloc(L"0");
  the_str_t s2_cmp = the_str_alloc(L"65535");

  assert(((void) "Stringifies 0", the_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 65535", the_str_eq(a2, s2_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);

  the_str_free(a1);
  the_str_free(a2);
}

static void test_u32_str (void) {
  the_str_t a1 = the_u32_str(0);
  the_str_t a2 = the_u32_str(UINT32_MAX);

  the_str_t s1_cmp = the_str_alloc(L"0");
  the_str_t s2_cmp = the_str_alloc(L"4294967295");

  assert(((void) "Stringifies 0", the_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 4294967295", the_str_eq(a2, s2_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);

  the_str_free(a1);
  the_str_free(a2);
}

static void test_u64_str (void) {
  the_str_t a1 = the_u64_str(0);
  the_str_t a2 = the_u64_str(UINT64_MAX);

  the_str_t s1_cmp = the_str_alloc(L"0");
  the_str_t s2_cmp = the_str_alloc(L"18446744073709551615");

  assert(((void) "Stringifies 0", the_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 18446744073709551615", the_str_eq(a2, s2_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);

  the_str_free(a1);
  the_str_free(a2);
}

static void test_usize_str (void) {
  the_str_t a1 = the_usize_str(0);
  the_str_t a2 = the_usize_str(SIZE_MAX);

  the_str_t s1_cmp = the_str_alloc(L"0");
  the_str_t s2_cmp = the_str_alloc(L"18446744073709551615");

  assert(((void) "Stringifies 0", the_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 18446744073709551615", the_str_eq(a2, s2_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);

  the_str_free(a1);
  the_str_free(a2);
}

int main (void) {
  test_f32_str();
  test_f64_str();
  test_float_str();
  test_i8_str();
  test_i16_str();
  test_i32_str();
  test_i64_str();
  test_int_str();
  test_isize_str();
  test_u8_str();
  test_u16_str();
  test_u32_str();
  test_u64_str();
  test_usize_str();
}
