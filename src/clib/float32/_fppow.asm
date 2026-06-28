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
; ***** Power x^y                                  *****
; ***** RF - Pointer to floating point number x    *****
; ***** RC - Pointer to floating point number y    *****
; ***** RD - Pointer to floating point destination *****
; ***** internal:                                  *****
; *****       R2+1     - x                         *****
; *****       R2+5     - y                         *****
; ******************************************************
              proc     _fppow

              extrn    _fpexp
              extrn    _fpln
              extrn    _mulfp

              inc      r7           ; x = log(x)
              inc      r7
              inc      r7
              inc      r7
              call     _fpln
              dec      r7           ; now x = x * y
              dec      r7
              dec      r7
              dec      r7
              call     _mulfp
              call     _fpexp       ; x = exp(x)
              rtn                   ; and return to caller

              endp
