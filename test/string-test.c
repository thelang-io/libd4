/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <assert.h>
#include "../src/string.h"
#include "utils.h"

static void test_string_snwprintf_vsnwprintf (void) {
  assert(((void) "snwprintf of empty format", snwprintf(L"") == 0));
  assert(((void) "snwprintf with one formatter of zero", snwprintf(L"%d", 0) == 1));
  assert(((void) "snwprintf with one formatter of number", snwprintf(L"%d", 123) == 3));
  assert(((void) "snwprintf with one formatter of string", snwprintf(L"%ls", L"test") == 4));
  assert(((void) "snwprintf with multiple formatters", snwprintf(L"%llu%ls", 10, L"test") == 6));
  assert(((void) "snwprintf with multiple formatters and text", snwprintf(L"Hi! My name is %ls, I'm %d y.o.", L"Aaron", 10) == 33));
  assert(((void) "snwprintf with long string", snwprintf(L"Lorem ipsum odor amet, consectetuer adipiscing elit. Ultricies taciti bibendum ornare blandit finibus. Primis facilisi consectetur ultrices posuere, aliquam ut habitant eget at. Arcu purus mi penatibus parturient, habitant adipiscing arcu. Torquent ligula pulvinar laoreet vivamus nostra eros convallis vehicula. Placerat molestie torquent dolor proin molestie tristique. Egestas hac montes sapien morbi ante turpis. Eu leo viverra risus; molestie etiam taciti. Orci semper aliquam lacus; erat habitasse sodales? Massa lobortis mauris pulvinar potenti hac primis nascetur etiam ligula. Viverra eros nisl egestas iaculis rutrum sollicitudin leo posuere leo. Ut vel habitant dictumst, amet turpis maecenas. Morbi vehicula ornare gravida gravida euismod nunc. Molestie leo parturient quis convallis, ante tempus risus semper. Lacus platea eleifend lacinia egestas turpis ante iaculis parturient. Commodo hendrerit pharetra curae magna facilisi dignissim sodales vehicula ligula. Pellentesque libero habitant facilisis sit convallis.") == 1029));
}

static void test_string_alloc (void) {
  d4_str_t s1 = d4_str_alloc(NULL);
  d4_str_t s5 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"Test");
  d4_str_t s3 = d4_str_alloc(L"%d", 10);
  d4_str_t s4 = d4_str_alloc(L"10");

  assert(((void) "Allocates empty", s1.data == NULL));
  assert(((void) "Allocates empty", s1.len == 0));

  assert(((void) "Allocates zero length", s5.data == NULL));
  assert(((void) "Allocates zero length", s5.len == 0));

  assert(((void) "Allocates non empty", s2.data != NULL));
  assert(((void) "Allocates non empty", s2.len == 4));

  assert(((void) "Allocates with format", d4_str_eq(s3, s4)));
  assert(((void) "Allocates with format", s3.len == 2));

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
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

  assert(((void) "Same string >= same string", d4_str_ge(s4, s4)));
  assert(((void) "Empty string not >= single char string", !d4_str_ge(s1, s2)));
  assert(((void) "Empty string not >= multi char string", !d4_str_ge(s1, s3)));
  assert(((void) "One letter string not >= than similar string", !d4_str_ge(s2, s3)));
  assert(((void) "Lowercase single char string >= uppercase string", d4_str_ge(s2, s4)));
  assert(((void) "Lowercase single char string >= digits string", d4_str_ge(s2, s5)));
  assert(((void) "Lowercase multi char string >= uppercase string", d4_str_ge(s3, s4)));
  assert(((void) "Lowercase multi char string >= uppercase string", d4_str_ge(s3, s5)));
  assert(((void) "Uppercase string >= digits string", d4_str_ge(s4, s5)));

  assert(((void) "Reverse same string >= same string", d4_str_ge(s4, s4)));
  assert(((void) "Reverse empty string not >= single char string", d4_str_ge(s2, s1)));
  assert(((void) "Reverse empty string not >= multi char string", d4_str_ge(s3, s1)));
  assert(((void) "Reverse one letter string not >= than similar string", d4_str_ge(s3, s2)));
  assert(((void) "Reverse lowercase single char string >= uppercase string", !d4_str_ge(s4, s2)));
  assert(((void) "Reverse lowercase single char string >= digits string", !d4_str_ge(s5, s2)));
  assert(((void) "Reverse lowercase multi char string >= uppercase string", !d4_str_ge(s4, s3)));
  assert(((void) "Reverse lowercase multi char string >= uppercase string", !d4_str_ge(s5, s3)));
  assert(((void) "Reverse uppercase string >= digits string", !d4_str_ge(s5, s4)));

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

  assert(((void) "Same string not > same string", !d4_str_gt(s4, s4)));
  assert(((void) "Empty string not > single char string", !d4_str_gt(s1, s2)));
  assert(((void) "Empty string not > multi char string", !d4_str_gt(s1, s3)));
  assert(((void) "One letter string not > than similar string", !d4_str_gt(s2, s3)));
  assert(((void) "Lowercase single char string > uppercase string", d4_str_gt(s2, s4)));
  assert(((void) "Lowercase single char string > digits string", d4_str_gt(s2, s5)));
  assert(((void) "Lowercase multi char string > uppercase string", d4_str_gt(s3, s4)));
  assert(((void) "Lowercase multi char string > uppercase string", d4_str_gt(s3, s5)));
  assert(((void) "Uppercase string > digits string", d4_str_gt(s4, s5)));

  assert(((void) "Reverse same string not > same string", !d4_str_gt(s4, s4)));
  assert(((void) "Reverse empty string not > single char string", d4_str_gt(s2, s1)));
  assert(((void) "Reverse empty string not > multi char string", d4_str_gt(s3, s1)));
  assert(((void) "Reverse one letter string not > than similar string", d4_str_gt(s3, s2)));
  assert(((void) "Reverse lowercase single char string > uppercase string", !d4_str_gt(s4, s2)));
  assert(((void) "Reverse lowercase single char string > digits string", !d4_str_gt(s5, s2)));
  assert(((void) "Reverse lowercase multi char string > uppercase string", !d4_str_gt(s4, s3)));
  assert(((void) "Reverse lowercase multi char string > uppercase string", !d4_str_gt(s5, s3)));
  assert(((void) "Reverse uppercase string > digits string", !d4_str_gt(s5, s4)));

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

  assert(((void) "Same string <= same string", d4_str_le(s4, s4)));
  assert(((void) "Empty string <= single char string", d4_str_le(s1, s2)));
  assert(((void) "Empty string <= multi char string", d4_str_le(s1, s3)));
  assert(((void) "One letter string <= than similar string", d4_str_le(s2, s3)));
  assert(((void) "Lowercase single char string not <= uppercase string", !d4_str_le(s2, s4)));
  assert(((void) "Lowercase single char string not <= digits string", !d4_str_le(s2, s5)));
  assert(((void) "Lowercase multi char string not <= uppercase string", !d4_str_le(s3, s4)));
  assert(((void) "Lowercase multi char string not <= uppercase string", !d4_str_le(s3, s5)));
  assert(((void) "Uppercase string not <= digits string", !d4_str_le(s4, s5)));

  assert(((void) "Reverse same string <= same string", d4_str_le(s4, s4)));
  assert(((void) "Reverse empty string <= single char string", !d4_str_le(s2, s1)));
  assert(((void) "Reverse empty string <= multi char string", !d4_str_le(s3, s1)));
  assert(((void) "Reverse one letter string <= than similar string", !d4_str_le(s3, s2)));
  assert(((void) "Reverse lowercase single char string not <= uppercase string", d4_str_le(s4, s2)));
  assert(((void) "Reverse lowercase single char string not <= digits string", d4_str_le(s5, s2)));
  assert(((void) "Reverse lowercase multi char string not <= uppercase string", d4_str_le(s4, s3)));
  assert(((void) "Reverse lowercase multi char string not <= uppercase string", d4_str_le(s5, s3)));
  assert(((void) "Reverse uppercase string not <= digits string", d4_str_le(s5, s4)));

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

  assert(((void) "Same string not < same string", !d4_str_lt(s4, s4)));
  assert(((void) "Empty string < single char string", d4_str_lt(s1, s2)));
  assert(((void) "Empty string < multi char string", d4_str_lt(s1, s3)));
  assert(((void) "One letter string < than similar string", d4_str_lt(s2, s3)));
  assert(((void) "Lowercase single char string not < uppercase string", !d4_str_lt(s2, s4)));
  assert(((void) "Lowercase single char string not < digits string", !d4_str_lt(s2, s5)));
  assert(((void) "Lowercase multi char string not < uppercase string", !d4_str_lt(s3, s4)));
  assert(((void) "Lowercase multi char string not < uppercase string", !d4_str_lt(s3, s5)));
  assert(((void) "Uppercase string not < digits string", !d4_str_lt(s4, s5)));

  assert(((void) "Reverse same string not < same string", !d4_str_lt(s4, s4)));
  assert(((void) "Reverse empty string < single char string", !d4_str_lt(s2, s1)));
  assert(((void) "Reverse empty string < multi char string", !d4_str_lt(s3, s1)));
  assert(((void) "Reverse one letter string < than similar string", !d4_str_lt(s3, s2)));
  assert(((void) "Reverse lowercase single char string not < uppercase string", d4_str_lt(s4, s2)));
  assert(((void) "Reverse lowercase single char string not < digits string", d4_str_lt(s5, s2)));
  assert(((void) "Reverse lowercase multi char string not < uppercase string", d4_str_lt(s4, s3)));
  assert(((void) "Reverse lowercase multi char string not < uppercase string", d4_str_lt(s5, s3)));
  assert(((void) "Reverse uppercase string not < digits string", d4_str_lt(s5, s4)));

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
  d4_str_t s4 = d4_str_alloc(L"test");

  s4 = d4_str_realloc(s4, s1);
  assert(((void) "Reallocates non-empty string with empty string", d4_str_eq(s1, s4) && s4.data == NULL));

  s3 = d4_str_realloc(s3, s1);
  assert(((void) "Reallocates empty string with empty string", d4_str_eq(s1, s3) && s3.data == NULL));

  s3 = d4_str_realloc(s3, s2);
  assert(((void) "Reallocates empty string with non-empty string", d4_str_eq(s2, s3)));

  s3 = d4_str_realloc(s3, s1);
  assert(((void) "Reallocates non-empty string with empty string", d4_str_eq(s1, s3)));

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
}

