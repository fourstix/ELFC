#include      ../include/ops_c.inc

;---------------------------------------------------------
; vstor8 - get a char value from the expression stack
; and store it in global or static variable 
; registers used:
;   R8 - pointer to char variable in memory 
;   R7 - pointer to expression stack    
; usage:   GOSUB vstor8
;            dw  vaddr 
; notes: leaves the 8-bit value on expression stack
;   with ESP unchanged
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

              proc vstor8          
            lda     r3    ; set up pointer to variable
            phi     r8
            lda     r3
            plo     r8    ; r8 points to variable
            sex     r7    ; X = ESP for expression stack
            irx           ; move ESP to LSB 
            ldn     r7    ; get LSB from stack
            str     r8    ; save LSB in variable
            dec     r7    ; move ESP  back to bottom of stack
            sex     r2    ; make sure X = SP 
            rsub          ; return from subroutine
              endp 
