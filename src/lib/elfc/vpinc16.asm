#include      ../include/ops_c.inc

;---------------------------------------------------------
; vpinc16 - increment a global or static pointer to a 
;   variable value at vaddr of size bytes
;
; registers used:
;   r8 - temporary value    
;   r9 - pointer to variable in memory
;   rc - size of pointer 
;
; usage:   CALL vpinc16
;            dw  vaddr 
;            dw  size
;
; note: static and global variable bytes are stored in 
;   the same order (LSB first) as auto variables on the
;   expression stack
;---------------------------------------------------------
              proc vpinc16       
     
            sex     r2      ; make sure X = SP 

            lda     r6      ; set up pointer to variable
            phi     r9
            lda     r6
            plo     r9      ; r9 points to variable

            lda     r6      ; set up pointer size
            phi     rc
            lda     r6
            plo     rc      ; rc has pointer size
            
            lda     r9      ; get LSB of variable value
            plo     r8      ; save in temp register
            ldn     r9      ; get MSB of variable value
            phi     r8      ; save in temp register
            
            addr16  r8, rc  ; increment pointer by size
            
            ghi     r8      ; get MSB of incremented value
            str     r9      ; save in MSB of variable
            dec     r9      ; move back to LSB of variable
            glo     r8      ; get LSB of incremented value
            str     r9      ; save in LSB of variable
            
            rtn             ; return to caller
              endp 
