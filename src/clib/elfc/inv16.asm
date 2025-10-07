#include      ../include/ops_c.inc

;-----------------------------------------------------
; Invert a 16-bit integer on expression stack       
;   R7 - pointer to expression stack              
;-----------------------------------------------------

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

                proc    inv16

              inc     r7               ; point to LSB of number
              ldn     r7               ; retrieve it
              xri     0ffh             ; invert it
              str     r7               ; put it back
              inc     r7               ; point to MSB
              ldn     r7               ; retrieve it
              xri     0ffh             ; invert it
              str     r7               ; and put it back
              dec     r7               ; restore R7's position
              dec     r7
              rsub                     ; return from subroutine

                endp
  
