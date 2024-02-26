/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "error-test.h"
#include <the/macro.h>
#include <assert.h>

static void test_error_assign (void) {
  the_str_t s1 = the_str_alloc(L"An error occurred");
  the_str_t s2 = the_str_alloc(L"Another error occurred");
  the_Error_t *err1;
  CustomError_t *err2;

  the_error_assign(&the_err_state, 0, 0, TYPE_Error, the_Error_alloc(s1), the_Error_free);
  err1 = the_err_state.ctx;

  assert(((void) "Has correct generic id", the_err_state.id == TYPE_Error));
  assert(((void) "Has correct generic message", the_str_eq(s1, err1->message)));

  the_err_state.free_cb(the_err_state.ctx);
  the_error_assign(&the_err_state, 0, 0, TYPE_CustomError, the_CustomError_alloc(s2), the_CustomError_free);
  err2 = the_err_state.ctx;

  assert(((void) "Has correct custom id", the_err_state.id == TYPE_CustomError));
  assert(((void) "Has correct custom message", the_str_eq(s2, err2->message)));

  the_err_state.free_cb(the_err_state.ctx);
  the_str_free(s1);
  the_str_free(s2);
}

static void test_error_assign_generic (void) {
  the_str_t s1 = the_str_alloc(L"An error occurred");
  the_Error_t *err1;

  the_error_assign_generic(&the_err_state, 0, 0, s1);
  err1 = the_err_state.ctx;

  assert(((void) "Has correct generic id", the_err_state.id == TYPE_Error));
  assert(((void) "Has correct generic message", the_str_eq(s1, err1->message)));

  the_err_state.free_cb(the_err_state.ctx);
  the_str_free(s1);
}

static void test_error_assign_generic_with_stack (void) {
  the_str_t s1 = the_str_alloc(L"An error occurred");
  the_str_t s2 = the_str_alloc(L"An error occurred" THE_EOL L"  at main (test.c)");
  the_str_t s3 = the_str_alloc(L"An error occurred" THE_EOL L"  at main (test.c:10)");
  the_str_t s4 = the_str_alloc(L"An error occurred" THE_EOL L"  at main (test.c:10:10)");
  the_str_t s5 = the_str_alloc(L"An error occurred" THE_EOL L"  at walk (test2.c:22:4)" THE_EOL L"  at main (test.c:20:1)");
  the_Error_t *err;

  the_error_stack_push(&the_err_state, L"test.c", L"main", 0, 0);
  the_error_assign_generic(&the_err_state, 0, 0, s1);
  err = the_err_state.ctx;

  assert(((void) "Has correct line", the_err_state.stack_last->line == 0));
  assert(((void) "Has correct col", the_err_state.stack_last->col == 0));
  assert(((void) "Has correct stack", the_str_eq(s2, err->stack)));

  the_err_state.free_cb(the_err_state.ctx);
  the_error_assign_generic(&the_err_state, 10, 0, s1);
  err = the_err_state.ctx;

  assert(((void) "Has correct line", the_err_state.stack_last->line == 10));
  assert(((void) "Has correct col", the_err_state.stack_last->col == 0));
  assert(((void) "Has correct stack", the_str_eq(s3, err->stack)));

  the_err_state.free_cb(the_err_state.ctx);
  the_error_assign_generic(&the_err_state, 10, 10, s1);
  err = the_err_state.ctx;

  assert(((void) "Has correct line", the_err_state.stack_last->line == 10));
  assert(((void) "Has correct col", the_err_state.stack_last->col == 10));
  assert(((void) "Has correct stack", the_str_eq(s4, err->stack)));

  the_err_state.free_cb(the_err_state.ctx);
  the_error_stack_push(&the_err_state, L"test2.c", L"walk", 20, 1);
  the_error_assign_generic(&the_err_state, 22, 4, s1);
  err = the_err_state.ctx;

  assert(((void) "Has correct line", the_err_state.stack_last->line == 22));
  assert(((void) "Has correct col", the_err_state.stack_last->col == 4));
  assert(((void) "Has correct stack", the_str_eq(s5, err->stack)));

  the_err_state.free_cb(the_err_state.ctx);
  the_error_stack_pop(&the_err_state);
  the_error_stack_pop(&the_err_state);

  the_str_free(s3);
  the_str_free(s2);
  the_str_free(s1);
}

