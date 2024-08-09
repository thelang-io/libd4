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
  d4_str_t s1 = d4_str_empty_val;
  d4_str_t s2 = d4_str_alloc(L"Test");
  d4_str_t s3 = d4_str_alloc(L"%d", 10);
  d4_str_t s4 = d4_str_alloc(L"10");

  assert(((void) "Allocates empty", s1.data == NULL));
  assert(((void) "Allocates empty", s1.len == 0));

  assert(((void) "Allocates non empty", s2.data != NULL));
  assert(((void) "Allocates non empty", s2.len == 4));

  assert(((void) "Allocates with format", d4_str_eq(s3, s4)));
  assert(((void) "Allocates with format", s3.len == 2));

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
}

static void test_string_calloc (void) {
  wchar_t data[] = L"1234567890";

  d4_str_t s1 = d4_str_calloc(data, 0);
  d4_str_t s2 = d4_str_calloc(data, 4);
  d4_str_t s3 = d4_str_calloc(&data[4], 3);

  d4_str_t s4 = d4_str_empty_val;
  d4_str_t s5 = d4_str_alloc(L"1234");
  d4_str_t s6 = d4_str_alloc(L"567");

  assert(((void) "Allocates empty", d4_str_eq(s1, s4)));
  assert(((void) "Allocates first 4 chars", d4_str_eq(s2, s5)));
  assert(((void) "Allocates 3 chars after first 4", d4_str_eq(s3, s6)));

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s6);
}

static void test_string_at (void) {
  d4_str_t s1 = d4_str_empty_val;
  d4_str_t s2 = d4_str_alloc(L"1234");

  ASSERT_THROW_WITH_MESSAGE(AT1, {
    d4_str_at(&d4_err_state, 0, 0, s1, 0);
  }, L"index 0 out of string bounds");

  ASSERT_THROW_WITH_MESSAGE(AT2, {
    d4_str_at(&d4_err_state, 0, 0, s2, 4);
  }, L"index 4 out of string bounds");

  ASSERT_THROW_WITH_MESSAGE(AT3, {
    d4_str_at(&d4_err_state, 0, 0, s2, -5);
  }, L"index -5 out of string bounds");

  ASSERT_NO_THROW(AT4, {
    assert(((void) "Finds at position 0", d4_str_at(&d4_err_state, 0, 0, s2, 0) == s2.data));
    assert(((void) "Finds at position 0", *d4_str_at(&d4_err_state, 0, 0, s2, 0) == L'1'));
    assert(((void) "Finds at position 1", *d4_str_at(&d4_err_state, 0, 0, s2, 1) == L'2'));
    assert(((void) "Finds at position 3", *d4_str_at(&d4_err_state, 0, 0, s2, 3) == L'4'));
    assert(((void) "Finds at position -4", *d4_str_at(&d4_err_state, 0, 0, s2, -4) == L'1'));
    assert(((void) "Finds at position -1", *d4_str_at(&d4_err_state, 0, 0, s2, -1) == L'4'));
  });

  d4_str_free(s1);
  d4_str_free(s2);
}

static void test_string_concat (void) {
  d4_str_t s1 = d4_str_empty_val;
  d4_str_t s2 = d4_str_alloc(L"hello");
  d4_str_t s3 = d4_str_alloc(L" world");
  d4_str_t s4 = d4_str_alloc(L"hello world");

  d4_str_t c1 = d4_str_concat(s1, s1);
  d4_str_t c2 = d4_str_concat(s1, s2);
  d4_str_t c3 = d4_str_concat(s2, s1);
  d4_str_t c4 = d4_str_concat(s2, s3);

  assert(((void) "Concatenates two empty", d4_str_eq(c1, s1)));
  assert(((void) "Concatenates one empty and one non-empty", d4_str_eq(c2, s2)));
  assert(((void) "Concatenates one non-empty and one empty", d4_str_eq(c3, s2)));
  assert(((void) "Concatenates two non-empty", d4_str_eq(c4, s4)));

  d4_str_free(c1);
  d4_str_free(c2);
  d4_str_free(c3);
  d4_str_free(c4);

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
}

