#include      ../macros.inc

;---------------------------------------------------------
; vpop16 - pop 2-byte value from expression stack into a
;   global or static variable location 
; registers used:
;   R8 - pointer to variable in memory 
;   R7 - pointer to expression stack 
; usage:   CALL vpop16
;            dw vaddr 
; returns: 16-bit variable set to TOS
; note: static and global variable bytes are stored in 
;   the same order (LSB first) as auto variables on the
;   expression stack
;---------------------------------------------------------
              proc vpop16
            sex     r7
            lda     r6   ; set r8 to point to variable 
            phi     r8
            lda     r6
            plo     r8  ; r8 points to LSB of variable
            irx         ; move to TOS 
            lda     r7  ; get LSB from stack
            str     r8  ; set LSB of variable
            inc     r8  ; move up to MSB of variable
            ldn     r7  ; get MSB from stack
            str     r8  ; set MSB of variable
            sex     r2
            rtn
              endp 
