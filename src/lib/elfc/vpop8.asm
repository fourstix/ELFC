#include      ../macros.inc

;---------------------------------------------------------
; vpop8 - pop 8-bit character value from expression stack 
;   into a static or global char variable
; registers used:
;   R8 - labeled variable address 
;   R7 - pointer to expression stack 
; usage:   CALL vpop8
;            dw vaddr 
; returns: char variable set to TOS
;---------------------------------------------------------
              proc epop8
            lda     r6  ; set r8 to point to variable 
            phi     r8
            lda     r6
            plo     r8  ; r8 points to char value
            sex     r7      
            irx         ; move to TOS 
            lda     r7  ; read byte from stack
            str     r8  ; store byte as character
            sex     r2  
            rtn
              endp 
