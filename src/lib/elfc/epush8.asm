#include      ../include/ops_c.inc

;---------------------------------------------------------
; epush8 - push 8-bit char value onto expression stack 
; registers used:
;   R7 - pointer to expression stack 
; usage:   CALL epush8u
;            db 'a'
;---------------------------------------------------------
              proc epush8
            sex     r7
            ldi     0   ; promote to unsigned 16 bit value
            stxd       
            lda     r6
            stxd
            sex     r2
            rtn
              endp 
