#include      ../include/ops_c.inc

;---------------------------------------------------------
; lpinc16 - increment a local pointer variable located 
;   at local data offset by size bytes.
;
;   R8 - temp variable    
;   R9 - local variable pointer
;   RB - base pointer to local data in expression stack
;   RC - size of pointer
;
; usage:  call lpinc16
;           dw loffset  ; index to local variable (signed)
;           dw size     ; size of pointer
;---------------------------------------------------------
              proc lpinc16
            sex     r2      ; make sure X = SP for arithmetic
            
            ;---- set pointer to 16-bit local variable
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
            inc     r9      ; move pointer up to local variable data 
            
            lda     r6      ; set up pointer size
            phi     rc
            lda     r6
            plo     rc      ; rc has pointer size
            
            ;---- get local value and increment it
            lda     r9      ; get LSB of variable value
            plo     r8      ; save in temp register
            ldn     r9      ; get MSB of variable value
            phi     r8      ; save in temp register
            
            addr16  r8, rc  ; increment temp value
            
            ghi     r8    ; get MSB of incremented value
            str     r9    ; save in MSB of variable
            dec     r9    ; move back to LSB of variable
            glo     r8    ; get LSB of incremented value
            str     r9    ; save in LSB of variable
            
            sex     r2    ; make sure X = SP 
            rtn           ; return to caller
              endp 