static void test_string_contains (void) {
  d4_str_t s1 = d4_str_empty_val;
  d4_str_t s2 = d4_str_alloc(L"hello");
  d4_str_t s3 = d4_str_alloc(L"he");
  d4_str_t s4 = d4_str_alloc(L"ell");
  d4_str_t s5 = d4_str_alloc(L"lo");
  d4_str_t s6 = d4_str_alloc(L"wor");

  assert(((void) "Empty contains itself", d4_str_contains(s1, s1)));
  assert(((void) "Empty doesn't contain non-empty", !d4_str_contains(s1, s4)));
  assert(((void) "Non-empty contains itself", d4_str_contains(s2, s2)));
  assert(((void) "Non-empty contains other part 1", d4_str_contains(s2, s3)));
  assert(((void) "Non-empty contains other part 2", d4_str_contains(s2, s4)));
  assert(((void) "Non-empty contains other part 3", d4_str_contains(s2, s5)));
  assert(((void) "Non-empty doesn't contains other part", !d4_str_contains(s2, s6)));

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s6);
}

static void test_string_copy (void) {
  d4_str_t s1 = d4_str_empty_val;
  d4_str_t s2 = d4_str_alloc(L"string");

  d4_str_t c1 = d4_str_copy(s1);
  d4_str_t c2 = d4_str_copy(s2);

  assert(((void) "Copies empty", d4_str_eq(c1, s1)));
  assert(((void) "Copies non-empty", d4_str_eq(c2, s2)));

  d4_str_free(c1);
  d4_str_free(c2);
  d4_str_free(s1);
  d4_str_free(s2);
}

static void test_string_empty (void) {
  d4_str_t s1 = d4_str_empty_val;
  d4_str_t s2 = d4_str_alloc(L"string");

  assert(((void) "Checks empty", d4_str_empty(s1)));
  assert(((void) "Checks non-empty", !d4_str_empty(s2)));

  d4_str_free(s1);
  d4_str_free(s2);
}

static void test_string_eq (void) {
  d4_str_t s1 = d4_str_empty_val;
  d4_str_t s2 = d4_str_empty_val;
  d4_str_t s3 = d4_str_alloc(L"string");
  d4_str_t s4 = d4_str_alloc(L"string");
  d4_str_t s5 = d4_str_alloc(L"non string");

  assert(((void) "Empty equals empty", d4_str_eq(s1, s2)));
  assert(((void) "Empty not equals empty", !d4_str_eq(s1, s3)));
  assert(((void) "Non-empty equals non-empty", d4_str_eq(s3, s4)));
  assert(((void) "Non-empty not equals empty", !d4_str_eq(s3, s1)));
  assert(((void) "Non-empty not equals non-empty", !d4_str_eq(s3, s5)));

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
}

static void test_string_escape (void) {
  d4_str_t s1 = d4_str_empty_val;
  d4_str_t s2 = d4_str_alloc(L"hello world");
  d4_str_t s3 = d4_str_alloc(L"hello \n world");
  d4_str_t s4 = d4_str_alloc(L"text \f text \n text \r text \t text \v text \" text");
  d4_str_t s5 = d4_str_alloc(L"\ntext");
  d4_str_t s6 = d4_str_alloc(L"text\n");

  d4_str_t e1 = d4_str_escape(s1);
  d4_str_t e2 = d4_str_escape(s2);
  d4_str_t e3 = d4_str_escape(s3);
  d4_str_t e4 = d4_str_escape(s4);
  d4_str_t e5 = d4_str_escape(s5);
  d4_str_t e6 = d4_str_escape(s6);

  d4_str_t r3 = d4_str_alloc(L"hello \\n world");
  d4_str_t r4 = d4_str_alloc(L"text \\f text \\n text \\r text \\t text \\v text \\\" text");
  d4_str_t r5 = d4_str_alloc(L"\\ntext");
  d4_str_t r6 = d4_str_alloc(L"text\\n");

  assert(((void) "Doesn't escape empty", d4_str_eq(e1, s1)));
  assert(((void) "Doesn't escape not containing escape characters", d4_str_eq(e2, s2)));
  assert(((void) "Escapes single character", d4_str_eq(e3, r3)));
  assert(((void) "Escapes all characters", d4_str_eq(e4, r4)));
  assert(((void) "Escapes in the front", d4_str_eq(e5, r5)));
  assert(((void) "Escapes in the back", d4_str_eq(e6, r6)));

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s6);

  d4_str_free(e1);
  d4_str_free(e2);
  d4_str_free(e3);
  d4_str_free(e4);
  d4_str_free(e5);
  d4_str_free(e6);

  d4_str_free(r3);
  d4_str_free(r4);
  d4_str_free(r5);
  d4_str_free(r6);
}

