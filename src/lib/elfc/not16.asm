#include      ../include/ops_c.inc

; **************************************************
; ***** Boolean Not of a 16-bit value          *****
; **** R7 - Pointer to expression stack        *****
; **************************************************
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

                proc    not16

                extrn   true16
                extrn   false16

              sex     r7               ; point X to expression stack
              irx                      ; point to LSB of result
              ldxa                     ; retrieve it
              or                       ; combine with MSB
              sex     r2               ; point X back to stack
              lbnz    false16          ; Not of any nonzero value, is false
              lbr     true16           ; otherwise Not zero is true
              ;---- returns through true16 or false16 subroutines

              endp
