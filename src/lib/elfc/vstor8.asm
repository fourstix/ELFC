#include      ../include/ops_c.inc

;---------------------------------------------------------
; vstor8 - get a char value from the expression stack
; and store it in global or static variable 
; registers used:
;   R8 - pointer to char variable in memory 
;   R7 - pointer to expression stack    
; usage:   CALL vstor8
;            dw  vaddr 
; notes: leaves the 8-bit value on expression stack
;   with ESP unchanged
;---------------------------------------------------------
              proc vstor8          
            lda     r6    ; set up pointer to variable
            phi     r8
            lda     r6
            plo     r8    ; r8 points to variable
            sex     r7    ; X = ESP for expression stack
            irx           ; move ESP to LSB 
            ldn     r7    ; get LSB from stack
            str     r8    ; save LSB in variable
            dec     r7    ; move ESP  back to bottom of stack
            sex     r2    ; make sure X = SP 
            rtn           ; return to caller
              endp 
