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
; ***** Compute arcsin                             *****
; ******************************************************
              proc    _fpasin

              extrn   _addfp
              extrn   _divfp
              extrn   _mulfp
              extrn   _fpatan
              extrn   _fpsqrt
              extrn   _subfp

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
              sex     r7           ; now place 2 1.0s
              ldi     03fh
              stxd
              ldi     080h
              stxd
              ldi     000h
              stxd
              stxd
              ldi     03fh
              stxd
              ldi     080h
              stxd
              ldi     000h
              stxd
              stxd
              ghi     r9           ; Put x back on the stack twice
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
              call    _mulfp       ; x * x
              call    _subfp       ; subtract from 1.0
              call    _fpsqrt      ; take square root
              call    _addfp       ; add 1.0
              call    _divfp       ; divide into x
              call    _fpatan      ; and then atan
              sex     r7           ; multiply result by 2.0
              ldi     040h
              stxd
              ldi     000h
              stxd
              stxd
              stxd
              sex     r2
              call    _mulfp
              rtn

              endp
