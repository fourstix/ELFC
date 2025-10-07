#include      ../include/ops_c.inc

;---------------------------------------------------------
; esmove - move the expression stack pointer by a  
;   signed offset 
;
; usage:   GOSUB esmove
;            dw offset  ; offset for ESP (signed)
; returns: DF = 0, success
;          DF = 1, error 
;          R7 = ES + offset
;---------------------------------------------------------

;*********************************************************
;  This subroutine should only be invoked via the GOSUB
;  opcode and not through the SCRT CALL opcode.  
;  It should return via the RSUB opcode, and not the 
;  SCRT RTN or RETURN opcodes.
;*********************************************************
; Subroutine Registers:
;  R9 is the Subroutine Instruction Pointer
;  R3 is the argument pointer and return vector for RSUB
;  R2 is the system stack pointer (SP)
;*********************************************************

            extrn  es_min
            
              proc esmove
            sex     r2  ; make sure X = SP
            lda     r3  ; get offset hi byte
            plo     re  ; save in scratch register
            lda     r3  ; get offset lo byte
            str     r2  ; save at M(X)
            glo     r7  ; get lo byte of ESP
            add           
            plo     r7  ; save updated value
            glo     re  ; get offset hi byte
            str     r2  ; save at M(X)
            ghi     r7  ; get hi byte of ESP 
            adc         ; propagate carry into hi byte
            phi     r7  ; save updated value
            
            glo     r7  ; verify r7 did not go below minimum
            sdi     es_min.0
            ghi     r7  ; DF = 1, means r7 < es_min and is an error
            sdbi    es_min.1
            
            rsub        ; return from subroutine
              endp 
