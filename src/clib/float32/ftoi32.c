#define _ELFCLIB_
#include <float32.h>
#include <errno.h>

#pragma             extrn _ftoi32
#pragma             extrn Cerrno

/*
 * Return: a as long integer value
 */
int32_t ftoi32(float32_t a) {
  int r_high = 0;
  int r_low = 0;
  static int32_t result = {0, 0};

  /* handle cases without calling routines */
  /* if either arg is Nan, return NaN */
  if (isNaN(a)) {
    errno = EDOM;
  } else if (isInf(a)) {
    errno = ERANGE;
  }

  asm("            gosub s_fp1arg       ; push argument onto ES");
  /* Save Registers Used by ElfC */
  asm("            sex     r2           ; make sure x = SP");
  asm("            push    r9           ; save c registers");
  asm("            push    rb           ; save c registers");
  /* call function in library */
  asm("            call    _ftoi32      ; call floating point library routine");
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
