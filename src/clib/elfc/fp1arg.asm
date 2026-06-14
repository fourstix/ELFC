#include      ../include/ops_c.inc

;---------------------------------------------------------
; fp1arg - push a 32-bit floating point arguments
;   onto expression stack for floating point routines
; registers used:
;   RB - stack frame pointer
;   R8 - pointer to arguments in stack frame
;   R7 - pointer to expression stack
; usage:   GOSUB fp1arg
; returns: argument 1 at TOS of expression stack
;   R7 points to the arguments on the expression stack
;---------------------------------------------------------

;*********************************************************
;  This subroutine should only be invoked via the GOSUB
;  opcode and not through the SCRT CALL opcode.
;  It should return via the RSUB opcode, and not the
;  SCRT RTN or RETURN opcodes.
;*********************************************************
; Subroutine Registers:
;  R9 is the Subroutine Instruction Pointer
;  R3 is the argument pointer and return vector for RSUB
;  R2 is the system stack pointer (SP)
;*********************************************************

              proc fp1arg
            ;---- push arguments onto expression stack, swapping order
            copy    rb, r8   ; copy argument onto expression stack
            inc     r8       ; point r8 to top of argument on ES
            inc     r8
            inc     r8
            inc     r8       ; r8 now points to top of argument on ES

            sex     r7       ; set x to expression stack
            ldn     r8       ; get MSB of high word
            stxd             ; push byte onto expression stack
            dec     r8       ; move to next value
            ldn     r8       ; get LSB of high word
            stxd             ; push byte onto expression stack
            dec     r8       ; move to next value
            ldn     r8       ; get MSB of low word
            stxd
            dec     r8
            ldn     r8       ; get LSB of low word
            stxd             ; argument is now on expression stack

            rsub             ; return from subroutine
              endp
