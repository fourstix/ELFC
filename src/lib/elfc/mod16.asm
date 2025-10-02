#include      ../include/ops_c.inc

;---------------------------------------------------------
; Compute the Modulo of top two numbers on expression stack
; by replacing their division quotient value with the
; remainder value on the TOS 
; registers:
;  R7 - pointer to expression stack                      
;  RA - remainder from previous division operation
;  TOS - quotation to be discarded
; result:
;  TOS - remainder (modulo value)
;---------------------------------------------------------

                proc    mod16

              sex     r7              ; set X to expression stack
              irx                     ; Remove division result
              irx     
              ghi     ra              ; div16 leaves remainder in RA
              stxd                    ; so store it on expression stack
              glo     ra              
              stxd   
              sex     r2              ; set X back to system stack
              rsub                    ; return from subroutine

                endp
