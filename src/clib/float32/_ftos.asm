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
; ***** Convert floating point to ASCII       *****
; ***** RF - pointer to floating point number *****
; ***** RD - destination buffer               *****
; ***** Uses:                                 *****
; *****       R9.0  - exponent                *****
; *****       R9.1  - E                       *****
; *****       R7:R8 - number                  *****
; *****       RA:RB - fractional              *****
; *****       RC.0  - digit count             *****
; *************************************************
              proc     _ftos

.link .requires C_fp_const

              extrn    _divfpi
              extrn    _itoa32
              extrn    _mulfpi
              extrn    C_fp_ten

              ghi      r7           ; save expr stack
              stxd
              glo      r7
              stxd
              lda      rf           ; retrieve number into R7:  R8
              plo      r8
              lda      rf
              phi      r8
              lda      rf
              plo      r7
              lda      rf
              phi      r7
              shl                   ; shift sign into DF
              lbnf     ftoa_1       ; jump if number is positive
              ldi      '-'          ; place minus sign into output
              str      rd
              inc      rd
ftoa_1:       glo      r7           ; get low bit of exponent
              shl                   ; shift into DF
              ghi      r7           ; get high 7 bits of exponent
              shlc                  ; shift in the low bit
              plo      r9           ; store it
              lbnz     ftoa_2       ; jump if exponent is not zero
              ldi      '0'          ; write 0 digit to output
              str      rd
              inc      rd
ftoa_t:       ldi      0            ; terminate output
              str      rd
              irx                   ; recover expr stack
              ldxa
              plo      r7
              ldx
              phi      r7
              rtn                   ; and return to caller
ftoa_2:       smi      0ffh         ; check for infinity
              lbnz     ftoa_3       ; jump if not
              ldi      'I'          ; write inf to output
              str      rd
              inc      rd
              ldi      'n'
              str      rd
              inc      rd
              ldi      'f'
              str      rd
              inc      rd
              lbr      ftoa_t       ; terminate string and return
ftoa_3:       ghi      rd           ; save destination pointer
              stxd
              glo      rd
              stxd
              ldi      0            ; clear E
              phi      r9
              glo      r9           ; check exponent for greater than 129
              smi      129

              lbnf     ftoa_4       ; jump if <= 129
              ghi      r7           ; put number on the stack
              stxd
              glo      r7
              stxd
              ghi      r8
              stxd
              glo      r8
              stxd
ftoa_3a:      glo      r9           ; get exponent
              smi      130          ; looking for below 131
              lbnf     ftoa_3z      ; jump if done scaling
              glo      r2           ; point to number
              plo      rf
              ghi      r2
              phi      rf
              inc      rf
              ghi      r9           ; get E
              stxd                  ; and save on stack
              ldi      C_fp_ten.1   ; need to divide by 10
              phi      rd
              ldi      C_fp_ten.0
              plo      rd
              call     _divfpi      ; perform the division
              irx                   ; recover E
              ldx
              adi      1            ; increment E
              phi      r9           ; and put it back
              glo      r2           ; point to new exponent
              adi      3
              plo      rf
              ghi      r2
              adci     0
              phi      rf
              lda      rf           ; get low bit
              shl                   ; shift into DF
              ldn      rf           ; get high 7 bites
              shlc                  ; shift in the low bit
              plo      r9           ; and store it
              lbr      ftoa_3a      ; loop until exponent in correct range
ftoa_3z:      irx                   ; retrieve the number from the stack
              ldxa
              plo      r8
              ldxa
              phi      r8
              ldxa
              plo      r7
              ldx
              phi      r7
ftoa_4:       glo      r9           ; check exponent for less than 127
              smi      127
              lbdf     ftoa_5       ; jump if > 127
              ghi      r7           ; put number on the stack
              stxd
              glo      r7
              stxd
              ghi      r8
              stxd
              glo      r8
              stxd
