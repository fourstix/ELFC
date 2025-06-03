#include      ../macros.inc

; ***********************************************************
; ***** Promote a signed 8-bot number on the expression *****
; ***** into a 16-bit signed number.
; ***** R7 - pointer to expression  stack               *****
; ***** Numbers on expression stack are LSB first        *****
; ***********************************************************
              proc    eprom8
              sex     r7    ; point X to expression stack
              irx           ; point to TOS
              ldxa          ; get LSB with 8-bit signed int
              shl           ; set DF to sign bit 
              ldi     $ff   ; sign extend negative integer
              lsdf          ; jump over if DF = 1
              ldi     0     ; sign extend positive integer
              stxd          ; update MSB with sign bits
              dec     r7    ; move ESP past LSB of 16-bit value       
              sex     r2    ; restore X to stack
              rtn           ; and return to caller

              endp
