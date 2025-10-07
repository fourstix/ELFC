#include      ../include/ops_c.inc

;---------------------------------------------------------
; deref8 - replace a pointer on the expression stack
;   with the 8-bit value it references
;
; usage:   GOSUB deref8
;            db  sgn     ; indicates signed or unsigned
; registers used:
;   RD - pointer value from expression stack 
;   R7 - pointer to expression stack    
; returns: dereferenced char value on TOS
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

              proc deref8
            sex     r7     ; set X = ESP
            irx            ; move to TOS 
            lda     r7     ; get low byte from stack
            plo     rd
            ldn     r7     ; get hi byte from stack
            phi     rd
            lda     r3     ; get signed indicator byte
            lbz     dr_msb ; load 0 in MSB if unsigned
            
            ldn     rd     ; get the LSB byte
            shl            ; set DF to sign bit of LSB (DF = 1 means negative)
            ldi     $ff    ; pad with all ones if negative
            lsdf           ; if negative, skip over to set MSB to all ones              
            ldi     0      ; if positive, pad with all zeros if positive            
            
dr_msb:     stxd           ; put MSB on stack
            ldn     rd     ; get char referenced by pointer
            stxd           ; save LSB on stack
            sex     r2     ; make sure X=SP for return  
            rsub           ; return from subroutine
              endp 
