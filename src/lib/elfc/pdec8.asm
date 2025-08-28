#include      ../include/ops_c.inc

;---------------------------------------------------------
; pdec8 - decrement a 1-byte value referenced by the  
; pointer value in the RA register
; registers used:
;   RA - pointer value pointing to variable   
;   R8 - temp value   
; usage:   CALL pdec8
; note: leaves the expression stack and ESP unchanged
;---------------------------------------------------------
                proc pdec8
              ldn     ra      ; get variable referenced by pointer
              plo     r8      ; save in temp register
              ldi     0       ; pad MSB with zero
              phi     r8      ; save in temp register
              
              dec     r8      ; decrement temp value
              
              glo     r8      ; get decremented value
              
              str     ra      ; save in referenced variable 
              sex     r2      ; make sure X = SP 
              rtn             ; return to caller
                endp 
          
