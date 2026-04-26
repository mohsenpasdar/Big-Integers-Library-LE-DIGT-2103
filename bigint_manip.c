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
  
    return bigint;
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
    bigint->first->value = -1;
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
  
    return bigint;
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
}
