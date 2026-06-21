#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

#pragma             extrn _fpacos
#pragma             extrn Cerrno
#pragma             extrn Cgtf
#pragma             extrn Cltf
/*
 * Inverse cosine function of a 32-bit floating point number
 *   Returns arcccosine of a
 *           0 to pi, for  1 => a => -1
 *           NaN of a is NaN
 *           NaN if a < -1 or a > +1
 */
float32_t acosf(float32_t a) {
  int r_high = 0;
  int r_low = 0;
  static float32_t result = {0, 0};
  static float32_t fp_one    = {FP_ONE_LO, FP_ONE_HI};
  static float32_t fp_negone = {FP_NEGONE_LO, FP_NEGONE_HI};

  /* Process special values */
  if (isNaN(a) || isInf(a) || gtf(a, fp_one) || ltf(a, fp_negone)) {
    /* out of domain -1 <= a <= 1 */
    errno = EDOM;
    result.low = FP_NAN;
    result.high = FP_NAN;
    return result;
  } else if (isZero(a)) {
    /* 0 is pi/2 */
    result.low = FP_HALFPI_LO;
    result.high = FP_HALFPI_HI;
    return result;
  } else if (FP_ONE_HI == (a.high & ~FP_SIGN)) {
    /* -1 is pi, +1 is 0 */
    if (isNeg(a)) {
      result.high = FP_PI_HI;
      result.low = FP_PI_LO;
    } else {
      result.high = 0;
      result.low = 0;
    }
    return result;
  }

  /* Push angle value onto the expression stack */
  asm("            gosub s_fp1arg       ; push argument onto ES");
  /* Save Registers Used by ElfC */
  asm("            sex     r2           ; make sure x = SP");
  asm("            push    r9           ; save c registers");
  asm("            push    rb           ; save c registers");
  /* call function in library */
  asm("            call    _fpacos      ; call floating point library routine");
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