static void test_string_find (void) {
  d4_str_t s1 = d4_str_empty_val;
  d4_str_t s2 = d4_str_alloc(L"s");
  d4_str_t s3 = d4_str_alloc(L"string");
  d4_str_t s4 = d4_str_alloc(L"str");
  d4_str_t s5 = d4_str_alloc(L"tri");
  d4_str_t s6 = d4_str_alloc(L"ing");
  d4_str_t s7 = d4_str_alloc(L"g");

  assert(((void) "Finds empty in empty", d4_str_find(s1, s1) == 0));
  assert(((void) "Finds empty in string", d4_str_find(s3, s1) == 0));
  assert(((void) "Doesn't find non-empty in empty 1", d4_str_find(s1, s2) == -1));
  assert(((void) "Doesn't find non-empty in empty 2", d4_str_find(s1, s4) == -1));
  assert(((void) "Finds itself in single character string", d4_str_find(s2, s2) == 0));
  assert(((void) "Doesn't find string in single character string", d4_str_find(s2, s3) == -1));
  assert(((void) "Finds single character string in string", d4_str_find(s3, s2) == 0));
  assert(((void) "Finds string at the front in string", d4_str_find(s3, s4) == 0));
  assert(((void) "Finds string in the middle in string", d4_str_find(s3, s5) == 1));
  assert(((void) "Finds string in the back in string", d4_str_find(s3, s6) == 3));
  assert(((void) "Finds single character string in the back in string", d4_str_find(s3, s7) == 5));

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s6);
  d4_str_free(s7);
}

static void test_string_free (void) {
  d4_str_t s1 = d4_str_empty_val;
  d4_str_t s2 = d4_str_alloc(L"Test");

  d4_str_free(s1);
  d4_str_free(s2);
}

static void test_string_ge (void) {
  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"t");
  d4_str_t s3 = d4_str_alloc(L"test");
  d4_str_t s4 = d4_str_alloc(L"AARON");
  d4_str_t s5 = d4_str_alloc(L"12345");

  assert(((void) "Same strings >= same stirng", d4_str_ge(s4, s4)));
  assert(((void) "Empty string not >= single char string", !d4_str_ge(s1, s2)));
  assert(((void) "Empty string not >= multi char string", !d4_str_ge(s1, s3)));
  assert(((void) "One letter string not >= than similar string", !d4_str_ge(s2, s3)));
  assert(((void) "Lowercase single char string >= uppercase string", d4_str_ge(s2, s4)));
  assert(((void) "Lowercase single char string >= digits string", d4_str_ge(s2, s5)));
  assert(((void) "Lowercase multi char string >= uppercase string", d4_str_ge(s3, s4)));
  assert(((void) "Lowercase multi char string >= uppercase string", d4_str_ge(s3, s5)));
  assert(((void) "Uppercase string >= digits string", d4_str_ge(s4, s5)));

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
}

static void test_string_gt (void) {
  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"t");
  d4_str_t s3 = d4_str_alloc(L"test");
  d4_str_t s4 = d4_str_alloc(L"AARON");
  d4_str_t s5 = d4_str_alloc(L"12345");

  assert(((void) "Same strings not > same string", !d4_str_gt(s4, s4)));
  assert(((void) "Empty string not > single char string", !d4_str_gt(s1, s2)));
  assert(((void) "Empty string not > multi char string", !d4_str_gt(s1, s3)));
  assert(((void) "One letter string not > than similar string", !d4_str_gt(s2, s3)));
  assert(((void) "Lowercase single char string > uppercase string", d4_str_gt(s2, s4)));
  assert(((void) "Lowercase single char string > digits string", d4_str_gt(s2, s5)));
  assert(((void) "Lowercase multi char string > uppercase string", d4_str_gt(s3, s4)));
  assert(((void) "Lowercase multi char string > uppercase string", d4_str_gt(s3, s5)));
  assert(((void) "Uppercase string > digits string", d4_str_gt(s4, s5)));

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
}

