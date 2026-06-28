#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

extern float32_t _fp_exp_max;
extern float32_t _fp_exp_min;
extern float32_t _fp_half;

#pragma             extrn _fpexp
#pragma             extrn Cerrno
#pragma             extrn Cltef
#pragma             extrn Cgtef
#pragma             extrn Cexpf
#pragma             extrn Cnegf
#pragma             extrn Csubf
#pragma             extrn Cmulf

/* constant value used in routine */
#pragma .link .requires C_fp_const
#pragma             extrn C_fp_exp_max
#pragma             extrn C_fp_exp_min
#pragma             extrn C_fp_half
/*
 * Hyperbolic Sine of a 32-bit floating point number
 *   Returns sinh(a)
 *           NaN of a is NaN
 *           +Inf if a is +Inf or a > ln(FLT_MAX) (88.72201)
 *           -Inf if a is -Inf or a < -ln(FLT_MAX) (-88.72201)
 *           0 if a is zero
 */
float32_t sinhf(float32_t a) {
  static float32_t e1;
  static float32_t e2;
  static float32_t result = {0, 0};

  /* Process special values */
  if (isNaN(a)) {
    /* out of domain -1 <= a <= 1 */
    errno = EDOM;
    result.high = FP_NAN;
    result.low = FP_NAN;
    return result;
  } else if (isZero(a)) {
    /* sinh(0) is 0 */
    result.high = 0;
    result.low = 0;
    return result;
  } else if (isNeg(a)) {
    if (ltef(a, _fp_exp_min)) {
      /* overflow: -Inf if exp(-a) < -FLT_MAX */
      errno = ERANGE;
      result.high = FP_NEGINF;
      result.low  = 0;
      return result;
    }
  } else if (gtef(a, _fp_exp_max)) {
    /* overflow: +Inf if exp(a) > FLT_MAX */
    errno = ERANGE;
    result.high = FP_POSINF;
    result.low  = 0;
    return result;
  }

  e1 = expf(a);
  a =  negf(a);
  e2 = expf(a);
  result = subf(e1, e2);
  result = mulf(result, _fp_half);

  return result;
}
