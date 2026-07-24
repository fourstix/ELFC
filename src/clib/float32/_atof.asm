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

; ********************************************
; ***** Convert ASCII to floating point  *****
; ***** RF - Pointer to ASCII string     *****
; ***** RD - Desintation FP              *****
; ***** Uses:                            *****
; *****       R7:R8 - mantissa           *****
; *****       R9.0  - exponent           *****
; *****       R9.1  - sign               *****
; *****       RA:RB - mask               *****
; *****       RC    - fractional pointer *****
; ********************************************
              proc     _atof

.link .requires C_fp_const

              extrn    _atoi32
              extrn    _divfpi
              extrn    _fpnorm
              extrn    _mulfpi

              extrn    C_fp_ten

; +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
; +++++ First convert integer portion to floating point +++++
; +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
              ghi      r7           ; save expr stack
              stxd
              glo      r7
              stxd
              ldi      0            ; set sign to positive
              phi      r9
              ldn      rf           ; get first byte from buffer
              smi      '-'          ; is it minus
              lbnz     atof_1       ; jump if not
              ldi      1            ; indicate negative number
              phi      r9
              inc      rf           ; and move past minus
atof_1:       ghi      rd           ; save destination
              stxd
              glo      rd
              stxd
              ghi      r9           ; save sign
              stxd
              call     _atoi32      ; convert integer portion of number
              irx
              ldxa                  ; recover sign
              phi      r9
              ldxa                  ; recover destination
              plo      rd
              ldx
              phi      rd
              dec      r2           ; and keep on stack
              dec      r2
              lda      rd           ; retrieve integer number
              phi      r7
              str      r2           ; store for zero check
              lda      rd
              plo      r7
              or                    ; combine with zero check
              str      r2
              lda      rd
              phi      r8
              or                    ; combine with zero check
              str      r2
              lda      rd
              plo      r8
              or                    ; combine with zero check
              lbz      atof_z       ; jump if integer is zero
              ldi      150          ; initial exponent starts at 150
              plo      r9
              ldi      1            ; initial mask is 1
              plo      rb
              ldi      0
              phi      rb
              plo      ra
              phi      ra
              ghi      r7           ; check if high byte has anything
              lbz      atof_b       ; jump if not
atof_a1:      ghi      r7           ; get high byte
              lbz      atof_a2      ; jump if done shifting
              shr                   ; shift mantissa right
              phi      r7
              glo      r7
              shrc
              plo      r7
              ghi      r8
              shrc
              phi      r8
              glo      r8
              shrc
              plo      r8
              glo      r9           ; get exponent
              adi      1            ; increment it
              plo      r9           ; put it back
              lbr      atof_a1      ; loop until high byte cleared
atof_a2:      ldi      0            ; clear mask
              phi      ra
              plo      ra
              phi      rb
              plo      rb
              lbr      atof_2       ; and then jump to next section
atof_b:       glo      r7           ; get first byte of mantissa
              shl                   ; shift high bit into DF
              lbdf     atof_2       ; if set, no more shifts needed
              glo      r8           ; shift mantissa left
              shl
              plo      r8
              ghi      r8
              shlc
              phi      r8
              glo      r7
              shlc
              plo      r7
              glo      rb           ; shift mask left
              shl
              plo      rb
              ghi      rb
              shlc
              phi      rb
              glo      ra
              shlc
              plo      ra
              glo      r9           ; get exponent
              smi      1            ; decrement it
              plo      r9           ; and put it back
              lbr      atof_b       ; loop until high bit of mantissa set
atof_z:       ldi      080h         ; set initial mask
              plo      ra
              ldi      0
              phi      ra
              phi      rb
              plo      rb
              ldi      127          ; initial exponent
              plo      r9
; ++++++++++++++++++++++++++++++++++++++++++++++++++
; +++++ Now convert number after decimal point +++++
; ++++++++++++++++++++++++++++++++++++++++++++++++++
atof_2:       ldn      rf           ; get next byte from input
              smi      '.'          ; is it a decimal
              lbnz     atof_e       ; jump if not
              inc      rf           ; move past decimal
              ldi      99           ; need marker on stack
              stxd
atof_2a:      lda      rf           ; get next byte from input
              plo      re           ; keep a copy
              smi      '0'          ; see if below digits
              lbnf     atof_2b      ; jump if not valid digit
              smi      10           ; check for high of range
              lbdf     atof_2b      ; jump if not valid digit
              glo      re           ; recover number
              smi      '0'          ; convert to binary
              stxd                  ; and store on stack
              lbr      atof_2a      ; loop until all numerals copied
atof_2b:      dec      rf           ; move pointer back to non-numeral character
; ------------------------------------
; ----- Main loop for fractional -----
; ------------------------------------
atof_2c:      glo      rb           ; check mask for zero
              lbnz     atof_2d
              ghi      rb
              lbnz     atof_2d
              glo      ra
              lbnz     atof_2d
              lbr      atof_2z      ; done with fractional
atof_2d:      glo      r7           ; check mantissa for zero
              lbnz     atof_2e
              ghi      r8
              lbnz     atof_2e
              glo      r8
              lbnz     atof_2e
              glo      r9           ; zero result
              smi      1            ; so subtract 1 from exponent
              plo      r9           ; put it back
              lbr      atof_2f
atof_2e:      glo      ra           ; if result nonzero, shift mask right
              shr
              plo      ra
              ghi      rb
              shrc
              phi      rb
              glo      rb
              shrc
              plo      rb
atof_2f:      ldi      0            ; set carry to 0
              plo      re
              glo      r2           ; point to fractional data
              plo      rc
              ghi      r2
              phi      rc
              inc      rc
