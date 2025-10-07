#include      ../include/ops_c.inc

;---------------------------------------------------------
; swap16 - swap two 16-bit numbers on expression stack 
; R7 - expression stack pointer    
; R8 - swap pointer
; RD - temp register
; usage:   CALL swap16
; returns: TOS swapped with SOS on expression stack
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

                proc    swap16
              sex     r7        ; point X to expression stack
              irx               ; point to LSB of first arg
              copy    r7, r8    ; set up swap pointer    
              lda     r8        ; retrieve LSB of previous TOS
              plo     rd        ; save in temp register
              lda     r8        ; retrieve MSB of previous TOS
              phi     rd        ; rd has previous TOS value
              ldn     r8        ; retrieve LSB of previous SOS
              str     r7        ; save as LSB of current TOS
              irx               ; move to MSB of current TOS
              glo     rd        ; get LSB of previous TOS
              str     r8        ; save as LSB of current SOS
              inc     r8        ; move to MSB of previous SOS
              ldn     r8        ; get MSB of previous SOS
              stxd              ; save as MSB of current TOS
              dec     r7        ; move ESP to bottom of expression stack
              ghi     rd        ; get MSB of prevous TOS
              str     r8        ; save as MSB of current SOS
              sex     r2        ; restore X to stack
              rsub              ; and return to caller
                endp