static void test_string_replace (void) {
  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"a");
  d4_str_t s3 = d4_str_alloc(L"blackish string");
  d4_str_t s4 = d4_str_alloc(L"Aaron has a black house and a black car");
  d4_str_t s5 = d4_str_alloc(L"aaa");

  d4_str_t search1 = d4_str_alloc(L"");
  d4_str_t search2 = d4_str_alloc(L"a");
  d4_str_t search3 = d4_str_alloc(L"black");

  d4_str_t replacement1 = d4_str_alloc(L"");
  d4_str_t replacement2 = d4_str_alloc(L"o");
  d4_str_t replacement3 = d4_str_alloc(L"green");

  d4_str_t r1 = d4_str_replace(s1, search1, replacement1, 0, 0);
  d4_str_t r2 = d4_str_replace(s1, search2, replacement1, 0, 0);
  d4_str_t r3 = d4_str_replace(s1, search3, replacement1, 0, 0);
  d4_str_t r4 = d4_str_replace(s1, search1, replacement2, 0, 0);
  d4_str_t r5 = d4_str_replace(s1, search2, replacement2, 0, 0);
  d4_str_t r6 = d4_str_replace(s1, search3, replacement2, 0, 0);
  d4_str_t r7 = d4_str_replace(s1, search1, replacement3, 0, 0);
  d4_str_t r8 = d4_str_replace(s1, search2, replacement3, 0, 0);
  d4_str_t r9 = d4_str_replace(s1, search3, replacement3, 0, 0);
  d4_str_t r10 = d4_str_replace(s1, search1, replacement1, 1, 1);
  d4_str_t r11 = d4_str_replace(s1, search2, replacement1, 1, 1);
  d4_str_t r12 = d4_str_replace(s1, search3, replacement1, 1, 1);
  d4_str_t r13 = d4_str_replace(s1, search1, replacement2, 1, 1);
  d4_str_t r14 = d4_str_replace(s1, search2, replacement2, 1, 1);
  d4_str_t r15 = d4_str_replace(s1, search3, replacement2, 1, 1);
  d4_str_t r16 = d4_str_replace(s1, search1, replacement3, 1, 1);
  d4_str_t r17 = d4_str_replace(s1, search2, replacement3, 1, 1);
  d4_str_t r18 = d4_str_replace(s1, search3, replacement3, 1, 1);
  d4_str_t r19 = d4_str_replace(s1, search1, replacement1, 1, 2);
  d4_str_t r20 = d4_str_replace(s1, search2, replacement1, 1, 2);
  d4_str_t r21 = d4_str_replace(s1, search3, replacement1, 1, 2);
  d4_str_t r22 = d4_str_replace(s1, search1, replacement2, 1, 2);
  d4_str_t r23 = d4_str_replace(s1, search2, replacement2, 1, 2);
  d4_str_t r24 = d4_str_replace(s1, search3, replacement2, 1, 2);
  d4_str_t r25 = d4_str_replace(s1, search1, replacement3, 1, 2);
  d4_str_t r26 = d4_str_replace(s1, search2, replacement3, 1, 2);
  d4_str_t r27 = d4_str_replace(s1, search3, replacement3, 1, 2);
  d4_str_t r28 = d4_str_replace(s2, search1, replacement1, 0, 0);
  d4_str_t r29 = d4_str_replace(s2, search2, replacement1, 0, 0);
  d4_str_t r30 = d4_str_replace(s2, search3, replacement1, 0, 0);
  d4_str_t r31 = d4_str_replace(s2, search1, replacement2, 0, 0);
  d4_str_t r32 = d4_str_replace(s2, search2, replacement2, 0, 0);
  d4_str_t r33 = d4_str_replace(s2, search3, replacement2, 0, 0);
  d4_str_t r34 = d4_str_replace(s2, search1, replacement3, 0, 0);
  d4_str_t r35 = d4_str_replace(s2, search2, replacement3, 0, 0);
  d4_str_t r36 = d4_str_replace(s2, search3, replacement3, 0, 0);
  d4_str_t r37 = d4_str_replace(s2, search1, replacement1, 1, 1);
  d4_str_t r38 = d4_str_replace(s2, search2, replacement1, 1, 1);
  d4_str_t r39 = d4_str_replace(s2, search3, replacement1, 1, 1);
  d4_str_t r40 = d4_str_replace(s2, search1, replacement2, 1, 1);
  d4_str_t r41 = d4_str_replace(s2, search2, replacement2, 1, 1);
  d4_str_t r42 = d4_str_replace(s2, search3, replacement2, 1, 1);
  d4_str_t r43 = d4_str_replace(s2, search1, replacement3, 1, 1);
  d4_str_t r44 = d4_str_replace(s2, search2, replacement3, 1, 1);
  d4_str_t r45 = d4_str_replace(s2, search3, replacement3, 1, 1);
  d4_str_t r46 = d4_str_replace(s2, search1, replacement1, 1, 2);
  d4_str_t r47 = d4_str_replace(s2, search2, replacement1, 1, 2);
  d4_str_t r48 = d4_str_replace(s2, search3, replacement1, 1, 2);
  d4_str_t r49 = d4_str_replace(s2, search1, replacement2, 1, 2);
  d4_str_t r50 = d4_str_replace(s2, search2, replacement2, 1, 2);
  d4_str_t r51 = d4_str_replace(s2, search3, replacement2, 1, 2);
  d4_str_t r52 = d4_str_replace(s2, search1, replacement3, 1, 2);
  d4_str_t r53 = d4_str_replace(s2, search2, replacement3, 1, 2);
  d4_str_t r54 = d4_str_replace(s2, search3, replacement3, 1, 2);
  d4_str_t r55 = d4_str_replace(s3, search1, replacement1, 0, 0);
  d4_str_t r56 = d4_str_replace(s3, search2, replacement1, 0, 0);
  d4_str_t r57 = d4_str_replace(s3, search3, replacement1, 0, 0);
  d4_str_t r58 = d4_str_replace(s3, search1, replacement2, 0, 0);
  d4_str_t r59 = d4_str_replace(s3, search2, replacement2, 0, 0);
  d4_str_t r60 = d4_str_replace(s3, search3, replacement2, 0, 0);
  d4_str_t r61 = d4_str_replace(s3, search1, replacement3, 0, 0);
  d4_str_t r62 = d4_str_replace(s3, search2, replacement3, 0, 0);
  d4_str_t r63 = d4_str_replace(s3, search3, replacement3, 0, 0);
  d4_str_t r64 = d4_str_replace(s3, search1, replacement1, 1, 1);
  d4_str_t r65 = d4_str_replace(s3, search2, replacement1, 1, 1);
  d4_str_t r66 = d4_str_replace(s3, search3, replacement1, 1, 1);
  d4_str_t r67 = d4_str_replace(s3, search1, replacement2, 1, 1);
  d4_str_t r68 = d4_str_replace(s3, search2, replacement2, 1, 1);
  d4_str_t r69 = d4_str_replace(s3, search3, replacement2, 1, 1);
  d4_str_t r70 = d4_str_replace(s3, search1, replacement3, 1, 1);
  d4_str_t r71 = d4_str_replace(s3, search2, replacement3, 1, 1);
  d4_str_t r72 = d4_str_replace(s3, search3, replacement3, 1, 1);
  d4_str_t r73 = d4_str_replace(s3, search1, replacement1, 1, 2);
  d4_str_t r74 = d4_str_replace(s3, search2, replacement1, 1, 2);
  d4_str_t r75 = d4_str_replace(s3, search3, replacement1, 1, 2);
  d4_str_t r76 = d4_str_replace(s3, search1, replacement2, 1, 2);
  d4_str_t r77 = d4_str_replace(s3, search2, replacement2, 1, 2);
  d4_str_t r78 = d4_str_replace(s3, search3, replacement2, 1, 2);
  d4_str_t r79 = d4_str_replace(s3, search1, replacement3, 1, 2);
  d4_str_t r80 = d4_str_replace(s3, search2, replacement3, 1, 2);
  d4_str_t r81 = d4_str_replace(s3, search3, replacement3, 1, 2);
  d4_str_t r82 = d4_str_replace(s4, search1, replacement1, 0, 0);
  d4_str_t r83 = d4_str_replace(s4, search2, replacement1, 0, 0);
  d4_str_t r84 = d4_str_replace(s4, search3, replacement1, 0, 0);
  d4_str_t r85 = d4_str_replace(s4, search1, replacement2, 0, 0);
  d4_str_t r86 = d4_str_replace(s4, search2, replacement2, 0, 0);
  d4_str_t r87 = d4_str_replace(s4, search3, replacement2, 0, 0);
  d4_str_t r88 = d4_str_replace(s4, search1, replacement3, 0, 0);
  d4_str_t r89 = d4_str_replace(s4, search2, replacement3, 0, 0);
  d4_str_t r90 = d4_str_replace(s4, search3, replacement3, 0, 0);
  d4_str_t r91 = d4_str_replace(s4, search1, replacement1, 1, 1);
  d4_str_t r92 = d4_str_replace(s4, search2, replacement1, 1, 1);
  d4_str_t r93 = d4_str_replace(s4, search3, replacement1, 1, 1);
  d4_str_t r94 = d4_str_replace(s4, search1, replacement2, 1, 1);
  d4_str_t r95 = d4_str_replace(s4, search2, replacement2, 1, 1);
  d4_str_t r96 = d4_str_replace(s4, search3, replacement2, 1, 1);
  d4_str_t r97 = d4_str_replace(s4, search1, replacement3, 1, 1);
  d4_str_t r98 = d4_str_replace(s4, search2, replacement3, 1, 1);
  d4_str_t r99 = d4_str_replace(s4, search3, replacement3, 1, 1);
  d4_str_t r100 = d4_str_replace(s4, search1, replacement1, 1, 2);
  d4_str_t r101 = d4_str_replace(s4, search2, replacement1, 1, 2);
  d4_str_t r102 = d4_str_replace(s4, search3, replacement1, 1, 2);
  d4_str_t r103 = d4_str_replace(s4, search1, replacement2, 1, 2);
  d4_str_t r104 = d4_str_replace(s4, search2, replacement2, 1, 2);
  d4_str_t r105 = d4_str_replace(s4, search3, replacement2, 1, 2);
  d4_str_t r106 = d4_str_replace(s4, search1, replacement3, 1, 2);
  d4_str_t r107 = d4_str_replace(s4, search2, replacement3, 1, 2);
  d4_str_t r108 = d4_str_replace(s4, search3, replacement3, 1, 2);
  d4_str_t r109 = d4_str_replace(s2, replacement2, replacement2, 0, 0);
  d4_str_t r110 = d4_str_replace(s5, search2, replacement1, 0, 0);

  d4_str_t cmp1 = d4_str_alloc(L"");
  d4_str_t cmp2 = d4_str_alloc(L"");
  d4_str_t cmp3 = d4_str_alloc(L"");
  d4_str_t cmp4 = d4_str_alloc(L"o");
  d4_str_t cmp5 = d4_str_alloc(L"");
  d4_str_t cmp6 = d4_str_alloc(L"");
  d4_str_t cmp7 = d4_str_alloc(L"green");
  d4_str_t cmp8 = d4_str_alloc(L"");
  d4_str_t cmp9 = d4_str_alloc(L"");
  d4_str_t cmp10 = d4_str_alloc(L"");
  d4_str_t cmp11 = d4_str_alloc(L"");
  d4_str_t cmp12 = d4_str_alloc(L"");
  d4_str_t cmp13 = d4_str_alloc(L"o");
  d4_str_t cmp14 = d4_str_alloc(L"");
  d4_str_t cmp15 = d4_str_alloc(L"");
  d4_str_t cmp16 = d4_str_alloc(L"green");
  d4_str_t cmp17 = d4_str_alloc(L"");
  d4_str_t cmp18 = d4_str_alloc(L"");
  d4_str_t cmp19 = d4_str_alloc(L"");
  d4_str_t cmp20 = d4_str_alloc(L"");
  d4_str_t cmp21 = d4_str_alloc(L"");
  d4_str_t cmp22 = d4_str_alloc(L"o");
  d4_str_t cmp23 = d4_str_alloc(L"");
  d4_str_t cmp24 = d4_str_alloc(L"");
  d4_str_t cmp25 = d4_str_alloc(L"green");
  d4_str_t cmp26 = d4_str_alloc(L"");
  d4_str_t cmp27 = d4_str_alloc(L"");
  d4_str_t cmp28 = d4_str_alloc(L"a");
  d4_str_t cmp29 = d4_str_alloc(L"");
  d4_str_t cmp30 = d4_str_alloc(L"a");
  d4_str_t cmp31 = d4_str_alloc(L"oao");
  d4_str_t cmp32 = d4_str_alloc(L"o");
  d4_str_t cmp33 = d4_str_alloc(L"a");
  d4_str_t cmp34 = d4_str_alloc(L"greenagreen");
  d4_str_t cmp35 = d4_str_alloc(L"green");
  d4_str_t cmp36 = d4_str_alloc(L"a");
  d4_str_t cmp37 = d4_str_alloc(L"a");
  d4_str_t cmp38 = d4_str_alloc(L"");
  d4_str_t cmp39 = d4_str_alloc(L"a");
  d4_str_t cmp40 = d4_str_alloc(L"oa");
  d4_str_t cmp41 = d4_str_alloc(L"o");
  d4_str_t cmp42 = d4_str_alloc(L"a");
  d4_str_t cmp43 = d4_str_alloc(L"greena");
  d4_str_t cmp44 = d4_str_alloc(L"green");
  d4_str_t cmp45 = d4_str_alloc(L"a");
  d4_str_t cmp46 = d4_str_alloc(L"a");
  d4_str_t cmp47 = d4_str_alloc(L"");
  d4_str_t cmp48 = d4_str_alloc(L"a");
  d4_str_t cmp49 = d4_str_alloc(L"oao");
  d4_str_t cmp50 = d4_str_alloc(L"o");
  d4_str_t cmp51 = d4_str_alloc(L"a");
  d4_str_t cmp52 = d4_str_alloc(L"greenagreen");
  d4_str_t cmp53 = d4_str_alloc(L"green");
  d4_str_t cmp54 = d4_str_alloc(L"a");
  d4_str_t cmp55 = d4_str_alloc(L"blackish string");
  d4_str_t cmp56 = d4_str_alloc(L"blckish string");
  d4_str_t cmp57 = d4_str_alloc(L"ish string");
  d4_str_t cmp58 = d4_str_alloc(L"oboloaocokoiosoho osotoroionogo");
  d4_str_t cmp59 = d4_str_alloc(L"blockish string");
  d4_str_t cmp60 = d4_str_alloc(L"oish string");
  d4_str_t cmp61 = d4_str_alloc(L"greenbgreenlgreenagreencgreenkgreenigreensgreenhgreen greensgreentgreenrgreenigreenngreenggreen");
  d4_str_t cmp62 = d4_str_alloc(L"blgreenckish string");
  d4_str_t cmp63 = d4_str_alloc(L"greenish string");
  d4_str_t cmp64 = d4_str_alloc(L"blackish string");
  d4_str_t cmp65 = d4_str_alloc(L"blckish string");
  d4_str_t cmp66 = d4_str_alloc(L"ish string");
  d4_str_t cmp67 = d4_str_alloc(L"oblackish string");
  d4_str_t cmp68 = d4_str_alloc(L"blockish string");
  d4_str_t cmp69 = d4_str_alloc(L"oish string");
  d4_str_t cmp70 = d4_str_alloc(L"greenblackish string");
  d4_str_t cmp71 = d4_str_alloc(L"blgreenckish string");
  d4_str_t cmp72 = d4_str_alloc(L"greenish string");
  d4_str_t cmp73 = d4_str_alloc(L"blackish string");
  d4_str_t cmp74 = d4_str_alloc(L"blckish string");
  d4_str_t cmp75 = d4_str_alloc(L"ish string");
  d4_str_t cmp76 = d4_str_alloc(L"obolackish string");
  d4_str_t cmp77 = d4_str_alloc(L"blockish string");
  d4_str_t cmp78 = d4_str_alloc(L"oish string");
  d4_str_t cmp79 = d4_str_alloc(L"greenbgreenlackish string");
  d4_str_t cmp80 = d4_str_alloc(L"blgreenckish string");
  d4_str_t cmp81 = d4_str_alloc(L"greenish string");
  d4_str_t cmp82 = d4_str_alloc(L"Aaron has a black house and a black car");
  d4_str_t cmp83 = d4_str_alloc(L"Aron hs  blck house nd  blck cr");
  d4_str_t cmp84 = d4_str_alloc(L"Aaron has a  house and a  car");
  d4_str_t cmp85 = d4_str_alloc(L"oAoaorooono ohoaoso oao oboloaocoko ohooouosoeo oaonodo oao oboloaocoko ocoaoro");
  d4_str_t cmp86 = d4_str_alloc(L"Aoron hos o block house ond o block cor");
  d4_str_t cmp87 = d4_str_alloc(L"Aaron has a o house and a o car");
  d4_str_t cmp88 = d4_str_alloc(L"greenAgreenagreenrgreenogreenngreen greenhgreenagreensgreen greenagreen greenbgreenlgreenagreencgreenkgreen greenhgreenogreenugreensgreenegreen greenagreenngreendgreen greenagreen greenbgreenlgreenagreencgreenkgreen greencgreenagreenrgreen");
  d4_str_t cmp89 = d4_str_alloc(L"Agreenron hgreens green blgreenck house greennd green blgreenck cgreenr");
  d4_str_t cmp90 = d4_str_alloc(L"Aaron has a green house and a green car");
  d4_str_t cmp91 = d4_str_alloc(L"Aaron has a black house and a black car");
  d4_str_t cmp92 = d4_str_alloc(L"Aron has a black house and a black car");
  d4_str_t cmp93 = d4_str_alloc(L"Aaron has a  house and a black car");
  d4_str_t cmp94 = d4_str_alloc(L"oAaron has a black house and a black car");
  d4_str_t cmp95 = d4_str_alloc(L"Aoron has a black house and a black car");
  d4_str_t cmp96 = d4_str_alloc(L"Aaron has a o house and a black car");
  d4_str_t cmp97 = d4_str_alloc(L"greenAaron has a black house and a black car");
  d4_str_t cmp98 = d4_str_alloc(L"Agreenron has a black house and a black car");
  d4_str_t cmp99 = d4_str_alloc(L"Aaron has a green house and a black car");
  d4_str_t cmp100 = d4_str_alloc(L"Aaron has a black house and a black car");
  d4_str_t cmp101 = d4_str_alloc(L"Aron hs a black house and a black car");
  d4_str_t cmp102 = d4_str_alloc(L"Aaron has a  house and a  car");
  d4_str_t cmp103 = d4_str_alloc(L"oAoaron has a black house and a black car");
  d4_str_t cmp104 = d4_str_alloc(L"Aoron hos a black house and a black car");
  d4_str_t cmp105 = d4_str_alloc(L"Aaron has a o house and a o car");
  d4_str_t cmp106 = d4_str_alloc(L"greenAgreenaron has a black house and a black car");
  d4_str_t cmp107 = d4_str_alloc(L"Agreenron hgreens a black house and a black car");
  d4_str_t cmp108 = d4_str_alloc(L"Aaron has a green house and a green car");
  d4_str_t cmp109 = d4_str_alloc(L"a");
  d4_str_t cmp110 = d4_str_alloc(L"");

  assert(((void) "Replaces all empty with empty in s1", d4_str_eq(r1, cmp1)));
  assert(((void) "Replaces all letter 'a' with empty in s1", d4_str_eq(r2, cmp2)));
  assert(((void) "Replaces all word 'black' with empty in s1", d4_str_eq(r3, cmp3)));
  assert(((void) "Replaces all empty with letter 'o' in s1", d4_str_eq(r4, cmp4)));
  assert(((void) "Replaces all letter 'a' with letter 'o' in s1", d4_str_eq(r5, cmp5)));
  assert(((void) "Replaces all word 'black' with letter 'o' in s1", d4_str_eq(r6, cmp6)));
  assert(((void) "Replaces all empty with word 'green' in s1", d4_str_eq(r7, cmp7)));
  assert(((void) "Replaces all letter 'a' with word 'green' in s1", d4_str_eq(r8, cmp8)));
  assert(((void) "Replaces all word 'black' with word 'green' in s1", d4_str_eq(r9, cmp9)));
  assert(((void) "Replaces one empty with empty in s1", d4_str_eq(r10, cmp10)));
  assert(((void) "Replaces one letter 'a' with empty in s1", d4_str_eq(r11, cmp11)));
  assert(((void) "Replaces one word 'black' with empty in s1", d4_str_eq(r12, cmp12)));
  assert(((void) "Replaces one empty with letter 'o' in s1", d4_str_eq(r13, cmp13)));
  assert(((void) "Replaces one letter 'a' with letter 'o' in s1", d4_str_eq(r14, cmp14)));
  assert(((void) "Replaces one word 'black' with letter 'o' in s1", d4_str_eq(r15, cmp15)));
  assert(((void) "Replaces one empty with word 'green' in s1", d4_str_eq(r16, cmp16)));
  assert(((void) "Replaces one letter 'a' with word 'green' in s1", d4_str_eq(r17, cmp17)));
  assert(((void) "Replaces one words 'black' with word 'green' in s1", d4_str_eq(r18, cmp18)));
  assert(((void) "Replaces two empty with empty in s1", d4_str_eq(r19, cmp19)));
  assert(((void) "Replaces two letter 'a' with empty in s1", d4_str_eq(r20, cmp20)));
  assert(((void) "Replaces two words 'black' with empty in s1", d4_str_eq(r21, cmp21)));
  assert(((void) "Replaces two empty with letter 'o' in s1", d4_str_eq(r22, cmp22)));
  assert(((void) "Replaces two letter 'a' with letter 'o' in s1", d4_str_eq(r23, cmp23)));
  assert(((void) "Replaces two words 'black' with letter 'o' in s1", d4_str_eq(r24, cmp24)));
  assert(((void) "Replaces two empty with word 'green' in s1", d4_str_eq(r25, cmp25)));
  assert(((void) "Replaces two letter 'a' with word 'green' in s1", d4_str_eq(r26, cmp26)));
  assert(((void) "Replaces two words 'black' with word 'green' in s1", d4_str_eq(r27, cmp27)));
  assert(((void) "Replaces all empty with empty in s2", d4_str_eq(r28, cmp28)));
  assert(((void) "Replaces all letter 'a' with empty in s2", d4_str_eq(r29, cmp29)));
  assert(((void) "Replaces all word 'black' with empty in s2", d4_str_eq(r30, cmp30)));
  assert(((void) "Replaces all empty with letter 'o' in s2", d4_str_eq(r31, cmp31)));
  assert(((void) "Replaces all letter 'a' with letter 'o' in s2", d4_str_eq(r32, cmp32)));
  assert(((void) "Replaces all word 'black' with letter 'o' in s2", d4_str_eq(r33, cmp33)));
  assert(((void) "Replaces all empty with word 'green' in s2", d4_str_eq(r34, cmp34)));
  assert(((void) "Replaces all letter 'a' with word 'green' in s2", d4_str_eq(r35, cmp35)));
  assert(((void) "Replaces all word 'black' with word 'green' in s2", d4_str_eq(r36, cmp36)));
  assert(((void) "Replaces one empty with empty in s2", d4_str_eq(r37, cmp37)));
  assert(((void) "Replaces one letter 'a' with empty in s2", d4_str_eq(r38, cmp38)));
  assert(((void) "Replaces one word 'black' with empty in s2", d4_str_eq(r39, cmp39)));
  assert(((void) "Replaces one empty with letter 'o' in s2", d4_str_eq(r40, cmp40)));
  assert(((void) "Replaces one letter 'a' with letter 'o' in s2", d4_str_eq(r41, cmp41)));
  assert(((void) "Replaces one word 'black' with letter 'o' in s2", d4_str_eq(r42, cmp42)));
  assert(((void) "Replaces one empty with word 'green' in s2", d4_str_eq(r43, cmp43)));
  assert(((void) "Replaces one letter 'a' with word 'green' in s2", d4_str_eq(r44, cmp44)));
  assert(((void) "Replaces one words 'black' with word 'green' in s2", d4_str_eq(r45, cmp45)));
  assert(((void) "Replaces two empty with empty in s2", d4_str_eq(r46, cmp46)));
  assert(((void) "Replaces two letter 'a' with empty in s2", d4_str_eq(r47, cmp47)));
  assert(((void) "Replaces two words 'black' with empty in s2", d4_str_eq(r48, cmp48)));
  assert(((void) "Replaces two empty with letter 'o' in s2", d4_str_eq(r49, cmp49)));
  assert(((void) "Replaces two letter 'a' with letter 'o' in s2", d4_str_eq(r50, cmp50)));
  assert(((void) "Replaces two words 'black' with letter 'o' in s2", d4_str_eq(r51, cmp51)));
  assert(((void) "Replaces two empty with word 'green' in s2", d4_str_eq(r52, cmp52)));
  assert(((void) "Replaces two letter 'a' with word 'green' in s2", d4_str_eq(r53, cmp53)));
  assert(((void) "Replaces two words 'black' with word 'green' in s2", d4_str_eq(r54, cmp54)));
  assert(((void) "Replaces all empty with empty in s3", d4_str_eq(r55, cmp55)));
  assert(((void) "Replaces all letter 'a' with empty in s3", d4_str_eq(r56, cmp56)));
  assert(((void) "Replaces all word 'black' with empty in s3", d4_str_eq(r57, cmp57)));
  assert(((void) "Replaces all empty with letter 'o' in s3", d4_str_eq(r58, cmp58)));
  assert(((void) "Replaces all letter 'a' with letter 'o' in s3", d4_str_eq(r59, cmp59)));
  assert(((void) "Replaces all word 'black' with letter 'o' in s3", d4_str_eq(r60, cmp60)));
  assert(((void) "Replaces all empty with word 'green' in s3", d4_str_eq(r61, cmp61)));
  assert(((void) "Replaces all letter 'a' with word 'green' in s3", d4_str_eq(r62, cmp62)));
  assert(((void) "Replaces all word 'black' with word 'green' in s3", d4_str_eq(r63, cmp63)));
  assert(((void) "Replaces one empty with empty in s3", d4_str_eq(r64, cmp64)));
  assert(((void) "Replaces one letter 'a' with empty in s3", d4_str_eq(r65, cmp65)));
  assert(((void) "Replaces one word 'black' with empty in s3", d4_str_eq(r66, cmp66)));
  assert(((void) "Replaces one empty with letter 'o' in s3", d4_str_eq(r67, cmp67)));
  assert(((void) "Replaces one letter 'a' with letter 'o' in s3", d4_str_eq(r68, cmp68)));
  assert(((void) "Replaces one word 'black' with letter 'o' in s3", d4_str_eq(r69, cmp69)));
  assert(((void) "Replaces one empty with word 'green' in s3", d4_str_eq(r70, cmp70)));
  assert(((void) "Replaces one letter 'a' with word 'green' in s3", d4_str_eq(r71, cmp71)));
  assert(((void) "Replaces one words 'black' with word 'green' in s3", d4_str_eq(r72, cmp72)));
  assert(((void) "Replaces two empty with empty in s3", d4_str_eq(r73, cmp73)));
  assert(((void) "Replaces two letter 'a' with empty in s3", d4_str_eq(r74, cmp74)));
  assert(((void) "Replaces two words 'black' with empty in s3", d4_str_eq(r75, cmp75)));
  assert(((void) "Replaces two empty with letter 'o' in s3", d4_str_eq(r76, cmp76)));
  assert(((void) "Replaces two letter 'a' with letter 'o' in s3", d4_str_eq(r77, cmp77)));
  assert(((void) "Replaces two words 'black' with letter 'o' in s3", d4_str_eq(r78, cmp78)));
  assert(((void) "Replaces two empty with word 'green' in s3", d4_str_eq(r79, cmp79)));
  assert(((void) "Replaces two letter 'a' with word 'green' in s3", d4_str_eq(r80, cmp80)));
  assert(((void) "Replaces two words 'black' with word 'green' in s3", d4_str_eq(r81, cmp81)));
  assert(((void) "Replaces all empty with empty in s4", d4_str_eq(r82, cmp82)));
  assert(((void) "Replaces all letter 'a' with empty in s4", d4_str_eq(r83, cmp83)));
  assert(((void) "Replaces all word 'black' with empty in s4", d4_str_eq(r84, cmp84)));
  assert(((void) "Replaces all empty with letter 'o' in s4", d4_str_eq(r85, cmp85)));
  assert(((void) "Replaces all letter 'a' with letter 'o' in s4", d4_str_eq(r86, cmp86)));
  assert(((void) "Replaces all word 'black' with letter 'o' in s4", d4_str_eq(r87, cmp87)));
  assert(((void) "Replaces all empty with word 'green' in s4", d4_str_eq(r88, cmp88)));
  assert(((void) "Replaces all letter 'a' with word 'green' in s4", d4_str_eq(r89, cmp89)));
  assert(((void) "Replaces all word 'black' with word 'green' in s4", d4_str_eq(r90, cmp90)));
  assert(((void) "Replaces one empty with empty in s4", d4_str_eq(r91, cmp91)));
  assert(((void) "Replaces one letter 'a' with empty in s4", d4_str_eq(r92, cmp92)));
  assert(((void) "Replaces one word 'black' with empty in s4", d4_str_eq(r93, cmp93)));
  assert(((void) "Replaces one empty with letter 'o' in s4", d4_str_eq(r94, cmp94)));
  assert(((void) "Replaces one letter 'a' with letter 'o' in s4", d4_str_eq(r95, cmp95)));
  assert(((void) "Replaces one word 'black' with letter 'o' in s4", d4_str_eq(r96, cmp96)));
  assert(((void) "Replaces one empty with word 'green' in s4", d4_str_eq(r97, cmp97)));
  assert(((void) "Replaces one letter 'a' with word 'green' in s4", d4_str_eq(r98, cmp98)));
  assert(((void) "Replaces one words 'black' with word 'green' in s4", d4_str_eq(r99, cmp99)));
  assert(((void) "Replaces two empty with empty in s4", d4_str_eq(r100, cmp100)));
  assert(((void) "Replaces two letter 'a' with empty in s4", d4_str_eq(r101, cmp101)));
  assert(((void) "Replaces two words 'black' with empty in s4", d4_str_eq(r102, cmp102)));
  assert(((void) "Replaces two empty with letter 'o' in s4", d4_str_eq(r103, cmp103)));
  assert(((void) "Replaces two letter 'a' with letter 'o' in s4", d4_str_eq(r104, cmp104)));
  assert(((void) "Replaces two words 'black' with letter 'o' in s4", d4_str_eq(r105, cmp105)));
  assert(((void) "Replaces two empty with word 'green' in s4", d4_str_eq(r106, cmp106)));
  assert(((void) "Replaces two letter 'a' with word 'green' in s4", d4_str_eq(r107, cmp107)));
  assert(((void) "Replaces two words 'black' with word 'green' in s4", d4_str_eq(r108, cmp108)));
  assert(((void) "Does not replace same length strings if does not match", d4_str_eq(r109, cmp109)));
  assert(((void) "Replaces multiple times repeated with empty", d4_str_eq(r110, cmp110)));

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);

  d4_str_free(search1);
  d4_str_free(search2);
  d4_str_free(search3);

  d4_str_free(replacement1);
  d4_str_free(replacement2);
  d4_str_free(replacement3);

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
  d4_str_free(r39);
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
  d4_str_free(r59);
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
  d4_str_free(r79);
  d4_str_free(r80);
  d4_str_free(r81);
  d4_str_free(r82);
  d4_str_free(r83);
  d4_str_free(r84);
  d4_str_free(r85);
  d4_str_free(r86);
  d4_str_free(r87);
  d4_str_free(r88);
  d4_str_free(r89);
  d4_str_free(r90);
  d4_str_free(r91);
  d4_str_free(r92);
  d4_str_free(r93);
  d4_str_free(r94);
  d4_str_free(r95);
  d4_str_free(r96);
  d4_str_free(r97);
  d4_str_free(r98);
  d4_str_free(r99);
  d4_str_free(r100);
  d4_str_free(r101);
  d4_str_free(r102);
  d4_str_free(r103);
  d4_str_free(r104);
  d4_str_free(r105);
  d4_str_free(r106);
  d4_str_free(r107);
  d4_str_free(r108);
  d4_str_free(r109);
  d4_str_free(r110);

  d4_str_free(cmp1);
  d4_str_free(cmp2);
  d4_str_free(cmp3);
  d4_str_free(cmp4);
  d4_str_free(cmp5);
  d4_str_free(cmp6);
  d4_str_free(cmp7);
  d4_str_free(cmp8);
  d4_str_free(cmp9);
  d4_str_free(cmp10);
  d4_str_free(cmp11);
  d4_str_free(cmp12);
  d4_str_free(cmp13);
  d4_str_free(cmp14);
  d4_str_free(cmp15);
  d4_str_free(cmp16);
  d4_str_free(cmp17);
  d4_str_free(cmp18);
  d4_str_free(cmp19);
  d4_str_free(cmp20);
  d4_str_free(cmp21);
  d4_str_free(cmp22);
  d4_str_free(cmp23);
  d4_str_free(cmp24);
  d4_str_free(cmp25);
  d4_str_free(cmp26);
  d4_str_free(cmp27);
  d4_str_free(cmp28);
  d4_str_free(cmp29);
  d4_str_free(cmp30);
  d4_str_free(cmp31);
  d4_str_free(cmp32);
  d4_str_free(cmp33);
  d4_str_free(cmp34);
  d4_str_free(cmp35);
  d4_str_free(cmp36);
  d4_str_free(cmp37);
  d4_str_free(cmp38);
  d4_str_free(cmp39);
  d4_str_free(cmp40);
  d4_str_free(cmp41);
  d4_str_free(cmp42);
  d4_str_free(cmp43);
  d4_str_free(cmp44);
  d4_str_free(cmp45);
  d4_str_free(cmp46);
  d4_str_free(cmp47);
  d4_str_free(cmp48);
  d4_str_free(cmp49);
  d4_str_free(cmp50);
  d4_str_free(cmp51);
  d4_str_free(cmp52);
  d4_str_free(cmp53);
  d4_str_free(cmp54);
  d4_str_free(cmp55);
  d4_str_free(cmp56);
  d4_str_free(cmp57);
  d4_str_free(cmp58);
  d4_str_free(cmp59);
  d4_str_free(cmp60);
  d4_str_free(cmp61);
  d4_str_free(cmp62);
  d4_str_free(cmp63);
  d4_str_free(cmp64);
  d4_str_free(cmp65);
  d4_str_free(cmp66);
  d4_str_free(cmp67);
  d4_str_free(cmp68);
  d4_str_free(cmp69);
  d4_str_free(cmp70);
  d4_str_free(cmp71);
  d4_str_free(cmp72);
  d4_str_free(cmp73);
  d4_str_free(cmp74);
  d4_str_free(cmp75);
  d4_str_free(cmp76);
  d4_str_free(cmp77);
  d4_str_free(cmp78);
  d4_str_free(cmp79);
  d4_str_free(cmp80);
  d4_str_free(cmp81);
  d4_str_free(cmp82);
  d4_str_free(cmp83);
  d4_str_free(cmp84);
  d4_str_free(cmp85);
  d4_str_free(cmp86);
  d4_str_free(cmp87);
  d4_str_free(cmp88);
  d4_str_free(cmp89);
  d4_str_free(cmp90);
  d4_str_free(cmp91);
  d4_str_free(cmp92);
  d4_str_free(cmp93);
  d4_str_free(cmp94);
  d4_str_free(cmp95);
  d4_str_free(cmp96);
  d4_str_free(cmp97);
  d4_str_free(cmp98);
  d4_str_free(cmp99);
  d4_str_free(cmp100);
  d4_str_free(cmp101);
  d4_str_free(cmp102);
  d4_str_free(cmp103);
  d4_str_free(cmp104);
  d4_str_free(cmp105);
  d4_str_free(cmp106);
  d4_str_free(cmp107);
  d4_str_free(cmp108);
  d4_str_free(cmp109);
  d4_str_free(cmp110);
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
  d4_str_t l_empty = d4_str_alloc(L"");
  d4_str_t l_space = d4_str_alloc(L" ");
  d4_str_t l_a = d4_str_alloc(L"a");
  d4_str_t l_d = d4_str_alloc(L"d");
  d4_str_t l_e = d4_str_alloc(L"e");
  d4_str_t l_h = d4_str_alloc(L"h");
  d4_str_t l_l = d4_str_alloc(L"l");
  d4_str_t l_o = d4_str_alloc(L"o");
  d4_str_t l_r = d4_str_alloc(L"r");
  d4_str_t l_s = d4_str_alloc(L"s");
  d4_str_t l_t = d4_str_alloc(L"t");
  d4_str_t l_w = d4_str_alloc(L"w");

  d4_str_t w_es = d4_str_alloc(L"es");
  d4_str_t w_he = d4_str_alloc(L"he");
  d4_str_t w_hello = d4_str_alloc(L"hello");
  d4_str_t w_hello_world = d4_str_alloc(L"hello world");
  d4_str_t w_spaced_a = d4_str_alloc(L" a ");
  d4_str_t w_o_world = d4_str_alloc(L"o world");
  d4_str_t w_t_a_te = d4_str_alloc(L"t a te");
  d4_str_t w_te = d4_str_alloc(L"te");
  d4_str_t w_test = d4_str_alloc(L"test");
  d4_str_t w_test_a_test_a_test = d4_str_alloc(L"test a test a test");
  d4_str_t w_world = d4_str_alloc(L"world");

  d4_str_t d1 = d4_str_alloc(L"");
  d4_str_t d2 = d4_str_alloc(L" ");
  d4_str_t d3 = d4_str_alloc(L" a ");
  d4_str_t d4 = d4_str_alloc(L"s");
  d4_str_t d5 = d4_str_alloc(L"t");
  d4_str_t d6 = d4_str_alloc(L"ll");
  d4_str_t d7 = d4_str_alloc(L"z");

  d4_str_t s1 = d4_str_alloc(L"");
  d4_str_t s2 = d4_str_alloc(L"t");
  d4_str_t s3 = d4_str_alloc(L"test");
  d4_str_t s4 = d4_str_alloc(L"hello world");
  d4_str_t s5 = d4_str_alloc(L"test a test a test");

  d4_arr_str_t r10 = d4_str_split(s1, 1, d1);
  d4_arr_str_t r11 = d4_str_split(s2, 1, d1);
  d4_arr_str_t r12 = d4_str_split(s3, 1, d1);
  d4_arr_str_t r13 = d4_str_split(s4, 1, d1);
  d4_arr_str_t r14 = d4_str_split(s5, 1, d1);
  d4_arr_str_t r15 = d4_str_split(s1, 1, d2);
  d4_arr_str_t r16 = d4_str_split(s2, 1, d2);
  d4_arr_str_t r17 = d4_str_split(s3, 1, d2);
  d4_arr_str_t r18 = d4_str_split(s4, 1, d2);
  d4_arr_str_t r19 = d4_str_split(s5, 1, d2);
  d4_arr_str_t r20 = d4_str_split(s1, 1, d3);
  d4_arr_str_t r21 = d4_str_split(s2, 1, d3);
  d4_arr_str_t r22 = d4_str_split(s3, 1, d3);
  d4_arr_str_t r23 = d4_str_split(s4, 1, d3);
  d4_arr_str_t r24 = d4_str_split(s5, 1, d3);
  d4_arr_str_t r25 = d4_str_split(s1, 1, d4);
  d4_arr_str_t r26 = d4_str_split(s2, 1, d4);
  d4_arr_str_t r27 = d4_str_split(s3, 1, d4);
  d4_arr_str_t r28 = d4_str_split(s4, 1, d4);
  d4_arr_str_t r29 = d4_str_split(s5, 1, d4);
  d4_arr_str_t r30 = d4_str_split(s1, 1, d5);
  d4_arr_str_t r31 = d4_str_split(s2, 1, d5);
  d4_arr_str_t r32 = d4_str_split(s3, 1, d5);
  d4_arr_str_t r33 = d4_str_split(s4, 1, d5);
  d4_arr_str_t r34 = d4_str_split(s5, 1, d5);
  d4_arr_str_t r35 = d4_str_split(s1, 1, d6);
  d4_arr_str_t r36 = d4_str_split(s2, 1, d6);
  d4_arr_str_t r37 = d4_str_split(s3, 1, d6);
  d4_arr_str_t r38 = d4_str_split(s4, 1, d6);
  d4_arr_str_t r39 = d4_str_split(s5, 1, d6);
  d4_arr_str_t r40 = d4_str_split(s1, 1, d7);
  d4_arr_str_t r41 = d4_str_split(s2, 1, d7);
  d4_arr_str_t r42 = d4_str_split(s3, 1, d7);
  d4_arr_str_t r43 = d4_str_split(s4, 1, d7);
  d4_arr_str_t r44 = d4_str_split(s5, 1, d7);

  d4_arr_str_t r10_cmp = d4_arr_str_alloc(0);
  d4_arr_str_t r11_cmp = d4_arr_str_alloc(1, l_t);
  d4_arr_str_t r12_cmp = d4_arr_str_alloc(4, l_t, l_e, l_s, l_t);
  d4_arr_str_t r13_cmp = d4_arr_str_alloc(11, l_h, l_e, l_l, l_l, l_o, l_space, l_w, l_o, l_r, l_l, l_d);
  d4_arr_str_t r14_cmp = d4_arr_str_alloc(18, l_t, l_e, l_s, l_t, l_space, l_a, l_space, l_t, l_e, l_s, l_t, l_space, l_a, l_space, l_t, l_e, l_s, l_t);
  d4_arr_str_t r15_cmp = d4_arr_str_alloc(1, l_empty);
  d4_arr_str_t r16_cmp = d4_arr_str_alloc(1, l_t);
  d4_arr_str_t r17_cmp = d4_arr_str_alloc(1, w_test);
  d4_arr_str_t r18_cmp = d4_arr_str_alloc(2, w_hello, w_world);
  d4_arr_str_t r19_cmp = d4_arr_str_alloc(5, w_test, l_a, w_test, l_a, w_test);
  d4_arr_str_t r20_cmp = d4_arr_str_alloc(1, l_empty);
  d4_arr_str_t r21_cmp = d4_arr_str_alloc(1, l_t);
  d4_arr_str_t r22_cmp = d4_arr_str_alloc(1, w_test);
  d4_arr_str_t r23_cmp = d4_arr_str_alloc(1, w_hello_world);
  d4_arr_str_t r24_cmp = d4_arr_str_alloc(3, w_test, w_test, w_test);
  d4_arr_str_t r25_cmp = d4_arr_str_alloc(1, l_empty);
  d4_arr_str_t r26_cmp = d4_arr_str_alloc(1, l_t);
  d4_arr_str_t r27_cmp = d4_arr_str_alloc(2, w_te, l_t);
  d4_arr_str_t r28_cmp = d4_arr_str_alloc(1, w_hello_world);
  d4_arr_str_t r29_cmp = d4_arr_str_alloc(4, w_te, w_t_a_te, w_t_a_te, l_t);
  d4_arr_str_t r30_cmp = d4_arr_str_alloc(1, l_empty);
  d4_arr_str_t r31_cmp = d4_arr_str_alloc(2, l_empty, l_empty);
  d4_arr_str_t r32_cmp = d4_arr_str_alloc(3, l_empty, w_es, l_empty);
  d4_arr_str_t r33_cmp = d4_arr_str_alloc(1, w_hello_world);
  d4_arr_str_t r34_cmp = d4_arr_str_alloc(7, l_empty, w_es, w_spaced_a, w_es, w_spaced_a, w_es, l_empty);
  d4_arr_str_t r35_cmp = d4_arr_str_alloc(1, l_empty);
  d4_arr_str_t r36_cmp = d4_arr_str_alloc(1, l_t);
  d4_arr_str_t r37_cmp = d4_arr_str_alloc(1, w_test);
  d4_arr_str_t r38_cmp = d4_arr_str_alloc(2, w_he, w_o_world);
  d4_arr_str_t r39_cmp = d4_arr_str_alloc(1, w_test_a_test_a_test);
  d4_arr_str_t r40_cmp = d4_arr_str_alloc(1, l_empty);
  d4_arr_str_t r41_cmp = d4_arr_str_alloc(1, l_t);
  d4_arr_str_t r42_cmp = d4_arr_str_alloc(1, w_test);
  d4_arr_str_t r43_cmp = d4_arr_str_alloc(1, w_hello_world);
  d4_arr_str_t r44_cmp = d4_arr_str_alloc(1, w_test_a_test_a_test);

  assert(((void) "Splits empty string by empty string", d4_arr_str_eq(r10, r10_cmp)));
  assert(((void) "Splits single letter string by empty string", d4_arr_str_eq(r11, r11_cmp)));
  assert(((void) "Splits multi letter string by empty string", d4_arr_str_eq(r12, r12_cmp)));
  assert(((void) "Splits multi word string by empty string", d4_arr_str_eq(r13, r13_cmp)));
  assert(((void) "Splits sentence string by empty string", d4_arr_str_eq(r14, r14_cmp)));

  assert(((void) "Splits empty string by space", d4_arr_str_eq(r15, r15_cmp)));
  assert(((void) "Splits single letter string by space", d4_arr_str_eq(r16, r16_cmp)));
  assert(((void) "Splits multi letter string by space", d4_arr_str_eq(r17, r17_cmp)));
  assert(((void) "Splits multi word string by space", d4_arr_str_eq(r18, r18_cmp)));
  assert(((void) "Splits sentence string by space", d4_arr_str_eq(r19, r19_cmp)));

  assert(((void) "Splits empty string by spaced letter 'a'", d4_arr_str_eq(r20, r20_cmp)));
  assert(((void) "Splits single letter string by spaced letter 'a'", d4_arr_str_eq(r21, r21_cmp)));
  assert(((void) "Splits multi letter string by spaced letter 'a'", d4_arr_str_eq(r22, r22_cmp)));
  assert(((void) "Splits multi word string by spaced letter 'a'", d4_arr_str_eq(r23, r23_cmp)));
  assert(((void) "Splits sentence string by spaced letter 'a'", d4_arr_str_eq(r24, r24_cmp)));

  assert(((void) "Splits empty string by letter 's'", d4_arr_str_eq(r25, r25_cmp)));
  assert(((void) "Splits single letter string by letter 's'", d4_arr_str_eq(r26, r26_cmp)));
  assert(((void) "Splits multi letter string by letter 's'", d4_arr_str_eq(r27, r27_cmp)));
  assert(((void) "Splits multi word string by letter 's'", d4_arr_str_eq(r28, r28_cmp)));
  assert(((void) "Splits sentence string by letter 's'", d4_arr_str_eq(r29, r29_cmp)));

  assert(((void) "Splits empty string by letter 't'", d4_arr_str_eq(r30, r30_cmp)));
  assert(((void) "Splits single letter string by letter 't'", d4_arr_str_eq(r31, r31_cmp)));
  assert(((void) "Splits multi letter string by letter 't'", d4_arr_str_eq(r32, r32_cmp)));
  assert(((void) "Splits multi word string by letter 't'", d4_arr_str_eq(r33, r33_cmp)));
  assert(((void) "Splits sentence string by letter 't'", d4_arr_str_eq(r34, r34_cmp)));

  assert(((void) "Splits empty string by two letters 'll'", d4_arr_str_eq(r35, r35_cmp)));
  assert(((void) "Splits single letter string by two letters 'll'", d4_arr_str_eq(r36, r36_cmp)));
  assert(((void) "Splits multi letter string by two letters 'll'", d4_arr_str_eq(r37, r37_cmp)));
  assert(((void) "Splits multi word string by two letters 'll'", d4_arr_str_eq(r38, r38_cmp)));
  assert(((void) "Splits sentence string by two letters 'll'", d4_arr_str_eq(r39, r39_cmp)));

  assert(((void) "Splits empty string by non-existing letter", d4_arr_str_eq(r40, r40_cmp)));
  assert(((void) "Splits single letter string by non-existing letter", d4_arr_str_eq(r41, r41_cmp)));
  assert(((void) "Splits multi letter string by non-existing letter", d4_arr_str_eq(r42, r42_cmp)));
  assert(((void) "Splits multi word string by non-existing letter", d4_arr_str_eq(r43, r43_cmp)));
  assert(((void) "Splits sentence string by non-existing letter", d4_arr_str_eq(r44, r44_cmp)));

  d4_str_free(l_empty);
  d4_str_free(l_space);
  d4_str_free(l_a);
  d4_str_free(l_d);
  d4_str_free(l_e);
  d4_str_free(l_h);
  d4_str_free(l_l);
  d4_str_free(l_o);
  d4_str_free(l_r);
  d4_str_free(l_s);
  d4_str_free(l_t);
  d4_str_free(l_w);

  d4_str_free(w_es);
  d4_str_free(w_he);
  d4_str_free(w_hello);
  d4_str_free(w_hello_world);
  d4_str_free(w_spaced_a);
  d4_str_free(w_o_world);
  d4_str_free(w_t_a_te);
  d4_str_free(w_te);
  d4_str_free(w_test);
  d4_str_free(w_test_a_test_a_test);
  d4_str_free(w_world);

  d4_str_free(d1);
  d4_str_free(d2);
  d4_str_free(d3);
  d4_str_free(d4);
  d4_str_free(d5);
  d4_str_free(d6);
  d4_str_free(d7);

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);

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
}

