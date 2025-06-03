#include      ../macros.inc

; *****************************************************************
; ***** Compute Module of top two numbers on expression stack *****
; ***** R7 - pointer to expression stack                      *****
; *****************************************************************
              proc    mod16

              extrn   div16

              call    div16            ; perform division
              inc     r7               ; Remove division result
              inc     r7
              ghi     rc               ; div16 leaves remainder in RC
              str     r7               ; so store it on expression stack
              dec     r7
              glo     rc
              str     r7
              dec     r7
              rtn                      ; then return to caller

              endp

