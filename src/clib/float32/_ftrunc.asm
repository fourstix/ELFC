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
; ***** Truncate a floating point to integer  *****
; ***** Numbers are on expr stack             *****
; ***** RF - pointer to floating point number *****
; ***** RD - destination integer              *****
; ***** Returns: DF=1 - overflow              *****
; ***** Uses:                                 *****
; *****       R9.0  - exponent                *****
; *****       R9.1  - sign                    *****
; *****       RD:RF - number                  *****
; *****       RA:RB - fractional mask         *****
; *****       RC.0  - shift count             *****
; *************************************************
              proc     _ftrunc

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
              glo      rd           ; get low bit of exponent
              shl                   ; shift into DF
              ghi      rd           ; get high 7 bits of exponent
              shlc                  ; shift in the low bit
              plo      r9           ; store it
              lbnz     trnc_2       ; jump if exponent is not zero
trnc_0:       ldi      0            ; result is zero
              str      r7
              dec      r7
              str      r7
              dec      r7
trnc_low:     str      r7           ; entry point to set low word to zero
              dec      r7
              str      r7
              dec      r7
              adi      0            ; clear DF
              rtn                   ; return to caller

trnc_1:       ldi      03fh         ; return float 1 (3F80:0000)
              str      r7           ; set high word MSB
              dec      r7
              ldi      080h
              str      r7           ; set high word LSB
              dec      r7
              ldi      00h
              lbr      trnc_low     ; set low word to zero

trnc_2:       smi      07fh         ; check for 127
              lbz      trnc_1       ; if e = 127, then result is one
              lbnf     trnc_0       ; if e < 127, then result is zero
              plo      rc           ; save value as shift count
              smi      23           ; is e >= 150, then number is all integer
              lbdf    trnc_ld       ; load number and return X as result

              ldi      0            ; set up mask registers
              phi      ra           ; RA:RB = 007F:FFFF
              ldi      07fh
              plo      ra           ; first 9 bits of RA is sign and exponent
              ldi      0ffh         ; rest of ra and all of rb are the 23 significand bits
              phi      rb
              plo      rb

trnc_shft:    glo      rc
              lbz      trnc_mask    ; if done shift go to apply mask
              shr16    ra           ; shift high word right, lsb -> DF (msb = 0)
              shrc16   rb           ; shift low word right with DF -> msb
              dec      rc           ; count down mask bits
              lbr      trnc_shft    ; keep going

trnc_mask:    ghi      ra           ; invert the mask bits in high word
              xri      0ffh
              phi      ra
              glo      ra
              xri      0ffh
              plo      ra
              ghi      rb           ; invert the mask bits in low word
              xri      0ffh
              phi      rb
              glo      rb
              xri      0ffh
              plo      rb

              ghi      ra           ; And mask RA:RB with RD:RF
              str      r2           ; put MSB of high word mask in M(X)
              ghi      rd           ; get MSB of x high word
              and                   ; apply mask
              phi      rd           ; save MSB of result high word
              glo      ra           ; get LSB of mask high word
              str      r2           ; save in M(X)
              glo      rd           ; get LSB of x high word
              and                   ; apply mask
              plo      rd           ; save LSB of result high word

              ghi      rb           ; apply mask to low word of x
              str      r2           ; put MSB of low word mask in M(X)
              ghi      rf           ; get MSB of x low word
              and                   ; apply mask
              phi      rf           ; save MSB of result low word
              glo      rb           ; get LSB of mask low word
              str      r2           ; save in M(X)
              glo      rf           ; get LSB of x low word
              and                   ; apply mask
              plo      rf           ; save LSB of result low word

trnc_ld:      ghi      rd           ; store number into destination
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