static void test_string_toFloat (void) {
  d4_str_t s1 = d4_str_alloc(L"0");
  d4_str_t s2 = d4_str_alloc(L"1");
  d4_str_t s3 = d4_str_alloc(L"1.23");
  d4_str_t s4 = d4_str_alloc(L"1.7976931348623157e+308");
  d4_str_t s5 = d4_str_alloc(L"3e+38");
  d4_str_t s6 = d4_str_alloc(L"2.2250738585072014e-308");
  d4_str_t s7 = d4_str_alloc(L"1E-38");
  d4_str_t s8 = d4_str_alloc(L"-1.7976931348623157e+308");

  d4_str_t s10 = d4_str_alloc(L"1e+500");
  d4_str_t s11 = d4_str_alloc(L"1e-500");
  d4_str_t s12 = d4_str_alloc(L"");
  d4_str_t s13 = d4_str_alloc(L" 1.23 ");
  d4_str_t s14 = d4_str_alloc(L"1.23f");
  d4_str_t s15 = d4_str_alloc(L"test");

  ASSERT_NO_THROW(TO_FLOAT1, {
    assert(((void) "Converts to float zero", d4_str_toFloat(&d4_err_state, 0, 0, s1) == 0));
    assert(((void) "Converts to float single digit", d4_str_toFloat(&d4_err_state, 0, 0, s2) == 1));
    assert(((void) "Converts to float with floating point", d4_str_toFloat(&d4_err_state, 0, 0, s3) == 1.23));
    assert(((void) "Converts to float max value", d4_str_toFloat(&d4_err_state, 0, 0, s4) == 1.7976931348623157e+308));
    assert(((void) "Converts to float only positive exponent", d4_str_toFloat(&d4_err_state, 0, 0, s5) == 3e+38));
    assert(((void) "Converts to float smallest value", d4_str_toFloat(&d4_err_state, 0, 0, s6) == 2.2250738585072014e-308));
    assert(((void) "Converts to float only negative exponent", d4_str_toFloat(&d4_err_state, 0, 0, s7) == 1E-38));
    assert(((void) "Converts to float min value", d4_str_toFloat(&d4_err_state, 0, 0, s8) == -1.7976931348623157e+308));
  });

  ASSERT_THROW_WITH_MESSAGE(TO_FLOAT2, {
    d4_str_toFloat(&d4_err_state, 0, 0, s10);
  }, L"value `1e+500` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_FLOAT3, {
    d4_str_toFloat(&d4_err_state, 0, 0, s11);
  }, L"value `1e-500` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_FLOAT4, {
    d4_str_toFloat(&d4_err_state, 0, 0, s12);
  }, L"value `` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_FLOAT5, {
    d4_str_toFloat(&d4_err_state, 0, 0, s13);
  }, L"value ` 1.23 ` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_FLOAT6, {
    d4_str_toFloat(&d4_err_state, 0, 0, s14);
  }, L"value `1.23f` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_FLOAT7, {
    d4_str_toFloat(&d4_err_state, 0, 0, s15);
  }, L"value `test` has invalid syntax");

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s6);
  d4_str_free(s7);
  d4_str_free(s8);
  d4_str_free(s10);
  d4_str_free(s11);
  d4_str_free(s12);
  d4_str_free(s13);
  d4_str_free(s14);
  d4_str_free(s15);
}

