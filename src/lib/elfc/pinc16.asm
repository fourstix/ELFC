#include      ../include/ops_c.inc

;---------------------------------------------------------
; pinc16 - increment a 2-byte value referenced by the  
; pointer value in the RA register
; registers used:
;   RA - pointer value pointing to variable   
;   R8 - temp value   
; usage:   GOSUB pinc16
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

                proc pinc16
              lda     ra      ; get variable LSB referenced by pointer
              plo     r8      ; save in temp register
              ldn     ra      ; get the variable MSB referenced by pointer
              phi     r8      ; save in temp register
              
              inc     r8      ; increment temp value
              
              ghi     r8      ; get MSB from incremented value
              str     ra      ; save in referenced variable MSB
              dec     ra      ; move pointer to reference LSB
              glo     r8      ; get LSB from incremented value
              
              str     ra      ; save in referenced variable LSB
              sex     r2      ; make sure X = SP 
              rsub            ; return from subroutine
                endp 
          
