#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

#pragma             extrn Cerrno
#pragma             extrn _ftrunc
#pragma             extrn Csubf
/*
 * Return: a as float integer value
 */
float32_t fracf(float32_t a) {
  int r_high = 0;
  int r_low = 0;
  static float32_t fint  = {0, 0};
  static float32_t result = {0, 0};

  /* handle special cases */
  /* if arg is Nan, return NaN */
  if (isNaN(a)) {
    errno = EDOM;
    result = a;
    return result;
  } else if (isInf(a)) {
    errno = ERANGE;
    result = a;
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

  /* subtract integer part from real number */
  result = subf(a, fint);
  return result;
}
