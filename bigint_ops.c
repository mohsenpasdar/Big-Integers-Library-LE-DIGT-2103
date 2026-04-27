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
  if (a == NULL || b == NULL) {
    return NULL;
  }

  if (a->sign == SIGN_ZERO) {
    return bigint_change_base(b, a->base);
  }

  if (b->sign == SIGN_ZERO) {
    return bigint_dup(a);
  }

  bigint_t *b_converted = b;
  int should_free_b = 0;

  if (a->base != b->base) {
    b_converted = bigint_change_base(b, a->base);

    if (b_converted == NULL) {
      return NULL;
    }

    should_free_b = 1;
  }

  bigint_t *result = malloc(sizeof(bigint_t));

  if (result == NULL) {
    if (should_free_b) {
      bigint_free(b_converted);
    }

    return NULL;
  }

  result->base = a->base;
  result->first = NULL;
  result->last = NULL;

  if (a->sign == b_converted->sign) {

    result->sign = a->sign;

    digit_t *a_current = a->last;
    digit_t *b_current = b_converted->last;

    uintmax_t carry = 0;

    while (a_current != NULL || b_current != NULL || carry > 0) {

      uintmax_t sum = carry;

      if (a_current != NULL) {
        sum += a_current->value;
        a_current = a_current->prev;
      }

      if (b_current != NULL) {
        sum += b_current->value;
        b_current = b_current->prev;
      }

      baseint_t digit = sum % a->base;
      carry = sum / a->base;

      if (bigint_add_digit(result, digit, result->first, NULL) == NULL) {
        bigint_free(result);

        if (should_free_b) {
          bigint_free(b_converted);
        }

        return NULL;
      }
    }

  } else {

    int cmp = 0;

    uintmax_t a_digits = bigint_num_digits(a);
    uintmax_t b_digits = bigint_num_digits(b_converted);

    if (a_digits > b_digits) {
      cmp = 1;
    } else if (a_digits < b_digits) {
      cmp = -1;
    } else {
      digit_t *a_current = a->first;
      digit_t *b_current = b_converted->first;

      while (a_current != NULL && b_current != NULL) {
        if (a_current->value > b_current->value) {
          cmp = 1;
          break;
        } else if (a_current->value < b_current->value) {
          cmp = -1;
          break;
        }

        a_current = a_current->next;
        b_current = b_current->next;
      }
    }

    if (cmp == 0) {
      free(result);

      if (should_free_b) {
        bigint_free(b_converted);
      }

      return new_basic_bigint(SIGN_ZERO, a->base, 0);
    }

    bigint_t *larger;
    bigint_t *smaller;

    if (cmp > 0) {
      larger = a;
      smaller = b_converted;
      result->sign = a->sign;
    } else {
      larger = b_converted;
      smaller = a;
      result->sign = b_converted->sign;
    }

    digit_t *larger_current = larger->last;
    digit_t *smaller_current = smaller->last;

    int borrow = 0;

    while (larger_current != NULL) {

      int diff = larger_current->value - borrow;

      if (smaller_current != NULL) {
        diff -= smaller_current->value;
        smaller_current = smaller_current->prev;
      }

      if (diff < 0) {
        diff += a->base;
        borrow = 1;
      } else {
        borrow = 0;
      }

      if (bigint_add_digit(result, diff, result->first, NULL) == NULL) {
        bigint_free(result);

        if (should_free_b) {
          bigint_free(b_converted);
        }

        return NULL;
      }

      larger_current = larger_current->prev;
    }
  }

  if (should_free_b) {
    bigint_free(b_converted);
  }

  return cleanup_bigint(result);
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
  if (a == NULL || b == NULL) {
    return NULL;
  }

  bigint_t *negative_b = bigint_dup(b);

  if (negative_b == NULL) {
    return NULL;
  }

  if (negative_b->sign == SIGN_POSITIVE) {
    negative_b->sign = SIGN_NEGATIVE;
  } else if (negative_b->sign == SIGN_NEGATIVE) {
    negative_b->sign = SIGN_POSITIVE;
  }

  bigint_t *result = bigint_add(a, negative_b);

  bigint_free(negative_b);

  if (result == NULL) {
    return NULL;
  }

  return cleanup_bigint(result);
}

