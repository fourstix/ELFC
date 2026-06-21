#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

#pragma             extrn _subfp
#pragma             extrn Cerrno

/*
 * Return: a - b
 *         NaN for (+inf) - (+inf) or (-inf) - (-inf)
 */
float32_t subf(float32_t a, float32_t b) {
  int r_high = 0;
  int r_low = 0;
  static float32_t result = {0, 0};

  /* handle cases without calling routines */
  /* if either arg is Nan, return NaN */
  if (isNaN(a)) {
    errno = EDOM;
    return a;
  } else if (isNaN(b)) {
    errno = EDOM;
    return b;
    /* check for +/- infinity */
  } else if (isInf(a)) {
    /* check for 2 inf values that the same sign */
    if (a.high == b.high) {
      errno = EDOM;
      /* return NaN */
      result.high = FP_NAN;
      result.low = FP_NAN;
      return result;
    } else {
      errno = ERANGE;
      /* otherwise return infinity */
      return a;
    }
    /* check for subtracting +/- infinity from any number */
  } else if (isInf(b)) {
    errno = ERANGE;
    /* flip sign bit of inf value and return */
    b.high ^= FP_SIGN;
    /* a can't be inf here, so return b as infintity */
    return b;
  } else if (isZero(b)) {
    /* anything minus zero is itself */
    return a;
  }

  /* push arguments onto expression stack, swapping order */
  asm("            gosub s_fp2args      ; push arguments onto expression stack");

  /* Save Registers Used by ElfC */
  asm("            sex     r2           ; make sure x = SP");
  asm("            push    r9           ; save c registers");
  asm("            push    rb           ; save c registers");

  /* call function in library */
  asm("            call    _subfp       ; call floating point library routine");

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
