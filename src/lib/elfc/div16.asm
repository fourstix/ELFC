#include      ../include/ops_c.inc

;---------------------------------------------------------
; Divide 2 signed 16-bit numbers on expression stack 
; inputs:
;  TOS - divisor
;  SOS - dividend
;  RA.0 - sign difference byte 
; registers:
;  RD - divisor (TOS)
;  RA - dividend (SOS)
;  RC - temporary register
;  R8 - temporary register
;  RF - quotient register
;  RE.0 - sign difference
; returns:
;  TOS - quotient of 16-bit division (SOS)/(TOS)
;  RA  - remainder 
; ******************************************************

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


                proc    div16
              glo     ra              ; get sign byte from ra
              plo     re              ; save sign difference for later
              sex     r7              ; set X to expression stack
              irx
              ldxa
              plo     rd
              ldxa
              phi     rd
              ldxa
              plo     ra
              ldx
              phi     ra
              sex     r2              ; set X back to system stack
              glo     rd
              lbnz    div16_1
              ghi     rd
              lbnz    div16_1
              sex     r7              ; if divisor zero, set result to zero for error
              ldi     0
              stxd
              stxd
              sex     r2
              rsub                    ; return from subroutine
              
div16_1:      ldi     0
              phi     rf
              plo     rf
              phi     r8
              plo     r8
              inc     r8
d16lp1:       ghi     rd
              ani     128
              lbnz    divst
              glo     rd
              shl
              plo     rd
              ghi     rd
              shlc
              phi     rd
              glo     r8
              shl
              plo     r8
              ghi     r8
              shlc
              phi     r8
              lbr     d16lp1
divst:        glo     rd
              lbnz    divgo
              ghi     rd
              lbnz    divgo
divret:       glo     re
              shr
              lbnf    divrt
              ghi     rf
              xri     0ffh
              phi     rf
              glo     rf
              xri     0ffh
              plo     rf
              inc     rf
divrt:        sex     r7
              ghi     rf
              stxd
              glo     rf
              stxd
              sex     r2
              rsub                    ; return from subroutine
divgo:        glo     ra
              plo     rc
              ghi     ra
              phi     rc
              glo     rd
              str     r2
              glo     ra
              sm
              plo     ra
              ghi     rd
              str     r2
              ghi     ra
              smb
              phi     ra
              lbdf    divyes
              glo     rc
              plo     ra
              ghi     rc
              phi     ra
              lbr     divno
divyes:       glo     r8
              str     r2
              glo     rf
              add
              plo     rf
              ghi     r8
              str     r2
              ghi     rf
              adc
              phi     rf
divno:        ghi     rd
              shr
              phi     rd
              glo     rd
              shrc
              plo     rd
              ghi     r8
              shr
              phi     r8
              glo     r8
              shrc
              plo     r8
              lbdf    divret
              lbr     divst

              endp
