#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

#pragma             extrn Cerrno
#pragma             extrn Csubf
#pragma             extrn Caddf
#pragma             extrn Ctruncf

/*
 * Return a split into a normalized fraction and a power of two.
 *   Returns normalized fractional part of a, and an exponent pointer
 *    to the exponent value for two, such that 2^exp * fract = a.
 *
 *    If a is zero, both parts are set to zero.
 *    If a is NaN, returns NaN and *exp is set to 255
 *    If a is +/-Inf, returns +/-Inf and *exp is set to 255
 */
float32_t frexpf(float32_t a, int *exp) {
  int e = 0;
  static float32_t nfrac = {0, 0};

  if (isNaN(a)) {
    errno = EDOM;
    *exp = 255;
    nfrac = a;
    return nfrac;
  } else if(isInf(a)) {
    errno = ERANGE;
    *exp  = 255;
    nfrac = a;
    return nfrac;
  } else if (isZero(a)) {
    *exp = 0;
    nfrac.high = 0;
    nfrac.low  = 0;
    return nfrac;
  }

  /* get biased exponent value from bits */
  e = (a.high & FP_EXP) >> 7;
  /* remove bias (127), ading one to normalize */
  e -= 126;

  /* set exponent value */
  *exp = e;

  /* set the fractional value to a */
  nfrac = a;
  /* clear exponent bits in floating point number */
  nfrac.high &= 0x807f;
  /* set exponent to biased -1 (126) to normalize it */
  nfrac.high |= 0x3f00;

  return nfrac;
}
