#include      ../include/ops_c.inc

;---------------------------------------------------------
; pdec8 - decrement a 1-byte value referenced by the  
; pointer value in the RA register
; registers used:
;   RA - pointer value pointing to variable   
;   R8 - temp value   
; usage:   GOSUB pdec8
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

                proc pdec8
              ldn     ra      ; get variable referenced by pointer
              plo     r8      ; save in temp register
              
              ;---- no need to pad signed/unsigned rolls under 
              
              dec     r8      ; decrement temp value
              
              glo     r8      ; get decremented value
              
              str     ra      ; save in referenced variable 
              sex     r2      ; make sure X = SP 
              rsub            ; return from subroutine
                endp 
          
