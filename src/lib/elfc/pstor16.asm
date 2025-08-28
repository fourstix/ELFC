#include      ../include/ops_c.inc

;---------------------------------------------------------
; pstor16 - get a 2-byte value from the expression stack
; and store it in a pointer
; registers used:
;   RA - pointer to variable in memory 
;   R7 - pointer to expression stack    
; usage:   CALL pstor16
; note: leaves 16-bit value on expression stack
;   with ESP unchanged
; note: all variable bytes are stored in 
;   the same order (LSB first) as auto variables on the
;   expression stack
;---------------------------------------------------------
                proc pstor16
              sex     r7    ; X = ESP for expression stack
              irx           ; move ESP to LSB
              lda     r7    ; get LSB from stack
              str     ra    ; save LSB in variable
              inc     ra    ; move to MSB of variable
              ldn     r7    ; get MSB from stack
              str     ra    ; save MSB in variable
              dec     r7    ; move ESP back to bottom of stack
              dec     r7
              sex     r2    ; make sure X = SP 
              rtn           ; return to caller
                endp 
          
