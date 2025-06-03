#include      ../macros.inc

;---------------------------------------------------------
; vpush16 - push 2-byte global or static variable 
;   onto expression stack
; registers used:
;   R8 - pointer to variable in memory 
;   R7 - pointer to expression stack    
; usage:   CALL vpush16
;            dw  vaddr 
; returns: 16-bit value on TOS
; note: static and global variable bytes are stored in 
;   the same order (LSB first) as auto variables on the
;   expression stack
;---------------------------------------------------------
              proc vpush16          
            lda     r6    ; set up pointer to variable
            phi     r8
            lda     r6
            plo     r8    ; r8 points to LSB of variable
            sex     r7    ; set X = ES
            lda     r8    ; get LSB of variable value
            plo     re    ; save in scratch register
            ldn     r8    ; get MSB of variable value
            stxd          ; save MSB on stack
            glo     re    ; get LSB from scratch register
            stxd          ; save on stack
            sex     r2    ; set X = SP
            rtn           ; return to caller
              endp 
