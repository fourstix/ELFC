#include      ../include/ops_c.inc

;---------------------------------------------------------------
; Convert 16-bit value on expression stack to Boolean (1 or 0) 
;   R7 - Pointer to expression stack
;   usage     GOSUB bool16
;   returns:  with .true value 1 or .false. value 0 on TOS                 
;---------------------------------------------------------------

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

                proc    bool16

                extrn   true16
                extrn   false16

              sex     r7               ; point X to expression stack
              irx                      ; point to LSB of result
              ldxa                     ; retrieve it
              or                       ; combine with MSB
              sex     r2               ; point X back to stack
              smi     0                ; Set DF = 1 for true value
              lbnz    true16           ; Any nonzero value, is true
              adi     0                ; Set DF = 0 for false
              lbr     false16          ; zero is false value
              
              ;---- returns through true16 or false16 subroutines
                endp
  
