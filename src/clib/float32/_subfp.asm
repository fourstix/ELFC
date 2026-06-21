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

; **************************************************
; ***** Subtract top two numbers on expr stack *****
; ***** R7 - points to expr stack              *****
; **************************************************
              proc    _subfp

.link .requires _addfp

              extrn   _subfpi

              glo     r7           ; Setup registers for call
              plo     rf
              plo     rd
              ghi     r7
              phi     rf
              phi     rd
              inc     rd
              inc     rf
              inc     rf
              inc     rf
              inc     rf
              inc     rf
              call    _subfpi      ; Call addition
              inc     r7           ; Adjust expr stack
              inc     r7
              inc     r7
              inc     r7
              rtn                  ; And return

              endp

; ********************************************
; ***** Floating point subtraction       *****
; ***** RF - pointer to first fp number  *****
; ***** RD - pointer to second fp number *****
; ***** Uses: R7:R8 - first number (aa)  *****
; *****       RA:RB - second number (bb) *****
; *****       R9.0  - exponent           *****
; *****       R9.1  - sign               *****
; ********************************************
              proc    _subfpi

              extrn   _fpargs
              extrn   _fpsub_1

              ghi     r7           ; save expr stack
              stxd
              glo     r7
              stxd
              ghi     rf           ; save destination address
              stxd
              glo     rf
              stxd
              call    _fpargs       ; retrieve arguments
              ghi     ra           ; invert number
              xri     080h
              phi     ra           ; save inverted sign
              ghi     r9
              lbr     _fpsub_1      ; now process with add

              endp
