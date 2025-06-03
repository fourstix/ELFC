#include      ../macros.inc

;---------------------------------------------------------
; linit16 - initialize a local variable to a 16-bit 
;   data value
;   R7 - pointer to expression stack   
;   R9 - local variable pointer
;   RB - base pointer to variables in expression stack
; usage:  call linit16
;           dw loffset  ; index to local variable (signed)
;           dw initval  ; init value for local variable
; note: does not move the expression stack pointer
;---------------------------------------------------------
              proc linit16
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
            inc     r9  ; move pointer up to local data
            
            lda     r6  ; get hi byte to update
            plo     re  ; save in scratch register
            lda     r6  ; get lo byte to update
            str     r9  ; save LSB in variable on stack
            inc     r9  ; move to hi byte on stack               
            glo     re  ; get MSB from scratch register
            str     r9  ; save MSB in variable on stack   
            rtn
              endp 
