#include      ../macros.inc

;---------------------------------------------------------
; dpop8 - pop 8-bit value from expression stack 
;   R7 - pointer to expression stack    
;   RA.0 - data value from expression stack 
; usage:   CALL dpop8
; returns: RA.0 - 8-bit value from expression stack
; note:    since char is unsigned type, RA.1 = 0   
;---------------------------------------------------------
              proc dpop8
            sex     r7      
            irx         ; move to TOS 
            lda     r7  ; read byte from stack
            plo     ra  ; no need to read last byte
            ldi     0   ; pad with zero
            phi     ra  ; since char is unsigned
            sex     r2  
            rtn
              endp 
