#include      ../macros.inc

; ******************************************************
; ***** Or two 16-bit numbers on expression stack  *****
; ***** R7 - pointer to expression  stack          *****
; ***** Numbers on expressin stack are LSB first   *****
; ******************************************************
              proc    or16

              sex     r7               ; point X to expression stack
              irx                      ; point to LSB of first arg
              ldxa                     ; retrieve it
              irx                      ; point to LSB of second arg
              or                       ; and or
              stxd                     ; strore result as LSB of arg2
              ldxa                     ; get MSB of arg 1
              irx                      ; move past LSB of arg
              or                       ; or MSB of arg 2
              stxd                     ; store to MSB of arg2
              dec     r7               ; move R7 to just before arg2
              sex     r2               ; restore X to stack
              rtn                      ; and return to caller

              endp

