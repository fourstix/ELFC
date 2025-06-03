#include      ../macros.inc 

;---------------------------------------------------------
; lstor16 - copy a 2-byte value from the expression stack
; and save it in a local variable 
; registers used:
;   R7 - pointer to expression stack 
;   R9 - local data value pointer
;   RB - base pointer to local data in expression stack
; usage:  call lstor16
;           dw loffset  ; index to local variable (signed)
; notes: leaves 16-bit value on expression stack
;        ESP is unchanged
;---------------------------------------------------------
              proc lstor16         
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
            
            ;---- copy stack value to local variable
            copy    r7, r8  ; set up pointer to stack data value   
            inc     r8      ; move ESP to LSB
            lda     r8      ; get LSB from stack
            str     r9      ; save as LSB for local variable
            inc     r9      ; move to MSB of local variable
            ldn     r8      ; get MSB from stack
            str     r9      ; save MSB in variable
            rtn             ; return to caller
              endp 
