#include      ../macros.inc

;---------------------------------------------------------
; deref8 - replace a pointer on the expression stack
;   with the 8-bit value it references
;
; usage:   call deref8
; registers used:
;   R9 - pointer value from expression stack 
;   R7 - pointer to expression stack    
; returns: dereferenced char value on TOS
;---------------------------------------------------------
              proc deref8
            sex     r7  ; set X = ESP
            irx         ; move to TOS 
            lda     r7  ; get low byte from stack
            plo     r9
            ldn     r7  ; get hi byte from stack
            phi     r9
            ldi     0   ; pad 8-bit value with zero
            stxd        ; put MSB on stack
            lda     r9  ; get char referenced by pointer
            stxd        ; save LSB on stack
            sex     r2  ; make sure X=SP for return  
            rtn
              endp 
