#include      ../include/ops_c.inc

;---------------------------------------------------------
; mcopy - copy the contents of a structure or union
;   referenced by the pointer at the SOS into the structure
;   or union referenced by the pointer at the TOS.
;
; R7 - expression stack pointer
; R8 - source pointer
; RC - number of bytes to copy
; RD - destination pointer
;
; usage:   GOSUB mcopy
;             dw  size      ; number of bytes
; returns: TOS pointer to destination structure or union
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

            proc    mcopy
          lda     r3        ; get hi byte of size
          phi     rc        ; save hi byte count in RC.1
          lda     r3        ; get lo byte of size
          plo     rc        ; RC has count of bytes to copy

          inc     r7        ; move to the source pointer
          lda     r7        ; get LSB for source
          plo     r8
          lda     r7        ; get MSB for source
          phi     r8        ; R8 has source

          lda     r7        ; get LSB for destination
          plo     rd
          ldn     r7        ; get MSB for destination
          phi     rd        ; RD has destination
          dec     r7        ; move back to LSB
          dec     r7        ; move back so destination stays on TOS

mcpy:     glo     rc        ; get low count byte
          lbnz    mcpy1     ; jump if not zero
          ghi     rc        ; get high count byte
          lbz     mcdone    ; if zero copying is done
mcpy1:    lda     r8        ; get byte from source
          str     rd        ; store into destination
          inc     rd        ; point to next destination position
          dec     rc        ; decrement count
          lbr     mcpy      ; and continue copy

mcdone:   sex     r2        ; make sure X = SP
          rsub              ; return from subroutine
            endp
