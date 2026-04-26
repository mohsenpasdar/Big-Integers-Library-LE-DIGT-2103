#include <stdio.h>
#include "bigint.h"

int main(void) {
  bigint_t *x = new_basic_bigint(SIGN_POSITIVE, 10, 3);

  bigint_add_digit(x, 5, NULL, x->last);
  bigint_add_digit(x, 7, NULL, x->last);

  printf("Number of digits should be 3: %ju\n", bigint_num_digits(x));

  printf("First digit should be 3: %u\n", x->first->value);
  printf("Last digit should be 7: %u\n", x->last->value);

  bigint_t *copy = bigint_dup(x);

  printf("Copy number of digits should be 3: %ju\n", bigint_num_digits(copy));
  printf("Copy first digit should be 3: %u\n", copy->first->value);
  printf("Copy last digit should be 7: %u\n", copy->last->value);

  bigint_free(x);
  bigint_free(copy);

  return 0;
}