#include      ../include/ops_c.inc

;---------------------------------------------------------
; Push .true. value (01) onto expression stack  
;  R7 - Pointer to expression stack 
; usage:   GOSUB true16
; returns: TOS contains .true. value 01
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

                proc    true16
              sex     r7               ; point X to expression stack
              ldi     00h              ; push 1 to expression stack
              stxd                     
              ldi     01h              ; true is 1
              stxd
              sex     r2               ; point X back to stack
              rsub                     ; return from subroutine
                endp
