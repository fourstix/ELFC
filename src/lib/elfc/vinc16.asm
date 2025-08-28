#include      ../include/ops_c.inc

;---------------------------------------------------------
; vinc16 - increment 2-byte global or static variable 
;
; registers used:
;   r8 - temporary value    
;   r9 - pointer to variable in memory 
;
; usage:   CALL vinc16
;            dw  vaddr 
;
; note: static and global variable bytes are stored in 
;   the same order (LSB first) as auto variables on the
;   expression stack
;---------------------------------------------------------
              proc vinc16          
            lda     r6    ; set up pointer to variable
            phi     r9
            lda     r6
            plo     r9    ; r9 points to variable
            
            lda     r9    ; get LSB of variable value
            plo     r8    ; save in temp register
            ldn     r9    ; get MSB of variable value
            phi     r8    ; save in temp register
            
            inc     r8    ; increment temp value
            
            ghi     r8    ; get MSB of incremented value
            str     r9    ; save in MSB of variable
            dec     r9    ; move back to LSB of variable
            glo     r8    ; get LSB of incremented value
            str     r9    ; save in LSB of variable
            
            sex     r2    ; make sure X = SP 
            rtn           ; return to caller
              endp 
