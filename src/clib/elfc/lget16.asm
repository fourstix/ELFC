#include      ../include/ops_c.inc

;---------------------------------------------------------
; lget16 - get a 2-byte local variable and save it 
; into register ra. 
; registers used:
;   R8 - local data value pointer
;   RA - 2-byte variable value
;   RB - base pointer to local data in expression stack
; usage:  GOSUB lget16
;           dw loffset  ; index to local variable (signed)
; returns: RA with 2-byte variable value
; notes: leaves 16-bit value on expression stack
;        ESP is unchanged
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

              proc lget16         
            ;---- set up pointer to local variable  
            sex     r2      ; make sure X = SP
            lda     r3      ; get the MSB of offset
            plo     re      ; save for MSB
            lda     r3      ; get the LSB of offset
            str     r2      ; save in M(X)
            glo     rb      ; get lo byte of base pointer
            add             ; add offset to data location
            plo     r8      ; save in local data pointer
            glo     re      ; save for MSB
            str     r2      ; save in M(X)
            ghi     rb      ; propagate carry flag into hi byte
            adc             ; add offset to data location with carry            
            phi     r8      ; pointer now points to one below local data
            inc     r8      ; move pointer up to local data
            
            ;---- copy local variable into ra
            lda     r8      ; get LSB from local variable 
            plo     ra      ; save in LSB of ra
            ldn     r8      ; get MSB from local variable
            phi     ra      ; save in ra
            rsub            ; return from subroutine
              endp 
