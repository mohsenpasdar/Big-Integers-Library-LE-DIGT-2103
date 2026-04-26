#include "bigint.h"

#include <stdlib.h>
#include <ctype.h>

/* Converts an unsigned integer to a big integer.
   
   Parameters:
   - value: the unsigned integer to be converted to a big integer.
   - base: the base at which the number is represented. Must be
     between MIN_BASE and MAX_BASE.

   Returns: a newly allocated big integer representing the same
   numeric value as 'value'.
 */
bigint_t *uint_to_bigint(uintmax_t value, baseint_t base) {

  // YOUR CODE HERE
  if (value == 0) {
    return new_basic_bigint(SIGN_ZERO, base, 0);
  }

  baseint_t digit = value % base;
  value = value / base;

  bigint_t *bigint = new_basic_bigint(SIGN_POSITIVE, base, digit);
  if (bigint == NULL) return NULL;

  while (value > 0) {
    digit = value % base;
    value = value / base;
    
    if(bigint_add_digit(bigint, digit, bigint->first, NULL) == NULL) {
      bigint_free(bigint);
      return NULL;
    }
  }

  return cleanup_bigint(bigint);
}

/* Converts a signed integer to a big integer.
   
   Parameters:
   - value: the signed integer to be converted to a big integer.
   - base: the base at which the number is represented. Must be
     between MIN_BASE and MAX_BASE.

   Returns: a newly allocated big integer representing the same
   numeric value as 'value'.
 */
bigint_t *int_to_bigint(intmax_t value, baseint_t base) {

  // YOUR CODE HERE
}

/* Converts a character to the digit value it represents. This is a
   helper function that can be used in following functions. */
static inline baseint_t char_to_digit(int c) {

  if ('0' <= c && c <= '9')
    return c - '0';
  else if ('A' <= c && c <= 'Z')
    return c - 'A' + 10;
  else if ('a' <= c && c <= 'z')
    return c - 'a' + 10;
  else
    return INVALID_DIGIT;
}

/* Converts the string in str to a big integer according to the given
   base. The behaviour of this function is similar to that of strtol:
   an arbitrary amount of white space (as determined by isspace) at
   the start, if found, is ignored. The string starts with a single
   optional '+' or '-' sign; if no sign is found, the number is
   assumed to be positive. Following the optional sign, each character
   is interpreted as a digit in the provided base, as determined by
   char_to_digit. Conversion stops at the first character which is not
   a valid digit in the given base (as determined by the char_to_digit
   function). Spaces after the sign or digits cause the conversion to
   stop.
   
   Parameters:
   - str: the string to be converted to a big integer.
   - endptr: if endptr is not NULL, this function stores the address
     of the first character that is not a valid digit in *endptr. If
     there were no digits at all, it stores the position where the
     first digit was expected to be found (i.e., after spaces and/or
     the sign) in *endptr, and returns the big integer representing
     zero. If the entire string was parsed, **endptr points to the
     '\0' character at the end of the string.
  - base: the base at which the number is represented. Must be between
    MIN_BASE and MAX_BASE. Corresponds both to the base of the
    characters and the base of the resulting bigint object.

   Returns: a newly allocated big integer representing the same
   numeric value as 'str'.
 */
bigint_t *str_to_bigint(char *str, char **endptr, baseint_t base) {

  // YOUR CODE HERE
}

/* Reads a big integer from a file or terminal in the given base.
   
   Characters (initial spaces, an optional sign and individual digits)
   are read using the same rules as str_to_bigint. Reading stops at
   the first character which is not a valid digit in the given base or
   if the stream reaches end-of-file. This invalid digit (if it
   exists) is returned (using ungetc) to the stream.
   
   Parameters:
   - file: the file or terminal to read data from. This may be 'stdin'
     to read from the standard input.
   - base: the base at which the number is represented. Must be
     between MIN_BASE and MAX_BASE.

   Returns: a newly allocated big integer representing the value read
   from the file pointer.
 */
bigint_t *read_bigint(FILE *file, baseint_t base) {

  // YOUR CODE HERE
}