ftoa_4a:      glo      r9           ; get exponent
              smi      127          ; looking for below 127
              lbdf     ftoa_4z      ; jump if done scaling
              glo      r2           ; point to number
              plo      rf
              ghi      r2
              phi      rf
              inc      rf
              ghi      r9           ; get E
              stxd                  ; and save on stack
              ldi      C_fp_ten.1   ; need to multiply by 10
              phi      rd
              ldi      C_fp_ten.0
              plo      rd
              call     _mulfpi      ; perform the multiplication
              irx                   ; recover E
              ldx
              smi      1            ; decrement E
              phi      r9           ; and put it back
              glo      r2           ; point to new exponent
              adi      3
              plo      rf
              ghi      r2
              adci     0
              phi      rf
              lda      rf           ; get low bit
              shl                   ; shift into DF
              ldn      rf           ; get high 7 bites
              shlc                  ; shift in the low bit
              plo      r9           ; and store it
              lbr      ftoa_4a      ; loop until exponent in correct range
ftoa_4z:      irx                   ; retrieve the number from the stack
              ldxa
              plo      r8
              ldxa
              phi      r8
              ldxa
              plo      r7
              ldx
              phi      r7
ftoa_5:       ldi      0            ; clear high byte of number
              phi      r7
              glo      r7           ; set implied 1
              ori      080h
              plo      r7           ; and put it back
              ldi      0            ; clear fractional
              phi      ra
              plo      ra
              phi      rb
              plo      rb
ftoa_6:       glo      r9           ; get exponent
              smi      150          ; check for less than 150
              lbdf     ftoa_7       ; jump if not
              glo      r7           ; shift number right
              shr
              plo      r7
              ghi      r8
              shrc
              phi      r8
              glo      r8
              shrc
              plo      r8
              glo      ra
              shrc
              plo      ra
              ghi      rb
              shrc
              phi      rb
              glo      rb
              shrc
              plo      rb
              glo      r9           ; get exponent
              adi      1            ; increase it
              plo      r9           ; put it back
              lbr      ftoa_6       ; loop back until exponent >= 150
ftoa_7:       glo      r9           ; get exponent
              smi      151          ; check for greater than 150
              lbnf     ftoa_8       ; jump if not
              glo      r8           ; shift number left
              shl
              plo      r8
              ghi      r8
              shlc
              phi      r8
              glo      r7
              shlc
              plo      r7
              ghi      r7
              shlc
              phi      r7
              glo      r9           ; get exponent
              adi      1            ; increment it
              plo      r9           ; and put it back
              lbr      ftoa_7       ; loop until exponent in range
ftoa_8:       irx                     ; recover destination
              ldxa
              plo      rd
              ldx
              phi      rd
              ghi      r7           ; place integer portion on stack
              stxd
              glo      r7
              stxd
              ghi      r8
              stxd
              glo      r8
              stxd
              glo      r2           ; point source to integer number
              plo      rf
              ghi      r2
              phi      rf
              inc      rf
              ghi      ra           ; save registers consumed by itoa
              stxd
              glo      ra
              stxd
              ghi      rb
              stxd
              glo      rb
              stxd
              ghi      r9
              stxd
              glo      r9
              stxd
              call     _itoa32      ; call itoa to convert integer portion of result
              irx                   ; recover consumed registers
              ldxa
              plo      r9
              ldxa
              phi      r9
              ldxa
              plo      rb
              ldxa
              phi      rb
              ldxa
              plo      ra
              ldx
              phi      ra
              irx                   ; remove number from stack
              irx
              irx
              irx
              glo      ra           ; check for nonzero fractional
              lbnz     ftoa_9       ; jump if not zero
              ghi      rb
              lbnz     ftoa_9
              glo      rb
              lbnz     ftoa_9
              ldi      '.'          ; need decimal point
              str      rd           ; store into destination
              inc      rd
              lbr      ftoa_e       ; no fractional digits, jump to E processing
ftoa_9:       ghi      r9           ; check if need E
              lbz      ftoa_9c2     ; jump if not
              dec      rd           ; get 2 characters back
              dec      rd
              lda      rd           ; get it
              smi      '1'          ; see if it was 1
              lbnz     ftoa_9c      ; jump if not
              ldn      rd           ; get 2nd number
              plo      re           ; save it
              ldi      '.'          ; replace it with a dot
              str      rd
              inc      rd
              glo      re           ; recover number
              str      rd           ; and store into destination
              inc      rd
              ghi      r9           ; get E
              adi      1            ; increment it
              phi      r9           ; and put it back
              lbr      ftoa_9d      ; then continue
