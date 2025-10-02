#include      ../include/ops_c.inc

;---------------------------------------------------------
; Multiply top 2 signed 16-bit numbers on expression stack 
; inputs:
;  TOS - multiplier
;  SOS - multiplicand
;  RA.0 - sign difference byte 
; registers:
;  RD - multiplier (TOS)
;  RC - multiplicand (SOS)
;  RF - product register
;  RE.0 - sign difference byte
; returns:
;  TOS - product of signed 16-bit multiplication 
; ******************************************************

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

              proc    mul16

              sex     r7              ; point X to expression stack
              irx                     ; retrieve first number into RD
              ldxa
              plo     rd
              ldxa
              phi     rd
              ldxa                    ; retrieve second number into RC
              plo     rc
              ldx
              phi     rc
              glo     ra              ; get sign flag byte
              plo     re              ; save sign difference for now
              ldi     0               ; clear result in RF
              phi     rf
              plo     rf
              sex     r2              ; set X back to system stack
mulloop:      glo     rd              ; check if multiplier is zero
              lbnz    mulcont         ; jump if not
              ghi     rd              ; check high byte too
              lbnz    mulcont         ; if zero, then multiply is done
              glo     re              ; retrieve sign difference
              shr                     ; shift into DF
              lbnf    mulexit         ; if like signs then all done
              glo     rf              ; otherwise 2's comp. the result
              xri     0ffh
              plo     rf
              ghi     rf
              xri     0ffh
              phi     rf
              inc     rf
mulexit:      sex     r7              ; point X to expression stack
              ghi     rf              ; push result to expression stack
              stxd
              glo     rf
              stxd
              sex     r2              ; point X back to stack
              rsub                    ; return from subroutine
mulcont:      ghi     rd              ; shift multiplier to the right
              shr
              phi     rd
              glo     rd
              shrc
              plo     rd
              lbnf    mulcont2        ; if low bit was 0, then no add
              glo     rc              ; otherwise add multiplicand to result
              str     r2
              glo     rf
              add
              plo     rf
              ghi     rc
              str     r2
              ghi     rf
              adc
              phi     rf
mulcont2:     glo     rc              ; shift multiplicand left
              shl
              plo     rc
              ghi     rc
              shlc
              phi     rc
              lbr     mulloop         ; then loop back for next bit

              endp