static void test_string_le (void) {
  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"t");
  d4_str_t s3 = d4_str_alloc(L"test");
  d4_str_t s4 = d4_str_alloc(L"AARON");
  d4_str_t s5 = d4_str_alloc(L"12345");

  assert(((void) "Same strings <= same string", d4_str_le(s4, s4)));
  assert(((void) "Empty string <= single char string", d4_str_le(s1, s2)));
  assert(((void) "Empty string <= multi char string", d4_str_le(s1, s3)));
  assert(((void) "One letter string <= than similar string", d4_str_le(s2, s3)));
  assert(((void) "Lowercase single char string not <= uppercase string", !d4_str_le(s2, s4)));
  assert(((void) "Lowercase single char string not <= digits string", !d4_str_le(s2, s5)));
  assert(((void) "Lowercase multi char string not <= uppercase string", !d4_str_le(s3, s4)));
  assert(((void) "Lowercase multi char string not <= uppercase string", !d4_str_le(s3, s5)));
  assert(((void) "Uppercase string not <= digits string", !d4_str_le(s4, s5)));

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
}

static void test_string_lines (void) {
  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"\n");
  d4_str_t s3 = d4_str_alloc(L"t");
  d4_str_t s4 = d4_str_alloc(L"test");
  d4_str_t s5 = d4_str_alloc(L"test\r\n");
  d4_str_t s6 = d4_str_alloc(L"\ntest");
  d4_str_t s7 = d4_str_alloc(L"\ntest\n");
  d4_str_t s8 = d4_str_alloc(L"\ntest\r\n\n");
  d4_str_t s9 = d4_str_alloc(L"hello\rworld");
  d4_str_t s10 = d4_str_alloc(L"\nhello\rworld");
  d4_str_t s11 = d4_str_alloc(L"hello\rworld\r\n");
  d4_str_t s12 = d4_str_alloc(L"\nhello\rworld\r\n");

  // todo
}

static void test_string_lower (void) {
  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"t");
  d4_str_t s3 = d4_str_alloc(L"test");
  d4_str_t s4 = d4_str_alloc(L"A");
  d4_str_t s5 = d4_str_alloc(L"AARON");
  d4_str_t s6 = d4_str_alloc(L"0");
  d4_str_t s7 = d4_str_alloc(L"12345");

  d4_str_t s4_cmp = d4_str_alloc(L"a");
  d4_str_t s5_cmp = d4_str_alloc(L"aaron");

  d4_str_t r1 = d4_str_lower(s1);
  d4_str_t r2 = d4_str_lower(s2);
  d4_str_t r3 = d4_str_lower(s3);
  d4_str_t r4 = d4_str_lower(s4);
  d4_str_t r5 = d4_str_lower(s5);
  d4_str_t r6 = d4_str_lower(s6);
  d4_str_t r7 = d4_str_lower(s7);

  assert(((void) "Lowers empty string", d4_str_eq(s1, r1)));
  assert(((void) "Lowers single char lowercase string", d4_str_eq(s2, r2)));
  assert(((void) "Lowers multi char lowercase string", d4_str_eq(s3, r3)));
  assert(((void) "Lowers single char uppercase string", d4_str_eq(s4_cmp, r4)));
  assert(((void) "Lowers multi char uppercase string", d4_str_eq(s5_cmp, r5)));
  assert(((void) "Lowers single digit string", d4_str_eq(s6, r6)));
  assert(((void) "Lowers multi digit string", d4_str_eq(s7, r7)));

  d4_str_free(r1);
  d4_str_free(r2);
  d4_str_free(r3);
  d4_str_free(r4);
  d4_str_free(r5);
  d4_str_free(r6);
  d4_str_free(r7);

  d4_str_free(s4_cmp);
  d4_str_free(s5_cmp);

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s6);
  d4_str_free(s7);
}

