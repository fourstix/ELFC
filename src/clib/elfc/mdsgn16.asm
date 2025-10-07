#include      ../include/ops_c.inc

;---------------------------------------------------------
; Prepare two signed 16-bit numbers on the expression
; stack for multiplication or division 
; registers:
;  RC - first signed 16-bit number at SOS
;  RD - second signed 16-bit number at TOS
; return:
;  TOS and SOS are converted to positive numbers
;  RA.0 - sign flag byte for signed multiply or divide  
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

              proc    mdsgn16
              
              sex     r7              ; set X to expression stack 
              irx                     ; move to TOS
              ldxa                    ; load TOS into rd
              plo     rd
              ldxa
              phi     rd
              ldxa
              plo     rc              ; load SOS into rc
              ldx
              phi     rc

              sex     r2              ; set x to SP 
              ghi     rc              ; get MSB of first number
              str     r2              ; store for upcoming XOR
              ghi     rd              ; get MSB of second number
              xor                     ; combine to see if like signs
              shl                     ; shift sign comparison to DF
              ldi     0               ; clear D
              shlc                    ; and then shift sign diff into D
              plo     re              ; set aside
              ghi     rc              ; get MSB of first number
              shl                     ; shift sign bit into DF
              lbnf    mdsgn2          ; jump if number is positive
              ghi     rc              ; otherwise 2's comp. the number
              xri     0ffh
              phi     rc
              glo     rc
              xri     0ffh
              plo     rc
              inc     rc
mdsgn2:       ghi     rd              ; get MSB of second number
              shl                     ; shift sign bit into DF
              lbnf    mdsgn3          ; no need to change if positive
              ghi     rd              ; otherwise 2's comp. the number
              xri     0ffh
              phi     rd
              glo     rd
              xri     0ffh
              plo     rd
              inc     rd
mdsgn3:       sex     r7              ; set X back to expression stack
              ghi     rc              ; put SOS value back on expression stack
              stxd                   
              glo     rc
              stxd
              ghi     rd               ; put TOS value back on expression stack
              stxd
              glo     rd
              stxd
              ldi     0                ; clear hi byte of accumulator
              phi     ra
              glo     re               ; recover sign difference byte
              plo     ra               ; save in accumulator for return
              sex     r2               ; set X back to SP for return
              rsub                     ; return from subroutine

              endp
