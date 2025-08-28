#include      ../include/ops_c.inc

;---------------------------------------------------------
; lpush16 - get a 16-bit local variable value and push it
;   onto the expression stack
;   R7 - pointer to expression stack    
;   R9 - local variable pointer
;   RB - base pointer to local data in expression stack
; usage:  call lpush16
;           dw loffset  ; index to local variable (signed)
;---------------------------------------------------------
              proc lpush16
            ;---- get 16-bit local variable  
            sex     r2  ; make sure X = SP
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
                        
            ;---- push local variable data value onto expression stack 
            sex     r7  ; set X = ES                    
            lda     r9  ; get LSB from local variable
            plo     re  ; save in scratch register
            ldn     r9  ; get MSB from local variable
            stxd        ; push MSB onto stack
            glo     re  ; get LSB from scratch register
            stxd        ; push LSB onto stack
            sex     r2
            rtn         ; return to caller
              endp 
