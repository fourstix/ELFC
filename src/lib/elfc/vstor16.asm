#include      ../macros.inc

;---------------------------------------------------------
; vstor16 - get a 2-byte value from the expression stack
; and store it in global or static variable 
; registers used:
;   R8 - pointer to variable in memory 
;   R7 - pointer to expression stack    
; usage:   CALL vstor16
;            dw  vaddr 
; note: leaves 16-bit value on expression stack
;   with ESP unchanged
; note: static and global variable bytes are stored in 
;   the same order (LSB first) as auto variables on the
;   expression stack

;---------------------------------------------------------
              proc vstor16          
            lda     r6    ; set up pointer to variable
            phi     r8
            lda     r6
            plo     r8
            sex     r7    ; X = ESP for expression stack
            irx           ; move ESP to LSB
            lda     r7    ; get LSB from stack
            str     r8    ; save LSB in variable
            inc     r8    ; move to MSB of variable
            ldn     r7    ; get MSB from stack
            str     r8    ; save MSB in variable
            dec     r7    ; move ESP back to bottom of stack
            dec     r7
            sex     r2    ; make sure X = SP 
            rtn           ; return to caller
              endp 
