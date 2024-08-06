/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "error-test.h"
#include <assert.h>
#include <string.h>

static void test_error_assign (void) {
  d4_str_t s1 = d4_str_alloc(L"An error occurred");
  d4_str_t s2 = d4_str_alloc(L"Another error occurred");
  d4_Error_t *err1;
  CustomError_t *err2;

  d4_error_assign(&d4_err_state, 0, 0, TYPE_Error, d4_Error_alloc(s1), d4_Error_free);
  err1 = d4_err_state.ctx;

  assert(((void) "Has correct generic id", d4_err_state.id == TYPE_Error));
  assert(((void) "Has correct generic message", d4_str_eq(s1, err1->message)));

  d4_err_state.free_cb(d4_err_state.ctx);
  d4_error_assign(&d4_err_state, 0, 0, TYPE_CustomError, d4_CustomError_alloc(s2), d4_CustomError_free);
  err2 = d4_err_state.ctx;

  assert(((void) "Has correct custom id", d4_err_state.id == TYPE_CustomError));
  assert(((void) "Has correct custom message", d4_str_eq(s2, err2->message)));

  d4_err_state.free_cb(d4_err_state.ctx);
  d4_str_free(s1);
  d4_str_free(s2);
}

static void test_error_assign_generic (void) {
  d4_str_t s1 = d4_str_alloc(L"An error occurred");
  d4_Error_t *err1;

  d4_error_assign_generic(&d4_err_state, 0, 0, s1);
  err1 = d4_err_state.ctx;

  assert(((void) "Has correct generic id", d4_err_state.id == TYPE_Error));
  assert(((void) "Has correct generic message", d4_str_eq(s1, err1->message)));

  d4_err_state.free_cb(d4_err_state.ctx);
  d4_str_free(s1);
}

static void test_error_assign_generic_with_stack (void) {
  d4_str_t s1 = d4_str_alloc(L"An error occurred");
  d4_str_t s2 = d4_str_alloc(L"An error occurred" D4_EOL L"  at main (test.c)");
  d4_str_t s3 = d4_str_alloc(L"An error occurred" D4_EOL L"  at main (test.c:10)");
  d4_str_t s4 = d4_str_alloc(L"An error occurred" D4_EOL L"  at main (test.c:10:10)");
  d4_str_t s5 = d4_str_alloc(L"An error occurred" D4_EOL L"  at walk (test2.c:22:4)" D4_EOL L"  at main (test.c:20:1)");
  d4_Error_t *err;

  d4_error_stack_push(&d4_err_state, L"test.c", L"main", 0, 0);
  d4_error_assign_generic(&d4_err_state, 0, 0, s1);
  err = d4_err_state.ctx;

  assert(((void) "Has correct line", d4_err_state.stack_last->line == 0));
  assert(((void) "Has correct col", d4_err_state.stack_last->col == 0));
  assert(((void) "Has correct stack", d4_str_eq(s2, err->stack)));

  d4_err_state.free_cb(d4_err_state.ctx);
  d4_error_assign_generic(&d4_err_state, 10, 0, s1);
  err = d4_err_state.ctx;

  assert(((void) "Has correct line", d4_err_state.stack_last->line == 10));
  assert(((void) "Has correct col", d4_err_state.stack_last->col == 0));
  assert(((void) "Has correct stack", d4_str_eq(s3, err->stack)));

  d4_err_state.free_cb(d4_err_state.ctx);
  d4_error_assign_generic(&d4_err_state, 10, 10, s1);
  err = d4_err_state.ctx;

  assert(((void) "Has correct line", d4_err_state.stack_last->line == 10));
  assert(((void) "Has correct col", d4_err_state.stack_last->col == 10));
  assert(((void) "Has correct stack", d4_str_eq(s4, err->stack)));

  d4_err_state.free_cb(d4_err_state.ctx);
  d4_error_stack_push(&d4_err_state, L"test2.c", L"walk", 20, 1);
  d4_error_assign_generic(&d4_err_state, 22, 4, s1);
  err = d4_err_state.ctx;

  assert(((void) "Has correct line", d4_err_state.stack_last->line == 22));
  assert(((void) "Has correct col", d4_err_state.stack_last->col == 4));
  assert(((void) "Has correct stack", d4_str_eq(s5, err->stack)));

  d4_err_state.free_cb(d4_err_state.ctx);
  d4_error_stack_pop(&d4_err_state);
  d4_error_stack_pop(&d4_err_state);

  d4_str_free(s5);
  d4_str_free(s4);
  d4_str_free(s3);
  d4_str_free(s2);
  d4_str_free(s1);
}

