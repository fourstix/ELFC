#include      ../macros.inc 

;---------------------------------------------------------
; lget8 - get a 1-byte value from a local variable
; into register ra. 
; registers used:
;   R9 - local data value pointer
;   RA - 2-byte variable value
;   RB - base pointer to local data in expression stack
; usage:  call lget8
;           dw loffset  ; index to local variable (signed)
; returns: RA with 1-byte variable value
; notes: leaves 16-bit value on expression stack
;        ESP is unchanged
;---------------------------------------------------------
              proc lget8         
            ;---- set up pointer to local variable  
            sex     r2      ; make sure X = SP
            lda     r6      ; get the MSB of offset
            plo     re      ; save for MSB
            lda     r6      ; get the LSB of offset
            str     r2      ; save in M(X)
            glo     rb      ; get lo byte of base pointer
            add             ; add offset to data location
            plo     r9      ; save in local data pointer
            glo     re      ; save for MSB
            str     r2      ; save in M(X)
            ghi     rb      ; propagate carry flag into hi byte
            adc             ; add offset to data location with carry            
            phi     r9      ; pointer now points to one below local data
            inc     r9      ; move pointer up to local data
            
            ;---- copy local variable into ra
            ldn     r9      ; get LSB from local variable 
            plo     ra      ; save in LSB of ra
            ldi     0       ; pad MSB with zero
            phi     ra      ; save in ra
            rtn             ; return to caller
              endp 