static void test_string_lowerFirst (void) {
  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"t");
  d4_str_t s3 = d4_str_alloc(L"test");
  d4_str_t s4 = d4_str_alloc(L"A");
  d4_str_t s5 = d4_str_alloc(L"AARON");
  d4_str_t s6 = d4_str_alloc(L"0");
  d4_str_t s7 = d4_str_alloc(L"12345");

  d4_str_t s4_cmp = d4_str_alloc(L"a");
  d4_str_t s5_cmp = d4_str_alloc(L"aARON");

  d4_str_t r1 = d4_str_lowerFirst(s1);
  d4_str_t r2 = d4_str_lowerFirst(s2);
  d4_str_t r3 = d4_str_lowerFirst(s3);
  d4_str_t r4 = d4_str_lowerFirst(s4);
  d4_str_t r5 = d4_str_lowerFirst(s5);
  d4_str_t r6 = d4_str_lowerFirst(s6);
  d4_str_t r7 = d4_str_lowerFirst(s7);

  assert(((void) "Lowers first empty string", d4_str_eq(s1, r1)));
  assert(((void) "Lowers first single char lowercase string", d4_str_eq(s2, r2)));
  assert(((void) "Lowers first multi char lowercase string", d4_str_eq(s3, r3)));
  assert(((void) "Lowers first single char uppercase string", d4_str_eq(s4_cmp, r4)));
  assert(((void) "Lowers first multi char uppercase string", d4_str_eq(s5_cmp, r5)));
  assert(((void) "Lowers first single digit string", d4_str_eq(s6, r6)));
  assert(((void) "Lowers first multi digit string", d4_str_eq(s7, r7)));

  d4_str_free(r1);
  d4_str_free(r2);
  d4_str_free(r3);
  d4_str_free(r4);
  d4_str_free(r5);
  d4_str_free(r6);
  d4_str_free(r7);

  d4_str_free(s4_cmp);
  d4_str_free(s5_cmp);

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s6);
  d4_str_free(s7);
}

static void test_string_lt (void) {
  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"t");
  d4_str_t s3 = d4_str_alloc(L"test");
  d4_str_t s4 = d4_str_alloc(L"AARON");
  d4_str_t s5 = d4_str_alloc(L"12345");

  assert(((void) "Same strings not < same string", !d4_str_lt(s4, s4)));
  assert(((void) "Empty string < single char string", d4_str_lt(s1, s2)));
  assert(((void) "Empty string < multi char string", d4_str_lt(s1, s3)));
  assert(((void) "One letter string < than similar string", d4_str_lt(s2, s3)));
  assert(((void) "Lowercase single char string not < uppercase string", !d4_str_lt(s2, s4)));
  assert(((void) "Lowercase single char string not < digits string", !d4_str_lt(s2, s5)));
  assert(((void) "Lowercase multi char string not < uppercase string", !d4_str_lt(s3, s4)));
  assert(((void) "Lowercase multi char string not < uppercase string", !d4_str_lt(s3, s5)));
  assert(((void) "Uppercase string not < digits string", !d4_str_lt(s4, s5)));

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
}

static void test_string_not (void) {
  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"t");
  d4_str_t s3 = d4_str_alloc(L"test");
  d4_str_t s4 = d4_str_alloc(L"0");

  assert(((void) "NOT on empty string", d4_str_not(s1)));
  assert(((void) "NOT on single char string", !d4_str_not(s2)));
  assert(((void) "NOT on multi char string", !d4_str_not(s3)));
  assert(((void) "NOT on zero digit string", !d4_str_not(s4)));

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
}

static void test_string_quoted_escape (void) {
  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"t");
  d4_str_t s3 = d4_str_alloc(L"\"");
  d4_str_t s4 = d4_str_alloc(L"\"t");
  d4_str_t s5 = d4_str_alloc(L"t\"");
  d4_str_t s6 = d4_str_alloc(L"\"t\"");
  d4_str_t s7 = d4_str_alloc(L"test");
  d4_str_t s8 = d4_str_alloc(L"\"test");
  d4_str_t s9 = d4_str_alloc(L"test\"");
  d4_str_t s10 = d4_str_alloc(L"\"test\"");

  // todo
}

static void test_string_realloc (void) {
  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"test");
  d4_str_t s3 = d4_str_alloc(L"");

  s3 = d4_str_realloc(s3, s1);
  assert(((void) "Reallocates empty string with empty string", d4_str_eq(s1, s3)));

  s3 = d4_str_realloc(s3, s2);
  assert(((void) "Reallocates empty string with non-empty string", d4_str_eq(s2, s3)));

  s3 = d4_str_realloc(s3, s1);
  assert(((void) "Reallocates non-empty string with empty string", d4_str_eq(s1, s3)));

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
}

static void test_string_replace (void) {
  // todo
}

static void test_string_slice (void) {
  // todo test negative numbers
}

static void test_string_split (void) {
  // todo test multi char delimiter
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
  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"t");
  d4_str_t s3 = d4_str_alloc(L"t ");
  d4_str_t s4 = d4_str_alloc(L"\ft");
  d4_str_t s5 = d4_str_alloc(L"\ft\r");
  d4_str_t s6 = d4_str_alloc(L"test");
  d4_str_t s7 = d4_str_alloc(L"\ntest");
  d4_str_t s8 = d4_str_alloc(L"test\t");
  d4_str_t s9 = d4_str_alloc(L"\vtest\r");
  d4_str_t s10 = d4_str_alloc(L"multiple words");
  d4_str_t s11 = d4_str_alloc(L"\nmultiple words");
  d4_str_t s12 = d4_str_alloc(L"multiple words\n");
  d4_str_t s13 = d4_str_alloc(L"\nmultiple words\n");

  // todo
}

