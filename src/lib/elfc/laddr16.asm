#include      ../macros.inc 

;---------------------------------------------------------
; laddr16 - put the address of a local variable onto 
;   the expression stack
; registers used:
;   R7 - pointer to expression stack 
;   R9 - local data value pointer
;   RB - base pointer to local data in expression stack
; usage:  call laddr16
;           dw loffset  ; index to local variable (signed)
; returns: address of local variable on TOS
;---------------------------------------------------------
              proc laddr16         
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
            
            ;---- push local variable address value onto expression stack 
            sex     r7      ; set X = ESP
            ghi     r9      ; get the MSB of address
            stxd            ; save on the expression stack
            glo     r9      ; get the LSB of address
            stxd            ; save on the expression
            sex     r2      ; make sure X = SP for return            
            rtn             ; return to caller
              endp 