static void test_string_toF32 (void) {
  d4_str_t s1 = d4_str_alloc(L"0");
  d4_str_t s2 = d4_str_alloc(L"1");
  d4_str_t s3 = d4_str_alloc(L"1.23");
  d4_str_t s4 = d4_str_alloc(L"3.40282347e+38");
  d4_str_t s5 = d4_str_alloc(L"3e+38");
  d4_str_t s6 = d4_str_alloc(L"1.17549435e-38");
  d4_str_t s7 = d4_str_alloc(L"1E-37");
  d4_str_t s8 = d4_str_alloc(L"-3.40282347e+38");

  d4_str_t s10 = d4_str_alloc(L"1e+500");
  d4_str_t s11 = d4_str_alloc(L"1e-500");
  d4_str_t s12 = d4_str_alloc(L"");
  d4_str_t s13 = d4_str_alloc(L" 1.23 ");
  d4_str_t s14 = d4_str_alloc(L"1.23f");
  d4_str_t s15 = d4_str_alloc(L"test");

  ASSERT_NO_THROW(TO_FLOAT32_1, {
    assert(((void) "Converts to f32 zero", d4_str_toF32(&d4_err_state, 0, 0, s1) == 0.0f));
    assert(((void) "Converts to f32 single digit", d4_str_toF32(&d4_err_state, 0, 0, s2) == 1.0f));
    assert(((void) "Converts to f32 with floating point", d4_str_toF32(&d4_err_state, 0, 0, s3) == 1.23f));
    assert(((void) "Converts to f32 max value", d4_str_toF32(&d4_err_state, 0, 0, s4) == 3.40282347e+38f));
    assert(((void) "Converts to f32 only positive exponent", d4_str_toF32(&d4_err_state, 0, 0, s5) == 3e+38f));
    assert(((void) "Converts to f32 smallest value", d4_str_toF32(&d4_err_state, 0, 0, s6) == 1.17549435e-38f));
    assert(((void) "Converts to f32 only negative exponent", d4_str_toF32(&d4_err_state, 0, 0, s7) == 1E-37f));
    assert(((void) "Converts to f32 min value", d4_str_toF32(&d4_err_state, 0, 0, s8) == -3.40282347e+38f));
  });

  ASSERT_THROW_WITH_MESSAGE(TO_FLOAT32_2, {
    d4_str_toF32(&d4_err_state, 0, 0, s10);
  }, L"value `1e+500` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_FLOAT32_3, {
    d4_str_toF32(&d4_err_state, 0, 0, s11);
  }, L"value `1e-500` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_FLOAT32_4, {
    d4_str_toF32(&d4_err_state, 0, 0, s12);
  }, L"value `` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_FLOAT32_5, {
    d4_str_toF32(&d4_err_state, 0, 0, s13);
  }, L"value ` 1.23 ` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_FLOAT32_6, {
    d4_str_toF32(&d4_err_state, 0, 0, s14);
  }, L"value `1.23f` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_FLOAT32_7, {
    d4_str_toF32(&d4_err_state, 0, 0, s15);
  }, L"value `test` has invalid syntax");

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s6);
  d4_str_free(s7);
  d4_str_free(s8);
  d4_str_free(s10);
  d4_str_free(s11);
  d4_str_free(s12);
  d4_str_free(s13);
  d4_str_free(s14);
  d4_str_free(s15);
}

