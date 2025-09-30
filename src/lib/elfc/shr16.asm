#include      ../include/ops_c.inc

;---------------------------------------------------------
; rsh16 - Right shift two numbers on expression stack so  
;         the SOS shifted right by TOS number of bits
; usage:   GOSUB rsh16
; RC - Shift counter
; R7 - Pointer to expression stack      
; R8 - Temporary value
; note: SOS is a 16-bit base, TOS is an 16-bit shift value 
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

              extrn   false16

                proc    shr16

              sex     r7          ; set x to ESP
              irx                 ; get shift count from stack
              ldxa                ; load LSB and move to MSB
              plo     rc          ; save count in rc.0
              or                  ; check for zero shift (nop)
              lbz     rshnop      ; shift by zero does nothing
                
              ldxa                ; get MSB and move to LSB dividend
              lbnz    rshzero     ; anything but 0 in MSB is too much
              glo     rc          ; check count
              smi     16          ; 16 or more shifts any dividend to zero
              lbdf    rshzero     ; so just push zero instead of shifting
                
              ldxa                ; get integer value LSB
              plo     r8          ; put LSB into r8
              ldn     r7          ; get integer value MSB
              phi     r8          ; put MSB into r8
  
  rshft16:    ghi     r8          ; get MSB for shifting
              shr                 ; shift right one bit position
              phi     r8          ; save result
              glo     r8          ; shift DF into LSB
              shrc              
              plo     r8  
              dec     rc          ; decrement bit counter
              glo     rc          ; check counter
              lbnz    rshft16     ; keep going until shifted completely
                              
              ghi     r8          ; get result MSB
              stxd                ; save on TOS as result     
              glo     r8          ; get result LSB
              stxd                ; save on TOS as result
  
  rshnop:     sex     r2          ; set X back to SP
              rsub                ; return from subroutine
              
  rshzero:    irx                 ; move to TOS
              lbr     false16     ; push zero on stack as result
                endp