static void test_error_buf_increase (void) {
  d4_error_buf_increase(&d4_err_state);

  assert(((void) "Increases to first item", d4_err_state.buf_first != NULL));
  assert(((void) "Increases to first item", d4_err_state.buf_last != NULL));
  assert(((void) "Next item is NULL", d4_err_state.buf_first->next == NULL));

  d4_error_buf_increase(&d4_err_state);

  assert(((void) "Increases to second item", d4_err_state.buf_first->next != NULL));

  d4_error_buf_decrease(&d4_err_state);
  d4_error_buf_decrease(&d4_err_state);
}

static void test_error_buf_decrease (void) {
  d4_error_buf_increase(&d4_err_state);
  d4_error_buf_decrease(&d4_err_state);

  assert(((void) "Decreases to NULL", d4_err_state.buf_first == NULL));
  assert(((void) "Decreases to NULL", d4_err_state.buf_last == NULL));

  d4_error_buf_increase(&d4_err_state);
  d4_error_buf_increase(&d4_err_state);
  d4_error_buf_decrease(&d4_err_state);
  d4_error_buf_decrease(&d4_err_state);

  assert(((void) "Decreases to NULL", d4_err_state.buf_first == NULL));
  assert(((void) "Decreases to NULL", d4_err_state.buf_last == NULL));
}

static void test_error_stack_push (void) {
  d4_error_stack_push(&d4_err_state, L"test.c", L"main", 0, 0);

  assert(((void) "Stack not empty", d4_err_state.stack_first != NULL));
  assert(((void) "Pushed correct file name", memcmp(d4_err_state.stack_first->file, L"test.c", 6 * sizeof(wchar_t)) == 0));
  assert(((void) "Pushed correct function name", memcmp(d4_err_state.stack_first->name, L"main", 4 * sizeof(wchar_t)) == 0));

  d4_error_stack_push(&d4_err_state, L"test2.c", L"main2", 10, 10);

  assert(((void) "Pushed correct second file name", memcmp(d4_err_state.stack_last->file, L"test2.c", 7 * sizeof(wchar_t)) == 0));
  assert(((void) "Pushed correct second function name", memcmp(d4_err_state.stack_last->name, L"main2", 5 * sizeof(wchar_t)) == 0));
  assert(((void) "Pushed correct second line number", d4_err_state.stack_first->line == 10));
  assert(((void) "Pushed correct second line column", d4_err_state.stack_first->col == 10));

  d4_error_stack_pop(&d4_err_state);
  d4_error_stack_pop(&d4_err_state);
}

static void test_error_stack_pop (void) {
  d4_error_stack_push(&d4_err_state, L"test.c", L"main", 0, 0);
  d4_error_stack_push(&d4_err_state, L"test2.c", L"main2", 10, 10);

  d4_error_stack_pop(&d4_err_state);
  d4_error_stack_pop(&d4_err_state);

  assert(((void) "Resets to empty", d4_err_state.stack_first == NULL && d4_err_state.stack_last == NULL));
}

static void test_error_unset (void) {
  d4_str_t s1 = d4_str_alloc(L"An error occurred");
  d4_Error_t *err1;

  d4_error_assign_generic(&d4_err_state, 0, 0, s1);
  err1 = d4_err_state.ctx;

  d4_error_unset(&d4_err_state);

  assert(((void) "Resets id", d4_err_state.id == -1));
  assert(((void) "Resets free callback", d4_err_state.free_cb == NULL));

  d4_Error_free(err1);
  d4_str_free(s1);
}

static void test_Error_alloc (void) {
  d4_str_t s1 = d4_str_empty_val;
  d4_str_t s2 = d4_str_alloc(L"An error occurred");
  d4_Error_t *err1 = d4_Error_alloc(s2);

  assert(((void) "Sets correct stack", d4_str_eq(err1->stack, s1)));
  assert(((void) "Sets correct message", d4_str_eq(err1->message, s2)));

  d4_Error_free(err1);
  d4_str_free(s2);
  d4_str_free(s1);
}

static void test_Error_free (void) {
  d4_str_t s1 = d4_str_alloc(L"An error occurred");
  d4_Error_free(d4_Error_alloc(s1));
  d4_str_free(s1);
}

int main (void) {
  test_error_assign();
  test_error_assign_generic();
  test_error_assign_generic_with_stack();
  test_error_buf_increase();
  test_error_buf_decrease();
  test_error_stack_push();
  test_error_stack_pop();
  test_error_unset();
  test_Error_alloc();
  test_Error_free();
}
