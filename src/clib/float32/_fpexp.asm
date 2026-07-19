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
; ***** Natural exp                                *****
; ***** RF - Pointer to floating point number      *****
; ***** RD - Pointer to floating point destination *****
; ***** internal:                                  *****
; *****       R2+1     - sum                       *****
; *****       R2+5     - last                      *****
; *****       R2+9     - fct                       *****
; *****       R2+13    - fctCount                  *****
; *****       R2+17    - pwr                       *****
; *****       R2+21    - tmp                       *****
; *****       R2+25    - n                         *****
; ******************************************************
              proc     _fpexp

; .link .requires _fpdata
.link .requires C_fp_const

              extrn    _addfpi
              extrn    _addtows
              extrn    _divfpi
              extrn    _getargs
              extrn    _mulfpi

              extrn    C_fp_zero
              extrn    C_fp_one
              extrn    C_fp_two

              ghi      r7           ; save expr stack
              stxd
              glo      r7
              stxd
              ghi      r7           ; source is expr stack
              phi      rf
              glo      r7
              plo      rf
              inc      rf
              ghi      rf           ; n = argument
              phi      rd
              glo      rf
              plo      rd
              call     _addtows
              stxd                  ; space for tmp
              stxd
              stxd
              stxd
              ghi      rf           ; pwr = argument
              phi      rd
              glo      rf
              plo      rd
              call     _addtows
              ldi      C_fp_two.1   ; fctCount = 2.0
              phi      rd
              ldi      C_fp_two.0
              plo      rd
              call     _addtows
              ldi      C_fp_one.1   ; fct = 1.0
              phi      rd
              ldi      C_fp_one.0
              plo      rd
              call     _addtows
              ldi      C_fp_zero.1  ; last = 0
              phi      rd
              ldi      C_fp_zero.0
              plo      rd
              call     _addtows
              ghi      rf           ; sum = argument
              phi      rd
              glo      rf
              plo      rd
              call     _addtows
              ghi      r2           ; sum = sum + 1
              phi      rf
              glo      r2
              plo      rf
              inc      rf
              ldi      C_fp_one.1
              phi      rd
              ldi      C_fp_one.0
              plo      rd
              call     _addfpi
fpexp_l:      call     _getargs     ; need to see if sum == last
              db       5,1
              ldi      4            ; 4 bytes to check
              plo      rc
              ldi      0            ; clear comparison flag
              plo      re
fpexp_1:      ldn      rd           ; get byte from sum
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
              lbnz     fpexp_1      ; jump if not
              glo      re           ; get comparison flag
              lbz      fpexp_d      ; jump if done
              call     _getargs     ; pwr = pwr * n
              db       17,25
              call     _mulfpi
              call     _getargs     ; fct = fct * fctCount
              db       9,13
              call     _mulfpi
              glo      r2           ; fctCount = fctCount + 1
              adi      13
              plo      rf
              ghi      r2
              adci     0
              phi      rf
              ldi      C_fp_one.1
              phi      rd
              ldi      C_fp_one.0
              plo      rd
              call     _addfpi
              call     _getargs     ; tmp = pwr
              db       21,17
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
              db       21,9
              call     _divfpi
              call     _getargs     ; sum = sum + tmp
              db       1,21
              call     _addfpi
              lbr      fpexp_l      ; loop until done
fpexp_d:      irx                   ; recover answer
              ldxa
              plo      r8
              ldxa
              phi      r8
              ldxa
              plo      ra
              ldx
              phi      ra
              glo      r2           ; clean workspace off stack
              adi      24
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

              endp
