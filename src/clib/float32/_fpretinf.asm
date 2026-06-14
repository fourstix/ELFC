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
; ***** Push +/-inf to expr stack             *****
; ***** R7 - set to point to expr stack       *****
; ***** Uses: RF - destination pointer        *****
; *****       R7 - high byte of first number  *****
; *****       RA - high byte of second number *****
; *************************************************
              proc    _fpret_inf

              irx                  ; recover destination address
              ldxa
              plo     rf
              ldx
              phi     rf

              ldi     0            ; write 0 for remaining bytes
              str     rf           ; store $7F or $FF into high byte
              inc     rf
              str     rf
              inc     rf
              ldi     $80          ; next byte is $80 (with lsb of exponent)
              str     rf
              inc     rf
              ghi     r7           ; get sign of a
              str     r2           ; store for xor
              ghi     ra           ; get sign of b
              xor                  ; now have sign comparison
              shl                  ; shift it into DF
              ldi     $FF          ; load inf exponent value
              shrc                 ; shift sign byte on inf value
              str     rf           ; $7F80:0000 or $FF80:0000 on stack

              irx                  ; restore expression stack pointer
              ldxa
              plo     r7
              ldx
              phi     r7
              rtn                  ; and return

              endp
