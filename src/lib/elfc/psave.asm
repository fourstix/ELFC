#include      ../macros.inc

;---------------------------------------------------------
; psave - get a pointer value from the TOS of the 
; expression stack and store it in the RA register
; registers used:
;   RA - pointer value from TOS  
;   R7 - pointer to expression stack    
;   R8 - operand pointer   
; usage:   CALL pstor16
; returns: RA with pointer value from TOS
; note: leaves 16-bit value on expression stack
;   with ESP unchanged
;---------------------------------------------------------
                proc psave
              copy    r7, r8  ; set up operand pointer
              inc     r8      ; move to LSB of pointer on stack
              lda     r8      ; get pointer LSB from stack
              plo     ra      ; save pointer LSB in variable
              ldn     r8      ; get pointer MSB from stack
              phi     ra      ; save MSB in variable
              sex     r2      ; make sure X = SP 
              rtn             ; return to caller
                endp 
          
