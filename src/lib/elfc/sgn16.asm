#include      ../macros.inc

; ***********************************************
; ***** Get sign of top of expression stack *****
; ***** R7 - pointer to expression stack    *****
; ***********************************************
              proc    sgn16

              inc     r7               ; point to LSB of number
              lda     r7               ; retrieve it
              str     r2               ; store for zero check
              ldn     r7               ; get MSB
              shl                      ; shift sign into DF
              lbdf    sgnm             ; jump if negative number
              ldn     r7               ; recover MSB
              or                       ; combine with LSB
              lbz     sgn0             ; jump if zero
              ldi     0                ; need to push +1 to expression stack
              str     r7
              dec     r7
              ldi     1
              str     r7
              dec     r7
              rtn                      ; and return to caller
sgnm:         ldi     0ffh             ; push -1 to expression stack
              str     r7
              dec     r7
              str     r7
              dec     r7
              rtn                      ; and return to caller
sgn0:         dec     r7               ; no need to touch if zero
              dec     r7
              rtn                      ; and return to caller

              endp

