#include      ../include/ops_c.inc

;---------------------------------------------------------
; lpush8 - copy an 8-bit local data value and push it onto
;   the expression stack 
;   R7 - pointer to expression stack    
;   RD - local data value pointer
;   RB - base pointer to local data in expression stack
; usage:  GOSUB lpush8
;           dw loffset  ; index to local variable 
;            db  sgn    ; indicates signed or unsigned
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

                proc lpush8
              ;---- get 8 bit local variable
              sex     r2      ; make sure X = SP
              lda     r3      ; get the MSB of offset
              plo     re      ; save for MSB
              lda     r3      ; get the LSB of offset
              str     r2      ; save in M(X)
              glo     rb      ; get lo byte of base pointer
              add             ; add offset to data location
              plo     rd      ; save in local data pointer
              glo     re      ; save for MSB
              str     r2      ; save in M(X)
              ghi     rb      ; propagate carry flag into hi byte
              adc             ; add offset to data location with carry            
              phi     rd      ; pointer now points to one below local data
              inc     rd      ; move pointer up to LSB of local variable
              
              ;---- push local variable char value onto expression stack 
              sex     r7      ; set X = ES
              lda     r3      ; get signed indicator byte
              lbz     lp_msb  ; load 0 in MSB if unsigned
              
              ldn     rd      ; get the LSB byte
              shl             ; set DF to sign bit of LSB (DF = 1 means negative)
              ldi     $ff     ; pad with all ones if negative
              lsdf            ; if negative, skip over to set MSB to all ones 
              ldi     0       ; if positive, pad with all zeros            
              
lp_msb:       stxd            ; push MSB on stack       
              ldn     rd      ; get char byte from local variable
              stxd            ; push LSB on stack
              sex     r2      ; set X = SP for return
              rsub            ; return from subroutine
                endp 
