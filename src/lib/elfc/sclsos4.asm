#include      ../macros.inc

;---------------------------------------------------------
; sclsos4 - scale a pointer offset to 32-bit value at the 
; SOS of the expression stack
; R7 - expression stack pointer    
; R8 - operand pointer
; usage:   CALL sclsos4
; returns: offset at SOS scaled by 4 on expression stack
;---------------------------------------------------------
            proc    sclsos4
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
          glo     re        ; get LSB from scratch register
          shl               ; multiply LSB by 2 again
          plo     re        ; save in scratch register
          ldn     r8        ; get shifted MSB of previous SOS
          shlc              ; multiply MSB by 2 with carry again
          str     r8        ; update MSB of SOS
          glo     re        ; get LSB from scratch register          
          dec     r8
          glo     re        ; get shifted LSB from scratch register
          str     r8        ; update LSB on stack
          sex     r2        ; make sure X = SP
          rtn               ; and return to caller
            endp
