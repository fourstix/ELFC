#include      ../include/ops_c.inc
#include      ../include/bios.inc
#include      ../include/kernel.inc

;---------------------------------------------------------
; escheck - check the expression stack for a stack creep
;  error and print an warning message if the stack pointer
;  has not returned to the base pointer.
;
; usage:   call escheck
; uses:    R7 - stack pointer
;          RB - base pointer
;          RD - hex value
;          RF - buffer pointer
; returns: DF = 0, success
;          DF = 1, error 
; note: R7 and RB are not changed by this function
;---------------------------------------------------------
              proc escheck
            sex     r2
            ;----- verify r7 == rb
            glo   r7            ; check r7 == rb
            str   r2            ; save LSB in M(X)
            glo   rb            ; compare with base LSB
            sm                  ; should be zero
            plo   re            ; save in scratch register
            ghi   r7            ; get MSB
            str   r2            ; save in M(X)
            ghi   rb            ; compare with base MSB
            smb                 ; subtract byte with borrow
            str   r2            ; save MSB difference in M(X)
            glo   re            ; get LSB difference in M(X)
            or                  ; both differences must be zero
            lbnz  es_bad        ; if not, expression stack is in error
            clc                 ; clear DF for no error 
            rtn                 ; return
            
            ;----- print expression stack error message
es_bad:     call  o_inmsg       
              db 'Stack Creep Error ',0
            copy  r7, rd
            load  rf, hex_dbg
            call  f_hexout4
            call  o_inmsg
            db 'R7:',0
            load  rf, hex_dbg
            call  o_msg
            copy  rb, rd
            load  rf, hex_dbg
            call  f_hexout4
            call  o_inmsg
              db ' != RB:',0
            load  rf, hex_dbg
            call  o_msg
            call   o_inmsg
              db 10,13,0
            stc                 ; set DF for error 
            rtn
            
hex_dbg:  db 0,0,0,0,0          ; hex value for debug msg    
            
              endp 
