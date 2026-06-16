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

; *********************************************
; ***** Add top two numbers on expr stack *****
; ***** R7 - points to expr stack         *****
; *********************************************
              proc    _addfp

              extrn   _addfpi

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
              call    _addfpi       ; Call addition
              inc     r7           ; Adjust expr stack
              inc     r7
              inc     r7
              inc     r7
              rtn                  ; And return

              endp

; ********************************************
; ***** Floating point addition          *****
; ***** RF - pointer to first fp number  *****
; ***** RD - pointer to second fp number *****
; ***** Uses: R7:R8 - first number (aa)  *****
; *****       RA:RB - second number (bb) *****
; *****       R9.0  - exponent           *****
; *****       R9.1  - sign               *****
; ********************************************
              proc    _addfpi

              extrn   _fpargs
              extrn   _fpcomp2
              extrn   _fpnorm
              extrn   _fpret_0
              extrn   _fpret_a
              extrn   _fpret_b

              ghi     r7           ; save expr stack
              stxd
              glo     r7
              stxd
              ghi     rf           ; save destination address
              stxd
              glo     rf
              stxd
              call    _fpargs      ; retrieve arguments
_fpsub_1:     lbz     _fpret_a      ; return a if b==0
              smi     0ffh         ; check for infinity
              lbz     _fpret_b     ; return b if b==infinity
              glo     r9           ; get exponent 1
              lbz     _fpret_b     ; return b if a==0
              smi     0ffh         ; check for infinity
              lbz     _fpret_a     ; return a if a==infinity
              glo     r9           ; get exponent 1
              str     r2           ; store for comparison
              ghi     r9           ; get exponent 2
              sm                   ; compare to exponent 1
              lbnf    fpadd_1      ; jump if b<a
              glo     r8           ; swap a and b
              plo     re
              glo     rb
              plo     r8
              glo     re
              plo     rb
              ghi     r8           ; swap a and b
              plo     re
              ghi     rb
              phi     r8
              glo     re
              phi     rb
              glo     r7           ; swap a and b
              plo     re
              glo     ra
              plo     r7
              glo     re
              plo     ra
              ghi     r7           ; swap a and b
              plo     re
              ghi     ra
              phi     r7
              glo     re
              phi     ra
              glo     r9           ; also swap exponents
              plo     re
              ghi     r9
              plo     r9
              glo     re
              phi     r9
fpadd_1:      ghi     r7           ; compare signs
              str     r2
              ghi     ra
              xor
              plo     rc           ; store operation, 0=+, 1=-
              ghi     r7           ; get sign of largest number
              phi     rc           ; save it for now
              ldi     0            ; clear high bytes of numbers
              phi     ra
              phi     r7
              glo     ra           ; set implied 1 bit
              ori     080h
              plo     ra
              glo     r7           ; in first number too
              ori     080h
              plo     r7
fpadd_2:      glo     r9           ; compare exponents
              str     r2
              ghi     r9
              sm
              lbz     fpadd_3;     ; jump if exponents match
              ghi     r9           ; increment exponent 2
              adi     1
              phi     r9
              ghi     ra           ; shift b right
              shr
              phi     ra
              glo     ra
              shrc
              plo     ra
              ghi     rb
              shrc
              phi     rb
              glo     rb
              shrc
              plo     rb
              lbr     fpadd_2      ; loop until exponents match
fpadd_3:      glo     rc           ; get operation
              shl                  ; shift into DF
              lbdf    fpadd_s      ; jump if subtraction
              glo     r8           ; a += b
              str     r2
              glo     rb
              add
              plo     r8
              ghi     r8
              str     r2
              ghi     rb
              adc
              phi     r8
              glo     r7
              str     r2
              glo     ra
              adc
              plo     r7
              ghi     r7
              str     r2
              ghi     ra
              adc
              phi     r7
              lbr     fpadd_4      ; jump to completion
fpadd_s:      glo     r8           ; a -= b
              str     r2
              glo     rb
              sd
              plo     r8
              ghi     r8
              str     r2
              ghi     rb
              sdb
              phi     r8
              glo     r7
              str     r2
              glo     ra
              sdb
              plo     r7
              ghi     r7
              str     r2
              ghi     ra
              sdb
              phi     r7
              shl                  ; need to check sign of answer
              lbnf    fpadd_4      ; jump if positive
              call    _fpcomp2     ; 2s compliment number
              ghi     rc           ; compliment sign
              xri     080h
              phi     rc           ; put it back
fpadd_4:      ghi     rc           ; move sign to R9.1
              shl
              ldi     0
              shlc
              phi     r9
              ghi     r7           ; check for zero
              lbnz    fpadd_5
              glo     r7
              lbnz    fpadd_5
              ghi     r8
              lbnz    fpadd_5
              glo     r8
              lbnz    fpadd_5
              lbr     _fpret_0     ; otherwise answer is 0
fpadd_5:      call    _fpnorm      ; normalize the answer
              lbr     _fpret_a     ; write answer and return

              public  _fpsub_1

              endp
