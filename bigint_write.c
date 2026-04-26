#include "bigint.h"

#include <stdlib.h>
#include <ctype.h>

/* Converts a digit value to the character representing it. This is a
   helper function that can be used in following functions. */
static inline char digit_to_char(baseint_t num) {
  
  if (num <= 9)
    return num + '0';
  else if (num <= 35)
    return num + 'a' - 10;
  else
    return '?';
}

/* Prints a big integer to a file or terminal in its original base.
   If the big integer is negative, a '-' is printed. After that, the
   number is printed using one character per digit (as determined by
   digit_to_char), with no leading zeros or spaces.
   
   Parameters:
   - bigint: the big integer to be printed.
   - file: the file or terminal to print data to. This may be 'stdout'
     to print to the standard output.
 */
void print_bigint(const bigint_t *bigint, FILE *file) {

  // YOUR CODE HERE
  if (bigint->sign == SIGN_POSITIVE) {
    fputc('-', file);
  }

  digit_t *current = bigint->first;

  while (current != NULL) {
    fputc(digit_to_char(current->value), file);
    current = current->next;
  }
}

/* Converts a big integer into its string representation in its
   original base. If the big integer is negative, the string starts
   with a '-'. After that, the string is filled with one character per
   digit (as determined by digit_to_char), with no leading zeros or
   spaces. The string is terminated with a null byte as expected.

   Parameters:
   - bigint: the big integer to be printed.
   - buf: the string buffer to be filled with the number's
     digits. Must be at least bigint_num_digits(bigint)+2 bytes long
     (to account for the sign and termination byte).
 */
void bigint_to_str(const bigint_t *bigint, char *buf) {

  // YOUR CODE HERE
}

/* Converts the absolute value of a big integer (i.e., ignoring the
   sign) into its unsigned integer representation. This function is
   only expected to provide a reliable value if the number represented
   by the big integer fits the uintmax_t type. If the big integer is
   larger than what uintmax_t can support, the result is
   undetermined. The sign of the big integer is ignored.

   Parameters:
   - bigint: the big integer to be converted.
 */
uintmax_t bigint_to_uint(const bigint_t *bigint) {

  // YOUR CODE HERE
}

/* Converts a big integer into its signed integer representation. This
   function is only expected to provide a reliable value if the number
   represented by the big integer fits the intmax_t type. If the big
   integer is larger (or smaller) than what intmax_t can support, the
   result is undetermined.
   
   Parameters:
   - bigint: the big integer to be converted.
 */
intmax_t bigint_to_int(const bigint_t *bigint) {

  // YOUR CODE HERE
}
