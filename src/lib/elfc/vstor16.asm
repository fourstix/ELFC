#include      ../include/ops_c.inc

;---------------------------------------------------------
; vstor16 - get a 2-byte value from the expression stack
; and store it in global or static variable 
; registers used:
;   R8 - pointer to variable in memory 
;   R7 - pointer to expression stack    
; usage:   GOSUB vstor16
;            dw  vaddr 
; note: leaves 16-bit value on expression stack
;   with ESP unchanged
; note: static and global variable bytes are stored in 
;   the same order (LSB first) as auto variables on the
;   expression stack
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

              proc vstor16          
            lda     r3    ; set up pointer to variable
            phi     r8
            lda     r3
            plo     r8
            sex     r7    ; X = ESP for expression stack
            irx           ; move ESP to LSB
            lda     r7    ; get LSB from stack
            str     r8    ; save LSB in variable
            inc     r8    ; move to MSB of variable
            ldn     r7    ; get MSB from stack
            str     r8    ; save MSB in variable
            dec     r7    ; move ESP back to bottom of stack
            dec     r7
            sex     r2    ; make sure X = SP 
            rsub          ; return from subroutine
              endp 
