#include      ../macros.inc

; ***********************************************************
; ***** Subtract two 16-bit numbers on expression stack *****
; ***** R7 - pointer to expression  stack               *****
; ***** Numbers on expression stack are LSB first       *****
; ***********************************************************
              proc    sub16

              sex     r7               ; point X to expression stack
              irx                      ; point to LSB of first arg
              ldxa                     ; retrieve it
              irx                      ; point to LSB of second arg
              sd                       ; and subtract
              stxd                     ; strore result as LSB of arg2
              ldxa                     ; get MSB of arg 1
              irx                      ; move past LSB of arg
              sdb                      ; subtract from MSB of arg 2
              stxd                     ; store to MSB of arg2
              dec     r7               ; move R7 to just before arg2
              sex     r2               ; restore X to SP
              rtn                      ; and return to caller

              endp
