#include      ../include/ops_c.inc

;---------------------------------------------------------
; lstor16 - copy a 2-byte value from the expression stack
; and save it in a local variable 
; registers used:
;   R7 - pointer to expression stack 
;   RD - local data value pointer
;   RB - base pointer to local data in expression stack
; usage:  GOSUB lstor16
;           dw loffset  ; index to local variable (signed)
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

              proc lstor16         
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
            
            ;---- copy stack value to local variable
            copy    r7, r8  ; set up pointer to stack data value   
            inc     r8      ; move ESP to LSB
            lda     r8      ; get LSB from stack
            str     rd      ; save as LSB for local variable
            inc     rd      ; move to MSB of local variable
            ldn     r8      ; get MSB from stack
            str     rd      ; save MSB in variable
            rsub            ; return from subroutine
              endp 
