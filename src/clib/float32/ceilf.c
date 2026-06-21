#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

#pragma             extrn Cerrno
#pragma             extrn Cmodf
#pragma             extrn Caddf

/*
 * Return next integer above a floating point number
 * Return ceil(a)
 *        NaN if number is NaN or +/-Infiinty
 */
float32_t ceilf(float32_t a) {
  int          e = 0;
  float32_t    c_int;
  float32_t    frac;
  static float32_t result = {0, 0};
  static float32_t fp_one = {FP_ONE_LO, FP_ONE_HI};

  /* handle special cases */
  if (isNaN(a)) {
    errno = EDOM;
    return a;
  } else if (isInf(a)) {
    errno = ERANGE;
    return a;
  } else if (isZero(a)) {
    result.high = 0;
    result.low  = 0;
    return result;
  }
  /* get biased exponent value from bits */
  e = (a.high & FP_EXP) >> 7;
  /* remove bias */
  e -= 127;
  /* debugging */
  if (e > 22) {
    /* if expoinent 23 or higher, a is a whole number */
    return a;
  } else if (e < 0) {
    /* fraction values in range of -1.0 < 0.0 < 1.0 */
    if (isNeg(a)) {
      /* for negative fractions, ceiling is 0 */
      result.high = 0;
      result.low = 0;
      return result;
    } else {
      /* for positive fractions, ceiling is 1 */
      result = fp_one;
      return result;
    }
  }
  /* get the integer part and fractional part of number */
  frac = modf(a, &c_int);

  /* if no remainder, the number is the ceiling */
  if (isZero(frac)) {
      result = c_int;
  } else if (isNeg(c_int)) {
    /* negative ceiling is truncated value */
    result = c_int;
  } else {
    /* positive ceiling is one above */
    result = addf(c_int, fp_one);
  }

return result;
}
