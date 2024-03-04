/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <assert.h>
#include "../src/string.h"
#include "utils.h"

static void test_string_snwprintf (void) {
  // todo
}

static void test_string_vsnwprintf (void) {
  // todo
}

static void test_string_alloc (void) {
  the_str_t s1 = the_str_alloc(L"");
  the_str_t s2 = the_str_alloc(L"Test");
  the_str_t s3 = the_str_alloc(L"%d", 10);
  the_str_t s4 = the_str_alloc(L"10");

  assert(((void) "Allocates empty", s1.data == NULL));
  assert(((void) "Allocates empty", s1.len == 0));

  assert(((void) "Allocates non empty", s2.data != NULL));
  assert(((void) "Allocates non empty", s2.len == 4));

  assert(((void) "Allocates with format", the_str_eq(s3, s4)));
  assert(((void) "Allocates with format", s3.len == 2));

  the_str_free(s1);
  the_str_free(s2);
  the_str_free(s3);
  the_str_free(s4);
}

static void test_string_calloc (void) {
  wchar_t data[] = L"1234567890";

  the_str_t s1 = the_str_calloc(data, 0);
  the_str_t s2 = the_str_calloc(data, 4);
  the_str_t s3 = the_str_calloc(&data[4], 3);

  the_str_t s4 = the_str_alloc(L"");
  the_str_t s5 = the_str_alloc(L"1234");
  the_str_t s6 = the_str_alloc(L"567");

  assert(((void) "Allocates empty", the_str_eq(s1, s4)));
  assert(((void) "Allocates first 4 chars", the_str_eq(s2, s5)));
  assert(((void) "Allocates 3 chars after first 4", the_str_eq(s3, s6)));

  the_str_free(s1);
  the_str_free(s2);
  the_str_free(s3);
  the_str_free(s4);
  the_str_free(s5);
  the_str_free(s6);
}

static void test_string_at (void) {
  the_str_t s1 = the_str_alloc(L"");
  the_str_t s2 = the_str_alloc(L"1234");

  ASSERT_THROW_WITH_MESSAGE(AT1, {
    the_str_at(&the_err_state, 0, 0, s1, 0);
  }, L"index 0 out of string bounds");

  ASSERT_THROW_WITH_MESSAGE(AT2, {
    the_str_at(&the_err_state, 0, 0, s2, 4);
  }, L"index 4 out of string bounds");

  ASSERT_THROW_WITH_MESSAGE(AT3, {
    the_str_at(&the_err_state, 0, 0, s2, -5);
  }, L"index -5 out of string bounds");

  ASSERT_NO_THROW(AT4, {
    assert(((void) "Finds at position 0", the_str_at(&the_err_state, 0, 0, s2, 0) == s2.data));
    assert(((void) "Finds at position 0", *the_str_at(&the_err_state, 0, 0, s2, 0) == L'1'));
    assert(((void) "Finds at position 1", *the_str_at(&the_err_state, 0, 0, s2, 1) == L'2'));
    assert(((void) "Finds at position 3", *the_str_at(&the_err_state, 0, 0, s2, 3) == L'4'));
    assert(((void) "Finds at position -4", *the_str_at(&the_err_state, 0, 0, s2, -4) == L'1'));
    assert(((void) "Finds at position -1", *the_str_at(&the_err_state, 0, 0, s2, -1) == L'4'));
  });
}

static void test_string_concat (void) {
  // todo
}

static void test_string_contains (void) {
  // todo
}

static void test_string_copy (void) {
  // todo
}

static void test_string_empty (void) {
  // todo
}

static void test_string_eq (void) {
  // todo
}

static void test_string_escape (void) {
  // todo
}

static void test_string_find (void) {
  // todo
}

static void test_string_free (void) {
  // todo
}

static void test_string_ge (void) {
  // todo
}

static void test_string_gt (void) {
  // todo
}

static void test_string_le (void) {
  // todo
}

static void test_string_lines (void) {
  // todo
}

static void test_string_lower (void) {
  // todo
}

static void test_string_lowerFirst (void) {
  // todo
}

static void test_string_lt (void) {
  // todo
}

static void test_string_ne (void) {
  // todo
}

static void test_string_not (void) {
  // todo
}

static void test_string_realloc (void) {
  // todo
}

static void test_string_replace (void) {
  // todo
}

static void test_string_slice (void) {
  // todo
}

static void test_string_split (void) {
  // todo
}

static void test_string_toFloat (void) {
  // todo
}

static void test_string_toF32 (void) {
  // todo
}

static void test_string_toF64 (void) {
  // todo
}

static void test_string_toIsize (void) {
  // todo
}

static void test_string_toI8 (void) {
  // todo
}

static void test_string_toI16 (void) {
  // todo
}

static void test_string_toI32 (void) {
  // todo
}

static void test_string_toI64 (void) {
  // todo
}

static void test_string_toUsize (void) {
  // todo
}

static void test_string_toU8 (void) {
  // todo
}

static void test_string_toU16 (void) {
  // todo
}

static void test_string_toU32 (void) {
  // todo
}

static void test_string_toU64 (void) {
  // todo
}

static void test_string_trim (void) {
  // todo
}

static void test_string_trimEnd (void) {
  // todo
}

static void test_string_trimStart (void) {
  // todo
}

static void test_string_upper (void) {
  // todo
}

static void test_string_upperFirst (void) {
  // todo
}

int main (void) {
  test_string_snwprintf();
  test_string_vsnwprintf();
  test_string_alloc();
  test_string_calloc();
  test_string_at();
  test_string_concat();
  test_string_contains();
  test_string_copy();
  test_string_empty();
  test_string_eq();
  test_string_escape();
  test_string_find();
  test_string_free();
  test_string_ge();
  test_string_gt();
  test_string_le();
  test_string_lines();
  test_string_lower();
  test_string_lowerFirst();
  test_string_lt();
  test_string_ne();
  test_string_not();
  test_string_realloc();
  test_string_replace();
  test_string_slice();
  test_string_split();
  test_string_toFloat();
  test_string_toF32();
  test_string_toF64();
  test_string_toIsize();
  test_string_toI8();
  test_string_toI16();
  test_string_toI32();
  test_string_toI64();
  test_string_toUsize();
  test_string_toU8();
  test_string_toU16();
  test_string_toU32();
  test_string_toU64();
  test_string_trim();
  test_string_trimEnd();
  test_string_trimStart();
  test_string_upper();
  test_string_upperFirst();
}
