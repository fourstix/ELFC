#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

#pragma             extrn Cerrno
#pragma             extrn Cdivf
#pragma             extrn Ctruncf
#pragma             extrn Cmulf
#pragma             extrn Csubf
/*
 *   Return floating-point remainder of a/|b|
 *     Returns:
 *         NaN, if a or b is NaN
 *         NaN, if a is +/-Inf or b is 0
 *         0, if a is zero, or b is +/-Inf
 */
float32_t fmodf(float32_t a, float32_t b) {
  int    sgn = 0;
  static float32_t tmp = {0, 0};
  static float32_t result = {0, 0};
  /* handle special cases */
  /* if either arg is Nan, return NaN */
  if (isNaN(a)) {
    errno = EDOM;
    result = a;
    return result;
  } else if (isNaN(b)) {
    errno = EDOM;
    result = b;
    return result;
  } else if (isInf(a) || isZero(b)) {
    /* infinity numerator or zero denominator results in NaN */
    errno = EDOM;
    result.high = FP_NAN;
    result.low = FP_NAN;
    return result;
  } else if (isZero(a) || isInf(b)) {
    /* zero numerator or infinite denominator results in zero */
    result.high = 0;
    result.low = 0;
    return result;
  }

  /* a determines the sign of the result */
  if (isNeg(a)) {
    sgn = 1;
    /* use absolute value for calculation */
    a.high &= ~FP_SIGN;
  }

  /* absolute value of b */
  b.high &= ~FP_SIGN;

  /* get the quotient */
  tmp = divf(a, b);
  /* truncate quotion to a whole number */
  tmp = truncf(tmp);

  /* multiply divisor by whole number */
  tmp = mulf(tmp, b);

  /* subtract it from numerator to get remainder */
  result = subf(a, tmp);

  /* by definition, the result has same sign as a */
  if(sgn) {
    result.high |= FP_SIGN;
  }

  return result;
}
