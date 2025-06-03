#include      ../macros.inc

;---------------------------------------------------------
; esmove - move the expression stack pointer by a  
;   signed offset 
;
; usage:   call esmove
;            dw offset  ; offset for ESP (signed)
; returns: DF = 0, success
;          DF = 1, error 
;          R7 = ES + offset
;---------------------------------------------------------
            extrn  es_min
            
              proc esmove
            sex     r2
            lda     r6  ; get offset hi byte
            plo     re  ; save in scratch register
            lda     r6  ; get offset lo byte
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
            
            rtn
              endp 
