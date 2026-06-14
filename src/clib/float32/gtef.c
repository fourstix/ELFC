#define _ELFCLIB_
#include <float32.h>
#include <errno.h>
#include <stdbool.h>

#pragma             extrn _gtefp
#pragma             extrn Cerrno

/*
 * Return: a >= b
 *         False if a = NaN or b = NaN
 *         False if a = +Inf and b = +Inf, or if a = -Inf and b = -Inf
 *         True if a = +Inf and b any other value
 *         False if a is -Inf and b is any other value
 *         False if a is any other value and b is +Inf
 *         True if a is any other value and b is -Inf
 */
int gtef(float32_t a, float32_t b) {
    int result = false;
    /* handle special cases first */
    /* NaN != NaN per IEEE 754 */
    if (isNaN(a) || isNaN(b) ) {
      errno = EDOM;
      return false;
    } else if (isInf(a) || isInf(b)) {
       /* +inf == +inf and -inf == -inf per IEEE 754 */
       if (a.high == b.high) return true;
       else if (a.high == FP_POSINF) return true;
       else if (a.high == FP_NEGINF) return false;
       else if (b.high == FP_POSINF) return false;
       else return true;
    }
    /* push arguments onto expression stack, swapping order */
    asm("            gosub s_fp2args      ; push arguments onto expression stack");

    /* Save Registers Used by ElfC */
    asm("            sex     r2           ; make sure x = SP");
    asm("            push    r9           ; save c registers");
    asm("            push    rb           ; save c registers");

    /* call function in library */
    asm("            call    _gtefp       ; call floating point library routine");

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
