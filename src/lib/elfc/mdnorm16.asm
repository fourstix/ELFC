#include      ../macros.inc

; **************************************************************
; ***** Prepare 16-bit numbers for multiplication/division *****
; ***** RC - first 16-bit number                           *****
; ***** RD - second 16-bit number                          *****
; **************************************************************
              proc    mdnorm16

              ghi     rc               ; get MSB of first number
              str     r2               ; store for upcoming XOR
              ghi     rd               ; get MSB of second number
              xor                      ; combine to see if like signs
              shl                      ; shift sign comparison to DF
              ldi     0                ; clear D
              shlc                     ; and then shift sign diff into D
              plo     re               ; set aside
              ghi     rc               ; get MSB of first number
              shl                      ; shift sign bit into DF
              lbnf    mdnorm2          ; jump if number is positive
              ghi     rc               ; otherwise 2's comp. the number
              xri     0ffh
              phi     rc
              glo     rc
              xri     0ffh
              plo     rc
              inc     rc
mdnorm2:      ghi     rd               ; get MSB of second number
              shl                      ; shift sign bit into DF
              lbnf    mdnorm3          ; no need to change if positive
              ghi     rd               ; otherwise 2's comp. the number
              xri     0ffh
              phi     rd
              glo     rd
              xri     0ffh
              plo     rd
              inc     rd
mdnorm3:      glo     re               ; recover sign difference'
              rtn                      ; and return to caller

              endp

