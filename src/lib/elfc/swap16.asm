#include      ../macros.inc

;---------------------------------------------------------
; swap16 - swap two 16-bit numbers on expression stack 
; R7 - expression stack pointer    
; R8 - swap pointer
; R9 - temp register
; usage:   CALL swap16
; returns: TOS swapped with SOS on expression stack
;---------------------------------------------------------
                proc    swap16
              sex     r7        ; point X to expression stack
              irx               ; point to LSB of first arg
              copy    r7, r8    ; set up swap pointer    
              lda     r8        ; retrieve LSB of previous TOS
              plo     r9        ; save in temp register
              lda     r8        ; retrieve MSB of previous TOS
              phi     r9        ; r9 has previous TOS value
              ldn     r8        ; retrieve LSB of previous SOS
              str     r7        ; save as LSB of current TOS
              irx               ; move to MSB of current TOS
              glo     r9        ; get LSB of previous TOS
              str     r8        ; save as LSB of current SOS
              inc     r8        ; move to MSB of previous SOS
              ldn     r8        ; get MSB of previous SOS
              stxd              ; save as MSB of current TOS
              dec     r7        ; move ESP to bottom of expression stack
              ghi     r9        ; get MSB of prevous TOS
              str     r8        ; save as MSB of current SOS
              sex     r2        ; restore X to stack
              rtn               ; and return to caller
                endp
