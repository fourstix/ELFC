#include      ../macros.inc

;---------------------------------------------------------
; epush16 - push 2-byte constant onto expression stack 
; R7 - pointer to expression stack    
; Usage:   CALL epush16
;            dw $4321
;---------------------------------------------------------
              proc epush16
            sex     r7
            lda     r6
            stxd
            lda     r6
            stxd
            sex     r2
            rtn           ; return to caller
              endp 
