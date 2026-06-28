#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

extern float32_t _fp_exp_max;
extern float32_t _fp_exp_min;

#pragma             extrn _fpexp
#pragma             extrn Cerrno
#pragma             extrn Cltef
#pragma             extrn Cgtef
#pragma             extrn Cexpf
#pragma             extrn Cnegf
#pragma             extrn Csubf
#pragma             extrn Caddf
#pragma             extrn Cdivf

/* constant value used in routine */
#pragma .link .requires C_fp_const
#pragma             extrn C_fp_exp_max
#pragma             extrn C_fp_exp_min


/*
 * Hyperbolic Tangent of a 32-bit floating point number
 *   Returns sinh(a)
 *           NaN of a is NaN
 *            1 if a is +Inf or a > ln(FLT_MAX) (88.72201)
 *           -1 if a is -Inf or a < -ln(FLT_MAX) (-88.72201)
 *            0 if  a is zero
 */
float32_t tanhf(float32_t a) {
  static float32_t e1;   //also used as denominator value
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
    /* sinh(0) is 0.5 */
    result.high = 0;
    result.low =  0;
    return result;
  } else if (isNeg(a)) {
    if (ltef(a, _fp_exp_min)) {
      /* -1 if -Inf if exp(-a) < -FLT_MAX */
      result.high = FP_ONE_HI | FP_SIGN;
      result.low  = FP_ONE_LO;
      return result;
    }
  } else if (gtef(a, _fp_exp_max)) {
    /* +1 if +Inf if exp(a) > FLT_MAX */
    result.high = FP_ONE_HI;
    result.low  = FP_ONE_LO;
    return result;
  }

  e1 = expf(a);
  a =  negf(a);
  e2 = expf(a);
  result = subf(e1, e2);
  e1 =  addf(e1, e2);
  result = divf(result, e1);

  return result;
}
