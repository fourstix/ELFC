#include      ../macros.inc

;---------------------------------------------------------
; scltos16 - scale a 16-bit pointer offset at the TOS 
; of the expression stack 
; R7 - expression stack pointer    
; R8 - operand pointer
; usage:   CALL scale16
; returns: TOS scaled by 2 on expression stack
;---------------------------------------------------------
            proc    scltos16
          copy    r7, r8    ; set up operand pointer
          inc     r8        ; move to LSB of TOS
          lda     r8        ; retrieve LSB of previous TOS
          shl               ; multiply by 2 
          plo     re        ; save in scratch register
          ldn     r8        ; get MSB of previous TOS
          shlc              ; multiply by 2 with carry
          str     r8        ; update MSB
          dec     r8
          glo     re        ; get shifted LSB from scratch register
          str     r8        ; update LSB on stack
          sex     r2        ; make sure X = SP
          rtn               ; and return to caller
            endp
