#include      ../macros.inc

; ************************************************
; Compare 2 unsigned 16-bit values for TOS >= SOS 
; R7 - Pointer to expression stack      
; ************************************************
              proc    uge16

              extrn   sub16
              extrn   true16
              extrn   false16

              call    sub16            ; subtract arg1 from arg2
              sex     r7               ; point X to expression stack
              irx                      ; point to LSB of result
              ldxa                     ; retrieve it
              or                       ; combine with MSB
              sex     r2               ; point X back to stack
              lbz     true16           ; If result was zero, then true
              lbnf    true16           ; If borrow, then TOS > SOS
              lbr     false16          ; otherwise false

              endp