static void test_string_toF64 (void) {
  d4_str_t s1 = d4_str_alloc(L"0");
  d4_str_t s2 = d4_str_alloc(L"1");
  d4_str_t s3 = d4_str_alloc(L"1.23");
  d4_str_t s4 = d4_str_alloc(L"1.7976931348623157e+308");
  d4_str_t s5 = d4_str_alloc(L"3e+38");
  d4_str_t s6 = d4_str_alloc(L"2.2250738585072014e-308");
  d4_str_t s7 = d4_str_alloc(L"1E-38");
  d4_str_t s8 = d4_str_alloc(L"-1.7976931348623157e+308");

  d4_str_t s10 = d4_str_alloc(L"1e+500");
  d4_str_t s11 = d4_str_alloc(L"1e-500");
  d4_str_t s12 = d4_str_alloc(L"");
  d4_str_t s13 = d4_str_alloc(L" 1.23 ");
  d4_str_t s14 = d4_str_alloc(L"1.23f");
  d4_str_t s15 = d4_str_alloc(L"test");

  ASSERT_NO_THROW(TO_FLOAT64_1, {
    assert(((void) "Converts to f64 zero", d4_str_toF64(&d4_err_state, 0, 0, s1) == 0));
    assert(((void) "Converts to f64 single digit", d4_str_toF64(&d4_err_state, 0, 0, s2) == 1));
    assert(((void) "Converts to f64 with floating point", d4_str_toF64(&d4_err_state, 0, 0, s3) == 1.23));
    assert(((void) "Converts to f64 max value", d4_str_toF64(&d4_err_state, 0, 0, s4) == 1.7976931348623157e+308));
    assert(((void) "Converts to f64 only positive exponent", d4_str_toF64(&d4_err_state, 0, 0, s5) == 3e+38));
    assert(((void) "Converts to f64 smallest value", d4_str_toF64(&d4_err_state, 0, 0, s6) == 2.2250738585072014e-308));
    assert(((void) "Converts to f64 only negative exponent", d4_str_toF64(&d4_err_state, 0, 0, s7) == 1E-38));
    assert(((void) "Converts to f64 min value", d4_str_toF64(&d4_err_state, 0, 0, s8) == -1.7976931348623157e+308));
  });

  ASSERT_THROW_WITH_MESSAGE(TO_FLOAT64_2, {
    d4_str_toF64(&d4_err_state, 0, 0, s10);
  }, L"value `1e+500` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_FLOAT64_3, {
    d4_str_toF64(&d4_err_state, 0, 0, s11);
  }, L"value `1e-500` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_FLOAT64_4, {
    d4_str_toF64(&d4_err_state, 0, 0, s12);
  }, L"value `` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_FLOAT64_5, {
    d4_str_toF64(&d4_err_state, 0, 0, s13);
  }, L"value ` 1.23 ` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_FLOAT64_6, {
    d4_str_toF64(&d4_err_state, 0, 0, s14);
  }, L"value `1.23f` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_FLOAT64_7, {
    d4_str_toF64(&d4_err_state, 0, 0, s15);
  }, L"value `test` has invalid syntax");

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s6);
  d4_str_free(s7);
  d4_str_free(s8);
  d4_str_free(s10);
  d4_str_free(s11);
  d4_str_free(s12);
  d4_str_free(s13);
  d4_str_free(s14);
  d4_str_free(s15);
}

static void test_string_toIsize (void) {
  d4_str_t s1 = d4_str_alloc(L"0");
  d4_str_t s2 = d4_str_alloc(L"1");
  d4_str_t s3 = d4_str_alloc(L"123");
  d4_str_t s4 = d4_str_alloc(L"9223372036854775807");
  d4_str_t s5 = d4_str_alloc(L"-9223372036854775808");

  d4_str_t s11 = d4_str_alloc(L"0");
  d4_str_t s12 = d4_str_alloc(L"1");
  d4_str_t s13 = d4_str_alloc(L"01111011");

  d4_str_t s21 = d4_str_alloc(L"0");
  d4_str_t s22 = d4_str_alloc(L"1");
  d4_str_t s23 = d4_str_alloc(L"173");

  d4_str_t s31 = d4_str_alloc(L"0");
  d4_str_t s32 = d4_str_alloc(L"1");
  d4_str_t s33 = d4_str_alloc(L"7B");

  d4_str_t s50 = d4_str_alloc(L"10223372036854775807");
  d4_str_t s51 = d4_str_alloc(L"-10223372036854775808");
  d4_str_t s52 = d4_str_alloc(L"");
  d4_str_t s53 = d4_str_alloc(L" 123 ");
  d4_str_t s54 = d4_str_alloc(L"123f");
  d4_str_t s55 = d4_str_alloc(L"test");

  ASSERT_NO_THROW(TO_ISIZE1, {
    assert(((void) "Converts to isize zero", d4_str_toIsize(&d4_err_state, 0, 0, s1, 0, 0) == 0));
    assert(((void) "Converts to isize single digit", d4_str_toIsize(&d4_err_state, 0, 0, s2, 0, 0) == 1));
    assert(((void) "Converts to isize multiples digits", d4_str_toIsize(&d4_err_state, 0, 0, s3, 0, 0) == 123));
    assert(((void) "Converts to isize max value", d4_str_toIsize(&d4_err_state, 0, 0, s4, 0, 0) == 9223372036854775807));
    assert(((void) "Converts to isize min value", d4_str_toIsize(&d4_err_state, 0, 0, s5, 0, 0) == (ptrdiff_t) (-9223372036854775808U)));

    assert(((void) "Converts to isize binary zero", d4_str_toIsize(&d4_err_state, 0, 0, s11, 1, 2) == 0));
    assert(((void) "Converts to isize binary single digit", d4_str_toIsize(&d4_err_state, 0, 0, s12, 1, 2) == 1));
    assert(((void) "Converts to isize binary multiples digits", d4_str_toIsize(&d4_err_state, 0, 0, s13, 1, 2) == 123));

    assert(((void) "Converts to isize octal zero", d4_str_toIsize(&d4_err_state, 0, 0, s21, 1, 8) == 0));
    assert(((void) "Converts to isize octal single digit", d4_str_toIsize(&d4_err_state, 0, 0, s22, 1, 8) == 1));
    assert(((void) "Converts to isize octal multiples digits", d4_str_toIsize(&d4_err_state, 0, 0, s23, 1, 8) == 123));

    assert(((void) "Converts to isize hexadecimal zero", d4_str_toIsize(&d4_err_state, 0, 0, s31, 1, 16) == 0));
    assert(((void) "Converts to isize hexadecimal single digit", d4_str_toIsize(&d4_err_state, 0, 0, s32, 1, 16) == 1));
    assert(((void) "Converts to isize hexadecimal multiples digits", d4_str_toIsize(&d4_err_state, 0, 0, s33, 1, 16) == 123));
  });

  ASSERT_THROW_WITH_MESSAGE(TO_ISIZE2, {
    d4_str_toIsize(&d4_err_state, 0, 0, s50, 0, 0);
  }, L"value `10223372036854775807` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_ISIZE3, {
    d4_str_toIsize(&d4_err_state, 0, 0, s51, 0, 0);
  }, L"value `-10223372036854775808` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_ISIZE4, {
    d4_str_toIsize(&d4_err_state, 0, 0, s52, 0, 0);
  }, L"value `` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_ISIZE5, {
    d4_str_toIsize(&d4_err_state, 0, 0, s53, 0, 0);
  }, L"value ` 123 ` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_ISIZE6, {
    d4_str_toIsize(&d4_err_state, 0, 0, s54, 0, 0);
  }, L"value `123f` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_ISIZE7, {
    d4_str_toIsize(&d4_err_state, 0, 0, s55, 0, 0);
  }, L"value `test` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_ISIZE8, {
    d4_str_toIsize(&d4_err_state, 0, 0, s55, 1, 1);
  }, L"radix 1 is invalid, must be >= 2 and <= 36, or 0");

  ASSERT_THROW_WITH_MESSAGE(TO_ISIZE9, {
    d4_str_toIsize(&d4_err_state, 0, 0, s55, 1, 40);
  }, L"radix 40 is invalid, must be >= 2 and <= 36, or 0");

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s11);
  d4_str_free(s12);
  d4_str_free(s13);
  d4_str_free(s21);
  d4_str_free(s22);
  d4_str_free(s23);
  d4_str_free(s31);
  d4_str_free(s32);
  d4_str_free(s33);
  d4_str_free(s50);
  d4_str_free(s51);
  d4_str_free(s52);
  d4_str_free(s53);
  d4_str_free(s54);
  d4_str_free(s55);
}

