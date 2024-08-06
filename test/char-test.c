/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <assert.h>
#include "../src/char.h"
#include "../src/string.h"

static void test_char_byte (void) {
  assert(((void) "Generates byte of 'a'", d4_char_byte('a') == 0x61));
  assert(((void) "Generates byte of '0'", d4_char_byte('0') == 0x30));
}

static void test_char_isDigit (void) {
  assert(((void) "Checks 'A'", !d4_char_isDigit('A')));
  assert(((void) "Checks 'a'", !d4_char_isDigit('a')));
  assert(((void) "Checks '@'", !d4_char_isDigit('@')));
  assert(((void) "Checks '0'", d4_char_isDigit('0')));
  assert(((void) "Checks '9'", d4_char_isDigit('9')));
}

static void test_char_isLetter (void) {
  assert(((void) "Checks 'A'", d4_char_isLetter('A')));
  assert(((void) "Checks 'a'", d4_char_isLetter('a')));
  assert(((void) "Checks '@'", !d4_char_isLetter('@')));
  assert(((void) "Checks '0'", !d4_char_isLetter('0')));
  assert(((void) "Checks '9'", !d4_char_isLetter('9')));
}

static void test_char_isLetterOrDigit (void) {
  assert(((void) "Checks 'A'", d4_char_isLetterOrDigit('A')));
  assert(((void) "Checks 'a'", d4_char_isLetterOrDigit('a')));
  assert(((void) "Checks '@'", !d4_char_isLetterOrDigit('@')));
  assert(((void) "Checks '0'", d4_char_isLetterOrDigit('0')));
  assert(((void) "Checks '9'", d4_char_isLetterOrDigit('9')));
}

static void test_char_isLower (void) {
  assert(((void) "Checks 'A'", !d4_char_isLower('A')));
  assert(((void) "Checks 'a'", d4_char_isLower('a')));
  assert(((void) "Checks '@'", !d4_char_isLower('@')));
  assert(((void) "Checks '0'", !d4_char_isLower('0')));
  assert(((void) "Checks '9'", !d4_char_isLower('9')));
}

static void test_char_isUpper (void) {
  assert(((void) "Checks 'A'", d4_char_isUpper('A')));
  assert(((void) "Checks 'a'", !d4_char_isUpper('a')));
  assert(((void) "Checks '@'", !d4_char_isUpper('@')));
  assert(((void) "Checks '0'", !d4_char_isUpper('0')));
  assert(((void) "Checks '9'", !d4_char_isUpper('9')));
}

static void test_char_isWhitespace (void) {
  assert(((void) "Checks 'A'", !d4_char_isWhitespace('A')));
  assert(((void) "Checks 'a'", !d4_char_isWhitespace('a')));
  assert(((void) "Checks '@'", !d4_char_isWhitespace('@')));
  assert(((void) "Checks '0'", !d4_char_isWhitespace('0')));
  assert(((void) "Checks '9'", !d4_char_isWhitespace('9')));
}

static void test_char_lower (void) {
  assert(((void) "Transforms into lowercase 'A'", d4_char_lower('A') == 'a'));
  assert(((void) "Transforms into lowercase 'a'", d4_char_lower('a') == 'a'));
  assert(((void) "Transforms into lowercase '@'", d4_char_lower('@') == '@'));
  assert(((void) "Transforms into lowercase '0'", d4_char_lower('0') == '0'));
  assert(((void) "Transforms into lowercase '9'", d4_char_lower('9') == '9'));
}

static void test_char_repeat (void) {
  d4_str_t a1 = d4_char_repeat('a', 0);
  d4_str_t a2 = d4_char_repeat('a', 1);
  d4_str_t a3 = d4_char_repeat('a', 2);
  d4_str_t a4 = d4_char_repeat('a', 10);

  d4_str_t s1_cmp = d4_str_empty_val;
  d4_str_t s2_cmp = d4_str_alloc(L"a");
  d4_str_t s3_cmp = d4_str_alloc(L"aa");
  d4_str_t s4_cmp = d4_str_alloc(L"aaaaaaaaaa");

  assert(((void) "Repeat 'a' times 0", d4_str_eq(a1, s1_cmp)));
  assert(((void) "Repeat 'a' times 1", d4_str_eq(a2, s2_cmp)));
  assert(((void) "Repeat 'a' times 2", d4_str_eq(a3, s3_cmp)));
  assert(((void) "Repeat 'a' times 10", d4_str_eq(a4, s4_cmp)));

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);
  d4_str_free(s3_cmp);
  d4_str_free(s4_cmp);

  d4_str_free(a1);
  d4_str_free(a2);
  d4_str_free(a3);
  d4_str_free(a4);
}

static void test_char_str (void) {
  d4_str_t a1 = d4_char_str('A');
  d4_str_t a2 = d4_char_str('9');

  d4_str_t s1_cmp = d4_str_alloc(L"A");
  d4_str_t s2_cmp = d4_str_alloc(L"9");

  assert(((void) "Stringifies 'A'", d4_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies '9'", d4_str_eq(a2, s2_cmp)));

  d4_str_free(s1_cmp);
  d4_str_free(s2_cmp);

  d4_str_free(a1);
  d4_str_free(a2);
}

static void test_char_upper (void) {
  assert(((void) "Transforms into uppercase 'A'", d4_char_upper('A') == 'A'));
  assert(((void) "Transforms into uppercase 'a'", d4_char_upper('a') == 'A'));
  assert(((void) "Transforms into uppercase '@'", d4_char_upper('@') == '@'));
  assert(((void) "Transforms into uppercase '0'", d4_char_upper('0') == '0'));
  assert(((void) "Transforms into uppercase '9'", d4_char_upper('9') == '9'));
}

int main (void) {
  test_char_byte();
  test_char_isDigit();
  test_char_isLetter();
  test_char_isLetterOrDigit();
  test_char_isLower();
  test_char_isUpper();
  test_char_isWhitespace();
  test_char_lower();
  test_char_repeat();
  test_char_str();
  test_char_upper();
}
