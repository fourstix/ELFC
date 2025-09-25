#include      ../include/ops_c.inc

;---------------------------------------------------------
; vpush8 - push a global or static char type variable 
;   onto expression stack 
; registers used:
;   R8 - pointr to char variable in memory 
;   R7 - pointer to expression stack 
; usage:   GOSUB vpush8
;            dw vaddr 
; returns: char value on TOS
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

              proc vpush8
            lda     r3  ; set up pointer to char variable
            phi     r8
            lda     r3
            plo     r8
            sex     r7        
            ldi     0   ; promote to unsigned 16 bit value
            stxd        ; save padding byte in MSB
            lda     r8  ; get char value
            stxd        ; save as LSB on stack
            sex     r2
            rsub        ; return from subroutine
              endp 
