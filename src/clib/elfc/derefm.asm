#include      ../include/ops_c.inc

;---------------------------------------------------------
; derefm - replace a pointer at the TOS of the expression
;   stack with the contents of the memory block referenced
;   by the pointer.
;
; R7 - expression stack pointer
; R8 - source pointer
; RC - number of bytes to copy
; RD - destination pointer
;
; usage:   GOSUB derefm
;             dw  size      ; number of bytes to push
;
; returns: DF = 0, success with struct/union on TOS
;          DF = 1, error
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

          extrn  es_min

            proc    derefm
          lda     r3        ; get hi byte of size
          phi     rc        ; save hi byte count in RC.1
          lda     r3        ; get lo byte of size
          plo     rc        ; RC has count of bytes to copy

          inc     r7        ; move to the source pointer at TOS
          lda     r7        ; get LSB for source
          plo     r8
          ldn     r7        ; get MSB for source
          phi     r8        ; R8 has source

          ;----- copy from top down
          glo     rc        ; get offset lo byte
          str     r2        ; save at M(X)
          glo     r8        ; get lo byte of ESP
          add               ; offset to source pointer
          plo     r8        ; save updated value

          ghi     rc        ; get offset hi byte
          str     r2        ; save at M(X)
          ghi     r8        ; get hi byte of ESP
          adc               ; add with carry from hi byte
          phi     r8        ; save updated value
          dec     r8        ; move back to point to top byte

          ;---- set push data from top down from sourcCe
          sex     r7        ; set x for copying data

mcpy:     glo     rc        ; get low count byte
          lbnz    mcpy1     ; jump if not zero
          ghi     rc        ; get high count byte
          lbz     mcdone    ; if zero copying is done
mcpy1:    ldn     r8        ; get byte from source
          stxd              ; push data on stack
          dec     r8        ; point to next source position
          dec     rc        ; decrement count
          lbr     mcpy      ; and continue copying bytes

          ;---- check stack value after move
mcdone:   glo     r7        ; verify r7 did not go below minimum
          sdi     es_min.0
          ghi     r7        ; DF = 1, means r7 < es_min and is an error
          sdbi    es_min.1

          sex     r2        ; make sure X = SP
          rsub              ; return from subroutine
            endp
