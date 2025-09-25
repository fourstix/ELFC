#include      ../include/ops_c.inc

;---------------------------------------------------------
; dpush16 - push 2-byte data value onto expression stack 
;   R7 - pointer to expression stack    
;   RA - data value for expression stack 
; Usage:   GOSUB dpush16
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

              proc dpush16
            sex     r7     ; set X to ESP
            ghi     ra     ; get MSB 
            stxd           
            glo     ra     ; get LSB
            stxd
            sex     r2     ; set X back to SP
            rsub           ; return from subroutine
              endp 
