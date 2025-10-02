#include      ../include/ops_c.inc

;---------------------------------------------------------
; Convert ASCII string to integer
; registers used:
;   RF - Pointer to Buffer with ASCII number string
;   RD - Sign flag for negative values
;   R8 - Temporary values
; returns:
;   RC - Converted 16-bit integer value
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

                proc    atoi16              
              sex     r2               ; make sure X = SP
              ldi     0                ; zero result
              plo     rc
              phi     rc
              plo     rd               ; and negative flag
              ldn     rf               ; get first byte
              smi     '-'              ; is it negative sign
              lbnz    atoi_0_1         ; jump if not
              inc     rf               ; move past negative
              inc     rd               ; set flag for negative number
atoi_0_1:     lda     rf               ; get next byte of input
              plo     re               ; set aside
              smi     '0'              ; see if below below numbers
              lbnf    atoi_no          ; done if so
              smi     10               ; see if character is above numbers
              lbnf    atoi_0_2         ; jump if actual numeral
atoi_no:      glo     rd               ; recover sign flag
              shr                      ; shift it into DF
              lbnf    atoi_rt          ; jump if number is positive
              glo     rc               ; 2's comp. the number
              xri     0ffh
              adi     1
              plo     rc
              ghi     rc
              xri     0ffh
              adci    0
              phi     rc
atoi_rt:      rsub                     ; return from subroutine
atoi_0_2:     glo     re               ; retrieve character
              smi     '0'              ; convert to binary number
              plo     re               ; set it aside
              glo     rc               ; multiply result by 2
              shl
              plo     rc
              plo     r8               ; keep a copy in R8
              ghi     rc
              shlc
              phi     rc
              phi     r8
              glo     r8               ; multiply R8 by 2 (original by 4)
              shl
              plo     r8
              ghi     r8
              shlc
              phi     r8
              glo     r8               ; multiply R8 by 4 (original by 8)
              shl
              plo     r8
              ghi     r8
              shlc
              phi     r8
              glo     r8               ; now add x8 with x2 to get x10
              str     r2
              glo     rc
              add
              plo     rc
              ghi     r8
              str     r2
              ghi     rc
              adc
              phi     rc
              glo     re               ; retrieve new value
              str     r2               ; and add it into result
              glo     rc
              add
              plo     rc
              ghi     rc
              adci    0
              phi     rc
              lbr     atoi_0_1         ; loop back for more digits

              endp
