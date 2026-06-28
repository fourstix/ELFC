#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

extern float32_t _fp_ln2;

#pragma             extrn _fpln
#pragma             extrn Cerrno
#pragma             extrn Cfrexpf
#pragma             extrn Citof
#pragma             extrn Cmulf
#pragma             extrn Caddf

#pragma .link .requires C_fp_const
#pragma             extrn C_fp_ln2
/*
 * Natural logarithm of a 32-bit floating point number
 *   Returns log(a)
 *          -Inf if a = 0
 *           NaN of a is NaN or a < 0
 *           +Inf if a is +Inf
 */
float32_t logf(float32_t a) {
  int r_high = 0;
  int r_low = 0;
  float32_t tmp;
  int k = 0;
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

/*
 *  Convert into mantissa and int 2^k
 *  ln(a)  = ln(m) + k * ln(2)
 */

  tmp = frexpf(a, &k);

  /* Push 32-bit mantissa onto the expression stack */
  //asm("            gosub s_fp1arg       ; push argument onto ES");
  asm("            gosub s_lpush16       ; push high word of mantissa onto ES");
  asm("              dw -6               ; in the local variable");
  asm("            gosub s_lpush16       ; push low word of mantissa onto ES");
  asm("              dw -8               ; in the local variable");
  /* Save Registers Used by ElfC */
  asm("            sex     r2           ; make sure x = SP");
  asm("            push    r9           ; save c registers");
  asm("            push    rb           ; save c registers");

  /* call function in library */
  asm("            call    _fpln      ; call floating point library routine");

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

  /* assign local variables to static result for calculation */
  result.high = r_high;
  result.low = r_low;

  tmp = itof(k);
  tmp = mulf(tmp, _fp_ln2);
  result = addf(result, tmp);
  return result;
}
