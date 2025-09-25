#include      ../include/ops_c.inc

;---------------------------------------------------------
; linc8 - increment an 8-bit local variable value 
;
;   R8 - temp variable    
;   RD - local variable pointer
;   RB - base pointer to local data in expression stack
;
; usage:  GOSUB linc8
;           dw loffset  ; index to local variable (signed)
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

              proc linc8
            ;---- set pointer to 16-bit local variable
            sex     r2  ; make sure X = SP for arithmetic
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
            inc     rd  ; move pointer up to local variable data 
            
            ;---- get local value and increment it
            ldn     rd    ; get variable value
            plo     r8    ; save in temp register
            ldi     0     ; pad temp byte with zero
            phi     r8    ; save in temp register
            
            inc     r8    ; increment temp value
            
            glo     r8    ; get incremented value
            str     rd    ; save in variable
            
            sex     r2    ; make sure X = SP 
            rsub          ; return from subroutine
              endp 
