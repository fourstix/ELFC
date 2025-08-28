#include      ../include/ops_c.inc

;---------------------------------------------------------------
; Convert 16-bit value on expression stack to Boolean (1 or 0) 
;   R7 - Pointer to expression stack
;   Returns:  DF = 1, true
;             DF = 0, false                      
;---------------------------------------------------------------
              proc    bool16

              extrn   true16
              extrn   false16

              sex     r7               ; point X to expression stack
              irx                      ; point to LSB of result
              ldxa                     ; retrieve it
              or                       ; combine with MSB
              sex     r2               ; point X back to stack
              smi     0                ; Set DF = 1 for true value
              lbnz    true16           ; Any nonzero value, is true
              adi     0                ; Set DF = 0 for false
              lbr     false16          ; zero is false value

              endp
