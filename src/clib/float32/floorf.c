#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

extern float32_t _fp_one;

#pragma             extrn Cerrno
#pragma             extrn Cmodf
#pragma             extrn Csubf

/* constant values used in routine */
#pragma .link .requires C_fp_const
#pragma             extrn C_fp_one

/*
 * Return next integer below a floating point number
 * Return floor(a)
 *        NaN if number is NaN
 */
float32_t floorf(float32_t a) {
  int e = 0;
  float32_t    f_int;
  float32_t    frac;
  static float32_t result = {0, 0};

  /* handle special cases */
  if (isNaN(a)) {
    errno = EDOM;
    result = a;
    return result;
  } else if (isInf(a)) {
    errno = ERANGE;
    result = a;
    return result;
  } else if (isZero(a)) {
    result.high = 0;
    result.low  = 0;
    return result;
  }

  /* get biased exponent value from bits */
  e = (a.high & FP_EXP) >> 7;
  /* remove bias */
  e -= 127;
  /* if expoinent 23 or higher, a is a whole number */
  if (e > 22) {
    result = a;
    return result;
  } else if (e < 0) {
    /* fraction values in range of -1.0 < 0.0 < 1.0 */
    if (isNeg(a)) {
      /* for negative fractions, the floor is -1 */
      result = _fp_one;
      result.high |= FP_SIGN;
      return result;
    } else {
      /* for positive fractions, floor is 0 */
      result.high = 0;
      result.low = 0;
      return result;
    }
  }

  /* get the integer part and remainder */
  frac = modf(a, &f_int);

  /* if no remainder, the number is the floor */
  if (isZero(frac)) {
      result = f_int;
  } else if (isNeg(f_int)) {
    /* negative floor is one below */
    result = subf(f_int, _fp_one);
  } else {
    /* positive floor is truncated value */
    result = f_int;
  }
return result;
}
