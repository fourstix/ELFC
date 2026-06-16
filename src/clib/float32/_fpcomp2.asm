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

#include ../include/ops_c.inc

; ******************************************
; ***** 2's compliment number in R7:R8 *****
; ******************************************
              proc    _fpcomp2

              glo     r8         ; perform 2s compliment on input
              xri     0ffh
              adi     1
              plo     r8
              ghi     r8
              xri     0ffh
              adci    0
              phi     r8
              glo     r7
              xri     0ffh
              adci    0
              plo     r7
              ghi     r7
              xri     0ffh
              adci    0
              phi     r7
              rtn

              endp
