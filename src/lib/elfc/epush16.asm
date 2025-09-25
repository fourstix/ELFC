#include      ../include/ops_c.inc

;---------------------------------------------------------
; epush16 - push 2-byte constant onto expression stack 
; R7 - pointer to expression stack    
; Usage:   GOSUB epush16
;            dw $4321
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

              proc epush16
            sex     r7     ; set X to ESP
            lda     r3     ; get MSB from argument
            stxd
            lda     r3     ; get LSB from argument
            stxd
            sex     r2     ; set X back to SP
            rsub           ; return from subroutine
              endp 
