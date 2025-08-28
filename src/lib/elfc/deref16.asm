#include      ../include/ops_c.inc

;---------------------------------------------------------
; deref16 - replace a pointer on the expression stack
;   with the 16-bit value it references
;
; usage:   call deref16
; registers used:
;   R9 - pointer value from expression stack 
;   R7 - pointer to expression stack    
; returns: dereferenced 16-bit value on TOS
; note: static and global variable bytes are stored in 
;   the same order (LSB first) as auto variables on the
;   expression stack, so all variable storage classes 
;   are dereferenced the same.
;---------------------------------------------------------
              proc deref16
            sex     r7  ; set X = ESP
            irx         ; move to TOS 
            lda     r7  ; get low byte from stack
            plo     r9
            ldn     r7  ; get hi byte from stack
            phi     r9
            lda     r9  ; get LSB referenced by pointer
            plo     re  ; save LSB in scratch register
            ldn     r9  ; get MSB referenced by pointer
            stxd        ; save MSB on stack
            glo     re  ; get LSB from scratch register
            stxd        ; save LSB on stack
            sex     r2  ; make sure X=SP for return  
            rtn
              endp 
