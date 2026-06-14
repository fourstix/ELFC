#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

#pragma             extrn _mulfp
#pragma             extrn Cerrno

/*
 * Return: a * b
 *         NaN for (+/- inf) * 0  or 0 + (+/- inf)
 */
float32_t mulf(float32_t a, float32_t b) {
  int r_high = 0;
  int r_low = 0;
  static float32_t result = {0, 0};

  /* handle special cases without calling routines */
  /* if either arg is Nan, return NaN */
  if (isNaN(a)) {
    errno = EDOM;
    return a;
  } else if (isNaN(b)) {
    errno = EDOM;
    return b;
    /* check for +/- infinity */
  } else if (isInf(a)) {
    /* check for inf * 0 */
    if (isZero(b)) {
      errno = EDOM;
      /* return NaN */
      result.high = FP_NAN;
      result.low = FP_NAN;
      return result;
    } else {
      /* multiplying by any negative flips sign of infinity */
      if (isNeg(b)) {
        a.high ^= FP_SIGN;
      }
        errno = ERANGE;
      /* return infinity */
      return a;
    }
  } else if (isInf(b)) {
    /* check for 0 * infinity */
    if (isZero(a)) {
      errno = EDOM;
      /* return NaN */
      result.high = FP_NAN;
      result.low = FP_NAN;
      return result;
    } else {
      /* multiplying by any negative flips sign of infinity */
      if (a.high & ~FP_SIGN) {
        b.high ^= FP_SIGN;
      }
      errno = ERANGE;
      /* return infinity */
      return b;
    }
    /* a and b are not NaN or infinity */
  } else if (isZero(a)) {
    return a;
  } else if (isZero(b)) {
    return b;
  }

  /* push arguments onto expression stack, swapping order */
  asm("            gosub s_fp2args      ; push arguments onto expression stack");
  /* Save Registers Used by ElfC */
  asm("            sex     r2           ; make sure x = SP");
  asm("            push    r9           ; save c registers");
  asm("            push    rb           ; save c registers");

  /* call function in library */
  asm("            call    _mulfp       ; call floating point library routine");
  /* restore C registers */
  asm("            pop     rb           ; restore C registers");
  asm("            pop     r9           ; restore C registers");

  /* get result from expression stack */
  asm("            gosub s_dpop32       ; pop result from expression stack");
  //BRKPT

  /* move arguments onto local variables */
  asm("            gosub s_lset16       ; set the high word return value");
  asm("              dw -2              ; in the local variable");
  asm("            copy  rf, ra         ; move low word into accumulator");
  asm("            gosub s_lset16       ; set the low word return value");
  asm("              dw -4              ; in the local variable");

  /* assign local variables to static result for return */
  result.high = r_high;
  result.low = r_low;

  /* set error if overflow occurred */
  if (isInf(result))
    errno = ERANGE;

  return result;
}
