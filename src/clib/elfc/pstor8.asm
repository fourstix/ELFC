#include      ../include/ops_c.inc

;---------------------------------------------------------
; pstor8 - get a 1-byte value from the expression stack
; and store it in a pointer variable 
; registers used:
;   RA - pointer to variable 
;   R7 - pointer to expression stack    
; usage:  GOSUB pstor8
; note: leaves 16-bit padded 1-byte value on expression 
;   stack with ESP unchanged
; note: all variable bytes are stored in 
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

                proc pstor8
              sex     r7    ; X = ESP for expression stack
              irx           ; move ESP to LSB
              ldn     r7    ; get LSB from stack
              str     ra    ; save LSB in variable
              dec     r7
              sex     r2    ; make sure X = SP 
              rsub          ; return from subroutine
                endp 
