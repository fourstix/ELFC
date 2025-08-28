#include      ../include/ops_c.inc

; ***************************************************
; ***** Output 16-bit integer                   *****
; ***** RC - 16-bit integer                     *****
; ***** RD - Buffer for output                  *****
; ***************************************************
              proc    itoa16

              extrn   tobcd16

              glo     r2
              smi     6
              plo     r2
              ghi     r2
              smbi    0
              phi     r2
              glo     r2
              plo     rf
              ghi     r2
              phi     rf
              inc     rf
              ghi     rc
              shl
              lbnf    itoa1
              ldi     '-'
              str     rd
              inc     rd
              glo     rc
              xri     0ffh
              plo     rc
              ghi     rc
              xri     0ffh
              phi     rc
              inc     rc
itoa1:        call    tobcd16
              glo     r2
              plo     rf
              ghi     r2
              phi     rf
              inc     rf
              ldi     5
              plo     r8
              ldi     4
              phi     r8
itoalp1:      lda     rf
              lbz     itoaz
              str     r2
              ldi     0
              phi     r8
              ldn     r2
itoa2:        adi     030h
              str     rd
              inc     rd
itoa3:        dec     r8
              glo     r8
              lbnz    itoalp1
              glo     r2
              adi     6
              plo     r2
              ghi     r2
              adci    0
              phi     r2
              ldi     0
              str     rd
              rtn
itoaz:        ghi     r8
              lbz     itoa2
              smi     1
              phi     r8
              lbr     itoa3

              endp
