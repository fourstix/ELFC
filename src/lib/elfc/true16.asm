#include      ../macros.inc

; ********************************************
; ***** Push .true. to expression stack  *****
; ***** R7 - Pointer to expression stack *****
; ********************************************
              proc    true16

              sex     r7               ; point X to expression stack
              ldi     00h              ; push 1 to expression stack
              stxd                     
              ldi     01h              ; true is 1
              stxd
              sex     r2               ; point X back to stack
              rtn                      ; return to caller

              endp