static void test_error_buf_increase (void) {
  the_error_buf_increase(&the_err_state);

  assert(((void) "Increases to first item", the_err_state.buf_first != NULL));
  assert(((void) "Increases to first item", the_err_state.buf_last != NULL));
  assert(((void) "Next item is NULL", the_err_state.buf_first->next == NULL));

  the_error_buf_increase(&the_err_state);

  assert(((void) "Increases to second item", the_err_state.buf_first->next != NULL));

  the_error_buf_decrease(&the_err_state);
  the_error_buf_decrease(&the_err_state);
}

static void test_error_buf_decrease (void) {
  the_error_buf_increase(&the_err_state);
  the_error_buf_decrease(&the_err_state);

  assert(((void) "Decreases to NULL", the_err_state.buf_first == NULL));
  assert(((void) "Decreases to NULL", the_err_state.buf_last == NULL));

  the_error_buf_increase(&the_err_state);
  the_error_buf_increase(&the_err_state);
  the_error_buf_decrease(&the_err_state);
  the_error_buf_decrease(&the_err_state);

  assert(((void) "Decreases to NULL", the_err_state.buf_first == NULL));
  assert(((void) "Decreases to NULL", the_err_state.buf_last == NULL));
}

static void test_error_stack_push (void) {
  the_error_stack_push(&the_err_state, L"test.c", L"main", 0, 0);

  assert(((void) "Stack not empty", the_err_state.stack_first != NULL));
  assert(((void) "Pushed correct file name", wmemcmp(the_err_state.stack_first->file, L"test.c", 6) == 0));
  assert(((void) "Pushed correct function name", wmemcmp(the_err_state.stack_first->name, L"main", 4) == 0));

  the_error_stack_push(&the_err_state, L"test2.c", L"main2", 10, 10);

  assert(((void) "Pushed correct second file name", wmemcmp(the_err_state.stack_last->file, L"test2.c", 7) == 0));
  assert(((void) "Pushed correct second function name", wmemcmp(the_err_state.stack_last->name, L"main2", 5) == 0));
  assert(((void) "Pushed correct second line number", the_err_state.stack_first->line == 10));
  assert(((void) "Pushed correct second line column", the_err_state.stack_first->col == 10));

  the_error_stack_pop(&the_err_state);
  the_error_stack_pop(&the_err_state);
}

static void test_error_stack_pop (void) {
  the_error_stack_push(&the_err_state, L"test.c", L"main", 0, 0);
  the_error_stack_push(&the_err_state, L"test2.c", L"main2", 10, 10);

  the_error_stack_pop(&the_err_state);
  the_error_stack_pop(&the_err_state);

  assert(((void) "Resets to empty", the_err_state.stack_first != NULL));
}

static void test_error_unset (void) {
  the_str_t s1 = the_str_alloc(L"An error occurred");
  the_Error_t *err1;

  the_error_assign_generic(&the_err_state, 0, 0, s1);
  err1 = the_err_state.ctx;

  the_error_unset(&the_err_state);

  assert(((void) "Resets id", the_err_state.id == -1));
  assert(((void) "Resets free callback", the_err_state.free_cb == NULL));

  the_Error_free(err1);
  the_str_free(s1);
}

static void test_Error_alloc (void) {
  the_str_t s1 = the_str_alloc(L"");
  the_str_t s2 = the_str_alloc(L"An error occurred");
  the_Error_t *err1 = the_Error_alloc(s2);

  assert(((void) "Sets correct stack", the_str_eq(err1->stack, s1)));
  assert(((void) "Sets correct message", the_str_eq(err1->message, s2)));

  the_Error_free(err1);
  the_str_free(s2);
  the_str_free(s1);
}

static void test_Error_free (void) {
  the_str_t s1 = the_str_alloc(L"An error occurred");
  the_Error_free(the_Error_alloc(s1));
  the_str_free(s1);
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
