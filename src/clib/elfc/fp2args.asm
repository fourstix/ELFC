#include      ../include/ops_c.inc

;---------------------------------------------------------
; fp2args - push two 32-bit floating point arguments
;   onto expression stack for floating point routines
; registers used:
;   RB - stack frame pointer
;   R8 - pointer to arguments in stack frame
;   R7 - pointer to expression stack
; usage:   GOSUB fp2args
; returns: argument 1 at SOS and argument 2 at TOS
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

              proc fp2args
            ;---- push arguments onto expression stack, swapping order
            copy    rb, r8   ; copy first argument onto expression stack
            glo     r8       ; point r8 to top of first argument on ES"
            adi     $04      ; 1 32-bit arg = 4 bytes
            plo     r8
            ghi     r8       ; adjust hi byte
            adci    $00      ; propagate carry bit into hi byte
            phi     r8       ; r8 points to MSB of high word of first argument

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
            stxd             ; first argument is now on expression stack

            copy    rb, r8   ; copy second argument onto expression stack
            glo     r8       ; point r8 to top of arguments on ES
            adi     $08      ; 2 32-bit args = 8 bytes
            plo     r8
            ghi     r8       ; adjust hi byte
            adci    $00      ; propagate carry bit into hi byte
            phi     r8       ; r8 points to MSB of high word of second argument

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
            stxd             ; second argument is now on expression stack

            sex     r2       ; set X = SP
            rsub             ; return from subroutine
              endp
