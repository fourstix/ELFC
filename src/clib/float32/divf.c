#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

#pragma             extrn _divfp
#pragma             extrn Cerrno

/*
 * Return a / b
 *  NaN if a = 0 and b = 0
 *  NaN if a = +/- inf and b = +/- inf
 */
float32_t divf(float32_t a, float32_t b) {
  int r_high = 0;
  int r_low = 0;
  static float32_t result = {0, 0};

  /* handle special cases without calling routines */

  /* if either arg is Nan, return NaN */
  if (isNaN(a)) {
    errno = EDOM;
    result = a;
    return result;
  } else if (isNaN(b)) {
    errno = EDOM;
    result = b;
    return result;
    /* check for zero divided by something */
  } else if (isZero(a)) {
    if (isZero(b)) {
      errno = EDOM;
      /* return NaN */
      result.high = FP_NAN;
      result.low  = FP_NAN;
      return result;
    } else {
      result = a;
      return result;
    }
  } else if (isInf(a)) {
     if (isInf(b)) {
       errno = EDOM;
       /* return NaN */
       result.high = FP_NAN;
       result.low  = FP_NAN;
       return result;
    } else {
      result = a;
      /* dividing by any negative flips sign of infinity */
      if (isNeg(b)) {
        result.high ^= FP_SIGN;
      }
      errno = ERANGE;
      return result;
    }
    /* anything divided by inf is zero */
  } else if (isInf(b)) {
    result.high = 0;
    result.low = 0;
    return result;
   /* divide by zero produces +/- infinity */
  } else if (isZero(b)) {
      errno = ERANGE;
    //grw - check sign bit of a +/- infinity
    if (a.high & FP_SIGN) {
      /* return -inf */
      result.high = FP_NEGINF;
      result.low  = 0;
      return result;
    } else {
      /* return +inf */
      result.high = FP_POSINF;
      result.low  = 0;
      return result;
    }
  }

  /* push arguments onto expression stack, swapping order */
  asm("            gosub s_fp2args      ; push arguments onto expression stack");
  /* Save Registers Used by ElfC */
  asm("            sex     r2           ; make sure x = SP");
  asm("            push    r9           ; save c registers");
  asm("            push    rb           ; save c registers");

  /* call function in library */
  asm("            call    _divfp       ; call floating point library routine");
  /* restore C registers */
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

  /* assign local variables to static result for return */
  result.high = r_high;
  result.low  = r_low;

  /* set error if overflow occurred */
  if (isInf(result))
    errno = ERANGE;

  return result;
}
