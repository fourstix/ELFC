#include      ../include/ops_c.inc

;---------------------------------------------------------
; epush8 - push 8-bit char value onto expression stack
; registers used:
;   R7 - pointer to expression stack
; usage:   GOSUB epush8u
;            db 'a'
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
; Note:
;   The stack should be kept two-byte integer aligned.
;   Careless use my result in a Stack Creep Error.
;*********************************************************

              proc epush8
            sex     r7  ; set X to ESP
            lda     r3  ; get byte value
            stxd
            sex     r2  ; set X back to SP
            rsub        ; return from subroutine
              endp
