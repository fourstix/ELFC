#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

#pragma             extrn _ftrunc
#pragma             extrn Csubf
#pragma             extrn Cerrno

/*
 * Return: a split into whole number and fractional parts.
 * Returns fractional part of a, and *ip is set to the
 *   whole number part.
 *   if a is NaN, returns NaN for fractional and whole number parts
 *   if a is +/-Inf returns +/-Inf for fractional and whole number parts
 */
float32_t modf(float32_t a, float32_t *ip) {
  int r_high = 0;
  int r_low = 0;
  static float32_t fint = {0, 0};
  static float32_t result = {0, 0};

  /* handle cases without calling routines */
  /* if either arg is Nan, return NaN */
  if (isNaN(a)) {
    errno = EDOM;
    /* set whole number to NaN */
    *ip = a;
    result = a;
    return result;
  } else if (isInf(a)) {
    errno = ERANGE;
    /* set whole number to infinity */
    *ip = a;
    /* set fraction to zero */
    result.high = 0;
    result.low = 0;
    return result;
  } else if (isZero(a)) {
    /* set whole number to zero */
    result.high = 0;
    result.low = 0;
    *ip = result;
    /* return fraction as zero */
    return result;
  }

  asm("            gosub s_fp1arg       ; push argument onto ES");

  /* Save Registers Used by ElfC */
  asm("            sex     r2           ; make sure x = SP");
  asm("            push    r9           ; save c registers");
  asm("            push    rb           ; save c registers");

  /* call function in library */
  asm("            call    _ftrunc        ; call floating point library routine");

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
  fint.high = r_high;
  fint.low = r_low;
  /* set integer pointer */
  *ip = fint;

  /* subtract integer part from real number */
  result = subf(a, fint);
  return result;
}
