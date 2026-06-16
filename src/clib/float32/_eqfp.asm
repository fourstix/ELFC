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

; *************************************************
; ***** Compare top two numbers on expr stack *****
; ***** R7 - points to expr stack             *****
; *************************************************
              proc    _eqfp

              extrn   _subfp
              extrn   _true32
              extrn   _false32

              call    _subfp
              sex     r7
              irx
              ldxa
              or
              ldxa
              or
              ldxa
              or
              ldx
              or
              sex     r2
              lbz     _true32
              lbr     _false32

              endp
