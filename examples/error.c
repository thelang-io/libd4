/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
#include "../include/d4/macro.h"
#include "../include/d4/error.h"
#include "../include/d4/string.h"

const char GATE[5] = "GATE";

static void pay_debt (int pay_amount, int debt_amount) {
  if (debt_amount != pay_amount) {
    d4_str_t message = d4_str_alloc(L"Not enough funds.");
    d4_error_assign_generic(&d4_err_state, 10, 10, message);
    d4_str_free(message);
  }

  if (d4_err_state.id != -1) longjmp(d4_err_state.buf_last->buf, d4_err_state.id);
}

static void lend_debt (int bank_amount, int debt_amount) {
  d4_str_t t1 = {NULL, 0, false};

  if (debt_amount > bank_amount) {
    d4_error_assign(
      &d4_err_state,
      10,
      10,
      TYPE_Error,
      (void *) d4_Error_alloc(t1 = d4_str_alloc(L"Not enough funds.")),
      (d4_err_state_free_cb) d4_Error_free
    );
  }

  d4_str_free(t1);
  if (d4_err_state.id != -1) longjmp(d4_err_state.buf_last->buf, d4_err_state.id);
}

int main (void) {
  d4_error_stack_push(&d4_err_state, L"/test", L"main", 0, 0);

  if (setjmp(d4_error_buf_increase(&d4_err_state)->buf) != 0) goto L1;
  lend_debt(200, 100);

  if (setjmp(d4_err_state.buf_last->buf) != 0) goto L1;
  lend_debt(100, 100);

  if (memcmp(GATE, "GATE", 4) == 0) {
    if (setjmp(d4_error_buf_increase(&d4_err_state)->buf) != 0) goto L2;
    pay_debt(100, 100);

L2:
    d4_error_buf_decrease(&d4_err_state);
    if (d4_err_state.id != -1) goto L1;
  }

L1:
  d4_error_buf_decrease(&d4_err_state);
  d4_error_stack_pop(&d4_err_state);

  if (d4_err_state.id != -1) {
    d4_Error_t *error = d4_err_state.ctx;

    fwprintf(stderr, L"Uncaught Error: %ls" D4_EOL, error->stack.data);
    d4_err_state.free_cb(d4_err_state.ctx);
    exit(EXIT_FAILURE);
  }

  return 0;
}
