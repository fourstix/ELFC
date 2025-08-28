#include      ../include/ops_c.inc

;---------------------------------------------------------
; pinc16 - increment a 2-byte value referenced by the  
; pointer value in the RA register
; registers used:
;   RA - pointer value pointing to variable   
;   R8 - temp value   
; usage:   CALL pinc16
; note: leaves the expression stack and ESP unchanged
;---------------------------------------------------------
                proc pinc16
              lda     ra      ; get variable LSB referenced by pointer
              plo     r8      ; save in temp register
              ldn     ra      ; get the variable MSB referenced by pointer
              phi     r8      ; save in temp register
              
              inc     r8      ; increment temp value
              
              ghi     r8      ; get MSB from incremented value
              str     ra      ; save in referenced variable MSB
              dec     ra      ; move pointer to reference LSB
              glo     r8      ; get LSB from incremented value
              
              str     ra      ; save in referenced variable LSB
              sex     r2      ; make sure X = SP 
              rtn             ; return to caller
                endp 
          
