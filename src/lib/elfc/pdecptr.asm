#include      ../macros.inc

;---------------------------------------------------------
; pdecptr - decrement a pointer value referenced by the  
; pointer value in the RA register
; registers used:
;   RA - pointer value pointing to another pointer 
;   R8 - temp value   
; usage:   CALL pdecptr
; note: leaves the expression stack and ESP unchanged
;---------------------------------------------------------
                proc pdecptr
              lda     ra      ; get pointer LSB referenced by pointer
              plo     r8      ; save in temp register
              ldn     ra      ; get pointer MSB referenced by pointer
              phi     r8      ; save in temp register
              
              dec     r8      ; decrement temp pointer value twice
              dec     r8      ; because all pointers are 2-byte
              
              ghi     r8      ; get MSB from decremented value
              str     ra      ; save in referenced pointer MSB
              dec     ra      ; move pointer to reference LSB
              glo     r8      ; get LSB from decremented value              
              str     ra      ; save in referenced pointer LSB
              
              sex     r2      ; make sure X = SP 
              rtn             ; return to caller
                endp 
          
