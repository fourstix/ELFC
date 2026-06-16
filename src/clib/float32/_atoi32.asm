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
; ***** Convert ascii to int32                   *****
; ***** RF - buffer to ascii                     *****
; ***** RD - destinatin int32                    *****
; ***** Returns R8:R9 result                     *****
; *****         RF - First non-numeric character *****
; ****************************************************
              proc    _atoi32

              ldi     0            ; zero result
              phi     r8
              plo     r8
              phi     r9
              plo     r9
              stxd                 ; store sign on stack
              ldn     rf           ; get byte from input
              smi     '-'          ; check for negative number
              lbnz    atoi32_lp    ; jump if not a negative number
              ldi     1            ; replace sign
              irx
              stxd
              inc     rf           ; move past sign
atoi32_lp:    ldn     rf           ; get byte from input
              smi     '0'          ; see if below digits
              lbnf    atoi32_dn    ; jump if not valid digit
              smi     10           ; check for high of range
              lbdf    atoi32_dn    ; jump if not valid digit
              glo     r9           ; multiply answer by 2
              shl
              plo     r9
              plo     rb           ; put a copy in RA:RB as well
              ghi     r9
              shlc
              phi     r9
              phi     rb
              glo     r8
              shlc
              plo     r8
              plo     ra
              ghi     r8
              shlc
              phi     r8
              phi     ra
              ldi     2            ; want to shift RA:RB twice
              plo     re
atoi32_1:     glo     rb           ; now shift RA:RB
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
              dec     re           ; decrement shift count
              glo     re           ; see if done
              lbnz    atoi32_1     ; shift again if not
              glo     rb           ; now add RA:RB to R8:R9
              str     r2
              glo     r9
              add
              plo     r9
              ghi     rb
              str     r2
              ghi     r9
              adc
              phi     r9
              glo     ra
              str     r2
              glo     r8
              adc
              plo     r8
              ghi     ra
              str     r2
              ghi     ra
              str     r2
              ghi     r8
              adc
              phi     r8
              lda     rf           ; get byte from input
              smi     '0'          ; conver to binary
              str     r2           ; and add it to R8:R9
              glo     r9
              add
              plo     r9
              ghi     r9
              adci    0
              phi     r9
              glo     r8
              adci    0
              plo     r8
              ghi     r8
              adci    0
              phi     r8
              lbr     atoi32_lp    ; loop back for more characters
atoi32_dn:    irx                  ; recover sign
              ldx
              shr                  ; shift into DF
              lbnf    atoi32_dn2   ; jump if not negative
              glo     r9           ; negate the number
              xri     0ffh
              adi     1
              plo     r9
              ghi     r9
              xri     0ffh
              adci    0
              phi     r9
              glo     r8
              xri     0ffh
              adci    0
              plo     r8
              ghi     r8
              xri     0ffh
              adci    0
              phi     r8
atoi32_dn2:   ghi     r8           ; store result into destination
              str     rd
              inc     rd
              glo     r8
              str     rd
              inc     rd
              ghi     r9
              str     rd
              inc     rd
              glo     r9
              str     rd
              dec     rd           ; restore RD
              dec     rd
              dec     rd
              rtn                  ; and return to caller

              endp
