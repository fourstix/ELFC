#include      ../include/ops_c.inc

;---------------------------------------------------------
; dget16 - get a 2-byte value from expression stack 
;   R7 - pointer to expression stack    
; usage:   CALL dget16
; returns: RA - value from expression stack
; notes: leaves 16-bit value on expression stack
;        ESP is unchanged
;---------------------------------------------------------
              proc dget16
            sex   r7      ; set X to ESP
            irx           ; move to TOS 
            lda   r7      ; get low byte from TOS
            plo   ra      ; save LSB in return register
            ldn   r7      ; get hi byte from TOS
            phi   ra      ; save MSB in return register
            dec   r7      ; move back to bottom of stack
            dec   r7      
            sex   r2      ; set X = SP for return
            rtn
              endp 
