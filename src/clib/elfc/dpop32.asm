#include      ../include/ops_c.inc

;---------------------------------------------------------
; dpop16 - pop 4-byte value from the expression stack
;   R7 - pointer to expression stack
;   RA - high byte of 32-bit value from expression stack
;   RF - low byte of 32-bit value from expression stack
; usage:   GOSUB epop16
; returns: RA:RF - 32-bit value from expression stack
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

              proc dpop32
            sex     r7  ; set X to ESP
            irx         ; move to TOS
            lda     r7  ; get low byte of low word from stack
            plo     rf  ; put in low word of result
            lda     r7  ; get high byte of low word from stack
            phi     rf  ; put in low word of result

            lda     r7  ; get low byte of high word from stack
            plo     ra  ; put in high word of result
            ldn     r7  ; get hi byte of high word from stack
            phi     ra  ; put in high word of result
            sex     r2  ; set X back to SP
            rsub        ; return from subroutine
              endp
