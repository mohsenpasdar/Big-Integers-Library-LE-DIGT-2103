#include "bigint.h"

#include <stdlib.h>
#include <ctype.h>

/* Increments the value of a bigint object in-place by one.

   Parameters:
   - bigint: the big integer to be incremented.
   
   Returns: the original bigint, with its value incremented by one.
 */
bigint_t *bigint_increment(bigint_t *bigint) {

  // YOUR CODE HERE
  if (bigint == NULL) return NULL;

  if (bigint->sign == SIGN_ZERO) {
    bigint->sign = SIGN_POSITIVE;
    bigint->first->value = 1;
    return cleanup_bigint(bigint);
  }

  if (bigint->sign == SIGN_POSITIVE) {

    digit_t *current = bigint->last;
    
    while (current != NULL) {
      if (current->value + 1 < bigint->base) {
        current->value++;
        return bigint;
      }
      
      current->value = 0;
      current = current->prev;
    }

    if (bigint_add_digit(bigint, 1, bigint->first, NULL) == NULL) {
      return NULL;
    }
  
    return cleanup_bigint(bigint);
  }

  if (bigint->sign == SIGN_NEGATIVE) {
    digit_t *current = bigint->last;
    
    while (current != NULL) {
      if (current->value > 0) {
        current->value--;
        break;
      }

      current->value = bigint->base - 1;
      current = current->prev;
    }

    return cleanup_bigint(bigint);
  }

  return bigint;
}

/* Increments the value of a bigint object in-place by one.

   Parameters:
   - bigint: the big integer to be incremented.
   
   Returns: the original bigint, with its value incremented by one.
 */
bigint_t *bigint_decrement(bigint_t *bigint) {

  // YOUR CODE HERE
  if (bigint == NULL) return NULL;

  if (bigint->sign == SIGN_ZERO) {
    bigint->sign = SIGN_NEGATIVE;
    bigint->first->value = 1;
    return cleanup_bigint(bigint);
  }

  if (bigint->sign == SIGN_POSITIVE) {
    digit_t *current = bigint->last;
    
    while (current != NULL) {
      if (current->value > 0) {
        current->value--;
        break;
      }

      current->value = bigint->base - 1;
      current = current->prev;
    }

    return cleanup_bigint(bigint);
  }

  if (bigint->sign == SIGN_NEGATIVE) {

    digit_t *current = bigint->last;
    
    while (current != NULL) {
      if (current->value + 1 < bigint->base) {
        current->value++;
        return bigint;
      }
      
      current->value = 0;
      current = current->prev;
    }

    if (bigint_add_digit(bigint, 1, bigint->first, NULL) == NULL) {
      return NULL;
    }
  
    return cleanup_bigint(bigint);
  }

  return bigint;
}

/* Divides a big integer by an unsigned integer divisor. This function
   can be used, among other things, as part of the computation
   required to convert a big integer into a new base (see
   bigint_change_base).

   Parameters:
   - dividend: the big integer corresponding to the dividend. This
     object remains unmodified.
   - divisor: the number that the dividend will be divided by. Cannot
     be zero.
   - remainder: if not NULL, the remainder of the division will be
     stored into *remainder.

   Returns: a newly allocated big integer corresponding to the result
   of the division of dividend by divisor.
 */
bigint_t *bigint_divide_by_uint(const bigint_t *dividend, baseint_t divisor,
				baseint_t *remainder) {

  // YOUR CODE HERE
  if (dividend == NULL || divisor == 0) {
    return NULL;
  }

  uintmax_t carry = 0;

  digit_t *current = dividend->first;

  uintmax_t value = carry * dividend->base + current->value;
  baseint_t quotient_digit = value / divisor;
  carry = value % divisor;

  bigint_t *quotient = new_basic_bigint(dividend->sign, dividend->base, quotient_digit);

  if (quotient == NULL) {
    return NULL;
  }

  current = current->next;

  while (current != NULL)
  {
    value = carry * dividend->base + current->value;
    quotient_digit = value / divisor;
    carry = value % divisor;

    if (bigint_add_digit(quotient, quotient_digit, NULL, quotient->last) == NULL ) {
      bigint_free(quotient);
      return NULL;
    }

    current = current->next;
  }
  
  if (remainder != NULL) {
    *remainder = carry;
  }

  return cleanup_bigint(quotient);
}

/* Creates a copy of a big integer, replacing the base with a new
   base. The copy will represent the same number but with a different
   base, performing the appropriate computations as required. Calling
   this function with a new_base that is the same as the bigint
   object's old base is equivalent to calling bigint_dup(old).

   Parameters:
   - old: the big integer to be copied.
   - base: the base at which the new number is to be represented. Must
     be between MIN_BASE and MAX_BASE.
   
   Returns: a newly allocated big integer representing the same number
   as src in a different base.
 */
bigint_t *bigint_change_base(bigint_t *old, baseint_t new_base) {

  // YOUR CODE HERE
  if (old == NULL) return NULL;

  if (new_base < MIN_BASE || new_base > MAX_BASE) {
    return NULL;
  }

  if (old->base == new_base) return bigint_dup(old);

  if (old->sign == SIGN_ZERO) {
    return new_basic_bigint(SIGN_ZERO, new_base, 0);
  }

  bigint_t *temp = bigint_dup(old);
  if (temp == NULL) {
    return NULL;
  }
  
  temp->sign = SIGN_POSITIVE;
  
  bigint_t *result = NULL;

  while (temp->sign != SIGN_ZERO)
  {
    baseint_t rem;
    bigint_t *quotient = bigint_divide_by_uint(temp, new_base, &rem);

    if (quotient == NULL) {
      bigint_free(temp);
      bigint_free(result);
      return NULL;
    }

    if (result == NULL) {
      result = new_basic_bigint(old->sign, new_base, rem);

      if (result == NULL) {
        bigint_free(temp);
        bigint_free(quotient);
        return NULL;
      }
    } else {
      if (bigint_add_digit(result, rem, result->first, NULL) == NULL) {
        bigint_free(temp);
        bigint_free(quotient);
        bigint_free(result);
        return NULL;
      }
    }
    bigint_free(temp);
    temp = quotient;
  }

  bigint_free(temp);

  return cleanup_bigint(result);
}
