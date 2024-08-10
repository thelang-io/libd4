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
  d4_str_t s_empty = d4_str_alloc(L"");
  d4_str_t s_t = d4_str_alloc(L"t");
  d4_str_t s_t_with_crnl = d4_str_alloc(L"t\r\n");
  d4_str_t s_t_with_nl = d4_str_alloc(L"t\n");
  d4_str_t s_test = d4_str_alloc(L"test");
  d4_str_t s_test_with_crnl = d4_str_alloc(L"test\r\n");
  d4_str_t s_test_with_nl = d4_str_alloc(L"test\n");
  d4_str_t s_hello = d4_str_alloc(L"hello");
  d4_str_t s_hello_with_cr = d4_str_alloc(L"hello\r");
  d4_str_t s_world = d4_str_alloc(L"world");
  d4_str_t s_world_with_crnl = d4_str_alloc(L"world\r\n");
  d4_str_t s_world_with_nl = d4_str_alloc(L"world\n");
  d4_str_t s_cr = d4_str_alloc(L"\r");
  d4_str_t s_nl = d4_str_alloc(L"\n");

  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"\n");
  d4_str_t s3 = d4_str_alloc(L"\n\n");
  d4_str_t s4 = d4_str_alloc(L"t");
  d4_str_t s5 = d4_str_alloc(L"t\n");
  d4_str_t s6 = d4_str_alloc(L"\rt");
  d4_str_t s7 = d4_str_alloc(L"\rt\r\n");
  d4_str_t s8 = d4_str_alloc(L"\rt\r\n\n");
  d4_str_t s9 = d4_str_alloc(L"test");
  d4_str_t s10 = d4_str_alloc(L"test\r\n");
  d4_str_t s11 = d4_str_alloc(L"\ntest");
  d4_str_t s12 = d4_str_alloc(L"\ntest\n");
  d4_str_t s13 = d4_str_alloc(L"\ntest\r\n\n");
  d4_str_t s14 = d4_str_alloc(L"hello\rworld");
  d4_str_t s15 = d4_str_alloc(L"hello\rworld\r\n");
  d4_str_t s16 = d4_str_alloc(L"\nhello\rworld");
  d4_str_t s17 = d4_str_alloc(L"\nhello\rworld\r\n");
  d4_str_t s18 = d4_str_alloc(L"\nhello\rworld\r\n\n");
  d4_str_t s19 = d4_str_alloc(L"hello\rworld\ntest");
  d4_str_t s20 = d4_str_alloc(L"hello\rworld\ntest\r\n");
  d4_str_t s21 = d4_str_alloc(L"\nhello\rworld\ntest");
  d4_str_t s22 = d4_str_alloc(L"\nhello\rworld\ntest\r\n");
  d4_str_t s23 = d4_str_alloc(L"\nhello\rworld\ntest\r\n\n");

  d4_arr_str_t r1 = d4_str_lines(s1, 0, false);
  d4_arr_str_t r2 = d4_str_lines(s2, 0, false);
  d4_arr_str_t r3 = d4_str_lines(s3, 0, false);
  d4_arr_str_t r4 = d4_str_lines(s4, 0, false);
  d4_arr_str_t r5 = d4_str_lines(s5, 0, false);
  d4_arr_str_t r6 = d4_str_lines(s6, 0, false);
  d4_arr_str_t r7 = d4_str_lines(s7, 0, false);
  d4_arr_str_t r8 = d4_str_lines(s8, 0, false);
  d4_arr_str_t r9 = d4_str_lines(s9, 0, false);
  d4_arr_str_t r10 = d4_str_lines(s10, 0, false);
  d4_arr_str_t r11 = d4_str_lines(s11, 0, false);
  d4_arr_str_t r12 = d4_str_lines(s12, 0, false);
  d4_arr_str_t r13 = d4_str_lines(s13, 0, false);
  d4_arr_str_t r14 = d4_str_lines(s14, 0, false);
  d4_arr_str_t r15 = d4_str_lines(s15, 0, false);
  d4_arr_str_t r16 = d4_str_lines(s16, 0, false);
  d4_arr_str_t r17 = d4_str_lines(s17, 0, false);
  d4_arr_str_t r18 = d4_str_lines(s18, 0, false);
  d4_arr_str_t r19 = d4_str_lines(s19, 0, false);
  d4_arr_str_t r20 = d4_str_lines(s20, 0, false);
  d4_arr_str_t r21 = d4_str_lines(s21, 0, false);
  d4_arr_str_t r22 = d4_str_lines(s22, 0, false);
  d4_arr_str_t r23 = d4_str_lines(s23, 0, false);

  d4_arr_str_t r24 = d4_str_lines(s1, 1, true);
  d4_arr_str_t r25 = d4_str_lines(s2, 1, true);
  d4_arr_str_t r26 = d4_str_lines(s3, 1, true);
  d4_arr_str_t r27 = d4_str_lines(s4, 1, true);
  d4_arr_str_t r28 = d4_str_lines(s5, 1, true);
  d4_arr_str_t r29 = d4_str_lines(s6, 1, true);
  d4_arr_str_t r30 = d4_str_lines(s7, 1, true);
  d4_arr_str_t r31 = d4_str_lines(s8, 1, true);
  d4_arr_str_t r32 = d4_str_lines(s9, 1, true);
  d4_arr_str_t r33 = d4_str_lines(s10, 1, true);
  d4_arr_str_t r34 = d4_str_lines(s11, 1, true);
  d4_arr_str_t r35 = d4_str_lines(s12, 1, true);
  d4_arr_str_t r36 = d4_str_lines(s13, 1, true);
  d4_arr_str_t r37 = d4_str_lines(s14, 1, true);
  d4_arr_str_t r38 = d4_str_lines(s15, 1, true);
  d4_arr_str_t r39 = d4_str_lines(s16, 1, true);
  d4_arr_str_t r40 = d4_str_lines(s17, 1, true);
  d4_arr_str_t r41 = d4_str_lines(s18, 1, true);
  d4_arr_str_t r42 = d4_str_lines(s19, 1, true);
  d4_arr_str_t r43 = d4_str_lines(s20, 1, true);
  d4_arr_str_t r44 = d4_str_lines(s21, 1, true);
  d4_arr_str_t r45 = d4_str_lines(s22, 1, true);
  d4_arr_str_t r46 = d4_str_lines(s23, 1, true);

  d4_arr_str_t r1_cmp = d4_arr_str_alloc(0);
  d4_arr_str_t r2_cmp = d4_arr_str_alloc(1, s_empty);
  d4_arr_str_t r3_cmp = d4_arr_str_alloc(2, s_empty, s_empty);
  d4_arr_str_t r4_cmp = d4_arr_str_alloc(1, s_t);
  d4_arr_str_t r5_cmp = d4_arr_str_alloc(1, s_t);
  d4_arr_str_t r6_cmp = d4_arr_str_alloc(2, s_empty, s_t);
  d4_arr_str_t r7_cmp = d4_arr_str_alloc(2, s_empty, s_t);
  d4_arr_str_t r8_cmp = d4_arr_str_alloc(3, s_empty, s_t, s_empty);
  d4_arr_str_t r9_cmp = d4_arr_str_alloc(1, s_test);
  d4_arr_str_t r10_cmp = d4_arr_str_alloc(1, s_test);
  d4_arr_str_t r11_cmp = d4_arr_str_alloc(2, s_empty, s_test);
  d4_arr_str_t r12_cmp = d4_arr_str_alloc(2, s_empty, s_test);
  d4_arr_str_t r13_cmp = d4_arr_str_alloc(3, s_empty, s_test, s_empty);
  d4_arr_str_t r14_cmp = d4_arr_str_alloc(2, s_hello, s_world);
  d4_arr_str_t r15_cmp = d4_arr_str_alloc(2, s_hello, s_world);
  d4_arr_str_t r16_cmp = d4_arr_str_alloc(3, s_empty, s_hello, s_world);
  d4_arr_str_t r17_cmp = d4_arr_str_alloc(3, s_empty, s_hello, s_world);
  d4_arr_str_t r18_cmp = d4_arr_str_alloc(4, s_empty, s_hello, s_world, s_empty);
  d4_arr_str_t r19_cmp = d4_arr_str_alloc(3, s_hello, s_world, s_test);
  d4_arr_str_t r20_cmp = d4_arr_str_alloc(3, s_hello, s_world, s_test);
  d4_arr_str_t r21_cmp = d4_arr_str_alloc(4, s_empty, s_hello, s_world, s_test);
  d4_arr_str_t r22_cmp = d4_arr_str_alloc(4, s_empty, s_hello, s_world, s_test);
  d4_arr_str_t r23_cmp = d4_arr_str_alloc(5, s_empty, s_hello, s_world, s_test, s_empty);

  d4_arr_str_t r24_cmp = d4_arr_str_alloc(0);
  d4_arr_str_t r25_cmp = d4_arr_str_alloc(1, s_nl);
  d4_arr_str_t r26_cmp = d4_arr_str_alloc(2, s_nl, s_nl);
  d4_arr_str_t r27_cmp = d4_arr_str_alloc(1, s_t);
  d4_arr_str_t r28_cmp = d4_arr_str_alloc(1, s_t_with_nl);
  d4_arr_str_t r29_cmp = d4_arr_str_alloc(2, s_cr, s_t);
  d4_arr_str_t r30_cmp = d4_arr_str_alloc(2, s_cr, s_t_with_crnl);
  d4_arr_str_t r31_cmp = d4_arr_str_alloc(3, s_cr, s_t_with_crnl, s_nl);
  d4_arr_str_t r32_cmp = d4_arr_str_alloc(1, s_test);
  d4_arr_str_t r33_cmp = d4_arr_str_alloc(1, s_test_with_crnl);
  d4_arr_str_t r34_cmp = d4_arr_str_alloc(2, s_nl, s_test);
  d4_arr_str_t r35_cmp = d4_arr_str_alloc(2, s_nl, s_test_with_nl);
  d4_arr_str_t r36_cmp = d4_arr_str_alloc(3, s_nl, s_test_with_crnl, s_nl);
  d4_arr_str_t r37_cmp = d4_arr_str_alloc(2, s_hello_with_cr, s_world);
  d4_arr_str_t r38_cmp = d4_arr_str_alloc(2, s_hello_with_cr, s_world_with_crnl);
  d4_arr_str_t r39_cmp = d4_arr_str_alloc(3, s_nl, s_hello_with_cr, s_world);
  d4_arr_str_t r40_cmp = d4_arr_str_alloc(3, s_nl, s_hello_with_cr, s_world_with_crnl);
  d4_arr_str_t r41_cmp = d4_arr_str_alloc(4, s_nl, s_hello_with_cr, s_world_with_crnl, s_nl);
  d4_arr_str_t r42_cmp = d4_arr_str_alloc(3, s_hello_with_cr, s_world_with_nl, s_test);
  d4_arr_str_t r43_cmp = d4_arr_str_alloc(3, s_hello_with_cr, s_world_with_nl, s_test_with_crnl);
  d4_arr_str_t r44_cmp = d4_arr_str_alloc(4, s_nl, s_hello_with_cr, s_world_with_nl, s_test);
  d4_arr_str_t r45_cmp = d4_arr_str_alloc(4, s_nl, s_hello_with_cr, s_world_with_nl, s_test_with_crnl);
  d4_arr_str_t r46_cmp = d4_arr_str_alloc(5, s_nl, s_hello_with_cr, s_world_with_nl, s_test_with_crnl, s_nl);

  assert(((void) "Splits into lines empty string", d4_arr_str_eq(r1, r1_cmp)));
  assert(((void) "Splits into lines single line-break string", d4_arr_str_eq(r2, r2_cmp)));
  assert(((void) "Splits into lines multi line-break string", d4_arr_str_eq(r3, r3_cmp)));
  assert(((void) "Splits into lines single char string", d4_arr_str_eq(r4, r4_cmp)));
  assert(((void) "Splits into lines single char string with trailing line-break", d4_arr_str_eq(r5, r5_cmp)));
  assert(((void) "Splits into lines single char string with leading line-break", d4_arr_str_eq(r6, r6_cmp)));
  assert(((void) "Splits into lines single char string with leading and trailing line-breaks", d4_arr_str_eq(r7, r7_cmp)));
  assert(((void) "Splits into lines single char string with leading and multiple trailing line-breaks", d4_arr_str_eq(r8, r8_cmp)));
  assert(((void) "Splits into lines multi char string", d4_arr_str_eq(r9, r9_cmp)));
  assert(((void) "Splits into lines multi char string with trailing line-break", d4_arr_str_eq(r10, r10_cmp)));
  assert(((void) "Splits into lines multi char string with leading line-break", d4_arr_str_eq(r11, r11_cmp)));
  assert(((void) "Splits into lines multi char string with leading and trailing line-breaks", d4_arr_str_eq(r12, r12_cmp)));
  assert(((void) "Splits into lines multi char string with leading and multiple trailing line-breaks", d4_arr_str_eq(r13, r13_cmp)));
  assert(((void) "Splits into lines multi char two-line string", d4_arr_str_eq(r14, r14_cmp)));
  assert(((void) "Splits into lines multi char two-line string with trailing line-break", d4_arr_str_eq(r15, r15_cmp)));
  assert(((void) "Splits into lines multi char two-line string with leading line-break", d4_arr_str_eq(r16, r16_cmp)));
  assert(((void) "Splits into lines multi char two-line string with leading and trailing line-breaks", d4_arr_str_eq(r17, r17_cmp)));
  assert(((void) "Splits into lines multi char two-line string with leading and multiple trailing line-breaks", d4_arr_str_eq(r18, r18_cmp)));
  assert(((void) "Splits into lines multi char multiline string", d4_arr_str_eq(r19, r19_cmp)));
  assert(((void) "Splits into lines multi char multiline string with trailing line-break", d4_arr_str_eq(r20, r20_cmp)));
  assert(((void) "Splits into lines multi char multiline string with leading line-break", d4_arr_str_eq(r21, r21_cmp)));
  assert(((void) "Splits into lines multi char multiline string with leading and trailing line-breaks", d4_arr_str_eq(r22, r22_cmp)));
  assert(((void) "Splits into lines multi char multiline string with leading and multiple trailing line-breaks", d4_arr_str_eq(r23, r23_cmp)));

  assert(((void) "Splits into lines keeping line-breaks empty string", d4_arr_str_eq(r24, r24_cmp)));
  assert(((void) "Splits into lines keeping line-breaks single line-break string", d4_arr_str_eq(r25, r25_cmp)));
  assert(((void) "Splits into lines keeping line-breaks multi line-break string", d4_arr_str_eq(r26, r26_cmp)));
  assert(((void) "Splits into lines keeping line-breaks single char string", d4_arr_str_eq(r27, r27_cmp)));
  assert(((void) "Splits into lines keeping line-breaks single char string with trailing line-break", d4_arr_str_eq(r28, r28_cmp)));
  assert(((void) "Splits into lines keeping line-breaks single char string with leading line-break", d4_arr_str_eq(r29, r29_cmp)));
  assert(((void) "Splits into lines keeping line-breaks single char string with leading and trailing line-breaks", d4_arr_str_eq(r30, r30_cmp)));
  assert(((void) "Splits into lines keeping line-breaks single char string with leading and multiple trailing line-breaks", d4_arr_str_eq(r31, r31_cmp)));
  assert(((void) "Splits into lines keeping line-breaks multi char string", d4_arr_str_eq(r32, r32_cmp)));
  assert(((void) "Splits into lines keeping line-breaks multi char string with trailing line-break", d4_arr_str_eq(r33, r33_cmp)));
  assert(((void) "Splits into lines keeping line-breaks multi char string with leading line-break", d4_arr_str_eq(r34, r34_cmp)));
  assert(((void) "Splits into lines keeping line-breaks multi char string with leading and trailing line-breaks", d4_arr_str_eq(r35, r35_cmp)));
  assert(((void) "Splits into lines keeping line-breaks multi char string with leading and multiple trailing line-breaks", d4_arr_str_eq(r36, r36_cmp)));
  assert(((void) "Splits into lines keeping line-breaks multi char two-line string", d4_arr_str_eq(r37, r37_cmp)));
  assert(((void) "Splits into lines keeping line-breaks multi char two-line string with trailing line-break", d4_arr_str_eq(r38, r38_cmp)));
  assert(((void) "Splits into lines keeping line-breaks multi char two-line string with leading line-break", d4_arr_str_eq(r39, r39_cmp)));
  assert(((void) "Splits into lines keeping line-breaks multi char two-line string with leading and trailing line-breaks", d4_arr_str_eq(r40, r40_cmp)));
  assert(((void) "Splits into lines keeping line-breaks multi char two-line string with leading and multiple trailing line-breaks", d4_arr_str_eq(r41, r41_cmp)));
  assert(((void) "Splits into lines keeping line-breaks multi char multiline string", d4_arr_str_eq(r42, r42_cmp)));
  assert(((void) "Splits into lines keeping line-breaks multi char multiline string with trailing line-break", d4_arr_str_eq(r43, r43_cmp)));
  assert(((void) "Splits into lines keeping line-breaks multi char multiline string with leading line-break", d4_arr_str_eq(r44, r44_cmp)));
  assert(((void) "Splits into lines keeping line-breaks multi char multiline string with leading and trailing line-breaks", d4_arr_str_eq(r45, r45_cmp)));
  assert(((void) "Splits into lines keeping line-breaks multi char multiline string with leading and multiple trailing line-breaks", d4_arr_str_eq(r46, r46_cmp)));

  d4_arr_str_free(r1_cmp);
  d4_arr_str_free(r2_cmp);
  d4_arr_str_free(r3_cmp);
  d4_arr_str_free(r4_cmp);
  d4_arr_str_free(r5_cmp);
  d4_arr_str_free(r6_cmp);
  d4_arr_str_free(r7_cmp);
  d4_arr_str_free(r8_cmp);
  d4_arr_str_free(r9_cmp);
  d4_arr_str_free(r10_cmp);
  d4_arr_str_free(r11_cmp);
  d4_arr_str_free(r12_cmp);
  d4_arr_str_free(r13_cmp);
  d4_arr_str_free(r14_cmp);
  d4_arr_str_free(r15_cmp);
  d4_arr_str_free(r16_cmp);
  d4_arr_str_free(r17_cmp);
  d4_arr_str_free(r18_cmp);
  d4_arr_str_free(r19_cmp);
  d4_arr_str_free(r20_cmp);
  d4_arr_str_free(r21_cmp);
  d4_arr_str_free(r22_cmp);
  d4_arr_str_free(r23_cmp);
  d4_arr_str_free(r24_cmp);
  d4_arr_str_free(r25_cmp);
  d4_arr_str_free(r26_cmp);
  d4_arr_str_free(r27_cmp);
  d4_arr_str_free(r28_cmp);
  d4_arr_str_free(r29_cmp);
  d4_arr_str_free(r30_cmp);
  d4_arr_str_free(r31_cmp);
  d4_arr_str_free(r32_cmp);
  d4_arr_str_free(r33_cmp);
  d4_arr_str_free(r34_cmp);
  d4_arr_str_free(r35_cmp);
  d4_arr_str_free(r36_cmp);
  d4_arr_str_free(r37_cmp);
  d4_arr_str_free(r38_cmp);
  d4_arr_str_free(r39_cmp);
  d4_arr_str_free(r40_cmp);
  d4_arr_str_free(r41_cmp);
  d4_arr_str_free(r42_cmp);
  d4_arr_str_free(r43_cmp);
  d4_arr_str_free(r44_cmp);
  d4_arr_str_free(r45_cmp);
  d4_arr_str_free(r46_cmp);

  d4_arr_str_free(r1);
  d4_arr_str_free(r2);
  d4_arr_str_free(r3);
  d4_arr_str_free(r4);
  d4_arr_str_free(r5);
  d4_arr_str_free(r6);
  d4_arr_str_free(r7);
  d4_arr_str_free(r8);
  d4_arr_str_free(r9);
  d4_arr_str_free(r10);
  d4_arr_str_free(r11);
  d4_arr_str_free(r12);
  d4_arr_str_free(r13);
  d4_arr_str_free(r14);
  d4_arr_str_free(r15);
  d4_arr_str_free(r16);
  d4_arr_str_free(r17);
  d4_arr_str_free(r18);
  d4_arr_str_free(r19);
  d4_arr_str_free(r20);
  d4_arr_str_free(r21);
  d4_arr_str_free(r22);
  d4_arr_str_free(r23);
  d4_arr_str_free(r24);
  d4_arr_str_free(r25);
  d4_arr_str_free(r26);
  d4_arr_str_free(r27);
  d4_arr_str_free(r28);
  d4_arr_str_free(r29);
  d4_arr_str_free(r30);
  d4_arr_str_free(r31);
  d4_arr_str_free(r32);
  d4_arr_str_free(r33);
  d4_arr_str_free(r34);
  d4_arr_str_free(r35);
  d4_arr_str_free(r36);
  d4_arr_str_free(r37);
  d4_arr_str_free(r38);
  d4_arr_str_free(r39);
  d4_arr_str_free(r40);
  d4_arr_str_free(r41);
  d4_arr_str_free(r42);
  d4_arr_str_free(r43);
  d4_arr_str_free(r44);
  d4_arr_str_free(r45);
  d4_arr_str_free(r46);

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s6);
  d4_str_free(s7);
  d4_str_free(s8);
  d4_str_free(s9);
  d4_str_free(s10);
  d4_str_free(s11);
  d4_str_free(s12);
  d4_str_free(s13);
  d4_str_free(s14);
  d4_str_free(s15);
  d4_str_free(s16);
  d4_str_free(s17);
  d4_str_free(s18);
  d4_str_free(s19);
  d4_str_free(s20);
  d4_str_free(s21);
  d4_str_free(s22);
  d4_str_free(s23);

  d4_str_free(s_empty);
  d4_str_free(s_t);
  d4_str_free(s_t_with_crnl);
  d4_str_free(s_t_with_nl);
  d4_str_free(s_test);
  d4_str_free(s_test_with_crnl);
  d4_str_free(s_test_with_nl);
  d4_str_free(s_hello);
  d4_str_free(s_hello_with_cr);
  d4_str_free(s_world);
  d4_str_free(s_world_with_crnl);
  d4_str_free(s_world_with_nl);
  d4_str_free(s_cr);
  d4_str_free(s_nl);
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
  d4_str_t s1 = d4_str_empty_val;
  d4_str_t s2 = d4_str_alloc(L"hello world");
  d4_str_t s3 = d4_str_alloc(L"hello \n world");
  d4_str_t s4 = d4_str_alloc(L"text \f text \n text \r text \t text \v text \" text");
  d4_str_t s5 = d4_str_alloc(L"\ntext");
  d4_str_t s6 = d4_str_alloc(L"text\n");

  d4_str_t e1 = d4_str_quoted_escape(s1);
  d4_str_t e2 = d4_str_quoted_escape(s2);
  d4_str_t e3 = d4_str_quoted_escape(s3);
  d4_str_t e4 = d4_str_quoted_escape(s4);
  d4_str_t e5 = d4_str_quoted_escape(s5);
  d4_str_t e6 = d4_str_quoted_escape(s6);

  d4_str_t r1 = d4_str_alloc(L"\"\"");
  d4_str_t r2 = d4_str_alloc(L"\"hello world\"");
  d4_str_t r3 = d4_str_alloc(L"\"hello \\n world\"");
  d4_str_t r4 = d4_str_alloc(L"\"text \\f text \\n text \\r text \\t text \\v text \\\" text\"");
  d4_str_t r5 = d4_str_alloc(L"\"\\ntext\"");
  d4_str_t r6 = d4_str_alloc(L"\"text\\n\"");

  assert(((void) "Quotes and doesn't escape empty", d4_str_eq(e1, r1)));
  assert(((void) "Doesn't escape not containing escape characters", d4_str_eq(e2, r2)));
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

  d4_str_free(r1);
  d4_str_free(r2);
  d4_str_free(r3);
  d4_str_free(r4);
  d4_str_free(r5);
  d4_str_free(r6);
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
  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"t");
  d4_str_t s3 = d4_str_alloc(L"test");
  d4_str_t s4 = d4_str_alloc(L"hello world");

  d4_str_t r1 = d4_str_slice(s1, 0, 0, 0, 0);
  d4_str_t r2 = d4_str_slice(s1, 1, 1, 0, 0);
  d4_str_t r3 = d4_str_slice(s1, 1, 3, 0, 0);
  d4_str_t r4 = d4_str_slice(s1, 1, 20, 0, 0);
  d4_str_t r5 = d4_str_slice(s1, 1, -1, 0, 0);
  d4_str_t r6 = d4_str_slice(s1, 1, -3, 0, 0);
  d4_str_t r7 = d4_str_slice(s1, 1, -20, 0, 0);
  d4_str_t r8 = d4_str_slice(s1, 0, 0, 1, 1);
  d4_str_t r9 = d4_str_slice(s1, 0, 0, 1, 3);
  d4_str_t r10 = d4_str_slice(s1, 0, 0, 1, 20);
  d4_str_t r11 = d4_str_slice(s1, 0, 0, 1, -1);
  d4_str_t r12 = d4_str_slice(s1, 0, 0, 1, -3);
  d4_str_t r13 = d4_str_slice(s1, 0, 0, 1, -20);
  d4_str_t r14 = d4_str_slice(s1, 1, 1, 1, 3);
  d4_str_t r15 = d4_str_slice(s1, 1, 3, 1, 20);
  d4_str_t r16 = d4_str_slice(s1, 1, 20, 1, 100);
  d4_str_t r17 = d4_str_slice(s1, 1, -3, 1, -1);
  d4_str_t r18 = d4_str_slice(s1, 1, -20, 1, -3);
  d4_str_t r19 = d4_str_slice(s1, 1, -100, 1, -20);

  d4_str_t r20 = d4_str_slice(s2, 0, 0, 0, 0);
  d4_str_t r21 = d4_str_slice(s2, 1, 1, 0, 0);
  d4_str_t r22 = d4_str_slice(s2, 1, 3, 0, 0);
  d4_str_t r23 = d4_str_slice(s2, 1, 20, 0, 0);
  d4_str_t r24 = d4_str_slice(s2, 1, -1, 0, 0);
  d4_str_t r25 = d4_str_slice(s2, 1, -3, 0, 0);
  d4_str_t r26 = d4_str_slice(s2, 1, -20, 0, 0);
  d4_str_t r27 = d4_str_slice(s2, 0, 0, 1, 1);
  d4_str_t r28 = d4_str_slice(s2, 0, 0, 1, 3);
  d4_str_t r29 = d4_str_slice(s2, 0, 0, 1, 20);
  d4_str_t r30 = d4_str_slice(s2, 0, 0, 1, -1);
  d4_str_t r31 = d4_str_slice(s2, 0, 0, 1, -3);
  d4_str_t r32 = d4_str_slice(s2, 0, 0, 1, -20);
  d4_str_t r33 = d4_str_slice(s2, 1, 1, 1, 3);
  d4_str_t r34 = d4_str_slice(s2, 1, 3, 1, 20);
  d4_str_t r35 = d4_str_slice(s2, 1, 20, 1, 100);
  d4_str_t r36 = d4_str_slice(s2, 1, -3, 1, -1);
  d4_str_t r37 = d4_str_slice(s2, 1, -20, 1, -3);
  d4_str_t r38 = d4_str_slice(s2, 1, -100, 1, -20);

  d4_str_t r40 = d4_str_slice(s3, 0, 0, 0, 0);
  d4_str_t r41 = d4_str_slice(s3, 1, 1, 0, 0);
  d4_str_t r42 = d4_str_slice(s3, 1, 3, 0, 0);
  d4_str_t r43 = d4_str_slice(s3, 1, 20, 0, 0);
  d4_str_t r44 = d4_str_slice(s3, 1, -1, 0, 0);
  d4_str_t r45 = d4_str_slice(s3, 1, -3, 0, 0);
  d4_str_t r46 = d4_str_slice(s3, 1, -20, 0, 0);
  d4_str_t r47 = d4_str_slice(s3, 0, 0, 1, 1);
  d4_str_t r48 = d4_str_slice(s3, 0, 0, 1, 3);
  d4_str_t r49 = d4_str_slice(s3, 0, 0, 1, 20);
  d4_str_t r50 = d4_str_slice(s3, 0, 0, 1, -1);
  d4_str_t r51 = d4_str_slice(s3, 0, 0, 1, -3);
  d4_str_t r52 = d4_str_slice(s3, 0, 0, 1, -20);
  d4_str_t r53 = d4_str_slice(s3, 1, 1, 1, 3);
  d4_str_t r54 = d4_str_slice(s3, 1, 3, 1, 20);
  d4_str_t r55 = d4_str_slice(s3, 1, 20, 1, 100);
  d4_str_t r56 = d4_str_slice(s3, 1, -3, 1, -1);
  d4_str_t r57 = d4_str_slice(s3, 1, -20, 1, -3);
  d4_str_t r58 = d4_str_slice(s3, 1, -100, 1, -20);

  d4_str_t r60 = d4_str_slice(s4, 0, 0, 0, 0);
  d4_str_t r61 = d4_str_slice(s4, 1, 1, 0, 0);
  d4_str_t r62 = d4_str_slice(s4, 1, 3, 0, 0);
  d4_str_t r63 = d4_str_slice(s4, 1, 20, 0, 0);
  d4_str_t r64 = d4_str_slice(s4, 1, -1, 0, 0);
  d4_str_t r65 = d4_str_slice(s4, 1, -3, 0, 0);
  d4_str_t r66 = d4_str_slice(s4, 1, -20, 0, 0);
  d4_str_t r67 = d4_str_slice(s4, 0, 0, 1, 1);
  d4_str_t r68 = d4_str_slice(s4, 0, 0, 1, 3);
  d4_str_t r69 = d4_str_slice(s4, 0, 0, 1, 20);
  d4_str_t r70 = d4_str_slice(s4, 0, 0, 1, -1);
  d4_str_t r71 = d4_str_slice(s4, 0, 0, 1, -3);
  d4_str_t r72 = d4_str_slice(s4, 0, 0, 1, -20);
  d4_str_t r73 = d4_str_slice(s4, 1, 1, 1, 3);
  d4_str_t r74 = d4_str_slice(s4, 1, 3, 1, 20);
  d4_str_t r75 = d4_str_slice(s4, 1, 20, 1, 100);
  d4_str_t r76 = d4_str_slice(s4, 1, -3, 1, -1);
  d4_str_t r77 = d4_str_slice(s4, 1, -20, 1, -3);
  d4_str_t r78 = d4_str_slice(s4, 1, -100, 1, -20);

  d4_str_t r_empty = d4_str_alloc(L"");
  d4_str_t r_d = d4_str_alloc(L"d");
  d4_str_t r_el = d4_str_alloc(L"el");
  d4_str_t r_ello_world = d4_str_alloc(L"ello world");
  d4_str_t r_es = d4_str_alloc(L"es");
  d4_str_t r_est = d4_str_alloc(L"est");
  d4_str_t r_h = d4_str_alloc(L"h");
  d4_str_t r_hel = d4_str_alloc(L"hel");
  d4_str_t r_hello_wo = d4_str_alloc(L"hello wo");
  d4_str_t r_hello_worl = d4_str_alloc(L"hello worl");
  d4_str_t r_hello_world = d4_str_alloc(L"hello world");
  d4_str_t r_lo_world = d4_str_alloc(L"lo world");
  d4_str_t r_rl = d4_str_alloc(L"rl");
  d4_str_t r_rld = d4_str_alloc(L"rld");
  d4_str_t r_t = d4_str_alloc(L"t");
  d4_str_t r_tes = d4_str_alloc(L"tes");
  d4_str_t r_test = d4_str_alloc(L"test");

  assert(((void) "Slices empty string with nil, nil", d4_str_eq(r1, r_empty)));
  assert(((void) "Slices empty string with 1, nil", d4_str_eq(r2, r_empty)));
  assert(((void) "Slices empty string with 3, nil", d4_str_eq(r3, r_empty)));
  assert(((void) "Slices empty string with 20, nil", d4_str_eq(r4, r_empty)));
  assert(((void) "Slices empty string with -1, nil", d4_str_eq(r5, r_empty)));
  assert(((void) "Slices empty string with -3, nil", d4_str_eq(r6, r_empty)));
  assert(((void) "Slices empty string with -20, nil", d4_str_eq(r7, r_empty)));
  assert(((void) "Slices empty string with nil, 1", d4_str_eq(r8, r_empty)));
  assert(((void) "Slices empty string with nil, 3", d4_str_eq(r9, r_empty)));
  assert(((void) "Slices empty string with nil, 20", d4_str_eq(r10, r_empty)));
  assert(((void) "Slices empty string with nil, -1", d4_str_eq(r11, r_empty)));
  assert(((void) "Slices empty string with nil, -3", d4_str_eq(r12, r_empty)));
  assert(((void) "Slices empty string with nil, -20", d4_str_eq(r13, r_empty)));
  assert(((void) "Slices empty string with 1, 3", d4_str_eq(r14, r_empty)));
  assert(((void) "Slices empty string with 3, 20", d4_str_eq(r15, r_empty)));
  assert(((void) "Slices empty string with 20, 100", d4_str_eq(r16, r_empty)));
  assert(((void) "Slices empty string with -3, -1", d4_str_eq(r17, r_empty)));
  assert(((void) "Slices empty string with -20, -3", d4_str_eq(r18, r_empty)));
  assert(((void) "Slices empty string with -100, -20", d4_str_eq(r19, r_empty)));

  assert(((void) "Slices single char string with nil, nil", d4_str_eq(r20, r_t)));
  assert(((void) "Slices single char string with 1, nil", d4_str_eq(r21, r_empty)));
  assert(((void) "Slices single char string with 3, nil", d4_str_eq(r22, r_empty)));
  assert(((void) "Slices single char string with 20, nil", d4_str_eq(r23, r_empty)));
  assert(((void) "Slices single char string with -1, nil", d4_str_eq(r24, r_t)));
  assert(((void) "Slices single char string with -3, nil", d4_str_eq(r25, r_t)));
  assert(((void) "Slices single char string with -20, nil", d4_str_eq(r26, r_t)));
  assert(((void) "Slices single char string with nil, 1", d4_str_eq(r27, r_t)));
  assert(((void) "Slices single char string with nil, 3", d4_str_eq(r28, r_t)));
  assert(((void) "Slices single char string with nil, 20", d4_str_eq(r29, r_t)));
  assert(((void) "Slices single char string with nil, -1", d4_str_eq(r30, r_empty)));
  assert(((void) "Slices single char string with nil, -3", d4_str_eq(r31, r_empty)));
  assert(((void) "Slices single char string with nil, -20", d4_str_eq(r32, r_empty)));
  assert(((void) "Slices single char string with 1, 3", d4_str_eq(r33, r_empty)));
  assert(((void) "Slices single char string with 3, 20", d4_str_eq(r34, r_empty)));
  assert(((void) "Slices single char string with 20, 100", d4_str_eq(r35, r_empty)));
  assert(((void) "Slices single char string with -3, -1", d4_str_eq(r36, r_empty)));
  assert(((void) "Slices single char string with -20, -3", d4_str_eq(r37, r_empty)));
  assert(((void) "Slices single char string with -100, -20", d4_str_eq(r38, r_empty)));

  assert(((void) "Slices single word string with nil, nil", d4_str_eq(r40, r_test)));
  assert(((void) "Slices single word string with 1, nil", d4_str_eq(r41, r_est)));
  assert(((void) "Slices single word string with 3, nil", d4_str_eq(r42, r_t)));
  assert(((void) "Slices single word string with 20, nil", d4_str_eq(r43, r_empty)));
  assert(((void) "Slices single word string with -1, nil", d4_str_eq(r44, r_t)));
  assert(((void) "Slices single word string with -3, nil", d4_str_eq(r45, r_est)));
  assert(((void) "Slices single word string with -20, nil", d4_str_eq(r46, r_test)));
  assert(((void) "Slices single word string with nil, 1", d4_str_eq(r47, r_t)));
  assert(((void) "Slices single word string with nil, 3", d4_str_eq(r48, r_tes)));
  assert(((void) "Slices single word string with nil, 20", d4_str_eq(r49, r_test)));
  assert(((void) "Slices single word string with nil, -1", d4_str_eq(r50, r_tes)));
  assert(((void) "Slices single word string with nil, -3", d4_str_eq(r51, r_t)));
  assert(((void) "Slices single word string with nil, -20", d4_str_eq(r52, r_empty)));
  assert(((void) "Slices single word string with 1, 3", d4_str_eq(r53, r_es)));
  assert(((void) "Slices single word string with 3, 20", d4_str_eq(r54, r_t)));
  assert(((void) "Slices single word string with 20, 100", d4_str_eq(r55, r_empty)));
  assert(((void) "Slices single word string with -3, -1", d4_str_eq(r56, r_es)));
  assert(((void) "Slices single word string with -20, -3", d4_str_eq(r57, r_t)));
  assert(((void) "Slices single word string with -100, -20", d4_str_eq(r58, r_empty)));

  assert(((void) "Slices multi word string with nil, nil", d4_str_eq(r60, r_hello_world)));
  assert(((void) "Slices multi word string with 1, nil", d4_str_eq(r61, r_ello_world)));
  assert(((void) "Slices multi word string with 3, nil", d4_str_eq(r62, r_lo_world)));
  assert(((void) "Slices multi word string with 20, nil", d4_str_eq(r63, r_empty)));
  assert(((void) "Slices multi word string with -1, nil", d4_str_eq(r64, r_d)));
  assert(((void) "Slices multi word string with -3, nil", d4_str_eq(r65, r_rld)));
  assert(((void) "Slices multi word string with -20, nil", d4_str_eq(r66, r_hello_world)));
  assert(((void) "Slices multi word string with nil, 1", d4_str_eq(r67, r_h)));
  assert(((void) "Slices multi word string with nil, 3", d4_str_eq(r68, r_hel)));
  assert(((void) "Slices multi word string with nil, 20", d4_str_eq(r69, r_hello_world)));
  assert(((void) "Slices multi word string with nil, -1", d4_str_eq(r70, r_hello_worl)));
  assert(((void) "Slices multi word string with nil, -3", d4_str_eq(r71, r_hello_wo)));
  assert(((void) "Slices multi word string with nil, -20", d4_str_eq(r72, r_empty)));
  assert(((void) "Slices multi word string with 1, 3", d4_str_eq(r73, r_el)));
  assert(((void) "Slices multi word string with 3, 20", d4_str_eq(r74, r_lo_world)));
  assert(((void) "Slices multi word string with 20, 100", d4_str_eq(r75, r_empty)));
  assert(((void) "Slices multi word string with -3, -1", d4_str_eq(r76, r_rl)));
  assert(((void) "Slices multi word string with -20, -3", d4_str_eq(r77, r_hello_wo)));
  assert(((void) "Slices multi word string with -100, -20", d4_str_eq(r78, r_empty)));

  d4_str_free(r1);
  d4_str_free(r2);
  d4_str_free(r3);
  d4_str_free(r4);
  d4_str_free(r5);
  d4_str_free(r6);
  d4_str_free(r7);
  d4_str_free(r8);
  d4_str_free(r9);
  d4_str_free(r10);
  d4_str_free(r11);
  d4_str_free(r12);
  d4_str_free(r13);
  d4_str_free(r14);
  d4_str_free(r15);
  d4_str_free(r16);
  d4_str_free(r17);
  d4_str_free(r18);
  d4_str_free(r19);
  d4_str_free(r20);
  d4_str_free(r21);
  d4_str_free(r22);
  d4_str_free(r23);
  d4_str_free(r24);
  d4_str_free(r25);
  d4_str_free(r26);
  d4_str_free(r27);
  d4_str_free(r28);
  d4_str_free(r29);
  d4_str_free(r30);
  d4_str_free(r31);
  d4_str_free(r32);
  d4_str_free(r33);
  d4_str_free(r34);
  d4_str_free(r35);
  d4_str_free(r36);
  d4_str_free(r37);
  d4_str_free(r38);
  d4_str_free(r40);
  d4_str_free(r41);
  d4_str_free(r42);
  d4_str_free(r43);
  d4_str_free(r44);
  d4_str_free(r45);
  d4_str_free(r46);
  d4_str_free(r47);
  d4_str_free(r48);
  d4_str_free(r49);
  d4_str_free(r50);
  d4_str_free(r51);
  d4_str_free(r52);
  d4_str_free(r53);
  d4_str_free(r54);
  d4_str_free(r55);
  d4_str_free(r56);
  d4_str_free(r57);
  d4_str_free(r58);
  d4_str_free(r60);
  d4_str_free(r61);
  d4_str_free(r62);
  d4_str_free(r63);
  d4_str_free(r64);
  d4_str_free(r65);
  d4_str_free(r66);
  d4_str_free(r67);
  d4_str_free(r68);
  d4_str_free(r69);
  d4_str_free(r70);
  d4_str_free(r71);
  d4_str_free(r72);
  d4_str_free(r73);
  d4_str_free(r74);
  d4_str_free(r75);
  d4_str_free(r76);
  d4_str_free(r77);
  d4_str_free(r78);

  d4_str_free(r_empty);
  d4_str_free(r_d);
  d4_str_free(r_el);
  d4_str_free(r_ello_world);
  d4_str_free(r_es);
  d4_str_free(r_est);
  d4_str_free(r_h);
  d4_str_free(r_hel);
  d4_str_free(r_hello_wo);
  d4_str_free(r_hello_worl);
  d4_str_free(r_hello_world);
  d4_str_free(r_lo_world);
  d4_str_free(r_rl);
  d4_str_free(r_rld);
  d4_str_free(r_t);
  d4_str_free(r_tes);
  d4_str_free(r_test);

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
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
  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"t");
  d4_str_t s3 = d4_str_alloc(L"t ");
  d4_str_t s4 = d4_str_alloc(L"\ft");
  d4_str_t s5 = d4_str_alloc(L"\ft\r");
  d4_str_t s6 = d4_str_alloc(L"test");
  d4_str_t s7 = d4_str_alloc(L"\ntest");
  d4_str_t s8 = d4_str_alloc(L"test\t");
  d4_str_t s9 = d4_str_alloc(L"\v\t\rtest\n\f");
  d4_str_t s10 = d4_str_alloc(L"multiple words");
  d4_str_t s11 = d4_str_alloc(L"\nmultiple words");
  d4_str_t s12 = d4_str_alloc(L"multiple words\n");
  d4_str_t s13 = d4_str_alloc(L"\nmultiple words\n");

  d4_str_t r1 = d4_str_trim(s1);
  d4_str_t r2 = d4_str_trim(s2);
  d4_str_t r3 = d4_str_trim(s3);
  d4_str_t r4 = d4_str_trim(s4);
  d4_str_t r5 = d4_str_trim(s5);
  d4_str_t r6 = d4_str_trim(s6);
  d4_str_t r7 = d4_str_trim(s7);
  d4_str_t r8 = d4_str_trim(s8);
  d4_str_t r9 = d4_str_trim(s9);
  d4_str_t r10 = d4_str_trim(s10);
  d4_str_t r11 = d4_str_trim(s11);
  d4_str_t r12 = d4_str_trim(s12);
  d4_str_t r13 = d4_str_trim(s13);

  d4_str_t r_empty = d4_str_alloc(L"");
  d4_str_t r_t = d4_str_alloc(L"t");
  d4_str_t r_test = d4_str_alloc(L"test");
  d4_str_t r_multiple_words = d4_str_alloc(L"multiple words");

  assert(((void) "Trims empty string", d4_str_eq(r1, r_empty)));
  assert(((void) "Trims single char string", d4_str_eq(r2, r_t)));
  assert(((void) "Trims single char string with trailing whitespace", d4_str_eq(r3, r_t)));
  assert(((void) "Trims single char string with leading whitespace", d4_str_eq(r4, r_t)));
  assert(((void) "Trims single char string with leading and trailing whitespaces", d4_str_eq(r5, r_t)));
  assert(((void) "Trims multi char string", d4_str_eq(r6, r_test)));
  assert(((void) "Trims multi char string with trailing whitespace", d4_str_eq(r7, r_test)));
  assert(((void) "Trims multi char string with leading whitespace", d4_str_eq(r8, r_test)));
  assert(((void) "Trims multi char string with leading and trailing whitespaces", d4_str_eq(r9, r_test)));
  assert(((void) "Trims multi word string", d4_str_eq(r10, r_multiple_words)));
  assert(((void) "Trims multi word string with trailing whitespace", d4_str_eq(r11, r_multiple_words)));
  assert(((void) "Trims multi word string with leading whitespace", d4_str_eq(r12, r_multiple_words)));
  assert(((void) "Trims multi word string with leading and trailing whitespaces", d4_str_eq(r13, r_multiple_words)));

  d4_str_free(r_empty);
  d4_str_free(r_t);
  d4_str_free(r_test);
  d4_str_free(r_multiple_words);

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s6);
  d4_str_free(s7);
  d4_str_free(s8);
  d4_str_free(s9);
  d4_str_free(s10);
  d4_str_free(s11);
  d4_str_free(s12);
  d4_str_free(s13);

  d4_str_free(r1);
  d4_str_free(r2);
  d4_str_free(r3);
  d4_str_free(r4);
  d4_str_free(r5);
  d4_str_free(r6);
  d4_str_free(r7);
  d4_str_free(r8);
  d4_str_free(r9);
  d4_str_free(r10);
  d4_str_free(r11);
  d4_str_free(r12);
  d4_str_free(r13);
}

