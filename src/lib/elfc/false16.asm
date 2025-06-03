#include      ../macros.inc

; ********************************************
; ***** Push .false. to expression stack *****
; ***** R7 - Pointer to expression stack *****
; ********************************************
              proc    false16

              ldi     0                ; false is 0
              sex     r7               ; point X to expression stack
              stxd                     ; push 0 to expression stack
              stxd
              sex     r2               ; point X back to stack
              rtn                      ; return to caller

              endp

