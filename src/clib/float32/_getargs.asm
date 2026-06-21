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

              proc     _getargs

              lda      r6           ; get passed argument
              str      r2           ; store for add
              glo      r2           ; add stack offset
              add
              plo      rf           ; put into first argument
              ghi      r2           ; high of stack
              adci     0            ; propagate carry
              phi      rf           ; rf now has argument address
              inc      rf           ; remove last call offset
              inc      rf
              lda      r6           ; get passed argument
              str      r2           ; store for add
              glo      r2           ; add stack offset
              add
              plo      rd           ; put into second argument
              ghi      r2           ; high of stack
              adci     0            ; propagate carry
              phi      rd           ; rd now has argument address
              inc      rd           ; remove last call offset
              inc      rd
              rtn                   ; return to caller

              endp
