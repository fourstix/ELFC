#include      ../include/ops_c.inc

;---------------------------------------------------------
; dpop16 - pop 2-byte value expression stack 
;   R7 - pointer to expression stack    
;   RA - data value from expression stack 
; usage:   GOSUB epop16
; returns: RA - value from expression stack
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

              proc dpop16
            sex     r7  ; set X to ESP
            irx         ; move to TOS 
            lda     r7  ; get low byte from stack
            plo     ra
            ldn     r7  ; get hi byte from stack
            phi     ra
            sex     r2  ; set X back to SP
            rsub        ; return from subroutine
              endp 
