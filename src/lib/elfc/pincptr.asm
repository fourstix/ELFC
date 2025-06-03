#include      ../macros.inc

;---------------------------------------------------------
; pincptr - increment a pointer value referenced by the  
; pointer value in the RA register
; registers used:
;   RA - pointer value pointing to another pointer 
;   R8 - temp value   
; usage:   CALL pincptr
; note: leaves the expression stack and ESP unchanged
;---------------------------------------------------------
                proc pincptr
              lda     ra      ; get pointer LSB referenced by pointer
              plo     r8      ; save in temp register
              ldn     ra      ; get the pointer MSB referenced by pointer
              phi     r8      ; save in temp register
              
              inc     r8      ; increment temp pointer value twice
              inc     r8      ; because all pointers have 2 bytes
              
              ghi     r8      ; get MSB from incremented value
              str     ra      ; save in referenced pointer MSB
              dec     ra      ; move pointer to reference LSB
              glo     r8      ; get LSB from incremented value              
              str     ra      ; save in referenced pointer LSB
              
              sex     r2      ; make sure X = SP 
              rtn             ; return to caller
                endp 
          
