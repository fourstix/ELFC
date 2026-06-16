#include ../include/ops_c.inc

; *******************************************************************
; *** This software is copyright 2005 by Michael H Riley          ***
; *** You have permission to use, modify, copy, and distribute    ***
; *** this software so long as this copyright notice is retained. ***
; *** This software may not be used in commercial applications    ***
; *** without express written permission from the author.         ***
; *******************************************************************

;*********************************************************
;  Note: This function uses registers that are reserved
;    by ELFC, and should only be called after the R9 and
;    RB registers are saved. R7 is used as the expression
;    stack pointer and is preserved by these routines.
;*********************************************************
; ELFC Reserved Registers:
;  R7 is the Expression Stack Pointer (ESP)
;  R9 is the Subroutine Instruction Pointer
;  RB is the  Stack Frame Base Pointer
;*********************************************************

; *************************************************
; ***** Multiply top two values on expr stack *****
; ***** R7 - pointer to expr stack            *****
; *************************************************
              proc    _mulfp

              extrn   _mulfpi

              glo     r7           ; Setup registers for call
              plo     rf
              plo     rd
              ghi     r7
              phi     rf
              phi     rd
              inc     rd
              inc     rf
              inc     rf
              inc     rf
              inc     rf
              inc     rf
              call    _mulfpi      ; Call multiplication
              inc     r7           ; Adjust expr stack
              inc     r7
              inc     r7
              inc     r7
              rtn                  ; And return

              endp

; ********************************************
; ***** Floating point multiplication    *****
; ***** RF - pointer to first fp number  *****
; ***** RD - pointer to second fp number *****
; ***** Uses: R7:R8 - answer       (cc)  *****
; *****       RA:RB - second number (bb) *****
; *****       R9.0  - exponent           *****
; *****       R9.1  - sign               *****
; *****       RC:RD - first number (aa)  *****
; ********************************************
              proc    _mulfpi

              extrn   _fpnorm
              extrn   _fpret_0
              extrn   _fpret_a
              extrn   _fpret_b
              extrn   _fpret_inf

              ghi     r7           ; save expr stack
              stxd
              glo     r7
              stxd
              ghi     rf           ; save destination address
              stxd
              glo     rf
              stxd
              lda      rd           ; retrieve second number
              plo      rb           ; place into bb
              lda      rd
              phi      rb
              lda      rd
              plo      ra
              shl                   ; shift high bit into DF
              lda      rd
              phi      ra
              shlc                  ; now have full 8 bits of exponent
              phi      r9           ; store into r9
              lbz      _fpret_0      ; jump if number is zero
              lda      rf           ; retrieve first number
              plo      rd           ; place into aa
              lda      rf
              phi      rd
              lda      rf
              plo      rc
              shl                   ; shift high bit into DF
              lda      rf
              phi      rc
              shlc                  ; now have exponent of first number
              plo      r9           ; save it
              lbz      _fpret_0     ; jump if number was zero
              glo      r9           ; get exponent of first number
              smi      0ffh         ; check for infinity
              lbz      fpmul_a      ; jump if so
              ghi      r9           ; get exponent of second number
              smi      0ffh         ; check for infinity
              lbz      _fpret_b     ; jump if so

              ;----- use 16-bit arithmetic to check for under/over flow
              ; glo      r9           ; get exponent 1
              ; smi      127          ; remove bias
              ; str      r2           ; store for add
              ; ghi      r9           ; get exponent 2
              ; smi      127          ; remove bias
              ; add                   ; add in exponent 1
              ; adi      127          ; add bias back in

              glo      r9           ; get exponent 1
              str      r2           ; store for addition
              ldi      0            ; set up scratch register for positive value
              phi      rf           ; extend sign bit into 16-bit arithmetic
              ghi      r9           ; get exponent 2
              add                   ; add exp1 and exp2
              plo      rf           ; save in scratch register
              ghi      rf
              adci     0            ; propagate carry into high byte
              phi      rf           ; rf now has sum + two bias values

              glo      rf           ; remove extra bias value from sum in rf
              smi      127
              plo      rf
              ghi      rf           ; propagate borrow into high byte
              smbi     0
              phi      rf           ; rf now has sum + one bias

              ghi      rf           ; check high byte of sum + bias
              lbz      chk_exp      ; if no bits in high byte, we are fine
              shl                   ; check sign bit of second byte of sum
              lbdf     _fpret_0     ; if negative number, underflow
ovr_flow:     ghi      rc           ; overflow, get sign of first number
              phi      r7           ; put sign into r7 to compare with ra
              lbr      _fpret_inf    ; return +/- infinty for overflow

chk_exp:      glo      rf           ; make sure sum is not 0 or $FF
              lbz      _fpret_0     ; if exponent 0, underflow
              smi      0ffh         ; check for overflow exponent
              lbz      ovr_flow     ; if overflow, jump to return infinity
              glo      rf           ; exp 1 to 254 is okay, so continue on

              plo      r9           ; r9 now has exponent of result
              ghi      ra           ; get msb of bb
              str      r2           ; store it
              ghi      rc           ; get msb of aa
              xor                   ; now have sign comparison
              shl                   ; shift sign into DF
              ldi      0            ; clear byte
              shlc                  ; shift in sign
              phi      r9           ; save sign for later
              ldi      0            ; need to clear high bytes
              phi      ra           ; of bb
              phi      rc           ; and aa
              plo      r8           ; also clear answer
              phi      r8
              plo      r7
              phi      r7
              glo      ra           ; get msb of bb mantissa
              ori      080h         ; add in implied 1
              plo      ra           ; and put it back
              glo      rc           ; get msb of aa mantissa
              ori      080h         ; add in implied 1
              plo      rc           ; and put it back
fpmul_lp:     glo      ra           ; need to zero check bb
              str      r2
              ghi      ra
              or
              str      r2
              glo      rb
              or
              str      r2
              ghi      rb
              or
              lbz      fpmul_dn     ; jump of bb==0
              ghi      r7           ; cc >>= 1
              shr
              phi      r7
              glo      r7
              shrc
              plo      r7
              ghi      r8
              shrc
              phi      r8
              glo      r8
              shrc
              plo      r8
              ghi      ra           ; bb >>= 1
              shr
              phi      ra
              glo      ra
              shrc
              plo      ra
              ghi      rb
              shrc
              phi      rb
              glo      rb
              shrc
              plo      rb
              lbnf     fpmul_lp     ; back to loop if no addition needed
              glo      r8           ; cc += aa
              str      r2
              glo      rd
              add
              plo      r8
              ghi      r8
              str      r2
              ghi      rd
              adc
              phi      r8
              glo      r7
              str      r2
              glo      rc
              adc
              plo      r7
              ghi      r7
              str      r2
              ghi      rc
              adc
              phi      r7
              lbr      fpmul_lp     ; back to beginning of loop
fpmul_dn:     call     _fpnorm      ; assemble answer
              lbr      _fpret_a     ; place result into destination
fpmul_a:      irx                   ; recover destination address
              ldxa
              plo      rf
              ldx
              phi      rf
              glo      rd           ; write a to answer
              str      rf
              inc      rf
              ghi      rd
              str      rf
              inc      rf
              glo      rc
              str      rf
              inc      rf
              ghi      rc
              str      rf
              irx                   ; recover expr stack
              ldxa
              plo      r7
              ldx
              phi      r7
              rtn                   ; and return to caller

              endp
