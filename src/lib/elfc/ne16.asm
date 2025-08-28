#include      ../include/ops_c.inc

; **************************************************
; ***** Compare 2 16-bit values for inequality *****
; **** R7 - Pointer to expression stack        *****
; **************************************************
              proc    ne16

              extrn   sub16
              extrn   true16
              extrn   false16

              call    sub16            ; subtract arg1 from arg2
              sex     r7               ; point X to expression stack
              irx                      ; point to LSB of result
              ldxa                     ; retrieve it
              or                       ; combine with MSB
              sex     r2               ; point X back to stack
              lbnz    true16           ; If result was nonzero, then inequal
              lbr     false16          ; otherwise not equal

              endp
