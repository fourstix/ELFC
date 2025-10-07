#include      ../include/ops_c.inc

;---------------------------------------------------------
; vdec16 - decrement 2-byte global or static variable 
;
; registers used:
;   R8 - temporary value
;   RD - pointer to variable in memory 
;   
; usage:   GOSUB vdec16
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

              proc vdec16          
            lda     r3    ; set up pointer to variable
            phi     rd
            lda     r3
            plo     rd    ; rd points to variable location
            
            lda     rd    ; get LSB of variable value
            plo     r8    ; save in temp register
            ldn     rd    ; get MSB of variable value
            phi     r8    ; save in temp register
            
            dec     r8    ; decrement temp value
            
            ghi     r8    ; get MSB of decremented value
            str     rd    ; save in MSB of variable
            dec     rd    ; move back to LSB of variable
            glo     r8    ; get LSB of decremented value
            str     rd    ; save in LSB of variable
            
            sex     r2    ; make sure X = SP 
            rsub          ; return from subroutine
              endp 
