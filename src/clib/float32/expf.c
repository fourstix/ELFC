#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

extern float32_t _fp_exp_max;
extern float32_t _fp_exp_min;
extern float32_t _fp_epsilon;
extern float32_t _fp_ln2;

#pragma             extrn _fpexp
#pragma             extrn Cerrno
#pragma             extrn Cgtef
#pragma             extrn Cltef
#pragma             extrn Czflushf
#pragma             extrn Cdivf
#pragma             extrn Cmodf
#pragma             extrn Cmulf
#pragma             extrn Cftoi
#pragma             extrn Cldexpf

/* constant value used in routine */
#pragma .link .requires C_fp_const
#pragma             extrn C_fp_exp_max
#pragma             extrn C_fp_exp_min
#pragma             extrn C_fp_epsilon
#pragma             extrn C_fp_ln2

/*
 * Natural logarithm base e raiased to a 32-bit floating point number
 *   Returns exp(a)
 *           NaN of a is NaN
 *           zero if a is -Inf
 *           +Inf if a is +Inf
 *           +Inf if a > ln(FLT_MAX) (88.72201)
 *           one if a is zero
 */
float32_t expf(float32_t a) {
  int r_high = 0;
  int r_low = 0;
  float32_t r;
  float32_t tmp;
  int k = 0;
  static float32_t result = {0, 0};

  /* Process special values */
  if (isNaN(a)) {
    /* out of domain -1 <= a <= 1 */
    errno = EDOM;
    result.high = FP_NAN;
    result.low = FP_NAN;
    return result;
  } else if (isInf(a)) {
    if (isNeg(a)) {
      /* exp(-Inf) = 0 */
      result.high = 0;
      result.low  = 0;
      return result;
    } else {
      errno = ERANGE;
      /* exp(+Inf) = +Inf */
      result = a;
      return result;
    }
  } else if (gtef(a, _fp_exp_max)) {
    /* overflow: +Inf if exp(a) > FLT_MAX */
    errno = ERANGE;
    result.high = FP_POSINF;
    result.low  = 0;
    return result;
  } else if (ltef(a, _fp_exp_min)) {
    /* underflow: 0 if exp(a) < FLT_MIN */
    result.high = 0;
    result.low  = 0;
    return result;
  }

  /* flush very small values to zero */
  a = zflushf(a, _fp_epsilon);

  if (isZero(a)) {
    /* exp(0) is 1 */
    result.high = FP_ONE_HI;
    result.low =  FP_ONE_LO;
    return result;
  }

  /*
   *  To cover the enter floating point range we use the lexpf function.
   *
   *  Given exp(x) = 2^(x / ln2)  (change of base formula)
   *  let int k = trunc(x/ln2) and float r = frac(x/ln2)*ln2
   *  Then x = r + ln2*k and exp(x) = exp(r + ln2*k)
   *  exp(r + ln2*k) = exp(r)*exp(ln2)^k = exp(r)*2^k
   *  let m = exp(r) to get exp(x) = m*2^k = ldexpf(m, k)
   */


  /* divide x by ln 2 */
  tmp = divf(a, _fp_ln2);

  /* split into whole number and remainder */
  r = modf(tmp, &tmp);

  /* convert whole number part to int */
  k = ftoi(tmp);

  /* convert fraction back into remainder */
  r = mulf(r, _fp_ln2);

  /* calculate m = exp(r) */
  /* Push remainder value onto the expression stack */
  asm("            gosub s_lpush16       ; push high word of mantissa onto ES");
  asm("              dw -6               ; in the local variable");
  asm("            gosub s_lpush16       ; push low word of mantissa onto ES");
  asm("              dw -8               ; in the local variable");
  /* Save Registers Used by ElfC */
  asm("            sex     r2           ; make sure x = SP");
  asm("            push    r9           ; save c registers");
  asm("            push    rb           ; save c registers");
  /* call function in library */
  asm("            call    _fpexp       ; call floating point library routine");
  /* restore ElfC registers */
  asm("            pop     rb           ; restore C registers");
  asm("            pop     r9           ; restore C registers");
  /* get result from expression stack */
  asm("            gosub s_dpop32       ; pop result from expression stack");
  /* move arguments onto local variables */
  asm("            gosub s_lset16       ; set the high word return value");
  asm("              dw -2              ; in the local variable");
  asm("            copy  rf, ra         ; move low word into accumulator");
  asm("            gosub s_lset16       ; set the low word return value");
  asm("              dw -4              ; in the local variable");

  /* assign local variables to static result for remainder */
  result.high = r_high;
  result.low = r_low;

  /* convert back to float number using m*2^k */
  result = ldexpf(result, k);

  return result;
}
