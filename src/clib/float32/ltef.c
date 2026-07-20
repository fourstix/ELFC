#define _ELFCLIB_
#include <float32.h>
#include <errno.h>
#include <stdbool.h>

#pragma             extrn _subfp
#pragma             extrn Cerrno

/*
 * Return: a <= b
 *         False if a = NaN or b = NaN
 *         True if a = +Inf and b = +Inf, or if a = -Inf and b = -Inf
 *         False if a = +Inf and b any other value
 *         True if a is -Inf and b is any other value
 *         True if a is any other value and b is +Inf
 *         False if a is any other value and b is -Inf
 */
int ltef(float32_t a, float32_t b) {
    int result = false;
    /* handle special cases first */
    /* NaN != NaN per IEEE 754 */
    if (isNaN(a) || isNaN(b) ) {
      errno = EDOM;
      return false;
    } else if (isInf(a) || isInf(b)) {
       /* +inf == +inf and -inf == -inf per IEEE 754 */
       if (a.high == b.high) return true;
       else if (a.high == FP_POSINF) return false;
       else if (a.high == FP_NEGINF) return true;
       else if (b.high == FP_POSINF) return true;
       else return false;
    }
    /* push arguments onto expression stack, swapping order */
    asm("            gosub s_fp2args      ; push arguments onto expression stack");

    /* Save Registers Used by ElfC */
    asm("            sex     r2           ; make sure x = SP");
    asm("            push    r9           ; save c registers");
    asm("            push    rb           ; save c registers");

    /* call function in library */
    //asm("            call    _ltefp       ; call floating point library routine");
    asm("            call    _subfp       ; call floating point library routine");
    asm("            sex     r7           ; set x = ESP");
    asm("            irx                  ; check stack for zero");
    asm("            ldxa                 ; get the first byte from stack");
    asm("            or                   ; OR all 4 bytes together");
    asm("            ldxa                 ");
    asm("            or                 ");
    asm("            ldxa                 ");
    asm("            or                 ");
    asm("            ldx                 ; OR last byte");
    asm("            or                  ; if all bytes are zero");
    asm("            lbz     lttrue      ; if equal, load true");
    asm("            ldn     r7          ; check sign bit of result");
    asm("            shl                 ; put sign bit in DF");
    asm("            lbdf    lttrue      ; if sign bit is set then true");
    asm("            ldi     000h        ; else load false value");
    asm("            lskp                ; jump over next two bytes");
    asm("lttrue:     ldi 0FFh            ; load true value");
    asm("            stxd                ; push value onto ESP ");
    asm("            stxd                ; 32-bit value ");
    asm("            stxd                 ");
    asm("            stxd                 ");
    asm("            sex     r2          ; set x back to SP");


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
