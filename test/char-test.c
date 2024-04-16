/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <assert.h>
#include "../src/char.h"
#include "../src/string.h"

static void test_char_byte (void) {
  assert(((void) "Generates byte of 'a'", the_char_byte('a') == 0x61));
  assert(((void) "Generates byte of '0'", the_char_byte('0') == 0x30));
}

static void test_char_isDigit (void) {
  assert(((void) "Checks 'A'", !the_char_isDigit('A')));
  assert(((void) "Checks 'a'", !the_char_isDigit('a')));
  assert(((void) "Checks '@'", !the_char_isDigit('@')));
  assert(((void) "Checks '0'", the_char_isDigit('0')));
  assert(((void) "Checks '9'", the_char_isDigit('9')));
}

static void test_char_isLetter (void) {
  assert(((void) "Checks 'A'", the_char_isLetter('A')));
  assert(((void) "Checks 'a'", the_char_isLetter('a')));
  assert(((void) "Checks '@'", !the_char_isLetter('@')));
  assert(((void) "Checks '0'", !the_char_isLetter('0')));
  assert(((void) "Checks '9'", !the_char_isLetter('9')));
}

static void test_char_isLetterOrDigit (void) {
  assert(((void) "Checks 'A'", the_char_isLetterOrDigit('A')));
  assert(((void) "Checks 'a'", the_char_isLetterOrDigit('a')));
  assert(((void) "Checks '@'", !the_char_isLetterOrDigit('@')));
  assert(((void) "Checks '0'", the_char_isLetterOrDigit('0')));
  assert(((void) "Checks '9'", the_char_isLetterOrDigit('9')));
}

static void test_char_isLower (void) {
  assert(((void) "Checks 'A'", !the_char_isLower('A')));
  assert(((void) "Checks 'a'", the_char_isLower('a')));
  assert(((void) "Checks '@'", !the_char_isLower('@')));
  assert(((void) "Checks '0'", !the_char_isLower('0')));
  assert(((void) "Checks '9'", !the_char_isLower('9')));
}

static void test_char_isUpper (void) {
  assert(((void) "Checks 'A'", the_char_isUpper('A')));
  assert(((void) "Checks 'a'", !the_char_isUpper('a')));
  assert(((void) "Checks '@'", !the_char_isUpper('@')));
  assert(((void) "Checks '0'", !the_char_isUpper('0')));
  assert(((void) "Checks '9'", !the_char_isUpper('9')));
}

static void test_char_isWhitespace (void) {
  assert(((void) "Checks 'A'", !the_char_isWhitespace('A')));
  assert(((void) "Checks 'a'", !the_char_isWhitespace('a')));
  assert(((void) "Checks '@'", !the_char_isWhitespace('@')));
  assert(((void) "Checks '0'", !the_char_isWhitespace('0')));
  assert(((void) "Checks '9'", !the_char_isWhitespace('9')));
}

static void test_char_lower (void) {
  assert(((void) "Transforms into lowercase 'A'", the_char_lower('A') == 'a'));
  assert(((void) "Transforms into lowercase 'a'", the_char_lower('a') == 'a'));
  assert(((void) "Transforms into lowercase '@'", the_char_lower('@') == '@'));
  assert(((void) "Transforms into lowercase '0'", the_char_lower('0') == '0'));
  assert(((void) "Transforms into lowercase '9'", the_char_lower('9') == '9'));
}

static void test_char_repeat (void) {
  the_str_t a1 = the_char_repeat('a', 0);
  the_str_t a2 = the_char_repeat('a', 1);
  the_str_t a3 = the_char_repeat('a', 2);
  the_str_t a4 = the_char_repeat('a', 10);

  the_str_t s1_cmp = empty_str_value;
  the_str_t s2_cmp = the_str_alloc(L"a");
  the_str_t s3_cmp = the_str_alloc(L"aa");
  the_str_t s4_cmp = the_str_alloc(L"aaaaaaaaaa");

  assert(((void) "Repeat 'a' times 0", the_str_eq(a1, s1_cmp)));
  assert(((void) "Repeat 'a' times 1", the_str_eq(a2, s2_cmp)));
  assert(((void) "Repeat 'a' times 2", the_str_eq(a3, s3_cmp)));
  assert(((void) "Repeat 'a' times 10", the_str_eq(a4, s4_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);
  the_str_free(s3_cmp);
  the_str_free(s4_cmp);

  the_str_free(a1);
  the_str_free(a2);
  the_str_free(a3);
  the_str_free(a4);
}

static void test_char_str (void) {
  the_str_t a1 = the_char_str('A');
  the_str_t a2 = the_char_str('9');

  the_str_t s1_cmp = the_str_alloc(L"A");
  the_str_t s2_cmp = the_str_alloc(L"9");

  assert(((void) "Stringifies 'A'", the_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies '9'", the_str_eq(a2, s2_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);

  the_str_free(a1);
  the_str_free(a2);
}

static void test_char_upper (void) {
  assert(((void) "Transforms into uppercase 'A'", the_char_upper('A') == 'A'));
  assert(((void) "Transforms into uppercase 'a'", the_char_upper('a') == 'A'));
  assert(((void) "Transforms into uppercase '@'", the_char_upper('@') == '@'));
  assert(((void) "Transforms into uppercase '0'", the_char_upper('0') == '0'));
  assert(((void) "Transforms into uppercase '9'", the_char_upper('9') == '9'));
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