ftoa_9c:      inc      rd           ; put RD back to original position
ftoa_9c2:     ldi      '.'          ; need decimal point
              str      rd           ; store into destination
              inc      rd
ftoa_9d:      ldi      6            ; set digit count
              plo      rc
ftoa_9a:      glo      ra           ; check if fractional is still non-zero
              lbnz     ftoa_9b      ; jump if not
              ghi      rb
              lbnz     ftoa_9b
              glo      rb
              lbz      ftoa_e       ; on to E processing if no more fractional bits
ftoa_9b:      glo      rb           ; multiply fractional by 2
              shl
              plo      rb
              plo      r8           ; put copy in R7:  R8 as well
              ghi      rb
              shlc
              phi      rb
              phi      r8
              glo      ra
              shlc
              plo      ra
              plo      r7
              ghi      ra
              shlc
              phi      ra
              phi      r7
              glo      r8           ; now multiply R7:  R8 by 2
              shl
              plo      r8
              ghi      r8
              shlc
              phi      r8
              glo      r7
              shlc
              plo      r7
              ghi      r7
              shlc
              phi      r7
              glo      r8           ; now multiply R7:  R8 by 4
              shl
              plo      r8
              ghi      r8
              shlc
              phi      r8
              glo      r7
              shlc
              plo      r7
              ghi      r7
              shlc
              phi      r7
              glo      rb           ; now add R7:  R8 to RA:RB
              str      r2
              glo      r8
              add
              plo      rb
              ghi      rb
              str      r2
              ghi      r8
              adc
              phi      rb
              glo      ra
              str      r2
              glo      r7
              adc
              plo      ra
              ghi      ra
              str      r2
              ghi      r7
              adc
              phi      ra           ; D now has decimal byte
              adi      '0'          ; convert to ASCII
              str      rd           ; and write to destination
              inc      rd
              ldi      0            ; clear high byte of fractional
              phi      ra
              dec      rc           ; increment counter
              glo      rc           ; need to see if done
              lbnz     ftoa_9a      ; loop until done
ftoa_e:       ghi      r9           ; need to check for E
              lbz      ftoa_dn      ; jump if no E needed
              ldi      'E'          ; write E to output
              str      rd
              inc      rd
              ghi      r9           ; see if E was negative
              shl
              lbnf     ftoa_ep      ; jump if not
              ldi      '-'          ; write minus sign to output
              str      rd
              inc      rd
              ghi      r9           ; then 2s compliment E
              xri      0ffh
              adi      1
              phi      r9           ; and put it back
              lbr      ftoa_e1      ; then continue
ftoa_ep:      ldi      '+'          ; write plus to output
              str      rd
              inc      rd
ftoa_e1:      ldi      0            ; place E as 32-bits onto stack
              stxd
              stxd
              stxd
              ghi      r9
              stxd
              glo      r2           ; point rf to number
              plo      rf
              ghi      r2
              phi      rf
              inc      rf
              call     _itoa32      ; call itoa to display E
              irx                   ; remove number from stack
              irx
              irx
              irx
ftoa_dn:      ldi      0            ; terminate string
              str      rd
              irx                   ; recover expr stack
              ldxa
              plo      r7
              ldx
              phi      r7
              rtn                   ; and return to caller

              endp

; ***************************************************
; ***** Convert 32-bit binary to ASCII          *****
; ***** RF - Pointer to 32-bit integer          *****
; ***** RD - destination buffer                 *****
; ***************************************************
              proc    _itoa32

              extrn   _tobcd32

              lda     rf           ; retrieve number into R7:R8
              plo     rb
              lda     rf
              phi     rb
              lda     rf
              plo     ra
              lda     rf
              phi     ra
              glo     r2           ; make room on stack for buffer
              smi     11
              plo     r2
              ghi     r2
              smbi    0
              phi     r2
              glo     r2           ; RF is output buffer
              plo     rf
              ghi     r2
              phi     rf
              inc     rf
              ghi     ra           ; get high byte
              shl                  ; shift bit to DF
              lbdf    itoa32n      ; negative number
