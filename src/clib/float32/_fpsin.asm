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

; ******************************************************
; ***** sin                                        *****
; ***** RF - Pointer to floating point number      *****
; ***** RD - Pointer to floating point destination *****
; ***** internal:                                  *****
; *****       R2+1  R7 - sum                       *****
; *****       R2+5  R8 - pwr                       *****
; *****       R2+9  R9 - last                      *****
; *****       R2+13 RA - fctPos                    *****
; *****       R2+17 RB - fct                       *****
; *****       R2+21 RC - tmp                       *****
; *****       R2+25 RD - sgn                       *****
; *****       R2+29    - angle                     *****
; ******************************************************
              proc     _fpsin

.link .requires _trigdata

              extrn    _addfpi
              extrn    _addtows
              extrn    _divfpi
              extrn    _fact
              extrn    _getargs
              extrn    _mulfpi

              ghi      r7           ; save expr stack
              stxd
              glo      r7
              stxd
              ghi      r7           ; source is expr stack
              phi      rf
              glo      r7
              plo      rf
              inc      rf
              ghi      rf           ; angle = argument
              phi      rd
              glo      rf
              plo      rd
              call     _addtows      ; add to workspace
              ldi      0            ; sign starts out positive
              stxd                  ; make space for sgn
              stxd
              stxd
              stxd
              stxd                  ; make space for tmp
              stxd
              stxd
              stxd
              stxd                  ; make space for fct
              stxd
              stxd
              stxd
              stxd                  ; make space for fctPos
              stxd
              ldi      (_fact+12).1 ; position of 3!
              stxd
              ldi      (_fact+12).0
              stxd
              ldi      0
              stxd                  ; make space for last
              stxd
              stxd
              stxd
              ghi      rf           ; pwr = argument
              phi      rd
              glo      rf
              plo      rd
              call     _addtows     ; add to workspace
              ghi      rf           ; sum = argument
              phi      rd
              glo      rf
              plo      rd
              call     _addtows     ; add to workspace
_sincos:      call     _getargs     ; angle = angle * angle
              db       29,29
              call     _mulfpi      ; angle = angle * angle
sincos_l:     call     _getargs     ; need to see if sum == last
              db       9,1
              ldi      4            ; 4 bytes to check
              plo      rc
              ldi      0            ; clear comparison flag
              plo      re
sincos_1:     ldn      rd           ; get byte from sum
              str      r2           ; save for comparison
              ldn      rf           ; get point from last
              sm                    ; compare them
              str      r2           ; store to combine with comparison flag
              glo      re           ; get comparison flag
              or                    ; combine
              plo      re           ; put back into comparison
              ldn      rd           ; get byte from sum
              str      rf           ; store into last
              inc      rd           ; increment pointers
              inc      rf
              dec      rc           ; decrement count
              glo      rc           ; see if done
              lbnz     sincos_1     ; jump if not
              glo      re           ; get comparison flag
              lbz      sincos_d     ; jump if done
              call     _getargs     ; pwr = pwr * angle
              db       5,29
              call     _mulfpi
              call     _getargs     ; fct = facts[fctPos]
              db       17,13
              ldn      rd           ; get address of facts[fctPos]
              plo      r7
              adi      8            ; and then point two constants up
              str      rd
              inc      rd
              ldn      rd           ; get high byte of address
              phi      r7
              adci     0
              str      rd           ; fctPos now points at next one needed
              lda      r7           ; read factorial into destination
              str      rf
              inc      rf
              lda      r7
              str      rf
              inc      rf
              lda      r7
              str      rf
              inc      rf
              glo      r2           ; point to sgn
              adi      25
              plo      rd
              ghi      r2
              adci     0
              phi      rd
              ldn      rd           ; get sign
              xri      080h         ; flip it
              str      rd           ; and put it back
              str      r2           ; store to combine with fct
              lda      r7
              or                    ; set sign
              str      rf
              call     _getargs     ; tmp = pwr
              db       21,5
              lda      rd
              str      rf
              inc      rf
              lda      rd
              str      rf
              inc      rf
              lda      rd
              str      rf
              inc      rf
              lda      rd
              str      rf
              call     _getargs     ; tmp = tmp / fct
              db       21,17
              call     _divfpi
              call     _getargs     ; sum = sum + tmp
              db       1,21
              call     _addfpi
              lbr      sincos_l     ; loop until done
sincos_d:     irx                   ; recover answer
              ldxa
              plo      r8
              ldxa
              phi      r8
              ldxa
              plo      ra
              ldx
              phi      ra
              glo      r2           ; clean workspace off stack
              adi      28
              plo      r2
              ghi      r2
              adci     0
              phi      r2
              irx                   ; recover expr stack
              ldxa
              plo      r7
              ldx
              phi      r7
              inc      r7
              glo      r8           ; store answer
              str      r7
              inc      r7
              ghi      r8
              str      r7
              inc      r7
              glo      ra
              str      r7
              inc      r7
              ghi      ra
              str      r7
              dec      r7
              dec      r7
              dec      r7
              dec      r7
              rtn                   ; and return to caller

              public   _sincos

              endp
