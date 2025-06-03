#include      ../macros.inc

;---------------------------------------------------------
; vdec8 - decrement 1-byte global or static variable 
;
; registers used:
;   R8 - temporary value    
;   R9 - pointer to variable in memory 
;
; usage:   CALL vdec8
;            dw  vaddr 
;
; note: static and global variable bytes are stored in 
;   the same order (LSB first) as auto variables on the
;   expression stack
;---------------------------------------------------------
              proc vdec8          
            lda     r6    ; set up pointer to variable
            phi     r9
            lda     r6
            plo     r9    ; r9 points to variable
            
            ldn     r9    ; get variable value
            plo     r8    ; save in temp register
            ldi     0     ; pad temp byte with zero
            phi     r8    ; save in temp register
            
            dec     r8    ; decrement temp value
            
            glo     r8    ; get decremented value
            str     r9    ; save in variable
            
            sex     r2    ; make sure X = SP 
            rtn           ; return to caller
              endp 