static void test_string_toI8 (void) {
  d4_str_t s1 = d4_str_alloc(L"0");
  d4_str_t s2 = d4_str_alloc(L"1");
  d4_str_t s3 = d4_str_alloc(L"123");
  d4_str_t s4 = d4_str_alloc(L"127");
  d4_str_t s5 = d4_str_alloc(L"-128");

  d4_str_t s11 = d4_str_alloc(L"0");
  d4_str_t s12 = d4_str_alloc(L"1");
  d4_str_t s13 = d4_str_alloc(L"01111011");

  d4_str_t s21 = d4_str_alloc(L"0");
  d4_str_t s22 = d4_str_alloc(L"1");
  d4_str_t s23 = d4_str_alloc(L"173");

  d4_str_t s31 = d4_str_alloc(L"0");
  d4_str_t s32 = d4_str_alloc(L"1");
  d4_str_t s33 = d4_str_alloc(L"7B");

  d4_str_t s50 = d4_str_alloc(L"128");
  d4_str_t s51 = d4_str_alloc(L"-129");
  d4_str_t s52 = d4_str_alloc(L"");
  d4_str_t s53 = d4_str_alloc(L" 123 ");
  d4_str_t s54 = d4_str_alloc(L"123f");
  d4_str_t s55 = d4_str_alloc(L"test");

  ASSERT_NO_THROW(TO_I8_1, {
    assert(((void) "Converts to i8 zero", d4_str_toI8(&d4_err_state, 0, 0, s1, 0, 0) == 0));
    assert(((void) "Converts to i8 single digit", d4_str_toI8(&d4_err_state, 0, 0, s2, 0, 0) == 1));
    assert(((void) "Converts to i8 multiples digits", d4_str_toI8(&d4_err_state, 0, 0, s3, 0, 0) == 123));
    assert(((void) "Converts to i8 max value", d4_str_toI8(&d4_err_state, 0, 0, s4, 0, 0) == 127));
    assert(((void) "Converts to i8 min value", d4_str_toI8(&d4_err_state, 0, 0, s5, 0, 0) == -128));

    assert(((void) "Converts to i8 binary zero", d4_str_toI8(&d4_err_state, 0, 0, s11, 1, 2) == 0));
    assert(((void) "Converts to i8 binary single digit", d4_str_toI8(&d4_err_state, 0, 0, s12, 1, 2) == 1));
    assert(((void) "Converts to i8 binary multiples digits", d4_str_toI8(&d4_err_state, 0, 0, s13, 1, 2) == 123));

    assert(((void) "Converts to i8 octal zero", d4_str_toI8(&d4_err_state, 0, 0, s21, 1, 8) == 0));
    assert(((void) "Converts to i8 octal single digit", d4_str_toI8(&d4_err_state, 0, 0, s22, 1, 8) == 1));
    assert(((void) "Converts to i8 octal multiples digits", d4_str_toI8(&d4_err_state, 0, 0, s23, 1, 8) == 123));

    assert(((void) "Converts to i8 hexadecimal zero", d4_str_toI8(&d4_err_state, 0, 0, s31, 1, 16) == 0));
    assert(((void) "Converts to i8 hexadecimal single digit", d4_str_toI8(&d4_err_state, 0, 0, s32, 1, 16) == 1));
    assert(((void) "Converts to i8 hexadecimal multiples digits", d4_str_toI8(&d4_err_state, 0, 0, s33, 1, 16) == 123));
  });

  ASSERT_THROW_WITH_MESSAGE(TO_I8_2, {
    d4_str_toI8(&d4_err_state, 0, 0, s50, 0, 0);
  }, L"value `128` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_I8_3, {
    d4_str_toI8(&d4_err_state, 0, 0, s51, 0, 0);
  }, L"value `-129` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_I8_4, {
    d4_str_toI8(&d4_err_state, 0, 0, s52, 0, 0);
  }, L"value `` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_I8_5, {
    d4_str_toI8(&d4_err_state, 0, 0, s53, 0, 0);
  }, L"value ` 123 ` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_I8_6, {
    d4_str_toI8(&d4_err_state, 0, 0, s54, 0, 0);
  }, L"value `123f` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_I8_7, {
    d4_str_toI8(&d4_err_state, 0, 0, s55, 0, 0);
  }, L"value `test` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_I8_8, {
    d4_str_toI8(&d4_err_state, 0, 0, s55, 1, 1);
  }, L"radix 1 is invalid, must be >= 2 and <= 36, or 0");

  ASSERT_THROW_WITH_MESSAGE(TO_I8_9, {
    d4_str_toI8(&d4_err_state, 0, 0, s55, 1, 40);
  }, L"radix 40 is invalid, must be >= 2 and <= 36, or 0");

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s11);
  d4_str_free(s12);
  d4_str_free(s13);
  d4_str_free(s21);
  d4_str_free(s22);
  d4_str_free(s23);
  d4_str_free(s31);
  d4_str_free(s32);
  d4_str_free(s33);
  d4_str_free(s50);
  d4_str_free(s51);
  d4_str_free(s52);
  d4_str_free(s53);
  d4_str_free(s54);
  d4_str_free(s55);
}

static void test_string_toI16 (void) {
  d4_str_t s1 = d4_str_alloc(L"0");
  d4_str_t s2 = d4_str_alloc(L"1");
  d4_str_t s3 = d4_str_alloc(L"123");
  d4_str_t s4 = d4_str_alloc(L"32767");
  d4_str_t s5 = d4_str_alloc(L"-32768");

  d4_str_t s11 = d4_str_alloc(L"0");
  d4_str_t s12 = d4_str_alloc(L"1");
  d4_str_t s13 = d4_str_alloc(L"01111011");

  d4_str_t s21 = d4_str_alloc(L"0");
  d4_str_t s22 = d4_str_alloc(L"1");
  d4_str_t s23 = d4_str_alloc(L"173");

  d4_str_t s31 = d4_str_alloc(L"0");
  d4_str_t s32 = d4_str_alloc(L"1");
  d4_str_t s33 = d4_str_alloc(L"7B");

  d4_str_t s50 = d4_str_alloc(L"32768");
  d4_str_t s51 = d4_str_alloc(L"-32769");
  d4_str_t s52 = d4_str_alloc(L"");
  d4_str_t s53 = d4_str_alloc(L" 123 ");
  d4_str_t s54 = d4_str_alloc(L"123f");
  d4_str_t s55 = d4_str_alloc(L"test");

  ASSERT_NO_THROW(TO_I16_1, {
    assert(((void) "Converts to i16 zero", d4_str_toI16(&d4_err_state, 0, 0, s1, 0, 0) == 0));
    assert(((void) "Converts to i16 single digit", d4_str_toI16(&d4_err_state, 0, 0, s2, 0, 0) == 1));
    assert(((void) "Converts to i16 multiples digits", d4_str_toI16(&d4_err_state, 0, 0, s3, 0, 0) == 123));
    assert(((void) "Converts to i16 max value", d4_str_toI16(&d4_err_state, 0, 0, s4, 0, 0) == 32767));
    assert(((void) "Converts to i16 min value", d4_str_toI16(&d4_err_state, 0, 0, s5, 0, 0) == -32768));

    assert(((void) "Converts to i16 binary zero", d4_str_toI16(&d4_err_state, 0, 0, s11, 1, 2) == 0));
    assert(((void) "Converts to i16 binary single digit", d4_str_toI16(&d4_err_state, 0, 0, s12, 1, 2) == 1));
    assert(((void) "Converts to i16 binary multiples digits", d4_str_toI16(&d4_err_state, 0, 0, s13, 1, 2) == 123));

    assert(((void) "Converts to i16 octal zero", d4_str_toI16(&d4_err_state, 0, 0, s21, 1, 8) == 0));
    assert(((void) "Converts to i16 octal single digit", d4_str_toI16(&d4_err_state, 0, 0, s22, 1, 8) == 1));
    assert(((void) "Converts to i16 octal multiples digits", d4_str_toI16(&d4_err_state, 0, 0, s23, 1, 8) == 123));

    assert(((void) "Converts to i16 hexadecimal zero", d4_str_toI16(&d4_err_state, 0, 0, s31, 1, 16) == 0));
    assert(((void) "Converts to i16 hexadecimal single digit", d4_str_toI16(&d4_err_state, 0, 0, s32, 1, 16) == 1));
    assert(((void) "Converts to i16 hexadecimal multiples digits", d4_str_toI16(&d4_err_state, 0, 0, s33, 1, 16) == 123));
  });

  ASSERT_THROW_WITH_MESSAGE(TO_I16_2, {
    d4_str_toI16(&d4_err_state, 0, 0, s50, 0, 0);
  }, L"value `32768` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_I16_3, {
    d4_str_toI16(&d4_err_state, 0, 0, s51, 0, 0);
  }, L"value `-32769` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_I16_4, {
    d4_str_toI16(&d4_err_state, 0, 0, s52, 0, 0);
  }, L"value `` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_I16_5, {
    d4_str_toI16(&d4_err_state, 0, 0, s53, 0, 0);
  }, L"value ` 123 ` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_I16_6, {
    d4_str_toI16(&d4_err_state, 0, 0, s54, 0, 0);
  }, L"value `123f` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_I16_7, {
    d4_str_toI16(&d4_err_state, 0, 0, s55, 0, 0);
  }, L"value `test` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_I16_8, {
    d4_str_toI16(&d4_err_state, 0, 0, s55, 1, 1);
  }, L"radix 1 is invalid, must be >= 2 and <= 36, or 0");

  ASSERT_THROW_WITH_MESSAGE(TO_I16_9, {
    d4_str_toI16(&d4_err_state, 0, 0, s55, 1, 40);
  }, L"radix 40 is invalid, must be >= 2 and <= 36, or 0");

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s11);
  d4_str_free(s12);
  d4_str_free(s13);
  d4_str_free(s21);
  d4_str_free(s22);
  d4_str_free(s23);
  d4_str_free(s31);
  d4_str_free(s32);
  d4_str_free(s33);
  d4_str_free(s50);
  d4_str_free(s51);
  d4_str_free(s52);
  d4_str_free(s53);
  d4_str_free(s54);
  d4_str_free(s55);
}

static void test_string_toI32 (void) {
  d4_str_t s1 = d4_str_alloc(L"0");
  d4_str_t s2 = d4_str_alloc(L"1");
  d4_str_t s3 = d4_str_alloc(L"123");
  d4_str_t s4 = d4_str_alloc(L"2147483647");
  d4_str_t s5 = d4_str_alloc(L"-2147483648");

  d4_str_t s11 = d4_str_alloc(L"0");
  d4_str_t s12 = d4_str_alloc(L"1");
  d4_str_t s13 = d4_str_alloc(L"01111011");

  d4_str_t s21 = d4_str_alloc(L"0");
  d4_str_t s22 = d4_str_alloc(L"1");
  d4_str_t s23 = d4_str_alloc(L"173");

  d4_str_t s31 = d4_str_alloc(L"0");
  d4_str_t s32 = d4_str_alloc(L"1");
  d4_str_t s33 = d4_str_alloc(L"7B");

  d4_str_t s50 = d4_str_alloc(L"2147483648");
  d4_str_t s51 = d4_str_alloc(L"-2147483649");
  d4_str_t s52 = d4_str_alloc(L"");
  d4_str_t s53 = d4_str_alloc(L" 123 ");
  d4_str_t s54 = d4_str_alloc(L"123f");
  d4_str_t s55 = d4_str_alloc(L"test");

  ASSERT_NO_THROW(TO_I32_1, {
    assert(((void) "Converts to i32 zero", d4_str_toI32(&d4_err_state, 0, 0, s1, 0, 0) == 0));
    assert(((void) "Converts to i32 single digit", d4_str_toI32(&d4_err_state, 0, 0, s2, 0, 0) == 1));
    assert(((void) "Converts to i32 multiples digits", d4_str_toI32(&d4_err_state, 0, 0, s3, 0, 0) == 123));
    assert(((void) "Converts to i32 max value", d4_str_toI32(&d4_err_state, 0, 0, s4, 0, 0) == 2147483647));
    assert(((void) "Converts to i32 min value", d4_str_toI32(&d4_err_state, 0, 0, s5, 0, 0) == -2147483648));

    assert(((void) "Converts to i32 binary zero", d4_str_toI32(&d4_err_state, 0, 0, s11, 1, 2) == 0));
    assert(((void) "Converts to i32 binary single digit", d4_str_toI32(&d4_err_state, 0, 0, s12, 1, 2) == 1));
    assert(((void) "Converts to i32 binary multiples digits", d4_str_toI32(&d4_err_state, 0, 0, s13, 1, 2) == 123));

    assert(((void) "Converts to i32 octal zero", d4_str_toI32(&d4_err_state, 0, 0, s21, 1, 8) == 0));
    assert(((void) "Converts to i32 octal single digit", d4_str_toI32(&d4_err_state, 0, 0, s22, 1, 8) == 1));
    assert(((void) "Converts to i32 octal multiples digits", d4_str_toI32(&d4_err_state, 0, 0, s23, 1, 8) == 123));

    assert(((void) "Converts to i32 hexadecimal zero", d4_str_toI32(&d4_err_state, 0, 0, s31, 1, 16) == 0));
    assert(((void) "Converts to i32 hexadecimal single digit", d4_str_toI32(&d4_err_state, 0, 0, s32, 1, 16) == 1));
    assert(((void) "Converts to i32 hexadecimal multiples digits", d4_str_toI32(&d4_err_state, 0, 0, s33, 1, 16) == 123));
  });

  ASSERT_THROW_WITH_MESSAGE(TO_I32_2, {
    d4_str_toI32(&d4_err_state, 0, 0, s50, 0, 0);
  }, L"value `2147483648` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_I32_3, {
    d4_str_toI32(&d4_err_state, 0, 0, s51, 0, 0);
  }, L"value `-2147483649` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_I32_4, {
    d4_str_toI32(&d4_err_state, 0, 0, s52, 0, 0);
  }, L"value `` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_I32_5, {
    d4_str_toI32(&d4_err_state, 0, 0, s53, 0, 0);
  }, L"value ` 123 ` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_I32_6, {
    d4_str_toI32(&d4_err_state, 0, 0, s54, 0, 0);
  }, L"value `123f` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_I32_7, {
    d4_str_toI32(&d4_err_state, 0, 0, s55, 0, 0);
  }, L"value `test` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_I32_8, {
    d4_str_toI32(&d4_err_state, 0, 0, s55, 1, 1);
  }, L"radix 1 is invalid, must be >= 2 and <= 36, or 0");

  ASSERT_THROW_WITH_MESSAGE(TO_I32_9, {
    d4_str_toI32(&d4_err_state, 0, 0, s55, 1, 40);
  }, L"radix 40 is invalid, must be >= 2 and <= 36, or 0");

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s11);
  d4_str_free(s12);
  d4_str_free(s13);
  d4_str_free(s21);
  d4_str_free(s22);
  d4_str_free(s23);
  d4_str_free(s31);
  d4_str_free(s32);
  d4_str_free(s33);
  d4_str_free(s50);
  d4_str_free(s51);
  d4_str_free(s52);
  d4_str_free(s53);
  d4_str_free(s54);
  d4_str_free(s55);
}

