#include      ../macros.inc

;---------------------------------------------------------
; dpush8 - push 1-byte data value onto expression stack 
;   R7 - pointer to expression stack    
;   RA.0 - data value for expression stack 
; Usage:   call dpush8
; note:    since char is unsigned type, MSB = 0 on stack   
;---------------------------------------------------------
              proc dpush8
            sex     r7
            ldi     0     ; char is unsigned type
            stxd          ; so pad with zero
            glo     ra
            stxd
            sex     r2
            rtn           ; return to caller
              endp 
