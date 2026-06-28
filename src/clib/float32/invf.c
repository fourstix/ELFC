#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

extern float32_t _fp_one;

#pragma             extrn Cdivf
#pragma             extrn Cerrno

/* constant values used in routine */
#pragma .link .requires C_fp_const
#pragma             extrn C_fp_one

/*
 * Return 1 / b
 *  NaN if a is NaN
 *  +Inf if a = 0
 *  0 if a = +/- Inf
 *
 */
float32_t invf(float32_t a) {
  int r_high = 0;
  int r_low = 0;
  static float32_t result = {0, 0};

  /* handle special cases without calling routines */

  /* if either arg is Nan, return NaN */
  if (isNaN(a)) {
    errno = EDOM;
    result = a;
    return result;
  } else if (isInf(a)) {
    result.high = 0;
    result.low = 0;
    return result;
   /* divide by zero produces +/- infinity */
  } else if (isZero(a)) {
    errno = ERANGE;
    /* return +inf */
    result.high = FP_POSINF;
    result.low = 0;
    return result;
  }

  /* take the recipricol of a */
  result = divf(_fp_one, a);

  return result;
}
