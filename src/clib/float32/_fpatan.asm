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
; ***** Compute arctangent                         *****
; ***** internal:                                  *****
; *****       R2+1     - ret                       *****
; *****       R2+5     - total                     *****
; *****       R2+9     - ydx                       *****
; *****       R2+13    - tmp                       *****
; ******************************************************
              proc    _fpatan

              extrn   _addfp
              extrn   _addfpi
              extrn   _addtows
              extrn   _divfp
              extrn   _fpcopy
              extrn   _fpsqrt
              extrn   _getargs
              extrn   _mulfp
              extrn   _mulfpi

              inc     r7           ; retrieve x
              lda     r7
              plo     r8
              lda     r7
              phi     r8
              lda     r7
              plo     r9
              ldn     r7
              phi     r9
              dec     r7           ; keep x on the expr stack
              dec     r7
              dec     r7
              dec     r7
              sex     r7           ; Put x back on the stack twice
              ghi     r9
              stxd
              glo     r9
              stxd
              ghi     r8
              stxd
              glo     r8
              stxd
              ghi     r9
              stxd
              glo     r9
              stxd
              ghi     r8
              stxd
              glo     r8
              stxd
              sex     r2
              call    _mulfp       ; x*x
              sex     r7           ; now add 1.0
              ldi     03fh
              stxd
              ldi     080h
              stxd
              ldi     000h
              stxd
              stxd
              sex     r2
              call    _addfp
              call    _fpsqrt      ; now sqrt
              sex     r7           ; now add 1.0
              ldi     03fh
              stxd
              ldi     080h
              stxd
              ldi     000h
              stxd
              stxd
              sex     r2
              call    _addfp
              call    _divfp        ; now have x/(1+sqrt(1+x*X))
              ghi      r7           ; save expr stack
              stxd
              glo      r7
              stxd
              stxd                  ; space on stack for tmp
              stxd
              stxd
              stxd
              ghi      r7           ; source is expr stack
              phi      rf
              glo      r7
              plo      rf
              inc      rf
              ghi      rf           ; ydx = argument
              phi      rd
              glo      rf
              plo      rd
              call     _addtows     ; add to workspace
              ghi      rf           ; total = argument
              phi      rd
              glo      rf
              plo      rd
              call     _addtows     ; add to workspace
              ghi      rf           ; ret = argument
              phi      rd
              glo      rf
              plo      rd
              call     _addtows     ; add to workspace
              call     _getargs     ; ydx = ydx * ydx
              db       9,9
              call     _mulfpi
              ldi      atandata.1   ; point to -1/3
              phi      r9
              ldi      atandata.0
              plo      r9
              ldi      10           ; 10 loops
              plo      rc
atanlp:       call     _getargs     ; total *= ydx
              db       5,9
              glo      rc           ; save needed registers
              stxd
              ghi      r9           ; save needed registers
              stxd
              glo      r9
              stxd
              call     _mulfpi
              call     _getargs     ; tmp = total
              db       16,8
              call     _fpcopy
              irx                   ; tmp = tmp * fractional
              ldxa
              plo      rd
              ldx
              phi      rd
              dec      r2
              glo      r2
              adi      15
              plo      rf
              ghi      r2
              adci     0
              phi      rf
              dec      r2
              call     _mulfpi
              call     _getargs     ; ret = ret + tmp
              db       4,16
              call     _addfpi
              irx                   ; recover registers
              ldxa
              plo      r9
              ldxa
              phi      r9
              ldx
              plo      rc
              inc      r9           ; move to next fractional
              inc      r9
              inc      r9
              inc      r9
              dec      rc           ; decrement loop count
              glo      rc           ; get remaining loops
              lbnz     atanlp       ; jump if more loops
              call     _getargs     ; ret = ret + ret
              db       1,1
              call     _addfpi
              irx                   ; recover answer
              ldxa
              plo      r8
              ldxa
              phi      r8
              ldxa
              plo      r9
              ldx
              phi      r9
              glo      r2           ; remove remaining workspace from stack
              adi      12
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
atandata:     db      0abh,0aah,0aah,0beh ; -1/3
              db      0cdh,0cch,04ch,03eh ;  1/5
              db      025h,049h,012h,0beh ; -1/7
              db      039h,08eh,0e3h,03dh ;  1/9
              db      08ch,02eh,0bah,0bdh ; -1/11
              db      0d9h,089h,09dh,03dh ;  1/13
              db      089h,088h,088h,0bdh ; -1/15
              db      0f1h,0f0h,070h,03dh ;  1/17
              db      036h,094h,057h,0bdh ; -1/19
              db      031h,00ch,043h,03dh ;  1/21

              endp
