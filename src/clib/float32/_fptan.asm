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
; ***** tan                                        *****
; ***** RF - Pointer to floating point number      *****
; ***** RD - Pointer to floating point destination *****
; ***** internal:                                  *****
; *****       R2+1     - s                         *****
; *****       R2+5     - c                         *****
; ******************************************************
              proc     _fptan

              extrn    _addtows
              extrn    _divfpi
              extrn    _fpcos
              extrn    _fpsin
              extrn    _getargs

              ghi      r7           ; save expr stack
              stxd
              glo      r7
              stxd
              ghi      r7           ; source is expr stack
              phi      rf
              glo      r7
              plo      rf
              inc      rf
              ghi      rf           ; s = argument
              phi      rd
              glo      rf
              plo      rd
              call     _addtows      ; add to workspace
              ghi      rf           ; c = argument
              phi      rd
              glo      rf
              plo      rd
              call     _addtows      ; add to workspace
              glo      r2           ; setup for computing sin
              plo      r7
              ghi      r2
              phi      r7
              call     _fpsin       ; compute sin
              glo      r2           ; setup to compute cos
              adi      4
              plo      r7
              ghi      r2
              adci     0
              phi      r7
              call     _fpcos       ; compute cos
              call     _getargs     ; get arguments for division
              db       1,5
              call     _divfpi      ; s = s / c
              irx                   ; recover answer
              ldxa
              plo      r8
              ldxa
              phi      r8
              ldxa
              plo      ra
              ldxa
              phi      ra
              irx                   ; move past c
              irx
              irx
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
