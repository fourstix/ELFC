#include      ../macros.inc

;---------------------------------------------------------
; pstor8 - get a 1-byte value from the expression stack
; and store it in a pointer variable 
; registers used:
;   RA - pointer to variable 
;   R7 - pointer to expression stack    
; usage:   CALL pstor8
; note: leaves 16-bit padded 1-byte value on expression 
;   stack with ESP unchanged
; note: all variable bytes are stored in 
;   the same order (LSB first) as auto variables on the
;   expression stack
;---------------------------------------------------------
                proc pstor8
              sex     r7    ; X = ESP for expression stack
              irx           ; move ESP to LSB
              ldn     r7    ; get LSB from stack
              str     ra    ; save LSB in variable
              dec     r7
              sex     r2    ; make sure X = SP 
              rtn           ; return to caller
                endp 
