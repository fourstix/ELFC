#include      ../include/ops_c.inc

;---------------------------------------------------------
; vpush16 - push 2-byte global or static variable 
;   onto expression stack
; registers used:
;   R8 - pointer to variable in memory 
;   R7 - pointer to expression stack    
; usage:   GOSUB vpush16
;            dw  vaddr 
; returns: 16-bit value on TOS
; note: static and global variable bytes are stored in 
;   the same order (LSB first) as auto variables on the
;   expression stack
;---------------------------------------------------------

;*********************************************************
;  This subroutine should only be invoked via the GOSUB
;  opcode and not through the SCRT CALL opcode.  
;  It should return via the RSUB opcode, and not the 
;  SCRT RTN or RETURN opcodes.
;*********************************************************
; Subroutine Registers:
;  R9 is the Subroutine Instruction Pointer
;  R3 is the argument pointer and return vector for RSUB
;  R2 is the system stack pointer (SP)
;*********************************************************

              proc vpush16          
            lda     r3    ; set up pointer to variable
            phi     r8
            lda     r3
            plo     r8    ; r8 points to LSB of variable
            sex     r7    ; set X = ES
            lda     r8    ; get LSB of variable value
            plo     re    ; save in scratch register
            ldn     r8    ; get MSB of variable value
            stxd          ; save MSB on stack
            glo     re    ; get LSB from scratch register
            stxd          ; save on stack
            sex     r2    ; set X = SP
            rsub          ; return from subroutine
              endp 
