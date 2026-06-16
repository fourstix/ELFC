#define _ELFCLIB_
#include <float32.h>
#include <errno.h>
#include <stdbool.h>

#pragma             extrn _eqfp
#pragma             extrn Cerrno

/*
 * Return: a == b
 *         False if a = NaN or b = NaN
 *         True if a = +Inf and b = +Inf, or if a = -Inf and b = -Inf
 *         False if a = +Inf and b = -Inf, or if a = -Inf and b = +Inf
 */
int eqf(float32_t a, float32_t b) {
    int result = false;
    /* handle special cases first */
    if (isNaN(a) || isNaN(b) ) {
      /* NaN != NaN per IEEE 754 */
      errno = EDOM;
      return false;
    } else if (isInf(a) || isInf(b)) {
       /* +inf == +inf and -inf == -inf per IEEE 754 */
       return (a.high == b.high);
    } else if (isZero(a) && isZero(b)) {
      /* IEEE 754 specifies equals comparison done without sign bit */
      return true;
    }
    /* push arguments onto expression stack, swapping order */
    asm("            gosub s_fp2args      ; push arguments onto expression stack");

    /* Save Registers Used by ElfC */
    asm("            sex     r2           ; make sure x = SP");
    asm("            push    r9           ; save c registers");
    asm("            push    rb           ; save c registers");

    /* call function in library */
    asm("            call    _eqfp       ; call floating point library routine");

    /* restore C registers */
    asm("            pop     rb           ; restore C registers");
    asm("            pop     r9           ; restore C registers");

    /* get result from expression stack */
    asm("            gosub s_dpop32       ; pop result from expression stack");

    /* move high word of result onto local variable */
    asm("            gosub s_lset16       ; set the high word return value");
    asm("              dw -2              ; in the local variable");

    return result;
}
