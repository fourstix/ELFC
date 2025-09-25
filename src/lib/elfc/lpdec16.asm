#include      ../include/ops_c.inc

;---------------------------------------------------------
; lpdec16 - decrement a local pointer variable located 
;   at the data offset by size bytes.
;
;   R8 - temp variable    
;   RD - local variable pointer
;   RB - base pointer to local data in expression stack
;   RC - size of pointer
;
; usage:  GOSUB lpdec16
;           dw loffset  ; index to local variable (signed)
;           dw size     ; size of pointer
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

              proc lpdec16
            sex     r2  ; make sure X = SP for arithmetic
            
            ;---- set pointer to 16-bit local variable
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
            
            lda     r3      ; set up pointer size
            phi     rc
            lda     r3
            plo     rc      ; rc has pointer size

            ;---- get local value and decrement it
            lda     rd      ; get LSB of variable value
            plo     r8      ; save in temp register
            ldn     rd      ; get MSB of variable value
            phi     r8      ; save in temp register
            
            subr16  r8, rc  ; decrement temp value
            
            ghi     r8      ; get MSB of decremented value
            str     rd      ; save in MSB of variable
            dec     rd      ; move back to LSB of variable
            glo     r8      ; get LSB of decremented value
            str     rd      ; save in LSB of variable
            rsub            ; return from subroutine
              endp 
