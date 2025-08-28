#include      ../include/ops_c.inc

; ************************************************
; ***** Compare 2 16-bit values for SOS      *****
; ***** greater than TOS                     *****
; **** R7 - Pointer to expression stack      *****
; ************************************************
              proc    gt16

              extrn   sub16
              extrn   true16
              extrn   false16

              call    sub16            ; subtract arg2 from arg1 (SOS - TOS)
              sex     r7               ; point X to expression stack
              irx                      ; point to LSB of result
              ldxa                     ; retrieve it
              or                       ; combine with MSB
              sex     r2               ; point X back to stack
              lbz     false16          ; If result was zero, then not greater
              ldn     r7               ; retrieve MSB
              shl                      ; get sign bit
              lbnf    true16           ; true if result is positive
              lbr     false16          ; otherwise false

              endp
