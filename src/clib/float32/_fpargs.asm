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

; *********************************
; ***** Retrieve fp arguments *****
; ***** M[RF] -> R7:R8 R9.0   *****
; ***** M[RD] -> RA:RB R9.1   *****
; *********************************
              proc    _fpargs

              lda     rf           ; retrieve first number
              plo     r8
              lda     rf
              phi     r8
              lda     rf
              plo     r7
              shl                  ; shift low bit of exponent
              lda     rf
              phi     r7
              shlc                 ; get full exponent
              plo     r9           ; save exponent 1
              lda     rd           ; retrieve second number
              plo     rb
              lda     rd
              phi     rb
              lda     rd
              plo     ra
              shl                  ; shift low bit of exponent
              lda     rd
              phi     ra
              shlc                 ; get full exponent
              phi     r9           ; save exponent 2
              rtn                  ; return to caller

              endp
