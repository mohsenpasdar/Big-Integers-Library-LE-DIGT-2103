#include <stdio.h>
#include "bigint.h"

int main(void) {
  bigint_t *x = uint_to_bigint(325, 10);


  printf("Number of digits should be 3: %ju\n", bigint_num_digits(x));

  printf("First digit should be 3: %u\n", x->first->value);
  printf("Last digit should be 5: %u\n", x->last->value);


  return 0;
}