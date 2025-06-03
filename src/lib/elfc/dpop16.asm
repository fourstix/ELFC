#include      ../macros.inc

;---------------------------------------------------------
; dpop16 - pop 2-byte value expression stack 
;   R7 - pointer to expression stack    
;   RA - data value from expression stack 
; usage:   CALL epop16
; returns: RA - value from expression stack
;---------------------------------------------------------
              proc dpop16
            sex     r7
            irx         ; move to TOS 
            lda     r7  ; get low byte from stack
            plo     ra
            ldn     r7  ; get hi byte from stack
            phi     ra
            sex     r2
            rtn
              endp 
