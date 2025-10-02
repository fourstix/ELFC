#include      ../include/ops_c.inc

;---------------------------------------------------------
; psave - get a pointer value from the TOS of the 
; expression stack and store it in the RA register
; registers used:
;   RA - pointer value from TOS  
;   R7 - pointer to expression stack    
;   R8 - operand pointer   
; usage:   GOSUB psave
; returns: RA with pointer value from TOS
; note: leaves 16-bit value on expression stack
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

                proc psave
              copy    r7, r8  ; set up operand pointer
              inc     r8      ; move to LSB of pointer on stack
              lda     r8      ; get pointer LSB from stack
              plo     ra      ; save pointer LSB in variable
              ldn     r8      ; get pointer MSB from stack
              phi     ra      ; save MSB in variable
              sex     r2      ; make sure X = SP 
              rsub            ; return from subroutine
                endp 
          
