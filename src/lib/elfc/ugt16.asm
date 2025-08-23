#include      ../macros.inc

; ************************************************
; Compare 2 unsigned 16-bit values for SOS > TOS 
; R7 - Pointer to expression stack      
; ************************************************
              proc    ugt16

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
              lbdf    true16           ; If no borrow, then SOS > TOS
              lbr     false16          ; otherwise false

              endp
