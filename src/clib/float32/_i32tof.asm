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

; ****************************************************
; ***** Convert 32-bit integer to floating point *****
; ***** numbers are on expr stack                *****
; ***** RF - Pointer to 32-bit integer           *****
; ***** RD - Destination floating point          *****
; ****************************************************
              proc    _i32tof

              inc     r7
              lda     r7         ; retrieve 32-bit integer into ra:rb
              plo     rb
              str     r2         ; store for zero check
              lda     r7
              phi     rb
              or                 ; combine with zero check
              str     r2         ; keep zero check on stack
              lda     r7
              plo     ra
              or
              str     r2
              ldn     r7         ; MSB
              phi     ra
              or
              lbz     itof0      ; jump if input number is zero
              ldi     0          ; set sign flag
              str     r2
              ghi     ra         ; see if number is negative
              shl                ; shift sign bit into DF
              lbnf    itof_p     ; jump if number is positive
              ldi     1          ; set sign flag
              stxd
              glo     rb         ; 2s compliment input number
              xri     0ffh
              adi     1
              plo     rb
              ghi     rb
              xri     0ffh
              adci    0
              phi     rb
              glo     ra
              xri     0ffh
              adci    0
              plo     ra
              ghi     ra
              xri     0ffh
              adci    0
              phi     ra
              irx                ; point x back to sign flag
itof_p:       ldi     150        ; exponent starts at 150
              plo     re
itof_1:       ghi     ra         ; see if need right shifts
              lbz     itof_2     ; jump if not
              shr                ; otherwise shift number right
              phi     ra
              glo     ra
              shrc
              plo     ra
              ghi     rb
              shrc
              phi     rb
              glo     rb
              shrc
              plo     rb
              inc     re         ; increment exponent
              lbr     itof_1     ; and loop to see if more shifts needed
itof_2:       glo     ra         ; see if we need left shifts
              ani     080h
              lbnz    itof_3     ; jump if no shifts needed
              glo     rb         ; shift number left
              shl
              plo     rb
              ghi     rb
              shlc
              phi     rb
              glo     ra
              shlc
              plo     ra
              ghi     ra
              shlc
              phi     ra
              dec     re         ; decrement exponent
              lbr     itof_2     ; and loop to see if more shifts needed
itof_3:       glo     ra         ; prepare to merge in exponent
              shl
              plo     ra
              glo     re         ; get exponent
              phi     ra         ; store into result
              shr                ; shift it right 1 bit
              glo     ra
              shrc               ; shift final exponent bit in
              plo     ra
              ldx                ; recover sign flag
              shr                ; shift it into DF
              ghi     ra         ; get msb of result
              shrc               ; shift in sign bit
              phi     ra         ; and put it back
itof0:        ghi     ra         ; store answer into destination
              str     r7
              dec     r7
              glo     ra
              str     r7
              dec     r7
              ghi     rb
              str     r7
              dec     r7
              glo     rb
              str     r7
              dec     r7
              rtn                ; and return

              endp
