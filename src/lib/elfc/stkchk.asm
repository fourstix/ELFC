#include      ../include/ops_c.inc

;---------------------------------------------------------
; stkchk - check the expression stack for a stack creep
;  error and return DF = 1 if the stack pointer has
;  not returned to the base pointer.
;
; usage:   call escheck
; uses:    R7 - stack pointer
;          RB - base pointer
; returns: DF = 0, success
;          DF = 1, error 
; note: R7 and RB are not changed by this function
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

              proc stkchk
            sex   r2            ; make sure X = SP
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
            lbnz  stk_bad       ; if not, expression stack is in error
            
            clc                 ; clear DF for no error 
            rsub                ; return from subroutine okay
            
stk_bad:    stc                 ; set DF for error 
            rsub                ; return from subroutine with error
            
              endp 
