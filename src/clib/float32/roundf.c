#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

#pragma             extrn Cerrno
#pragma             extrn Csubf
#pragma             extrn Caddf
#pragma             extrn Ctruncf

/*
 * Return the integer nearest a floating point number
 * Return ceil(a)
 *        NaN if number is NaN or +/-Infiinty
 */
float32_t roundf(float32_t a) {
  int          e = 0;
  float32_t    rnd;
  static float32_t result = {0, 0};
  static float32_t fp_half = {FP_DOT5_LO, FP_DOT5_HI};

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
  if (e > 22) {
    /* if expoinent 23 or higher, a is a whole number */
    return a;
  }

  if (isNeg(a)) {
    /* round negative numbers down */
    rnd = subf(a, fp_half);
  } else {
    /* round positive numbers up */
    rnd = addf(a, fp_half);
  }

  /* truncate to nearest number */
  result = truncf(rnd);

return result;
}