itoa321:      call    _tobcd32     ; convert to bcd
              glo     r2
              plo     rf
              ghi     r2
              phi     rf
              inc     rf
              ldi     10
              plo     rb
              ldi     9            ; max 9 leading zeros
              phi     rb
loop1:        lda     rf
              lbz     itoa32z      ; check leading zeros
              str     r2           ; save for a moment
              ldi     0            ; signal no more leading zeros
              phi     rb
              ldn     r2           ; recover character
itoa322:      adi     030h
              str     rd           ; store into output buffer
              inc     rd
itoa323:      dec     rb
              glo     rb
              lbnz    loop1
              glo     r2           ; pop work buffer off stack
              adi     11
              plo     r2
              ghi     r2
              adci    0
              phi     r2
              ldi     0            ; place terminator in destination
              str     rd
              rtn                  ; return to caller
itoa32z:      ghi     rb           ; see if leading have been used up
              lbz     itoa322      ; jump if so
              smi     1            ; decrement count
              phi     rb
              lbr     itoa323      ; and loop for next character
itoa32n:      ldi     '-'          ; show negative
              str     rd           ; write to destination buffer
              inc     rd
              glo     rb           ; 2s compliment
              xri     0ffh
              adi     1
              plo     rb
              ghi     rb
              xri     0ffh
              adci    0
              phi     rb
              glo     ra
              xri     0ffh
              adci    0
              plo     ra
              ghi     ra
              xri     0ffh
              adci    0
              phi     ra
              lbr     itoa321        ; now convert/show number

              endp

; *****************************************
; ***** Convert RA:RB to bcd in M[RF] *****
; *****************************************
              proc    _tobcd32

              glo     rf           ; transfer address to rc
              plo     rc
              ghi     rf
              phi     rc
              ldi     10           ; 10 bytes to clear
              plo     re
tobcd32lp1:   ldi     0
              str     rc           ; store into answer
              inc     rc
              dec     re           ; decrement count
              glo     re           ; get count
              lbnz    tobcd32lp1   ; loop until done
              glo     rf           ; recover address
              plo     rc
              ghi     rf
              phi     rc
              ldi     32           ; 32 bits to process
              plo     r9
tobcd32lp2:   ldi     10           ; need to process 5 cells
              plo     re           ; put into count
tobcd32lp3:   ldn     rc           ; get byte
              smi     5            ; need to see if 5 or greater
              lbnf    tobcd32l3a   ; jump if not
              adi     8            ; add 3 to original number
              str     rc           ; and put it back
tobcd32l3a:   inc     rc           ; point to next cell
              dec     re           ; decrement cell count
              glo     re           ; retrieve count
              lbnz    tobcd32lp3   ; loop back if not done
              glo     rb           ; start by shifting number to convert
              shl
              plo     rb
              ghi     rb
              shlc
              phi     rb
              glo     ra
              shlc
              plo     ra
              ghi     ra
              shlc
              phi     ra
              shlc                 ; now shift result to bit 3
              shl
              shl
              shl
              str     rc
              glo     rf           ; recover address
              plo     rc
              ghi     rf
              phi     rc
              ldi     10           ; 10 cells to process
              plo     re
tobcd32lp4:   lda     rc           ; get current cell
              str     r2           ; save it
              ldn     rc           ; get next cell
              shr                  ; shift bit 3 into df
              shr
              shr
              shr
              ldn     r2           ; recover value for current cell
              shlc                 ; shift with new bit
              ani     0fh          ; keep only bottom 4 bits
              dec     rc           ; point back
              str     rc           ; store value
              inc     rc           ; and move to next cell
              dec     re           ; decrement count
              glo     re           ; see if done
              lbnz    tobcd32lp4   ; jump if not
              glo     rf           ; recover address
              plo     rc
              ghi     rf
              phi     rc
              dec     r9           ; decrement bit count
              glo     r9           ; see if done
              lbnz    tobcd32lp2   ; loop until done
              rtn                  ; return to caller

              endp
