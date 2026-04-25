#include "bigint.h"

#include <stdlib.h>
#include <ctype.h>

/* Allocates and initializes a new digit struct. Also updates
   neighbouring digits and the bigint pointers to point to the new
   digit. This function is intended to be used as a helper function
   for other bigint functions, and is not intended to be used outside
   of the bigint library itself.
   
   Parameters:
   - value: digit value of the new digit, must be between 0 and
     base-1.
   - next: digit to the right of the new digit. If set, will also be
     updated to point to new digit. If NULL, will cause bigint->last
     to be updated instead.
   - prev: digit to the left of the new digit. If set, will also be
     updated to point to new digit. If NULL, will cause bigint->first
     to be updated instead.

   Returns: a pointer to the newly allocated digit.
 */
digit_t *bigint_add_digit(bigint_t *bigint, baseint_t value, digit_t *next, digit_t *prev) {

  // YOUR CODE HERE
}

/* Allocates and initializes a new big integer struct that has a
   single digit.
   
   Parameters:
   - sign: the sign of the new number (positive, negative, zero).
   - base: the base at which the number is represented. Assumed to be
     between MIN_BASE and MAX_BASE.
   - digit_value: the value of the single digit. Must be between
     0 and base-1.
   
   Returns: a pointer to the newly allocated big integer.
 */
bigint_t *new_basic_bigint(sign_t sign, baseint_t base, baseint_t digit_value) {
  
  // YOUR CODE HERE
}

/* Ensures that the big integer data structure is clean. Removes
   leading zeros, and updates the sign to SIGN_ZERO if there is only a
   single digit with the value zero.

   This function is expected to be called by most (if not all) library
   functions that return a `bigint` object before it is returned.

   Parameter: bigint: the big integer to be cleaned up.

   Returns: the same bigint passed as a parameter.
 */
bigint_t *cleanup_bigint(bigint_t *bigint) {

  // YOUR CODE HERE
}

/* Frees a big integer and all its digits.
   
   Parameter: bigint: the big integer to be freed.
 */
void bigint_free(bigint_t *bigint) {
  
  // YOUR CODE HERE
}

/* Counts the number of digits in a big integer.

   Parameters: bigint: the big integer to be evaluated.
   
   Returns: a positive integer representing the number of digits in
   the big integer. The sign is not counted as a digit. A value of
   zero is considered to have one digit.
 */
uintmax_t bigint_num_digits(bigint_t *bigint) {

  // YOUR CODE HERE
}

/* Creates a new copy of a big integer. The copy will represent the
   same number in the same base, with new digits.

   Parameters: src: the big integer to be copied.
   
   Returns: a newly allocated big integer representing the same number
   as src in the same base.
 */
bigint_t *bigint_dup(bigint_t *src) {

  // YOUR CODE HERE
}
