/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/error.h>
#include <the/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char GATE[4] = "GATE";

static void pay_debt (int pay_amount, int debt_amount) {
  if (debt_amount != pay_amount) {
    the_error_assign_generic(&the_err_state, 10, 10, the_str_alloc(L"Not enough funds."));
  }

  if (the_err_state.id != -1) longjmp(the_err_state.buf_last->buf, the_err_state.id);
}

static void lend_debt (int bank_amount, int debt_amount) {
  the_str_t t1 = {NULL, 0};

  if (debt_amount > bank_amount) {
    the_error_assign(
      &the_err_state,
      10,
      10,
      TYPE_Error,
      (void *) the_Error_alloc(t1 = the_str_alloc(L"Not enough funds.")),
      (the_err_state_free_cb) the_Error_free
    );
  }

  the_str_free(t1);
  if (the_err_state.id != -1) longjmp(the_err_state.buf_last->buf, the_err_state.id);
}

int main (void) {
  the_error_stack_push(&the_err_state, L"/test", L"main", 0, 0);

  if (setjmp(the_error_buf_increase(&the_err_state)->buf) != 0) goto L1;
  lend_debt(200, 100);

  if (setjmp(the_err_state.buf_last->buf) != 0) goto L1;
  lend_debt(100, 100);

  if (memcmp(GATE, "GATE", 4) == 0) {
    if (setjmp(the_error_buf_increase(&the_err_state)->buf) != 0) goto L2;
    pay_debt(100, 100);

L2:
    the_error_buf_decrease(&the_err_state);
    if (the_err_state.id != -1) goto L1;
  }

L1:
  the_error_buf_decrease(&the_err_state);
  the_error_stack_pop(&the_err_state);

  if (the_err_state.id != -1) {
    the_Error_t *error = the_err_state.ctx;

    fwprintf(stderr, L"Uncaught Error: %ls" THE_EOL, error->stack.data);
    the_err_state.free_cb(the_err_state.ctx);
    exit(EXIT_FAILURE);
  }

  return 0;
}
