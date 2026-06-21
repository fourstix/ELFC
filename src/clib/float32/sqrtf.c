#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

#pragma             extrn _fpsqrt
#pragma             extrn Cerrno

/*
 * Square root of a 32-bit floating point number
 *  Return square root of a
 *         NaN if number is NaN or negative
 */
float32_t sqrtf(float32_t a) {
  int r_high = 0;
  int r_low = 0;
  static float32_t result = {0, 0};

  /* Process special values */
  if (isNaN(a) || isNeg(a)) {
    errno = EDOM;
    result.low = FP_NAN;
    result.high = FP_NAN;
    return result;
  } else if (isInf(a)) {
    errno = ERANGE;
    result.high = FP_POSINF;
    result.low = 0;
    return result;
  } else if (isZero(a)) {
    result.low = 0;
    result.high = 0;
    return result;
  }
  /* Push angle value onto the expression stack */
  asm("            gosub s_fp1arg       ; push argument onto ES");
  /* Save Registers Used by ElfC */
  asm("            sex     r2           ; make sure x = SP");
  asm("            push    r9           ; save c registers");
  asm("            push    rb           ; save c registers");
  /* call function in library */
  asm("            call    _fpsqrt      ; call floating point library routine");
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
