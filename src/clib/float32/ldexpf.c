#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

#pragma             extrn Cerrno
#pragma             extrn Csubf
#pragma             extrn Caddf
#pragma             extrn Cmulf
#pragma             extrn Ctruncf

/*
 * Multiple a float number a by 2 raised to the n power.
 *    If a is zero, result is zero.
 *    If a is NaN, returns NaN
 *    If a is +/-Inf, returns +/-Inf
 *    If n < -126, return zero
 *    If n > 127, return +Inf
 *    else resturn result = a * 2^n
 */
float32_t ldexpf(float32_t a, int n) {
  int e = 0;
  static float32_t scale;
  static float32_t result = {0, 0};

  if (isNaN(a)) {
    errno = EDOM;
    result = a;
    return result;
  } else if(isInf(a)) {
    errno = ERANGE;
    result = a;
    return result;
  } else if (isZero(a)) {
    result.high = 0;
    result.low  = 0;
    return result;
  }

  /* get biased exponent value from bits to check for overflow or underflow */
  e = (a.high & FP_EXP) >> 7;

  /* remove bias (127) and do calculation as 16-bit values */
  e -= 127;

  /* add power to get sum of exponents */
  e += n;

  /* check if n or sum is within valid 16-bit range from -126 to 127 */

  if ( n < -126 || e < -126) {
    /* Underflow */
    result.high = 0;
    result.low  = 0;
    return result;
  } else if (n > 127 || e > 127) {
    /* Overflow */
    if (isNeg(a)) {
      result.high = FP_NEGINF;
    } else {
      result.high = FP_POSINF;
    }
    result.low = 0;
    errno = ERANGE;
    return result;
  }

  /* if exponent sum is okay, add bias to create the power 2 exponent */
  n += 127;

  /* clear high byte to convert to 8 bit biased exponent value */
  n &= 0x00FF;

  /* shift biased exponent bits into floating point position for high word */
  n <<= 7;


  /* set the power of 2 value (always positive) */
  scale.high = n;
  /* all other bits except exponent bits are zero */
  scale.low  = 0;

  /* multiply number by 2^n */
  result = mulf(a, scale);

  /* if result overflowed, set the error flag */
  if (isInf(result))
    errno = ERANGE;

  return result;
}
