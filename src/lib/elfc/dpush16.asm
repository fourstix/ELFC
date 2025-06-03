#include      ../macros.inc

;---------------------------------------------------------
; dpush16 - push 2-byte data value onto expression stack 
;   R7 - pointer to expression stack    
;   RA - data value for expression stack 
; Usage:   CALL dpush16
;---------------------------------------------------------
              proc dpush16
            sex     r7
            ghi     ra
            stxd
            glo     ra
            stxd
            sex     r2
            rtn           ; return to caller
              endp 
