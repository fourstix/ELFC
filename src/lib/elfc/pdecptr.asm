#include      ../macros.inc

;---------------------------------------------------------
; pdecptr - decrement a pointer value referenced by the  
; pointer value in the RA register
; registers used:
;   R8 - temp value   
;   RA - pointer value pointing to another pointer 
;   RC - size of pointer
; usage:   CALL pdecptr
;            dw  size
; note: leaves the expression stack and ESP unchanged
;---------------------------------------------------------
                proc pdecptr
              sex     r2      ; make sure X = SP 
              lda     ra      ; get pointer LSB referenced by pointer
              plo     r8      ; save in temp register
              ldn     ra      ; get pointer MSB referenced by pointer
              phi     r8      ; save in temp register
              
              lda     r6      ; set up pointer size
              phi     rc
              lda     r6
              plo     rc      ; rc has pointer size

              sub16   r8, rc  ; decrement temp pointer by size
              
              ghi     r8      ; get MSB from decremented value
              str     ra      ; save in referenced pointer MSB
              dec     ra      ; move pointer to reference LSB
              glo     r8      ; get LSB from decremented value              
              str     ra      ; save in referenced pointer LSB
              
              rtn             ; return to caller
                endp 
          
