#include      ../include/ops_c.inc

; ************************************************
; ****  Compare 2 16-bit values for SOS      *****
; ****  less than TOS                        *****
; **** R7 - Pointer to expression stack      *****
; ************************************************

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

                proc    lt16

                extrn   true16
                extrn   false16

              sex     r7               ; point X to expression stack

              ;----- subtract args  (SOS - TOS)
              irx                      ; point to LSB of first arg
              ldxa                     ; retrieve it
              irx                      ; point to LSB of second arg
              sd                       ; and subtract
              stxd                     ; strore result as LSB of arg2
              ldxa                     ; get MSB of arg 1
              irx                      ; move past LSB of arg
              sdb                      ; subtract from MSB of arg 2
              stxd                     ; store to MSB of arg2

              ldxa                     ; retrieve it
              or                       ; combine with MSB
              sex     r2               ; point X back to stack
              lbz     false16          ; If result was zero, then not less
              ldn     r7               ; retrieve MSB
              shl                      ; get sign bit
              lbdf    true16           ; true if result is negative
              lbr     false16          ; otherwise false
              ;---- returns through true16 or false16 subroutines

                endp
