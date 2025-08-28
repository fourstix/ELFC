#include      ../include/ops_c.inc

; *********************************************************
; ***** Get absolute value of top of expression stack *****
; ***** R7 - pointer to expression stack              *****
; *********************************************************
              proc    abs16

              extrn   neg16

              inc     r7               ; point to MSB
              inc     r7
              ldn     r7               ; retrieve it
              dec     r7               ; restore expression pointer
              dec     r7
              shl                      ; shift sign into DF
              lbdf    neg16            ; if negative, need to 2s comp.
              rtn                      ; and return to caller

              endp