static void test_string_trimEnd (void) {
  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"t");
  d4_str_t s3 = d4_str_alloc(L"t ");
  d4_str_t s4 = d4_str_alloc(L"\ft");
  d4_str_t s5 = d4_str_alloc(L"\ft\r");
  d4_str_t s6 = d4_str_alloc(L"test");
  d4_str_t s7 = d4_str_alloc(L"\ntest");
  d4_str_t s8 = d4_str_alloc(L"test\t\r\n");
  d4_str_t s9 = d4_str_alloc(L"\vtest\r");
  d4_str_t s10 = d4_str_alloc(L"multiple words");
  d4_str_t s11 = d4_str_alloc(L"\nmultiple words");
  d4_str_t s12 = d4_str_alloc(L"multiple words\n");
  d4_str_t s13 = d4_str_alloc(L"\nmultiple words\n");

  d4_str_t r1 = d4_str_trimEnd(s1);
  d4_str_t r2 = d4_str_trimEnd(s2);
  d4_str_t r3 = d4_str_trimEnd(s3);
  d4_str_t r4 = d4_str_trimEnd(s4);
  d4_str_t r5 = d4_str_trimEnd(s5);
  d4_str_t r6 = d4_str_trimEnd(s6);
  d4_str_t r7 = d4_str_trimEnd(s7);
  d4_str_t r8 = d4_str_trimEnd(s8);
  d4_str_t r9 = d4_str_trimEnd(s9);
  d4_str_t r10 = d4_str_trimEnd(s10);
  d4_str_t r11 = d4_str_trimEnd(s11);
  d4_str_t r12 = d4_str_trimEnd(s12);
  d4_str_t r13 = d4_str_trimEnd(s13);

  d4_str_t r1_cmp = d4_str_alloc(L"");
  d4_str_t r2_cmp = d4_str_alloc(L"t");
  d4_str_t r3_cmp = d4_str_alloc(L"t");
  d4_str_t r4_cmp = d4_str_alloc(L"\ft");
  d4_str_t r5_cmp = d4_str_alloc(L"\ft");
  d4_str_t r6_cmp = d4_str_alloc(L"test");
  d4_str_t r7_cmp = d4_str_alloc(L"\ntest");
  d4_str_t r8_cmp = d4_str_alloc(L"test");
  d4_str_t r9_cmp = d4_str_alloc(L"\vtest");
  d4_str_t r10_cmp = d4_str_alloc(L"multiple words");
  d4_str_t r11_cmp = d4_str_alloc(L"\nmultiple words");
  d4_str_t r12_cmp = d4_str_alloc(L"multiple words");
  d4_str_t r13_cmp = d4_str_alloc(L"\nmultiple words");

  assert(((void) "Trims end of empty string", d4_str_eq(r1, r1_cmp)));
  assert(((void) "Trims end of single char string", d4_str_eq(r2, r2_cmp)));
  assert(((void) "Trims end of single char string with trailing whitespace", d4_str_eq(r3, r3_cmp)));
  assert(((void) "Trims end of single char string with leading whitespace", d4_str_eq(r4, r4_cmp)));
  assert(((void) "Trims end of single char string with leading and trailing whitespaces", d4_str_eq(r5, r5_cmp)));
  assert(((void) "Trims end of multi char string", d4_str_eq(r6, r6_cmp)));
  assert(((void) "Trims end of multi char string with trailing whitespace", d4_str_eq(r7, r7_cmp)));
  assert(((void) "Trims end of multi char string with leading whitespace", d4_str_eq(r8, r8_cmp)));
  assert(((void) "Trims end of multi char string with leading and trailing whitespaces", d4_str_eq(r9, r9_cmp)));
  assert(((void) "Trims end of multi word string", d4_str_eq(r10, r10_cmp)));
  assert(((void) "Trims end of multi word string with trailing whitespace", d4_str_eq(r11, r11_cmp)));
  assert(((void) "Trims end of multi word string with leading whitespace", d4_str_eq(r12, r12_cmp)));
  assert(((void) "Trims end of multi word string with leading and trailing whitespaces", d4_str_eq(r13, r13_cmp)));

  d4_str_free(r1_cmp);
  d4_str_free(r2_cmp);
  d4_str_free(r3_cmp);
  d4_str_free(r4_cmp);
  d4_str_free(r5_cmp);
  d4_str_free(r6_cmp);
  d4_str_free(r7_cmp);
  d4_str_free(r8_cmp);
  d4_str_free(r9_cmp);
  d4_str_free(r10_cmp);
  d4_str_free(r11_cmp);
  d4_str_free(r12_cmp);
  d4_str_free(r13_cmp);

  d4_str_free(r1);
  d4_str_free(r2);
  d4_str_free(r3);
  d4_str_free(r4);
  d4_str_free(r5);
  d4_str_free(r6);
  d4_str_free(r7);
  d4_str_free(r8);
  d4_str_free(r9);
  d4_str_free(r10);
  d4_str_free(r11);
  d4_str_free(r12);
  d4_str_free(r13);

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s6);
  d4_str_free(s7);
  d4_str_free(s8);
  d4_str_free(s9);
  d4_str_free(s10);
  d4_str_free(s11);
  d4_str_free(s12);
  d4_str_free(s13);
}

