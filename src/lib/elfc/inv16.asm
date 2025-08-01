#include      ../macros.inc

;-----------------------------------------------------
; Invert a 16-bit integer on expression stack       
;   R7 - pointer to expression stack              
;-----------------------------------------------------
              proc    inv16

              inc     r7               ; point to LSB of number
              ldn     r7               ; retrieve it
              xri     0ffh             ; invert it
              str     r7               ; put it back
              inc     r7               ; point to MSB
              ldn     r7               ; retrieve it
              xri     0ffh             ; invert it
              str     r7               ; and put it back
              dec     r7               ; restore R7's position
              dec     r7
              rtn                      ; and return to caller

              endp
