#include      ../include/ops_c.inc

;---------------------------------------------------------
; pinc8 - increment a 1-byte value referenced by the  
; pointer value in the RA register
; registers used:
;   RA - pointer value pointing to variable   
;   R8 - temp value   
; usage:   GOSUB pinc8
; note: leaves the expression stack and ESP unchanged
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

                proc pinc8
              ldn     ra      ; get variable referenced by pointer
              plo     r8      ; save in temp register
              ldi     0       ; pad MSB with zero
              phi     r8      ; save in temp register
              
              inc     r8      ; increment temp value
              
              glo     r8      ; get incremented value
              
              str     ra      ; save in referenced variable
              sex     r2      ; make sure X = SP 
              rsub            ; return from subroutine
                endp 
          
