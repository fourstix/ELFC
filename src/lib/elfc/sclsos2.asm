#include      ../macros.inc

;---------------------------------------------------------
; sclsos2 - scale a 16-bit pointer offset at the SOS
; of the expression stack 
; R7 - expression stack pointer    
; R8 - operand pointer
; usage:   CALL sclsos2
; returns: offset at SOS scaled by 2 on expression stack
;---------------------------------------------------------
            proc    sclsos2
          copy    r7, r8    ; set up operand pointer
          inc     r8        ; move to LSB of TOS
          inc     r8        ; move to MSB of TOS 
          inc     r8        ; move to LSB of SOS
          lda     r8        ; retrieve LSB of previous SOS
          shl               ; multiply by 2 
          plo     re        ; save in scratch register
          ldn     r8        ; get MSB of previous SOS
          shlc              ; multiply by 2 with carry
          str     r8        ; update MSB of SOS
          dec     r8
          glo     re        ; get shifted LSB from scratch register
          str     r8        ; update LSB on stack
          sex     r2        ; make sure X = SP
          rtn               ; and return to caller
            endp
