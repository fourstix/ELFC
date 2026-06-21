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
; ***** cos                                        *****
; ***** RF - Pointer to floating point number      *****
; ***** RD - Pointer to floating point destination *****
; ***** internal:                                  *****
; *****       R2+1  R7 - sum                       *****
; *****       R2+5  R8 - pwr                       *****
; *****       R2+9  R9 - last                      *****
; *****       R2+13 RA - fctPos                    *****
; *****       R2+17 RB - fct                       *****
; *****       R2+21 RC - tmp                       *****
; *****       R2+25 RD - sgn                       *****
; *****       R2+29    - angle                     *****
; ******************************************************
              proc     _fpcos

.link .requires _fpdata
.link .requires _trigdata

              extrn    _addtows
              extrn    _fact
              extrn    fp_1
              extrn    _sincos

              ghi      r7           ; save expr stack
              stxd
              glo      r7
              stxd
              ghi      r7           ; source is expr stack
              phi      rf
              glo      r7
              plo      rf
              inc      rf
              ghi      rf           ; angle = argument
              phi      rd
              glo      rf
              plo      rd
              call     _addtows     ; add to workspace
              ldi      0            ; sign starts out positive
              stxd                  ; make space for sgn
              stxd
              stxd
              stxd
              stxd                  ; make space for tmp
              stxd
              stxd
              stxd
              stxd                  ; make space for fct
              stxd
              stxd
              stxd
              stxd                  ; make space for fctPos
              stxd
              ldi      (_fact+8).1  ; position of 2!
              stxd
              ldi      (_fact+8).0
              stxd
              ldi      0
              stxd                  ; make space for last
              stxd
              stxd
              stxd
              ldi      fp_1.1       ; pwr = 1.0
              phi      rd
              ldi      fp_1.0
              plo      rd
              call     _addtows     ; add to workspace
              ldi      fp_1.1       ; pwr = 1.0
              phi      rd
              ldi      fp_1.0
              plo      rd
              call     _addtows     ; add to workspace
              lbr      _sincos      ; now compute

              endp
