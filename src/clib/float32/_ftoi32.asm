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
; ***** Convert floating point to integer     *****
; ***** Numbers are on expr stack             *****
; ***** RF - pointer to floating point number *****
; ***** RD - destination integer              *****
; ***** Returns: DF=1 - overflow              *****
; ***** Uses:                                 *****
; *****       R9.0  - exponent                *****
; *****       R9.1  - sign                    *****
; *****       RD:RF - number                  *****
; *****       RA:RB - fractional              *****
; *****       RC.0  - digit count             *****
; *************************************************
              proc     _ftoi32

              inc      r7
              lda      r7         ; retrieve number into RD:RF
              plo      rf
              lda      r7
              phi      rf
              lda      r7
              plo      rd
              ldn      r7
              phi      rd
              shl                   ; shift sign into DF
              ldi      0            ; clear D
              shlc                  ; shift sign into D
              phi      r9           ; and store it
ftoi_1:       glo      rd           ; get low bit of exponent
              shl                   ; shift into DF
              ghi      rd           ; get high 7 bits of exponent
              shlc                  ; shift in the low bit
              plo      r9           ; store it
              lbnz     ftoi_2       ; jump if exponent is not zero
              ldi      0            ; result is zero
              str      r7
              dec      r7
              str      r7
              dec      r7
              str      r7
              dec      r7
              str      r7
              dec      r7
              adi      0            ; clear DF
              rtn                   ; return to caller
ftoi_2:       smi      0ffh         ; check for infinity
              lbnz     ftoi_5       ; jump if not
ftoi_ov:      ldi      0ffh         ; write highest integer
              str      r7
              dec      r7
              str      r7
              dec      r7
              str      r7
              dec      r7
              ldi      07fh         ; positive number
              str      r7
              dec      r7
              smi      0            ; set DF to signal ovelow
              rtn                   ; and return
ftoi_5:       ldi      0            ; clear high byte of number
              phi      rd
              glo      rd           ; set implied 1
              ori      080h
              plo      rd           ; and put it back
              ldi      0            ; clear fractional
              phi      ra
              plo      ra
              phi      rb
              plo      rb
ftoi_6:       glo      r9           ; get exponent
              smi      150          ; check for less than 150
              lbdf     ftoi_7       ; jump if not
              glo      ra           ; shift fractional right
              shr
              plo      ra
              ghi      rb
              shrc
              phi      rb
              glo      rb
              shrc
              plo      rb
              glo      rf           ; get low bit of number
              shr                   ; shift it into DF
              lbnf     ftoi_6a      ; jump if bit was clear
              glo      ra           ; otherwise set high bit in fractional
              ori      080h
              plo      ra           ; put it back
ftoi_6a:      glo      rd           ; shift number right
              shr
              plo      rd
              ghi      rf
              shrc
              phi      rf
              glo      rf
              shrc
              plo      rf
              glo      r9           ; get exponent
              adi      1            ; increase it
              plo      r9           ; put it back
              lbr      ftoi_6       ; loop back until exponent >= 150
ftoi_7:       glo      r9           ; get exponent
              smi      151          ; check for greater than 150
              lbnf     ftoi_8       ; jump if not
              ghi      rd           ; check for ovelow
              ani      080h
              lbnz     ftoi_ov      ; jump if ovelow
              glo      rf           ; shift number left
              shl
              plo      rf
              ghi      rf
              shlc
              phi      rf
              glo      rd
              shlc
              plo      rd
              ghi      rd
              shlc
              phi      rd
              glo      r9           ; get exponent
              adi      1            ; increment it
              plo      r9           ; and put it back
              lbr      ftoi_7       ; loop until exponent in range
ftoi_8:       ghi      r9           ; was fp number negative
              lbz      ftoi_8a
              glo      rf           ; 2's compliment number
              xri      0ffh
              adi      1
              plo      rf
              ghi      rf
              xri      0ffh
              adci     0
              phi      rf
              glo      rd
              xri      0ffh
              adci     0
              plo      rd
              ghi      rd
              xri      0ffh
              adci     0
              phi      rd
ftoi_8a:      ghi      rd           ; store number into destination
              str      r7
              dec      r7
              glo      rd
              str      r7
              dec      r7
              ghi      rf
              str      r7
              dec      r7
              glo      rf
              str      r7
              dec      r7           ; move destination pointer back
              adi      0            ; signal no ovelow
              rtn                   ; and return to caller

              endp
