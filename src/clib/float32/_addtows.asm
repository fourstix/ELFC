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

              proc     _addtows

              irx                   ; retrieve return address
              ldxa
              phi      r8
              ldx
              plo      r8
              inc      rd           ; move to msb
              inc      rd
              inc      rd
              ldn      rd           ; retrieve
              stxd                  ; and place on stack
              dec      rd
              ldn      rd           ; retrieve next byte
              stxd                  ; and place on stack
              dec      rd
              ldn      rd           ; retrieve next byte
              stxd                  ; and place on stack
              dec      rd
              ldn      rd           ; retrieve next byte
              stxd                  ; and place on stack
              glo      r8           ; put return address back on stack
              stxd
              ghi      r8
              stxd
              rtn                   ; return to caller

              endp
