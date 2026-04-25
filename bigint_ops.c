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