static void test_string_toI64 (void) {
  d4_str_t s1 = d4_str_alloc(L"0");
  d4_str_t s2 = d4_str_alloc(L"1");
  d4_str_t s3 = d4_str_alloc(L"123");
  d4_str_t s4 = d4_str_alloc(L"9223372036854775807");
  d4_str_t s5 = d4_str_alloc(L"-9223372036854775808");

  d4_str_t s11 = d4_str_alloc(L"0");
  d4_str_t s12 = d4_str_alloc(L"1");
  d4_str_t s13 = d4_str_alloc(L"01111011");

  d4_str_t s21 = d4_str_alloc(L"0");
  d4_str_t s22 = d4_str_alloc(L"1");
  d4_str_t s23 = d4_str_alloc(L"173");

  d4_str_t s31 = d4_str_alloc(L"0");
  d4_str_t s32 = d4_str_alloc(L"1");
  d4_str_t s33 = d4_str_alloc(L"7B");

  d4_str_t s50 = d4_str_alloc(L"9223372036854775808");
  d4_str_t s51 = d4_str_alloc(L"-9223372036854775809");
  d4_str_t s52 = d4_str_alloc(L"");
  d4_str_t s53 = d4_str_alloc(L" 123 ");
  d4_str_t s54 = d4_str_alloc(L"123f");
  d4_str_t s55 = d4_str_alloc(L"test");

  ASSERT_NO_THROW(TO_I64_1, {
    assert(((void) "Converts to i64 zero", d4_str_toI64(&d4_err_state, 0, 0, s1, 0, 0) == 0));
    assert(((void) "Converts to i64 single digit", d4_str_toI64(&d4_err_state, 0, 0, s2, 0, 0) == 1));
    assert(((void) "Converts to i64 multiples digits", d4_str_toI64(&d4_err_state, 0, 0, s3, 0, 0) == 123));
    assert(((void) "Converts to i64 max value", d4_str_toI64(&d4_err_state, 0, 0, s4, 0, 0) == 9223372036854775807));
    assert(((void) "Converts to i64 min value", d4_str_toI64(&d4_err_state, 0, 0, s5, 0, 0) == (int64_t) (-9223372036854775808U)));

    assert(((void) "Converts to i64 binary zero", d4_str_toI64(&d4_err_state, 0, 0, s11, 1, 2) == 0));
    assert(((void) "Converts to i64 binary single digit", d4_str_toI64(&d4_err_state, 0, 0, s12, 1, 2) == 1));
    assert(((void) "Converts to i64 binary multiples digits", d4_str_toI64(&d4_err_state, 0, 0, s13, 1, 2) == 123));

    assert(((void) "Converts to i64 octal zero", d4_str_toI64(&d4_err_state, 0, 0, s21, 1, 8) == 0));
    assert(((void) "Converts to i64 octal single digit", d4_str_toI64(&d4_err_state, 0, 0, s22, 1, 8) == 1));
    assert(((void) "Converts to i64 octal multiples digits", d4_str_toI64(&d4_err_state, 0, 0, s23, 1, 8) == 123));

    assert(((void) "Converts to i64 hexadecimal zero", d4_str_toI64(&d4_err_state, 0, 0, s31, 1, 16) == 0));
    assert(((void) "Converts to i64 hexadecimal single digit", d4_str_toI64(&d4_err_state, 0, 0, s32, 1, 16) == 1));
    assert(((void) "Converts to i64 hexadecimal multiples digits", d4_str_toI64(&d4_err_state, 0, 0, s33, 1, 16) == 123));
  });

  ASSERT_THROW_WITH_MESSAGE(TO_I64_2, {
    d4_str_toI64(&d4_err_state, 0, 0, s50, 0, 0);
  }, L"value `9223372036854775808` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_I64_3, {
    d4_str_toI64(&d4_err_state, 0, 0, s51, 0, 0);
  }, L"value `-9223372036854775809` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_I64_4, {
    d4_str_toI64(&d4_err_state, 0, 0, s52, 0, 0);
  }, L"value `` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_I64_5, {
    d4_str_toI64(&d4_err_state, 0, 0, s53, 0, 0);
  }, L"value ` 123 ` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_I64_6, {
    d4_str_toI64(&d4_err_state, 0, 0, s54, 0, 0);
  }, L"value `123f` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_I64_7, {
    d4_str_toI64(&d4_err_state, 0, 0, s55, 0, 0);
  }, L"value `test` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_I64_8, {
    d4_str_toI64(&d4_err_state, 0, 0, s55, 1, 1);
  }, L"radix 1 is invalid, must be >= 2 and <= 36, or 0");

  ASSERT_THROW_WITH_MESSAGE(TO_I64_9, {
    d4_str_toI64(&d4_err_state, 0, 0, s55, 1, 40);
  }, L"radix 40 is invalid, must be >= 2 and <= 36, or 0");

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s5);
  d4_str_free(s11);
  d4_str_free(s12);
  d4_str_free(s13);
  d4_str_free(s21);
  d4_str_free(s22);
  d4_str_free(s23);
  d4_str_free(s31);
  d4_str_free(s32);
  d4_str_free(s33);
  d4_str_free(s50);
  d4_str_free(s51);
  d4_str_free(s52);
  d4_str_free(s53);
  d4_str_free(s54);
  d4_str_free(s55);
}

static void test_string_toUsize (void) {
  d4_str_t s1 = d4_str_alloc(L"0");
  d4_str_t s2 = d4_str_alloc(L"1");
  d4_str_t s3 = d4_str_alloc(L"123");
  d4_str_t s4 = d4_str_alloc(L"18446744073709551615");

  d4_str_t s11 = d4_str_alloc(L"0");
  d4_str_t s12 = d4_str_alloc(L"1");
  d4_str_t s13 = d4_str_alloc(L"01111011");

  d4_str_t s21 = d4_str_alloc(L"0");
  d4_str_t s22 = d4_str_alloc(L"1");
  d4_str_t s23 = d4_str_alloc(L"173");

  d4_str_t s31 = d4_str_alloc(L"0");
  d4_str_t s32 = d4_str_alloc(L"1");
  d4_str_t s33 = d4_str_alloc(L"7B");

  d4_str_t s50 = d4_str_alloc(L"20446744073709551615");
  d4_str_t s51 = d4_str_alloc(L"-1");
  d4_str_t s52 = d4_str_alloc(L"");
  d4_str_t s53 = d4_str_alloc(L" 123 ");
  d4_str_t s54 = d4_str_alloc(L"123f");
  d4_str_t s55 = d4_str_alloc(L"test");

  ASSERT_NO_THROW(TO_USIZE1, {
    assert(((void) "Converts to usize zero", d4_str_toUsize(&d4_err_state, 0, 0, s1, 0, 0) == 0));
    assert(((void) "Converts to usize single digit", d4_str_toUsize(&d4_err_state, 0, 0, s2, 0, 0) == 1));
    assert(((void) "Converts to usize multiples digits", d4_str_toUsize(&d4_err_state, 0, 0, s3, 0, 0) == 123));
    assert(((void) "Converts to usize max value", d4_str_toUsize(&d4_err_state, 0, 0, s4, 0, 0) == 18446744073709551615U));

    assert(((void) "Converts to usize binary zero", d4_str_toUsize(&d4_err_state, 0, 0, s11, 1, 2) == 0));
    assert(((void) "Converts to usize binary single digit", d4_str_toUsize(&d4_err_state, 0, 0, s12, 1, 2) == 1));
    assert(((void) "Converts to usize binary multiples digits", d4_str_toUsize(&d4_err_state, 0, 0, s13, 1, 2) == 123));

    assert(((void) "Converts to usize octal zero", d4_str_toUsize(&d4_err_state, 0, 0, s21, 1, 8) == 0));
    assert(((void) "Converts to usize octal single digit", d4_str_toUsize(&d4_err_state, 0, 0, s22, 1, 8) == 1));
    assert(((void) "Converts to usize octal multiples digits", d4_str_toUsize(&d4_err_state, 0, 0, s23, 1, 8) == 123));

    assert(((void) "Converts to usize hexadecimal zero", d4_str_toUsize(&d4_err_state, 0, 0, s31, 1, 16) == 0));
    assert(((void) "Converts to usize hexadecimal single digit", d4_str_toUsize(&d4_err_state, 0, 0, s32, 1, 16) == 1));
    assert(((void) "Converts to usize hexadecimal multiples digits", d4_str_toUsize(&d4_err_state, 0, 0, s33, 1, 16) == 123));
  });

  ASSERT_THROW_WITH_MESSAGE(TO_USIZE2, {
    d4_str_toUsize(&d4_err_state, 0, 0, s50, 0, 0);
  }, L"value `20446744073709551615` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_USIZE3, {
    d4_str_toUsize(&d4_err_state, 0, 0, s51, 0, 0);
  }, L"value `-1` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_USIZE4, {
    d4_str_toUsize(&d4_err_state, 0, 0, s52, 0, 0);
  }, L"value `` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_USIZE5, {
    d4_str_toUsize(&d4_err_state, 0, 0, s53, 0, 0);
  }, L"value ` 123 ` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_USIZE6, {
    d4_str_toUsize(&d4_err_state, 0, 0, s54, 0, 0);
  }, L"value `123f` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_USIZE7, {
    d4_str_toUsize(&d4_err_state, 0, 0, s55, 0, 0);
  }, L"value `test` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_USIZE8, {
    d4_str_toUsize(&d4_err_state, 0, 0, s55, 1, 1);
  }, L"radix 1 is invalid, must be >= 2 and <= 36, or 0");

  ASSERT_THROW_WITH_MESSAGE(TO_USIZE9, {
    d4_str_toUsize(&d4_err_state, 0, 0, s55, 1, 40);
  }, L"radix 40 is invalid, must be >= 2 and <= 36, or 0");

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s11);
  d4_str_free(s12);
  d4_str_free(s13);
  d4_str_free(s21);
  d4_str_free(s22);
  d4_str_free(s23);
  d4_str_free(s31);
  d4_str_free(s32);
  d4_str_free(s33);
  d4_str_free(s50);
  d4_str_free(s51);
  d4_str_free(s52);
  d4_str_free(s53);
  d4_str_free(s54);
  d4_str_free(s55);
}

static void test_string_toU8 (void) {
  d4_str_t s1 = d4_str_alloc(L"0");
  d4_str_t s2 = d4_str_alloc(L"1");
  d4_str_t s3 = d4_str_alloc(L"123");
  d4_str_t s4 = d4_str_alloc(L"255");

  d4_str_t s11 = d4_str_alloc(L"0");
  d4_str_t s12 = d4_str_alloc(L"1");
  d4_str_t s13 = d4_str_alloc(L"01111011");

  d4_str_t s21 = d4_str_alloc(L"0");
  d4_str_t s22 = d4_str_alloc(L"1");
  d4_str_t s23 = d4_str_alloc(L"173");

  d4_str_t s31 = d4_str_alloc(L"0");
  d4_str_t s32 = d4_str_alloc(L"1");
  d4_str_t s33 = d4_str_alloc(L"7B");

  d4_str_t s50 = d4_str_alloc(L"256");
  d4_str_t s51 = d4_str_alloc(L"-1");
  d4_str_t s52 = d4_str_alloc(L"");
  d4_str_t s53 = d4_str_alloc(L" 123 ");
  d4_str_t s54 = d4_str_alloc(L"123f");
  d4_str_t s55 = d4_str_alloc(L"test");

  ASSERT_NO_THROW(TO_U8_1, {
    assert(((void) "Converts to u8 zero", d4_str_toU8(&d4_err_state, 0, 0, s1, 0, 0) == 0));
    assert(((void) "Converts to u8 single digit", d4_str_toU8(&d4_err_state, 0, 0, s2, 0, 0) == 1));
    assert(((void) "Converts to u8 multiples digits", d4_str_toU8(&d4_err_state, 0, 0, s3, 0, 0) == 123));
    assert(((void) "Converts to u8 max value", d4_str_toU8(&d4_err_state, 0, 0, s4, 0, 0) == 255));

    assert(((void) "Converts to u8 binary zero", d4_str_toU8(&d4_err_state, 0, 0, s11, 1, 2) == 0));
    assert(((void) "Converts to u8 binary single digit", d4_str_toU8(&d4_err_state, 0, 0, s12, 1, 2) == 1));
    assert(((void) "Converts to u8 binary multiples digits", d4_str_toU8(&d4_err_state, 0, 0, s13, 1, 2) == 123));

    assert(((void) "Converts to u8 octal zero", d4_str_toU8(&d4_err_state, 0, 0, s21, 1, 8) == 0));
    assert(((void) "Converts to u8 octal single digit", d4_str_toU8(&d4_err_state, 0, 0, s22, 1, 8) == 1));
    assert(((void) "Converts to u8 octal multiples digits", d4_str_toU8(&d4_err_state, 0, 0, s23, 1, 8) == 123));

    assert(((void) "Converts to u8 hexadecimal zero", d4_str_toU8(&d4_err_state, 0, 0, s31, 1, 16) == 0));
    assert(((void) "Converts to u8 hexadecimal single digit", d4_str_toU8(&d4_err_state, 0, 0, s32, 1, 16) == 1));
    assert(((void) "Converts to u8 hexadecimal multiples digits", d4_str_toU8(&d4_err_state, 0, 0, s33, 1, 16) == 123));
  });

  ASSERT_THROW_WITH_MESSAGE(TO_U8_2, {
    d4_str_toU8(&d4_err_state, 0, 0, s50, 0, 0);
  }, L"value `256` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_U8_3, {
    d4_str_toU8(&d4_err_state, 0, 0, s51, 0, 0);
  }, L"value `-1` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_U8_4, {
    d4_str_toU8(&d4_err_state, 0, 0, s52, 0, 0);
  }, L"value `` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_U8_5, {
    d4_str_toU8(&d4_err_state, 0, 0, s53, 0, 0);
  }, L"value ` 123 ` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_U8_6, {
    d4_str_toU8(&d4_err_state, 0, 0, s54, 0, 0);
  }, L"value `123f` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_U8_7, {
    d4_str_toU8(&d4_err_state, 0, 0, s55, 0, 0);
  }, L"value `test` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_U8_8, {
    d4_str_toU8(&d4_err_state, 0, 0, s55, 1, 1);
  }, L"radix 1 is invalid, must be >= 2 and <= 36, or 0");

  ASSERT_THROW_WITH_MESSAGE(TO_U8_9, {
    d4_str_toU8(&d4_err_state, 0, 0, s55, 1, 40);
  }, L"radix 40 is invalid, must be >= 2 and <= 36, or 0");

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s11);
  d4_str_free(s12);
  d4_str_free(s13);
  d4_str_free(s21);
  d4_str_free(s22);
  d4_str_free(s23);
  d4_str_free(s31);
  d4_str_free(s32);
  d4_str_free(s33);
  d4_str_free(s50);
  d4_str_free(s51);
  d4_str_free(s52);
  d4_str_free(s53);
  d4_str_free(s54);
  d4_str_free(s55);
}

