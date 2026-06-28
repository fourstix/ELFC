#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

extern float32_t _fp_one;

#pragma             extrn _fppow
#pragma             extrn Cerrno
#pragma             extrn Ceqf

/* constant value used in routine */
#pragma .link .requires C_fp_const
#pragma             extrn C_fp_one

/*
 * Raise a 32-bit floating point number b to the power p
 * Returns: b ^ p
 *           NaN of b or p is NaN
 *           NaN if b is negative
 *           NaN if either b or p is +/-Inf
 *           NaN if b is 0 and p is 0 or negative
 *           0 if b is 0 and p is any positive number
 *           1 if p is 0 or if b is 1
 */
float32_t powf(float32_t b, float32_t p) {
  int r_high = 0;
  int r_low = 0;
  static float32_t result = {0, 0};

  /* Process special values */
  if (isNaN(b) || isNaN(p) || isNeg(b) || isInf(b) || isInf(p)) {
    /* out of domain if b < 0 or if either b or p is +/-Inf */
    errno = EDOM;
    result.low = FP_NAN;
    result.high = FP_NAN;
    return result;
  } else if (isZero(b)) {
    /* out of domain if b = 0 and p is 0 or negative */
    if (isZero(p) || isNeg(p)) {
      errno = EDOM;
      result.low = FP_NAN;
      result.high = FP_NAN;
      return result;
    } else {
      /* otherwise zero to any positive power is zero */
      result.low = 0;
      result.high = 0;
      return result;
    }
  } else if (isZero(p) || (eqf(b, _fp_one))) {
    /* any number raised to the zero power is one */
    /* or one raised to any power is one */
    result.low = FP_ONE_LO;
    result.high = FP_ONE_HI;
    return result;
  }

  /* Push angle value onto the expression stack */
  asm("            gosub s_fp2args      ; push arguments onto ES");
  /* Save Registers Used by ElfC */
  asm("            sex     r2           ; make sure x = SP");
  asm("            push    r9           ; save c registers");
  asm("            push    rb           ; save c registers");
  /* call function in library */
  asm("            call    _fppow       ; call floating point library routine");
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

  /* assign local variables to static result for return */
  result.high = r_high;
  result.low = r_low;

  return result;
}
