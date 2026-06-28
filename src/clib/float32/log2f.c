#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

extern float32_t _fp_ln2;

#pragma             extrn Cerrno
#pragma             extrn Clogf
#pragma             extrn Cdivf

/* constant value used in routine */
#pragma .link .requires C_fp_const
#pragma             extrn C_fp_ln2

/*
 * Base 2 logarithm of a 32-bit floating point number
 *   Returns Basae 2 log of a
 *          -Inf if a = 0
 *           NaN of a is NaN or a < 0
 *           +Inf if a is +Inf
 */
float32_t log2f(float32_t a) {
  static float32_t result = {0, 0};

  /* Process special values */
  if (isNaN(a) || isNeg(a)) {
    /* out of domain -1 <= a <= 1 */
    errno = EDOM;
    result.high = FP_NAN;
    result.low = FP_NAN;
    return result;
  } else if (isZero(a)) {
    /* ln(0) is -Inf */
    errno = ERANGE;
    result.high = FP_NEGINF;
    result.low = 0;
    return result;
  } else if (isInf(a)){
    /* ln(+Inf) = +Inf */
    errno = ERANGE;
    result = a;
    return result;
  }

  /* first take the natural logarithm */
  result = logf(a);
  /* then divide by natural log of base */
  result = divf(result, _fp_ln2);

  return result;
}
