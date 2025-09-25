#include      ../include/ops_c.inc

;---------------------------------------------------------
; deref16 - replace a pointer on the expression stack
;   with the 16-bit value it references
;
; usage:   GOSUB deref16
; registers used:
;   RD - pointer value from expression stack 
;   R7 - pointer to expression stack    
; returns: dereferenced 16-bit value on TOS
; note: static and global variable bytes are stored in 
;   the same order (LSB first) as auto variables on the
;   expression stack, so all variable storage classes 
;   are dereferenced the same.
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

              proc deref16
            sex     r7  ; set X = ESP
            irx         ; move to TOS 
            lda     r7  ; get low byte from stack
            plo     rd
            ldn     r7  ; get hi byte from stack
            phi     rd
            lda     rd  ; get LSB referenced by pointer
            plo     re  ; save LSB in scratch register
            ldn     rd  ; get MSB referenced by pointer
            stxd        ; save MSB on stack
            glo     re  ; get LSB from scratch register
            stxd        ; save LSB on stack
            sex     r2  ; make sure X=SP for return 
            rsub        ; return from subroutine 
              endp 
