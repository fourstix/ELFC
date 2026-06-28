#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

extern float32_t _fp_rad2deg;

#pragma             extrn Cmulf
#pragma             extrn Cerrno


/* constant value used in routine */
#pragma .link .requires C_fp_const
#pragma             extrn C_fp_rad2deg
/*
 * Convert an angle in radians into degrees.
 *  NaN if a is NaN or +/-Inf
 *  0 if a = 0
 *  Return a * (180/pi) degrees
 */
float32_t rad2degf(float32_t a) {
  int r_high = 0;
  int r_low = 0;
  static float32_t result = {0, 0};

  if (isNaN(a) || isInf(a)) {
    result.high = FP_NAN;
    result.low  = FP_NAN;
    return result;
  }
  if (isZero(a)) {
    result = a;
    return result;
  }

  /* Multiply a by 180/pi to get degrees */
  result = mulf(a, _fp_rad2deg);

  return result;
}