static void test_string_toU16 (void) {
  d4_str_t s1 = d4_str_alloc(L"0");
  d4_str_t s2 = d4_str_alloc(L"1");
  d4_str_t s3 = d4_str_alloc(L"123");
  d4_str_t s4 = d4_str_alloc(L"65535");

  d4_str_t s11 = d4_str_alloc(L"0");
  d4_str_t s12 = d4_str_alloc(L"1");
  d4_str_t s13 = d4_str_alloc(L"01111011");

  d4_str_t s21 = d4_str_alloc(L"0");
  d4_str_t s22 = d4_str_alloc(L"1");
  d4_str_t s23 = d4_str_alloc(L"173");

  d4_str_t s31 = d4_str_alloc(L"0");
  d4_str_t s32 = d4_str_alloc(L"1");
  d4_str_t s33 = d4_str_alloc(L"7B");

  d4_str_t s50 = d4_str_alloc(L"65536");
  d4_str_t s51 = d4_str_alloc(L"-1");
  d4_str_t s52 = d4_str_alloc(L"");
  d4_str_t s53 = d4_str_alloc(L" 123 ");
  d4_str_t s54 = d4_str_alloc(L"123f");
  d4_str_t s55 = d4_str_alloc(L"test");

  ASSERT_NO_THROW(TO_U16_1, {
    assert(((void) "Converts to u16 zero", d4_str_toU16(&d4_err_state, 0, 0, s1, 0, 0) == 0));
    assert(((void) "Converts to u16 single digit", d4_str_toU16(&d4_err_state, 0, 0, s2, 0, 0) == 1));
    assert(((void) "Converts to u16 multiples digits", d4_str_toU16(&d4_err_state, 0, 0, s3, 0, 0) == 123));
    assert(((void) "Converts to u16 max value", d4_str_toU16(&d4_err_state, 0, 0, s4, 0, 0) == 65535));

    assert(((void) "Converts to u16 binary zero", d4_str_toU16(&d4_err_state, 0, 0, s11, 1, 2) == 0));
    assert(((void) "Converts to u16 binary single digit", d4_str_toU16(&d4_err_state, 0, 0, s12, 1, 2) == 1));
    assert(((void) "Converts to u16 binary multiples digits", d4_str_toU16(&d4_err_state, 0, 0, s13, 1, 2) == 123));

    assert(((void) "Converts to u16 octal zero", d4_str_toU16(&d4_err_state, 0, 0, s21, 1, 8) == 0));
    assert(((void) "Converts to u16 octal single digit", d4_str_toU16(&d4_err_state, 0, 0, s22, 1, 8) == 1));
    assert(((void) "Converts to u16 octal multiples digits", d4_str_toU16(&d4_err_state, 0, 0, s23, 1, 8) == 123));

    assert(((void) "Converts to u16 hexadecimal zero", d4_str_toU16(&d4_err_state, 0, 0, s31, 1, 16) == 0));
    assert(((void) "Converts to u16 hexadecimal single digit", d4_str_toU16(&d4_err_state, 0, 0, s32, 1, 16) == 1));
    assert(((void) "Converts to u16 hexadecimal multiples digits", d4_str_toU16(&d4_err_state, 0, 0, s33, 1, 16) == 123));
  });

  ASSERT_THROW_WITH_MESSAGE(TO_U16_2, {
    d4_str_toU16(&d4_err_state, 0, 0, s50, 0, 0);
  }, L"value `65536` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_U16_3, {
    d4_str_toU16(&d4_err_state, 0, 0, s51, 0, 0);
  }, L"value `-1` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_U16_4, {
    d4_str_toU16(&d4_err_state, 0, 0, s52, 0, 0);
  }, L"value `` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_U16_5, {
    d4_str_toU16(&d4_err_state, 0, 0, s53, 0, 0);
  }, L"value ` 123 ` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_U16_6, {
    d4_str_toU16(&d4_err_state, 0, 0, s54, 0, 0);
  }, L"value `123f` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_U16_7, {
    d4_str_toU16(&d4_err_state, 0, 0, s55, 0, 0);
  }, L"value `test` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_U16_8, {
    d4_str_toU16(&d4_err_state, 0, 0, s55, 1, 1);
  }, L"radix 1 is invalid, must be >= 2 and <= 36, or 0");

  ASSERT_THROW_WITH_MESSAGE(TO_U16_9, {
    d4_str_toU16(&d4_err_state, 0, 0, s55, 1, 40);
  }, L"radix 40 is invalid, must be >= 2 and <= 36, or 0");

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s11);
  d4_str_free(s12);
  d4_str_free(s13);
  d4_str_free(s21);
  d4_str_free(s22);
  d4_str_free(s23);
  d4_str_free(s31);
  d4_str_free(s32);
  d4_str_free(s33);
  d4_str_free(s50);
  d4_str_free(s51);
  d4_str_free(s52);
  d4_str_free(s53);
  d4_str_free(s54);
  d4_str_free(s55);
}

static void test_string_toU32 (void) {
  d4_str_t s1 = d4_str_alloc(L"0");
  d4_str_t s2 = d4_str_alloc(L"1");
  d4_str_t s3 = d4_str_alloc(L"123");
  d4_str_t s4 = d4_str_alloc(L"4294967295");

  d4_str_t s11 = d4_str_alloc(L"0");
  d4_str_t s12 = d4_str_alloc(L"1");
  d4_str_t s13 = d4_str_alloc(L"01111011");

  d4_str_t s21 = d4_str_alloc(L"0");
  d4_str_t s22 = d4_str_alloc(L"1");
  d4_str_t s23 = d4_str_alloc(L"173");

  d4_str_t s31 = d4_str_alloc(L"0");
  d4_str_t s32 = d4_str_alloc(L"1");
  d4_str_t s33 = d4_str_alloc(L"7B");

  d4_str_t s50 = d4_str_alloc(L"4294967296");
  d4_str_t s51 = d4_str_alloc(L"-1");
  d4_str_t s52 = d4_str_alloc(L"");
  d4_str_t s53 = d4_str_alloc(L" 123 ");
  d4_str_t s54 = d4_str_alloc(L"123f");
  d4_str_t s55 = d4_str_alloc(L"test");

  ASSERT_NO_THROW(TO_U32_1, {
    assert(((void) "Converts to u32 zero", d4_str_toU32(&d4_err_state, 0, 0, s1, 0, 0) == 0));
    assert(((void) "Converts to u32 single digit", d4_str_toU32(&d4_err_state, 0, 0, s2, 0, 0) == 1));
    assert(((void) "Converts to u32 multiples digits", d4_str_toU32(&d4_err_state, 0, 0, s3, 0, 0) == 123));
    assert(((void) "Converts to u32 max value", d4_str_toU32(&d4_err_state, 0, 0, s4, 0, 0) == 4294967295));

    assert(((void) "Converts to u32 binary zero", d4_str_toU32(&d4_err_state, 0, 0, s11, 1, 2) == 0));
    assert(((void) "Converts to u32 binary single digit", d4_str_toU32(&d4_err_state, 0, 0, s12, 1, 2) == 1));
    assert(((void) "Converts to u32 binary multiples digits", d4_str_toU32(&d4_err_state, 0, 0, s13, 1, 2) == 123));

    assert(((void) "Converts to u32 octal zero", d4_str_toU32(&d4_err_state, 0, 0, s21, 1, 8) == 0));
    assert(((void) "Converts to u32 octal single digit", d4_str_toU32(&d4_err_state, 0, 0, s22, 1, 8) == 1));
    assert(((void) "Converts to u32 octal multiples digits", d4_str_toU32(&d4_err_state, 0, 0, s23, 1, 8) == 123));

    assert(((void) "Converts to u32 hexadecimal zero", d4_str_toU32(&d4_err_state, 0, 0, s31, 1, 16) == 0));
    assert(((void) "Converts to u32 hexadecimal single digit", d4_str_toU32(&d4_err_state, 0, 0, s32, 1, 16) == 1));
    assert(((void) "Converts to u32 hexadecimal multiples digits", d4_str_toU32(&d4_err_state, 0, 0, s33, 1, 16) == 123));
  });

  ASSERT_THROW_WITH_MESSAGE(TO_U32_2, {
    d4_str_toU32(&d4_err_state, 0, 0, s50, 0, 0);
  }, L"value `4294967296` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_U32_3, {
    d4_str_toU32(&d4_err_state, 0, 0, s51, 0, 0);
  }, L"value `-1` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_U32_4, {
    d4_str_toU32(&d4_err_state, 0, 0, s52, 0, 0);
  }, L"value `` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_U32_5, {
    d4_str_toU32(&d4_err_state, 0, 0, s53, 0, 0);
  }, L"value ` 123 ` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_U32_6, {
    d4_str_toU32(&d4_err_state, 0, 0, s54, 0, 0);
  }, L"value `123f` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_U32_7, {
    d4_str_toU32(&d4_err_state, 0, 0, s55, 0, 0);
  }, L"value `test` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_U32_8, {
    d4_str_toU32(&d4_err_state, 0, 0, s55, 1, 1);
  }, L"radix 1 is invalid, must be >= 2 and <= 36, or 0");

  ASSERT_THROW_WITH_MESSAGE(TO_U32_9, {
    d4_str_toU32(&d4_err_state, 0, 0, s55, 1, 40);
  }, L"radix 40 is invalid, must be >= 2 and <= 36, or 0");

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s11);
  d4_str_free(s12);
  d4_str_free(s13);
  d4_str_free(s21);
  d4_str_free(s22);
  d4_str_free(s23);
  d4_str_free(s31);
  d4_str_free(s32);
  d4_str_free(s33);
  d4_str_free(s50);
  d4_str_free(s51);
  d4_str_free(s52);
  d4_str_free(s53);
  d4_str_free(s54);
  d4_str_free(s55);
}

static void test_string_toU64 (void) {
  d4_str_t s1 = d4_str_alloc(L"0");
  d4_str_t s2 = d4_str_alloc(L"1");
  d4_str_t s3 = d4_str_alloc(L"123");
  d4_str_t s4 = d4_str_alloc(L"18446744073709551615");

  d4_str_t s11 = d4_str_alloc(L"0");
  d4_str_t s12 = d4_str_alloc(L"1");
  d4_str_t s13 = d4_str_alloc(L"01111011");

  d4_str_t s21 = d4_str_alloc(L"0");
  d4_str_t s22 = d4_str_alloc(L"1");
  d4_str_t s23 = d4_str_alloc(L"173");

  d4_str_t s31 = d4_str_alloc(L"0");
  d4_str_t s32 = d4_str_alloc(L"1");
  d4_str_t s33 = d4_str_alloc(L"7B");

  d4_str_t s50 = d4_str_alloc(L"18446744073709551616");
  d4_str_t s51 = d4_str_alloc(L"-1");
  d4_str_t s52 = d4_str_alloc(L"");
  d4_str_t s53 = d4_str_alloc(L" 123 ");
  d4_str_t s54 = d4_str_alloc(L"123f");
  d4_str_t s55 = d4_str_alloc(L"test");

  ASSERT_NO_THROW(TO_U64_1, {
    assert(((void) "Converts to u64 zero", d4_str_toU64(&d4_err_state, 0, 0, s1, 0, 0) == 0));
    assert(((void) "Converts to u64 single digit", d4_str_toU64(&d4_err_state, 0, 0, s2, 0, 0) == 1));
    assert(((void) "Converts to u64 multiples digits", d4_str_toU64(&d4_err_state, 0, 0, s3, 0, 0) == 123));
    assert(((void) "Converts to u64 max value", d4_str_toU64(&d4_err_state, 0, 0, s4, 0, 0) == 18446744073709551615U));

    assert(((void) "Converts to u64 binary zero", d4_str_toU64(&d4_err_state, 0, 0, s11, 1, 2) == 0));
    assert(((void) "Converts to u64 binary single digit", d4_str_toU64(&d4_err_state, 0, 0, s12, 1, 2) == 1));
    assert(((void) "Converts to u64 binary multiples digits", d4_str_toU64(&d4_err_state, 0, 0, s13, 1, 2) == 123));

    assert(((void) "Converts to u64 octal zero", d4_str_toU64(&d4_err_state, 0, 0, s21, 1, 8) == 0));
    assert(((void) "Converts to u64 octal single digit", d4_str_toU64(&d4_err_state, 0, 0, s22, 1, 8) == 1));
    assert(((void) "Converts to u64 octal multiples digits", d4_str_toU64(&d4_err_state, 0, 0, s23, 1, 8) == 123));

    assert(((void) "Converts to u64 hexadecimal zero", d4_str_toU64(&d4_err_state, 0, 0, s31, 1, 16) == 0));
    assert(((void) "Converts to u64 hexadecimal single digit", d4_str_toU64(&d4_err_state, 0, 0, s32, 1, 16) == 1));
    assert(((void) "Converts to u64 hexadecimal multiples digits", d4_str_toU64(&d4_err_state, 0, 0, s33, 1, 16) == 123));
  });

  ASSERT_THROW_WITH_MESSAGE(TO_U64_2, {
    d4_str_toU64(&d4_err_state, 0, 0, s50, 0, 0);
  }, L"value `18446744073709551616` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_U64_3, {
    d4_str_toU64(&d4_err_state, 0, 0, s51, 0, 0);
  }, L"value `-1` out of range");

  ASSERT_THROW_WITH_MESSAGE(TO_U64_4, {
    d4_str_toU64(&d4_err_state, 0, 0, s52, 0, 0);
  }, L"value `` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_U64_5, {
    d4_str_toU64(&d4_err_state, 0, 0, s53, 0, 0);
  }, L"value ` 123 ` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_U64_6, {
    d4_str_toU64(&d4_err_state, 0, 0, s54, 0, 0);
  }, L"value `123f` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_U64_7, {
    d4_str_toU64(&d4_err_state, 0, 0, s55, 0, 0);
  }, L"value `test` has invalid syntax");

  ASSERT_THROW_WITH_MESSAGE(TO_U64_8, {
    d4_str_toU64(&d4_err_state, 0, 0, s55, 1, 1);
  }, L"radix 1 is invalid, must be >= 2 and <= 36, or 0");

  ASSERT_THROW_WITH_MESSAGE(TO_U64_9, {
    d4_str_toU64(&d4_err_state, 0, 0, s55, 1, 40);
  }, L"radix 40 is invalid, must be >= 2 and <= 36, or 0");

  d4_str_free(s1);
  d4_str_free(s2);
  d4_str_free(s3);
  d4_str_free(s4);
  d4_str_free(s11);
  d4_str_free(s12);
  d4_str_free(s13);
  d4_str_free(s21);
  d4_str_free(s22);
  d4_str_free(s23);
  d4_str_free(s31);
  d4_str_free(s32);
  d4_str_free(s33);
  d4_str_free(s50);
  d4_str_free(s51);
  d4_str_free(s52);
  d4_str_free(s53);
  d4_str_free(s54);
  d4_str_free(s55);
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
  d4_str_t s14 = d4_str_alloc(L"\n\n\n");

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
  d4_str_t r14 = d4_str_trim(s14);

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
  assert(((void) "Trims only whitespaces string", d4_str_eq(r14, r_empty)));

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
  d4_str_free(s14);

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
  d4_str_t s14 = d4_str_alloc(L"\n\n\n");

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
  d4_str_t r14 = d4_str_trimEnd(s14);

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
  d4_str_t r14_cmp = d4_str_alloc(L"");

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
  assert(((void) "Trims end of only whitespaces string", d4_str_eq(r14, r14_cmp)));

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
  d4_str_free(r14_cmp);

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
  d4_str_t s14 = d4_str_alloc(L"\n\n\n");

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
  d4_str_t r14 = d4_str_trimStart(s14);

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
  d4_str_t r14_cmp = d4_str_alloc(L"");

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
  assert(((void) "Trims start of only whitespaces string", d4_str_eq(r14, r14_cmp)));

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
  d4_str_free(r14_cmp);

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
  test_string_snwprintf_vsnwprintf();
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
