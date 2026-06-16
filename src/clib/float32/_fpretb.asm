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

; **********************************************
; ***** Strore FP register B on expr stack *****
; ***** R7 - points to expr stack          *****
; **********************************************
              proc    _fpret_b

              irx                  ; recover destination address
              ldxa
              plo     rf
              ldx
              phi     rf
              glo     rb           ; store a as answer
              str     rf
              inc     rf
              ghi     rb
              str     rf
              inc     rf
              glo     ra
              str     rf
              inc     rf
              ghi     ra
              str     rf
              irx
              ldxa
              plo     r7
              ldx
              phi     r7
              rtn                  ; and return to caller

              endp
