#include      ../include/ops_c.inc

; ***********************************************************
; ***** Subtract two 16-bit numbers on expression stack *****
; ***** R7 - pointer to expression  stack               *****
; ***** Numbers on expression stack are LSB first       *****
; ***********************************************************

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

                proc    sub16

              sex     r7               ; point X to expression stack
              irx                      ; point to LSB of first arg
              ldxa                     ; retrieve it
              irx                      ; point to LSB of second arg
              sd                       ; and subtract
              stxd                     ; strore result as LSB of arg2
              ldxa                     ; get MSB of arg 1
              irx                      ; move past LSB of arg
              sdb                      ; subtract from MSB of arg 2
              stxd                     ; store to MSB of arg2
              dec     r7               ; move R7 to just before arg2
              sex     r2               ; restore X to SP
              rsub                     ; return from subroutine

                endp
