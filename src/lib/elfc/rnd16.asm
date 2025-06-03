#include      ../macros.inc

; ***************************************************************************
; ***** Get random number from 0 to 1 below number on top of expr stack *****
; ***************************************************************************
              proc    rnd16

              extrn   LFSR_
              extrn   lfsr_shift
              extrn   mod16

              ldi     16            ; need 16 shifts of the LFSR
              plo     rc
              call    lfsr_shift    ; Shift the register
              ldi     LFSR_.1       ; point to LFSR data
              phi     r9
              ldi     LFSR_.0
              plo     r9
              lda     r9            ; retrieve 16-bits
              plo     rf            ; into RF
              ldn     r9
              phi     rf
              inc     r7            ; retrieve random range
              lda     r7
              plo     r9            ; into R9
              ldn     r7
              phi     r9
              ghi     rf            ; push number from LFSR to expr stack
              ani     07fh          ; make sure it is positive
              str     r7
              dec     r7
              glo     rf
              str     r7
              dec     r7
              ghi     r9            ; now push range back to expr stack
              str     r7
              dec     r7
              glo     r9
              str     r7
              dec     r7
              lbr     mod16         ; and compute modulo

              endp