atof_2g:      ldn      rc           ; get next byte from fractional
              smi      99           ; check for end
              lbz      atof_2j      ; jump if end found
              glo      re           ; get carry
              shr                   ; shift into DF
              ldn      rc           ; get next fractional digit
              shlc                  ; add to itself plus carry
              str      rc           ; put it back
              smi      10           ; see if exceeded 10
              lbnf     atof_2h      ; jump if not
              str      rc           ; store corrected number
              ldi      1            ; set carry
atof_2i:      plo      re
              inc      rc           ; point to next character
              lbr      atof_2g      ; and loop back for more
atof_2h:      ldi      0            ; clear carry
              lbr      atof_2i
atof_2j:      glo      re           ; get carry
              shr                   ; shift into DF
              lbnf     atof_2c      ; loop until mask==0
              glo      rb           ; check mask for zero
              lbnz     atof_2k      ; jump if not zero
              ghi      rb
              lbnz     atof_2k      ; jump if not zero
              glo      ra
              lbnz     atof_2k      ; jump if not zero
              glo      r8           ; mask==0, add 1
              adi      1
              plo      r8
              ghi      r8
              adci     0
              phi      r8
              glo      r7
              adci     0
              plo      r7
              lbr      atof_2z      ; done with fractional
atof_2k:      glo      rb           ; combine mask with result
              str      r2
              glo      r8
              or
              plo      r8
              ghi      rb
              str      r2
              ghi      r8
              or
              phi      r8
              glo      ra
              str      r2
              glo      r7
              or
              plo      r7
              lbr      atof_2c      ; loop until mask == 0
atof_2z:      irx                   ; clean temp data from stack
atof_2z2:     ldxa                  ; get next byte
              smi      99           ; look for end marker
              lbnz     atof_2z2     ; loop until marker found
              dec      r2           ; move stack pointer back
atof_e:       call     _fpnorm       ; normalize number
              ldn      rf           ; get next character
              smi      'E'          ; check for exponent
              lbz      atof_ex      ; jump if so
              smi      32           ; check lowercase e as well
              lbz      atof_ex      ; jump if exponent
atof_dn:      irx                   ; recover destination
              ldxa
              plo      rd
              ldx
              phi      rd
              ghi      r7           ; store answer in destination
              str      rd
              inc      rd
              glo      r7
              str      rd
              inc      rd
              ghi      r8
              str      rd
              inc      rd
              glo      r8
              str      rd
              dec      rd           ; restore destination pointer
              dec      rd
              dec      rd
              irx                   ; recover expr stack
              ldxa
              plo      r7
              ldx
              phi      r7
              rtn                   ; return to caller
; ++++++++++++++++++++++++++++
; +++++ Process exponent +++++
; ++++++++++++++++++++++++++++
atof_ex:      ldi      0            ; signal positive exponent
              phi      r9           ; put it here
              inc      rf           ; move past E
              ldn      rf           ; need to check for sign
              smi      '+'          ; check for positive
              lbz      atof_exp     ; jump if so
              smi      2            ; check for negative
              lbnz     atof_ex1     ; jump if not
              ldi      1            ; signal negative number
              phi      r9
atof_exp:     inc      rf           ; move past sign
atof_ex1:     ldi      0            ; set exponent count to zero
              plo      rc
atof_ex2:     ldn      rf           ; get byte from input
              smi      '0'          ; see if below digits
              lbnf     atof_ex3     ; jump if not valid digit
              smi      10           ; check for high of range
              lbdf     atof_ex3     ; jump if not valid digit
              glo      rc           ; get count
              shl                   ; multiply by 2
              str      r2           ; save for add
              shl                   ; multiply by 4
              shl                   ; by 8
              add                   ; by 10
              str      r2           ; store for add
              lda      rf           ; get input byte
              smi      '0'          ; convert to binary
              add                   ; add in prior total
              plo      rc           ; put it back
              lbr      atof_ex2     ; loop until no more digits
atof_ex3:     ghi      r7           ; put result on stack
              stxd
              glo      r7
              stxd
              ghi      r8
              stxd
              glo      r8
              stxd
              ghi      r9           ; check sign of exponent
              shr
              lbdf     atof_exn     ; jump if negative
atof_ex4:     glo      rc           ; see if done
              lbz      atof_exd     ; jump if done
              glo      r2           ; point to result
              plo      rf
              ghi      r2
              phi      rf
              inc      rf
              ldi      C_fp_ten.1   ; point to 10.0
              phi      rd
              ldi      C_fp_ten.0
              plo      rd
              glo      rc           ; save count
              stxd
              call     _mulfpi       ; multiply result by 10.0
              irx                   ; recover count
              ldx
              plo      rc           ; put back into count
              dec      rc           ; decrement count
              lbr      atof_ex4     ; loop until done
atof_exn:     glo      rc           ; see if done
              lbz      atof_exd     ; jump if done
              glo      r2           ; point to result
              plo      rf
              ghi      r2
              phi      rf
              inc      rf
              ldi      C_fp_ten.1   ; point to 10.0
              phi      rd
              ldi      C_fp_ten.0
              plo      rd
              glo      rc           ; save count
              stxd
              call     _divfpi      ; divide result by 10.0
              irx                   ; recover count
              ldx
              plo      rc           ; put back into count
              dec      rc           ; decrement count
              lbr      atof_exn     ; loop until done
atof_exd:     irx                   ; recover answer
              ldxa
              plo      r8
              ldxa
              phi      r8
              ldxa
              plo      r7
              ldx
              phi      r7
              lbr      atof_dn      ; and return result

              endp
