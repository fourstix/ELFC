#include      ../include/ops_c.inc

;---------------------------------------------------------
; vdec8 - decrement 1-byte global or static variable 
;
; registers used:
;   R8 - temporary value    
;   RD - pointer to variable in memory 
;
; usage:   GOSUB vdec8
;            dw  vaddr 
;
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

              proc vdec8          
            lda     r3    ; set up pointer to variable
            phi     rd
            lda     r3
            plo     rd    ; rd points to variable
            
            ldn     rd    ; get variable value
            plo     r8    ; save in temp register
            ldi     0     ; pad temp byte with zero
            phi     r8    ; save in temp register
            
            dec     r8    ; decrement temp value
            
            glo     r8    ; get decremented value
            str     rd    ; save in variable
            
            sex     r2    ; make sure X = SP 
            rsub          ; return from subroutine
              endp 
