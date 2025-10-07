#include      ../include/ops_c.inc

;---------------------------------------------------------
; vpop16 - pop 2-byte value from expression stack into a
;   global or static variable location 
; registers used:
;   R8 - pointer to variable in memory 
;   R7 - pointer to expression stack 
; usage:   GOSUB vpop16
;            dw vaddr 
; returns: 16-bit variable set to TOS
; note: static and global variable bytes are stored in 
;   the same order (LSB first) as auto variables on the
;   expression stack
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

              proc vpop16
            sex     r7
            lda     r3   ; set r8 to point to variable 
            phi     r8
            lda     r3
            plo     r8  ; r8 points to LSB of variable
            irx         ; move to TOS 
            lda     r7  ; get LSB from stack
            str     r8  ; set LSB of variable
            inc     r8  ; move up to MSB of variable
            ldn     r7  ; get MSB from stack
            str     r8  ; set MSB of variable
            sex     r2  ; make sure X = SP
            rsub        ; return from subroutine
              endp 
