#include      ../include/ops_c.inc

;---------------------------------------------------------
; scltos2 - scale a 16-bit pointer offset at the TOS
; of the expression stack by a power of 2.
; R7 - expression stack pointer
; R8 - operand pointer
; usage:   GOSUB scltos2n
;             db  n      ; number of shifts
; returns: offset at TOS scaled by 2^n on expression stack
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

            proc    scltos2n
          lda     r3        ; get shift count
          plo     rc        ; save count in RC.0

          copy    r7, r8    ; set up operand pointer
          inc     r8        ; move to LSB of TOS

st_rpt:   glo     rc        ; check count
          lbz     st_end    ; if zero we ae done

          lda     r8        ; retrieve LSB of previous TOS
          shl               ; multiply by 2
          plo     re        ; save in scratch register
          ldn     r8        ; get MSB of previous TOS
          shlc              ; multiply by 2 with carry
          str     r8        ; update MSB
          dec     r8
          glo     re        ; get shifted LSB from scratch register
          str     r8        ; update LSB on stack
          dec     rc        ; decrement count
          lbr     st_rpt    ; keep shifting

  st_end: sex     r2        ; make sure X = SP
          rsub              ; return from subroutine
            endp