static void test_string_trimStart (void) {
  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"t");
  d4_str_t s3 = d4_str_alloc(L"t ");
  d4_str_t s4 = d4_str_alloc(L"\ft");
  d4_str_t s5 = d4_str_alloc(L"\ft\r");
  d4_str_t s6 = d4_str_alloc(L"test");
  d4_str_t s7 = d4_str_alloc(L"\n\r\ttest");
  d4_str_t s8 = d4_str_alloc(L"test\t");
  d4_str_t s9 = d4_str_alloc(L"\vtest\r");
  d4_str_t s10 = d4_str_alloc(L"multiple words");
  d4_str_t s11 = d4_str_alloc(L"\nmultiple words");
  d4_str_t s12 = d4_str_alloc(L"multiple words\n");
  d4_str_t s13 = d4_str_alloc(L"\nmultiple words\n");

  d4_str_t r1 = d4_str_trimStart(s1);
  d4_str_t r2 = d4_str_trimStart(s2);
  d4_str_t r3 = d4_str_trimStart(s3);
  d4_str_t r4 = d4_str_trimStart(s4);
  d4_str_t r5 = d4_str_trimStart(s5);
  d4_str_t r6 = d4_str_trimStart(s6);
  d4_str_t r7 = d4_str_trimStart(s7);
  d4_str_t r8 = d4_str_trimStart(s8);
  d4_str_t r9 = d4_str_trimStart(s9);
  d4_str_t r10 = d4_str_trimStart(s10);
  d4_str_t r11 = d4_str_trimStart(s11);
  d4_str_t r12 = d4_str_trimStart(s12);
  d4_str_t r13 = d4_str_trimStart(s13);

  d4_str_t r1_cmp = d4_str_alloc(L"");
  d4_str_t r2_cmp = d4_str_alloc(L"t");
  d4_str_t r3_cmp = d4_str_alloc(L"t ");
  d4_str_t r4_cmp = d4_str_alloc(L"t");
  d4_str_t r5_cmp = d4_str_alloc(L"t\r");
  d4_str_t r6_cmp = d4_str_alloc(L"test");
  d4_str_t r7_cmp = d4_str_alloc(L"test");
  d4_str_t r8_cmp = d4_str_alloc(L"test\t");
  d4_str_t r9_cmp = d4_str_alloc(L"test\r");
  d4_str_t r10_cmp = d4_str_alloc(L"multiple words");
  d4_str_t r11_cmp = d4_str_alloc(L"multiple words");
  d4_str_t r12_cmp = d4_str_alloc(L"multiple words\n");
  d4_str_t r13_cmp = d4_str_alloc(L"multiple words\n");

  assert(((void) "Trims start of empty string", d4_str_eq(r1, r1_cmp)));
  assert(((void) "Trims start of single char string", d4_str_eq(r2, r2_cmp)));
  assert(((void) "Trims start of single char string with trailing whitespace", d4_str_eq(r3, r3_cmp)));
  assert(((void) "Trims start of single char string with leading whitespace", d4_str_eq(r4, r4_cmp)));
  assert(((void) "Trims start of single char string with leading and trailing whitespaces", d4_str_eq(r5, r5_cmp)));
  assert(((void) "Trims start of multi char string", d4_str_eq(r6, r6_cmp)));
  assert(((void) "Trims start of multi char string with trailing whitespace", d4_str_eq(r7, r7_cmp)));
  assert(((void) "Trims start of multi char string with leading whitespace", d4_str_eq(r8, r8_cmp)));
  assert(((void) "Trims start of multi char string with leading and trailing whitespaces", d4_str_eq(r9, r9_cmp)));
  assert(((void) "Trims start of multi word string", d4_str_eq(r10, r10_cmp)));
  assert(((void) "Trims start of multi word string with trailing whitespace", d4_str_eq(r11, r11_cmp)));
  assert(((void) "Trims start of multi word string with leading whitespace", d4_str_eq(r12, r12_cmp)));
  assert(((void) "Trims start of multi word string with leading and trailing whitespaces", d4_str_eq(r13, r13_cmp)));

  d4_str_free(r1_cmp);
  d4_str_free(r2_cmp);
  d4_str_free(r3_cmp);
  d4_str_free(r4_cmp);
  d4_str_free(r5_cmp);
  d4_str_free(r6_cmp);
  d4_str_free(r7_cmp);
  d4_str_free(r8_cmp);
  d4_str_free(r9_cmp);
  d4_str_free(r10_cmp);
  d4_str_free(r11_cmp);
  d4_str_free(r12_cmp);
  d4_str_free(r13_cmp);

  d4_str_free(r1);
  d4_str_free(r2);
  d4_str_free(r3);
  d4_str_free(r4);
  d4_str_free(r5);
  d4_str_free(r6);
  d4_str_free(r7);
  d4_str_free(r8);
  d4_str_free(r9);
  d4_str_free(r10);
  d4_str_free(r11);
  d4_str_free(r12);
  d4_str_free(r13);

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s6);
  d4_str_free(s7);
  d4_str_free(s8);
  d4_str_free(s9);
  d4_str_free(s10);
  d4_str_free(s11);
  d4_str_free(s12);
  d4_str_free(s13);
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
