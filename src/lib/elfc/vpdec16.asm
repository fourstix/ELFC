#include      ../include/ops_c.inc

;---------------------------------------------------------
; vpdec16 - decrement a global or static pointer to 
;   a variable value at vaddr of size bytes
;
; registers used:
;   r8 - temporary value
;   rd - pointer to variable in memory
;   rc - pointer size 
;   
; usage:   GOSUB vpdec16
;            dw  vaddr
;            dw  size 
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

              proc vpdec16
            
            sex     r2      ; make sure X = SP 

            lda     r3      ; set up pointer to variable
            phi     rd
            lda     r3
            plo     rd      ; rd points to variable location

            lda     r3      ; set up pointer size
            phi     rc
            lda     r3
            plo     rc      ; rc has pointer size
            
            lda     rd      ; get LSB of variable value
            plo     r8      ; save in temp register
            ldn     rd      ; get MSB of variable value
            phi     r8      ; save in temp register
            
            subr16  r8, rc  ; decrement pointer by size 
            
            ghi     r8      ; get MSB of decremented value
            str     rd      ; save in MSB of variable
            dec     rd      ; move back to LSB of variable
            glo     r8      ; get LSB of decremented value
            str     rd      ; save in LSB of variable
            
            rsub            ; return from subroutine
              endp 
