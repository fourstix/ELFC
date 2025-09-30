#include      ../include/ops_c.inc

;---------------------------------------------------------
; vpush8 - push a global or static char type variable 
;   onto expression stack 
; registers used:
;   R8 - pointr to char variable in memory 
;   R7 - pointer to expression stack 
; usage:   GOSUB vpush8
;            dw vaddr    ; address of variable
;            db  sgn     ; indicates signed or unsigned
; returns: char value on TOS
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

              proc vpush8
            lda     r3      ; set up pointer to char variable
            phi     r8
            lda     r3
            plo     r8
            sex     r7        
            lda     r3      ; get signed indicator byte
            lbz     vp_msb  ; load 0 in MSB if unsigned
            
            ldn     r8      ; get the LSB byte
            shl             ; set DF to sign bit of LSB (DF = 1 means negative)
            ldi     $ff     ; pad with all ones if negative
            lsdf            ; if negative, skip over to set MSB to all ones 
            ldi     0       ; if positive, pad with all zeros if positive
                        
vp_msb:     stxd            ; save padding byte in MSB
            lda     r8      ; get char value
            stxd            ; save as LSB on stack
            sex     r2
            rsub            ; return from subroutine
              endp 
