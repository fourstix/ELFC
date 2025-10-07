#include      ../include/ops_c.inc

;---------------------------------------------------------
; laddr16 - put the address of a local variable onto 
;   the expression stack
; registers used:
;   R7 - pointer to expression stack 
;   RD - local data value pointer
;   RB - base pointer to local data in expression stack
; usage:  GOSUB laddr16
;           dw loffset  ; index to local variable (signed)
; returns: address of local variable on TOS
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

              proc laddr16         
            ;---- set up pointer to local variable  
            sex     r2      ; make sure X = SP
            lda     r3      ; get the MSB of offset
            plo     re      ; save for MSB
            lda     r3      ; get the LSB of offset
            str     r2      ; save in M(X)
            glo     rb      ; get lo byte of base pointer
            add             ; add offset to data location
            plo     rd      ; save in local data pointer
            glo     re      ; save for MSB
            str     r2      ; save in M(X)
            ghi     rb      ; propagate carry flag into hi byte
            adc             ; add offset to data location with carry            
            phi     rd      ; pointer now points to one below local data
            inc     rd      ; move pointer up to local data
            
            ;---- push local variable address value onto expression stack 
            sex     r7      ; set X = ESP
            ghi     rd      ; get the MSB of address
            stxd            ; save on the expression stack
            glo     rd      ; get the LSB of address
            stxd            ; save on the expression
            sex     r2      ; make sure X = SP for return            
            rsub            ; return from subroutine
              endp 
