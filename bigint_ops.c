#include "bigint.h"

#include <stdlib.h>
#include <ctype.h>

/* Compares two big integers. The two integers may be represented in
   the same base or in different bases.

   Parameters: a, b: big integers to be compared.
   
   Returns: 0 (zero) if a = b; some negative number if a < b; or some
   positive number if a > b.
 */
int bigint_cmp(bigint_t *a, bigint_t *b) {

  // YOUR CODE HERE
  if (a == NULL || b == NULL) {
    return 0;
  }

  if (a->sign != b->sign) {
    return a->sign - b->sign;
  }

  if (a->sign == SIGN_ZERO) {
    return 0;
  }

  bigint_t *b_converted = b;
  int should_free_b = 0;

  if (a->base != b->base) {
    b_converted = bigint_change_base(b, a->base);

    if (b_converted == NULL) {
      return 0;
    }

    should_free_b = 1;
  }

  int result = 0;

  uintmax_t a_digits = bigint_num_digits(a);
  uintmax_t b_digits = bigint_num_digits(b_converted);

  if (a_digits < b_digits) {
    result = -1;
  } else if (a_digits > b_digits) {
    result = 1;
  } else {
    digit_t *a_current = a->first;
    digit_t *b_current = b_converted->first;

    while (a_current != NULL && b_current != NULL) {
      if (a_current->value < b_current->value) {
        result = -1;
        break;
      } else if (a_current->value > b_current->value) {
        result = 1;
        break;
      }

      a_current = a_current->next;
      b_current = b_current->next;
    }
  }

  if (should_free_b) {
    bigint_free(b_converted);
  }

  if (a->sign == SIGN_NEGATIVE) {
    result = -result;
  }

  return result;
}

/* Creates a new big integer representing the sum of two big
   integers. The two integers may be represented in the same base or
   in different bases. The base of the result matches the base of the
   first operand.
   
   Parameters: a, b: operands of the add operation.
   
   Returns: a newly allocated big integer representing the sum of the
   numbers in a and b (i.e., a+b), in the base of a.
 */
bigint_t *bigint_add(bigint_t *a, bigint_t *b) {

  // YOUR CODE HERE
}

/* Creates a new big integer representing the difference between two
   big integers. The two integers may be represented in the same base
   or in different bases. The base of the result matches the base of
   the first operand. This function is equivalent to bigint_add
   applied to a and the opposite of b.
   
   Parameters: a, b: operands of the subtract operation.
   
   Returns: a newly allocated big integer representing the difference
   between the numbers in a and b (i.e., a-b), in the base of a.
 */
bigint_t *bigint_sub(bigint_t *a, bigint_t *b) {

  // YOUR CODE HERE
}

