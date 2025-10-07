#include      ../include/ops_c.inc

;---------------------------------------------------------
; lpush16 - get a 16-bit local variable value and push it
;   onto the expression stack
;   R7 - pointer to expression stack    
;   RD - local variable pointer
;   RB - base pointer to local data in expression stack
; usage:  GOSUB lpush16
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

              proc lpush16
            ;---- get 16-bit local variable  
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
            inc     rd  ; move pointer up to local variable data 
                        
            ;---- push local variable data value onto expression stack 
            sex     r7  ; set X = ES                    
            lda     rd  ; get LSB from local variable
            plo     re  ; save in scratch register
            ldn     rd  ; get MSB from local variable
            stxd        ; push MSB onto stack
            glo     re  ; get LSB from scratch register
            stxd        ; push LSB onto stack
            sex     r2
            rsub        ; return from subroutine
              endp 
