#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

extern float32_t _fp_pi;

#pragma             extrn Cerrno
#pragma             extrn Cdivf
#pragma             extrn Catanf
#pragma             extrn Csubf
#pragma             extrn Cnegf

/* constant values used in routine */
#pragma .link .requires C_fp_const
#pragma             extrn C_fp_pi

/*
 * Inverse tangent function of a two floating point numbers
 *
 * Returns
 *   arctangent of a/b in the proper quardrant, in the range of -pi to +pi.
 *   NaN if x or y is NaN
 *   +/-pi/4, +/-3pi/4 if y is Infinity and x is Infinity
 *   pi or 0 if y is zero or x is Infinity
 *   +/-pi/2 if y is Infinity or x is zero
 */
float32_t atan2f(float32_t y, float32_t x) {
  int r_high = 0;
  int r_low = 0;
  int quad = 1;
  static float32_t result = {0, 0};

  /* Process special values */
  if (isNaN(y)) {
    errno = EDOM;
    return y;
  } else if (isNaN(x)) {
    errno = EDOM;
    return x;
  }

  /* +/-Inf is not considred a range error for this function */

  /* determine quadrant for result */
  if (isNeg(y)) {
    if (isNeg(x)) {
      quad = 3;
    } else {
      quad = 4;
    }
  } else if (isNeg(x)) {
    quad = 2;
  } else {
    quad = 1;
  }

  /* convert to absolute values */
  y.high &= ~FP_SIGN;
  x.high &= ~FP_SIGN;

  /* handle special cases first */
  if (isZero(y)) {
    result.high = 0;
    result.low  = 0;
  } else if (isInf(x)) {
    if isInf(y) {
      result.high = FP_4THPI_HI;
      result.low = FP_4THPI_LO;
    } else {
      result.high = 0;
      result.low  = 0;
    }
  } else if (isInf(y)) {
      result.high = FP_HALFPI_HI;
      result.low  = FP_HALFPI_LO;
  } else {
    /* calculate result from ratio */
    result = divf(y, x);
    /* result is in range 0 to pi/2 */
    result = atanf(result);
  }


  /* adjust result for quadrant */
  switch(quad) {
             /* quadrant 2 is pi - a */
    case 2:  result = subf(_fp_pi, result);
             break;
            /* quadrant 3 is a - pi */
    case 3:  result = subf(result, _fp_pi);
             break;
             /* quadrant 4 is -a */
    case 4:  result = negf(result);
             break;
             /* quadrant 1 needs no adjustment */
    default:
             break;
  }

  return result;
}
