#include      ../include/ops_c.inc

;---------------------------------------------------------
; linit16 - initialize a local variable to a 16-bit 
;   data value
;   R7 - pointer to expression stack   
;   RD - local variable pointer
;   RB - base pointer to variables in expression stack
; usage:  GOSUB linit16
;           dw loffset  ; index to local variable (signed)
;           dw initval  ; init value for local variable
; note: does not move the expression stack pointer
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

              proc linit16
            sex     r2  ; make sure X = SP
            lda     r3  ; get the MSB of offset
            plo     re  ; save for MSB
            lda     r3  ; get the LSB of offset
            str     r2  ; save in M(X)
            glo     rb  ; get lo byte of base pointer
            add         ; add offset to data location
            plo     rd  ; save in local data pointer
            glo     re  ; save for MSB
            str     r2  ; save in M(X)
            ghi     rb  ; propagate carry flag into hi byte
            adc         ; add offset to data location with carry            
            phi     rd  ; pointer now points to one below local data
            inc     rd  ; move pointer up to local data
            
            lda     r3  ; get hi byte to update
            plo     re  ; save in scratch register
            lda     r3  ; get lo byte to update
            str     rd  ; save LSB in variable on stack
            inc     rd  ; move to hi byte on stack               
            glo     re  ; get MSB from scratch register
            str     rd  ; save MSB in variable on stack   
            rsub        ; return from subroutine
              endp 
