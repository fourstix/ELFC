#include      ../include/ops_c.inc

; **************************************************
; ***** Boolean Not of a 16-bit value          *****
; **** R7 - Pointer to expression stack        *****
; **************************************************
              proc    not16

              extrn   true16
              extrn   false16

              sex     r7               ; point X to expression stack
              irx                      ; point to LSB of result
              ldxa                     ; retrieve it
              or                       ; combine with MSB
              sex     r2               ; point X back to stack
              lbnz    false16          ; Not of any nonzero value, is false
              lbr     true16           ; otherwise Not zero is true

              endp
