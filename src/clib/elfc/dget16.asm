#include      ../include/ops_c.inc

;---------------------------------------------------------
; dget16 - get a 2-byte value from expression stack 
;   R7 - pointer to expression stack    
; usage:   GOSUB dget16
; returns: RA - value from expression stack
; notes: leaves 16-bit value on expression stack
;        ESP is unchanged
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

              proc dget16
            sex   r7      ; set X to ESP
            irx           ; move to TOS 
            lda   r7      ; get low byte from TOS
            plo   ra      ; save LSB in return register
            ldn   r7      ; get hi byte from TOS
            phi   ra      ; save MSB in return register
            dec   r7      ; move back to bottom of stack
            dec   r7      
            sex   r2      ; set X = SP for return
            rsub          ; return from subroutine
              endp 
