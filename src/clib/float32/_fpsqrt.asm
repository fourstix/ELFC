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
; ***** Square root                                *****
; ***** RF - Pointer to floating point number x    *****
; *****       R2+1     - x                         *****
; *****       R2+5     - s                         *****
; *****       R2+9     - p                         *****
; *****       R2+13    - arg                       *****
; ******************************************************
              proc     _fpsqrt

.link .requires _fpdata

              extrn    _addfpi
              extrn    _addtows
              extrn    _divfpi
              extrn    fp_dot5
              extrn    _fpcopy
              extrn    _getargs
              extrn    _mulfpi

              ghi      r7           ; argument is on expr stack
              phi      rf
              glo      r7
              plo      rf
              inc      rf
              ghi      rf           ; arg = argument
              phi      rd
              glo      rf
              plo      rd
              call     _addtows
              ghi      rf           ; p = argument
              phi      rd
              glo      rf
              plo      rd
              call     _addtows
              ghi      rf           ; s = argument
              phi      rd
              glo      rf
              plo      rd
              call     _addtows
              ghi      rf           ; x = argument
              phi      rd
              glo      rf
              plo      rd
              call     _addtows
              ldi      255          ; set max iteration count
              plo      rc
fpsqrtlp:     call     _getargs     ; x = arg
              db       1,13
              call     _fpcopy
              glo      rc           ; save iteration count
              stxd
              call     _getargs     ; x = x / s
              db       2,6
              call     _divfpi
              call     _getargs     ; s = s + x
              db       6,2
              call     _addfpi
              glo      r2           ; s = s * 0.5
              adi      6
              plo      rf
              ghi      r2
              adci     0
              phi      rf
              ldi      fp_dot5.1
              phi      rd
              ldi      fp_dot5.0
              plo      rd
              call     _mulfpi
              irx                   ; recover iteration count
              ldx
              plo      rc
              call     _getargs     ; check p=s
              db       9,5
              lda      rf
              ani      0fch
              str      r2
              lda      rd
              ani      0fch
              sm
              lbnz     fpsqrtn
              lda      rf
              str      r2
              lda      rd
              sm
              lbnz     fpsqrtn
              lda      rf
              str      r2
              lda      rd
              sm
              lbnz     fpsqrtn
              lda      rf
              str      r2
              lda      rd
              sm
              lbz      fpsqrtd
fpsqrtn:      dec      rc           ; decrement iteration count
              glo      rc
              lbz      fpsqrtd      ; jump if reached
              call     _getargs      ; p = s
              db       9,5
              call     _fpcopy
              lbr      fpsqrtlp     ; loop until convergence
fpsqrtd:      irx                   ; retrieve answer
              irx
              irx
              irx
              irx
              ldxa
              plo      r8
              ldxa
              phi      r8
              ldxa
              plo      r9
              ldx
              phi      r9
              glo      r2           ; remove remaining workspace
              adi      8
              plo      r2
              ghi      r2
              adci     0
              phi      r2
              inc      r7
              glo      r8           ; store answer
              str      r7
              inc      r7
              ghi      r8
              str      r7
              inc      r7
              glo      r9
              str      r7
              inc      r7
              ghi      r9
              str      r7
              dec      r7
              dec      r7
              dec      r7
              dec      r7
              rtn                   ; and return to caller

              endp
