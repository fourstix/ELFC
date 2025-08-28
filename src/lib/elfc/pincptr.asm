#include      ../include/ops_c.inc

;---------------------------------------------------------
; pincptr - increment a pointer value referenced by the  
; pointer value in the RA register
; registers used:
;   RA - pointer value pointing to another pointer 
;   R8 - temp value   
;   RC - size of pointer
; usage:   CALL pincptr
;            dw  size
; note: leaves the expression stack and ESP unchanged
;---------------------------------------------------------
                proc pincptr

              sex     r2      ; make sure X = SP 
              
              lda     r6      ; set up pointer size
              phi     rc
              lda     r6
              plo     rc      ; rc has pointer size

              lda     ra      ; get pointer LSB referenced by pointer
              plo     r8      ; save in temp register
              ldn     ra      ; get the pointer MSB referenced by pointer
              phi     r8      ; save in temp register
              
              addr16  r8, rc  ; increment temp pointer by size
              
              ghi     r8      ; get MSB from incremented value
              str     ra      ; save in referenced pointer MSB
              dec     ra      ; move pointer to reference LSB
              glo     r8      ; get LSB from incremented value              
              str     ra      ; save in referenced pointer LSB
              
              rtn             ; return to caller
                endp 
          
