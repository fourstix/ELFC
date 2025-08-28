#include      ../include/ops_c.inc

;---------------------------------------------------------
; ldec8 - decrement an 8-bit local variable value 
;
;   R8 - temp variable    
;   R9 - local variable pointer
;   RB - base pointer to local data in expression stack
;
; usage:  call ldec8
;           dw loffset  ; index to local variable (signed)
;---------------------------------------------------------
              proc linc8
            ;---- set pointer to 16-bit local variable
            sex     r2  ; make sure X = SP for arithmetic
            lda     r6  ; get the MSB of offset
            plo     re  ; save for MSB
            lda     r6  ; get the LSB of offset
            str     r2  ; save in M(X)
            glo     rb  ; get lo byte of base pointer
            add         ; add offset to data location
            plo     r9  ; save in local data pointer
            glo     re  ; save for MSB
            str     r2  ; save in M(X)
            ghi     rb  ; propagate carry flag into hi byte
            adc         ; add offset to data location with carry            
            phi     r9  ; pointer now points to one below local data
            inc     r9  ; move pointer up to local variable data 
            
            ;---- get local value and increment it
            ldn     r9    ; get variable value
            plo     r8    ; save in temp register
            ldi     0     ; pad temp byte with zero
            phi     r8    ; save in temp register
            
            dec     r8    ; decrement temp value
            
            glo     r8    ; get decremented value
            str     r9    ; save in variable
            
            sex     r2    ; make sure X = SP 
            rtn           ; return to caller
              endp 
