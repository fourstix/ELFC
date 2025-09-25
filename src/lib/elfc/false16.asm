#include      ../include/ops_c.inc

;---------------------------------------------------------
; Push .false. value (0) onto expression stack  
;  R7 - Pointer to expression stack 
; usage:   GOSUB false16
; returns: TOS contains .false. value 0
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

                proc    false16
              ldi     0                ; false is 0
              sex     r7               ; point X to expression stack
              stxd                     ; push 0 to expression stack
              stxd
              sex     r2               ; point X back to stack
              rsub                     ; return from subroutine
                endp
