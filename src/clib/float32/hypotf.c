#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

#pragma             extrn Cmulf
#pragma             extrn Caddf
#pragma             extrn Csqrtf
#pragma             extrn Cerrno

/*
 * Calculate the Square root of a squared + b squared
 * Returns:
 *        NaN if a or b is NaN
 *        +Inf if a or b is +/- Inf
 *        hypotenucse = Sqrt(a*a + b*b)
 */
float32_t hypotf(float32_t a, float32_t b) {
  float32_t a2, b2;
  static float32_t result = {0, 0};

  /* handle cases without calling routines */
  /* if either arg is Nan, return NaN */
  if (isNaN(a)) {
    errno = EDOM;
    result = a;
    return result;
  } else if (isNaN(b)) {
    errno = EDOM;
    result = b;
    return result;
    /* check for +/- infinity */
  } else if (isInf(a) || isInf(b)) {
    /* set error if overflow occurred */
    errno = ERANGE;
    result.high = FP_POSINF;
    result.low = 0;
    return result;
  }

  /* calculate the hypotenuse */
  a2 = mulf(a, a);
  b2 = mulf(b, b);
  result = addf(a2, b2);
  result = sqrtf(result);

  /* if result overflowed, set the error flag */
  if (isInf(result))
    errno = ERANGE;

  return result;
}
