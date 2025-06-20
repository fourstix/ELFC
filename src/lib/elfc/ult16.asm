#include      ../macros.inc

; ************************************************
; Compare 2 unsigned 16-bit values for TOS < SOS 
; R7 - Pointer to expression stack     
; ************************************************
              proc    ult16

              extrn   sub16
              extrn   true16
              extrn   false16

              call    sub16            ; subtract TOS from SOS
              sex     r7               ; point X to expression stack
              irx                      ; point to LSB of result
              ldxa                     ; retrieve it
              or                       ; combine with MSB
              sex     r2               ; point X back to stack
              lbz     false16          ; If result was zero, then not less than
              lbdf    true16           ; If no borrow, TOS < SOS 
              lbr     false16          ; otherwise false

              endp
