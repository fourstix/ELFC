#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

extern float32_t _fp_deg2rad;


#pragma             extrn Cmulf
#pragma             extrn Cerrno

/* constant value used in routine */
#pragma .link .requires C_fp_const
#pragma             extrn C_fp_deg2rad
/*
 * Convert an angle in degrees into radians.
 *  NaN if a is NaN or +/-Inf
 *  0 if a = 0
 *  Return a * (pi/180) radians
 */
float32_t deg2radf(float32_t a) {
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

  /* Multiply a by pi/180 to get radians */
  result = mulf(a, _fp_deg2rad);

  return result;
}
