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
#pragma             extrn Caddf
#pragma             extrn Cmulf


/* constant value used in routine */
#pragma .link .requires C_fp_const
#pragma             extrn C_fp_exp_max
#pragma             extrn C_fp_exp_min
#pragma             extrn C_fp_half

/*
 * Hyperbolic Cosine of a 32-bit floating point number
 *   Returns sinh(a)
 *           NaN of a is NaN
 *           +Inf if a is +/-Inf or |a| > ln(FLT_MAX) (88.72201)
 *           1 if  a is zero
 */
float32_t coshf(float32_t a) {
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
    /* cosh(0) is 1 */
    result.high = FP_ONE_HI;
    result.low =  FP_ONE_LO;
    return result;
  } else if (isNeg(a)) {
    if (ltef(a, _fp_exp_min)) {
      /* overflow: -Inf if exp(-a) < -FLT_MAX */
      errno = ERANGE;
      result.high = FP_POSINF;
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
  result = addf(e1, e2);
  result = mulf(result, _fp_half);

  return result;
}
