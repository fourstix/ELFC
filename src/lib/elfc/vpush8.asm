#include      ../macros.inc

;---------------------------------------------------------
; vpush8 - push a global or static char type variable 
;   onto expression stack 
; registers used:
;   R8 - pointr to char variable in memory 
;   R7 - pointer to expression stack 
; usage:   CALL vpush8
;            dw vaddr 
; returns: char value on TOS
;---------------------------------------------------------
              proc vpush8
            lda     r6  ; set up pointer to char variable
            phi     r8
            lda     r6
            plo     r8
            sex     r7        
            ldi     0   ; promote to unsigned 16 bit value
            stxd        ; save padding byte in MSB
            lda     r8  ; get char value
            stxd        ; save as LSB on stack
            sex     r2
            rtn
              endp 
