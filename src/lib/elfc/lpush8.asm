#include      ../macros.inc

;---------------------------------------------------------
; lpush8 - copy an 8-bit local data value and push it onto
;   the expression stack 
;   R7 - pointer to expression stack    
;   R9 - local data value pointer
;   RB - base pointer to local data in expression stack
; usage:  call lpush8
;           dw loffset  ; index to local variable (signed)
;---------------------------------------------------------
                proc lpush8
              ;---- get 8 bit local variable
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
              inc     r9  ; move pointer up to LSB of local variable
              
              ;---- push local variable char value onto expression stack 
              sex     r7  ; set X = ES          
              ldi     0   ; pad MSB of char with zero
              stxd        ; push MSB on stack       
              ldn     r9  ; get char byte from local variable
              stxd        ; push LSB on stack
              sex     r2  ; set X = SP for return
              rtn         ; return to caller
                endp 
