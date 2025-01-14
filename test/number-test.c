/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <assert.h>
#include <stdio.h>
#include "../src/number.h"
#include "../src/string.h"

static void test_f32_str (void) {
  d4_str_t a1 = d4_f32_str(0.0f);
  d4_str_t a2 = d4_f32_str(12.34f);

  d4_str_t s1_cmp = d4_str_alloc(L"0.0");
  d4_str_t s2_cmp = d4_str_alloc(L"12.34");

  assert(((void) "Stringifies 0.0", d4_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 12.34", d4_str_eq(a2, s2_cmp)));

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);

  d4_str_free(a1);
  d4_str_free(a2);
}

static void test_f64_str (void) {
  d4_str_t a1 = d4_f64_str(0.0);
  d4_str_t a2 = d4_f64_str(12.34);

  d4_str_t s1_cmp = d4_str_alloc(L"0.0");
  d4_str_t s2_cmp = d4_str_alloc(L"12.34");

  assert(((void) "Stringifies 0.0", d4_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 12.34", d4_str_eq(a2, s2_cmp)));

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);

  d4_str_free(a1);
  d4_str_free(a2);
}

static void test_float_str (void) {
  d4_str_t a1 = d4_float_str(0.0);
  d4_str_t a2 = d4_float_str(12.34);

  d4_str_t s1_cmp = d4_str_alloc(L"0.0");
  d4_str_t s2_cmp = d4_str_alloc(L"12.34");

  assert(((void) "Stringifies 0.0", d4_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 12.34", d4_str_eq(a2, s2_cmp)));

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);

  d4_str_free(a1);
  d4_str_free(a2);
}

static void test_i8_str (void) {
  d4_str_t a1 = d4_i8_str(INT8_MIN);
  d4_str_t a2 = d4_i8_str(0);
  d4_str_t a3 = d4_i8_str(INT8_MAX);

  d4_str_t s1_cmp = d4_str_alloc(L"-128");
  d4_str_t s2_cmp = d4_str_alloc(L"0");
  d4_str_t s3_cmp = d4_str_alloc(L"127");

  assert(((void) "Stringifies -128", d4_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 0", d4_str_eq(a2, s2_cmp)));
  assert(((void) "Stringifies 127", d4_str_eq(a3, s3_cmp)));

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);
  d4_str_free(s3_cmp);

  d4_str_free(a1);
  d4_str_free(a2);
  d4_str_free(a3);
}

static void test_i16_str (void) {
  d4_str_t a1 = d4_i16_str(INT16_MIN);
  d4_str_t a2 = d4_i16_str(0);
  d4_str_t a3 = d4_i16_str(INT16_MAX);

  d4_str_t s1_cmp = d4_str_alloc(L"-32768");
  d4_str_t s2_cmp = d4_str_alloc(L"0");
  d4_str_t s3_cmp = d4_str_alloc(L"32767");

  assert(((void) "Stringifies -32768", d4_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 0", d4_str_eq(a2, s2_cmp)));
  assert(((void) "Stringifies 32767", d4_str_eq(a3, s3_cmp)));

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);
  d4_str_free(s3_cmp);

  d4_str_free(a1);
  d4_str_free(a2);
  d4_str_free(a3);
}

static void test_i32_str (void) {
  d4_str_t a1 = d4_i32_str(INT32_MIN);
  d4_str_t a2 = d4_i32_str(0);
  d4_str_t a3 = d4_i32_str(INT32_MAX);

  d4_str_t s1_cmp = d4_str_alloc(L"-2147483648");
  d4_str_t s2_cmp = d4_str_alloc(L"0");
  d4_str_t s3_cmp = d4_str_alloc(L"2147483647");

  assert(((void) "Stringifies -2147483648", d4_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 0", d4_str_eq(a2, s2_cmp)));
  assert(((void) "Stringifies 2147483647", d4_str_eq(a3, s3_cmp)));

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);
  d4_str_free(s3_cmp);

  d4_str_free(a1);
  d4_str_free(a2);
  d4_str_free(a3);
}

static void test_i64_str (void) {
  d4_str_t a1 = d4_i64_str(INT64_MIN);
  d4_str_t a2 = d4_i64_str(0);
  d4_str_t a3 = d4_i64_str(INT64_MAX);

  d4_str_t s1_cmp = d4_str_alloc(L"-9223372036854775808");
  d4_str_t s2_cmp = d4_str_alloc(L"0");
  d4_str_t s3_cmp = d4_str_alloc(L"9223372036854775807");

  assert(((void) "Stringifies -9223372036854775808", d4_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 0", d4_str_eq(a2, s2_cmp)));
  assert(((void) "Stringifies 9223372036854775807", d4_str_eq(a3, s3_cmp)));

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);
  d4_str_free(s3_cmp);

  d4_str_free(a1);
  d4_str_free(a2);
  d4_str_free(a3);
}

static void test_int_str (void) {
  d4_str_t a1 = d4_int_str(INT32_MIN);
  d4_str_t a2 = d4_int_str(0);
  d4_str_t a3 = d4_int_str(INT32_MAX);

  d4_str_t s1_cmp = d4_str_alloc(L"-2147483648");
  d4_str_t s2_cmp = d4_str_alloc(L"0");
  d4_str_t s3_cmp = d4_str_alloc(L"2147483647");

  assert(((void) "Stringifies -2147483648", d4_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 0", d4_str_eq(a2, s2_cmp)));
  assert(((void) "Stringifies 2147483647", d4_str_eq(a3, s3_cmp)));

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);
  d4_str_free(s3_cmp);

  d4_str_free(a1);
  d4_str_free(a2);
  d4_str_free(a3);
}

static void test_isize_str (void) {
  d4_str_t a1 = d4_isize_str(PTRDIFF_MIN);
  d4_str_t a2 = d4_isize_str(0);
  d4_str_t a3 = d4_isize_str(PTRDIFF_MAX);

  d4_str_t s1_cmp = d4_str_alloc(L"-9223372036854775808");
  d4_str_t s2_cmp = d4_str_alloc(L"0");
  d4_str_t s3_cmp = d4_str_alloc(L"9223372036854775807");

  assert(((void) "Stringifies -9223372036854775808", d4_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 0", d4_str_eq(a2, s2_cmp)));
  assert(((void) "Stringifies 9223372036854775807", d4_str_eq(a3, s3_cmp)));

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);
  d4_str_free(s3_cmp);

  d4_str_free(a1);
  d4_str_free(a2);
  d4_str_free(a3);
}

static void test_u8_str (void) {
  d4_str_t a1 = d4_u8_str(0);
  d4_str_t a2 = d4_u8_str(UINT8_MAX);

  d4_str_t s1_cmp = d4_str_alloc(L"0");
  d4_str_t s2_cmp = d4_str_alloc(L"255");

  assert(((void) "Stringifies 0", d4_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 255", d4_str_eq(a2, s2_cmp)));

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);

  d4_str_free(a1);
  d4_str_free(a2);
}

static void test_u16_str (void) {
  d4_str_t a1 = d4_u16_str(0);
  d4_str_t a2 = d4_u16_str(UINT16_MAX);

  d4_str_t s1_cmp = d4_str_alloc(L"0");
  d4_str_t s2_cmp = d4_str_alloc(L"65535");

  assert(((void) "Stringifies 0", d4_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 65535", d4_str_eq(a2, s2_cmp)));

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);

  d4_str_free(a1);
  d4_str_free(a2);
}

static void test_u32_str (void) {
  d4_str_t a1 = d4_u32_str(0);
  d4_str_t a2 = d4_u32_str(UINT32_MAX);

  d4_str_t s1_cmp = d4_str_alloc(L"0");
  d4_str_t s2_cmp = d4_str_alloc(L"4294967295");

  assert(((void) "Stringifies 0", d4_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 4294967295", d4_str_eq(a2, s2_cmp)));

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);

  d4_str_free(a1);
  d4_str_free(a2);
}

static void test_u64_str (void) {
  d4_str_t a1 = d4_u64_str(0);
  d4_str_t a2 = d4_u64_str(UINT64_MAX);

  d4_str_t s1_cmp = d4_str_alloc(L"0");
  d4_str_t s2_cmp = d4_str_alloc(L"18446744073709551615");

  assert(((void) "Stringifies 0", d4_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 18446744073709551615", d4_str_eq(a2, s2_cmp)));

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);

  d4_str_free(a1);
  d4_str_free(a2);
}

static void test_usize_str (void) {
  d4_str_t a1 = d4_usize_str(0);
  d4_str_t a2 = d4_usize_str(SIZE_MAX);

  d4_str_t s1_cmp = d4_str_alloc(L"0");
  d4_str_t s2_cmp = d4_str_alloc(L"18446744073709551615");

  assert(((void) "Stringifies 0", d4_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies 18446744073709551615", d4_str_eq(a2, s2_cmp)));

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);

  d4_str_free(a1);
  d4_str_free(a2);
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