static void test_string_trimEnd (void) {
  // todo
}

static void test_string_trimStart (void) {
  // todo
}

static void test_string_upper (void) {
  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"t");
  d4_str_t s3 = d4_str_alloc(L"test");
  d4_str_t s4 = d4_str_alloc(L"A");
  d4_str_t s5 = d4_str_alloc(L"AARON");
  d4_str_t s6 = d4_str_alloc(L"0");
  d4_str_t s7 = d4_str_alloc(L"12345");

  d4_str_t s2_cmp = d4_str_alloc(L"T");
  d4_str_t s3_cmp = d4_str_alloc(L"TEST");

  d4_str_t r1 = d4_str_upper(s1);
  d4_str_t r2 = d4_str_upper(s2);
  d4_str_t r3 = d4_str_upper(s3);
  d4_str_t r4 = d4_str_upper(s4);
  d4_str_t r5 = d4_str_upper(s5);
  d4_str_t r6 = d4_str_upper(s6);
  d4_str_t r7 = d4_str_upper(s7);

  assert(((void) "Uppers empty string", d4_str_eq(s1, r1)));
  assert(((void) "Uppers single char lowercase string", d4_str_eq(s2_cmp, r2)));
  assert(((void) "Uppers multi char lowercase string", d4_str_eq(s3_cmp, r3)));
  assert(((void) "Uppers single char uppercase string", d4_str_eq(s4, r4)));
  assert(((void) "Uppers multi char uppercase string", d4_str_eq(s5, r5)));
  assert(((void) "Uppers single digit string", d4_str_eq(s6, r6)));
  assert(((void) "Uppers multi digit string", d4_str_eq(s7, r7)));

  d4_str_free(r1);
  d4_str_free(r2);
  d4_str_free(r3);
  d4_str_free(r4);
  d4_str_free(r5);
  d4_str_free(r6);
  d4_str_free(r7);

  d4_str_free(s2_cmp);
  d4_str_free(s3_cmp);

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s6);
  d4_str_free(s7);
}

static void test_string_upperFirst (void) {
  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"t");
  d4_str_t s3 = d4_str_alloc(L"test");
  d4_str_t s4 = d4_str_alloc(L"A");
  d4_str_t s5 = d4_str_alloc(L"AARON");
  d4_str_t s6 = d4_str_alloc(L"0");
  d4_str_t s7 = d4_str_alloc(L"12345");

  d4_str_t s2_cmp = d4_str_alloc(L"T");
  d4_str_t s3_cmp = d4_str_alloc(L"Test");

  d4_str_t r1 = d4_str_upperFirst(s1);
  d4_str_t r2 = d4_str_upperFirst(s2);
  d4_str_t r3 = d4_str_upperFirst(s3);
  d4_str_t r4 = d4_str_upperFirst(s4);
  d4_str_t r5 = d4_str_upperFirst(s5);
  d4_str_t r6 = d4_str_upperFirst(s6);
  d4_str_t r7 = d4_str_upperFirst(s7);

  assert(((void) "Uppers first empty string", d4_str_eq(s1, r1)));
  assert(((void) "Uppers first single char lowercase string", d4_str_eq(s2_cmp, r2)));
  assert(((void) "Uppers first multi char lowercase string", d4_str_eq(s3_cmp, r3)));
  assert(((void) "Uppers first single char uppercase string", d4_str_eq(s4, r4)));
  assert(((void) "Uppers first multi char uppercase string", d4_str_eq(s5, r5)));
  assert(((void) "Uppers first single digit string", d4_str_eq(s6, r6)));
  assert(((void) "Uppers first multi digit string", d4_str_eq(s7, r7)));

  d4_str_free(r1);
  d4_str_free(r2);
  d4_str_free(r3);
  d4_str_free(r4);
  d4_str_free(r5);
  d4_str_free(r6);
  d4_str_free(r7);

  d4_str_free(s2_cmp);
  d4_str_free(s3_cmp);

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s6);
  d4_str_free(s7);
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
  test_string_not();
  test_string_quoted_escape();
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
