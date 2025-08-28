#include      ../include/ops_c.inc

; **************************************
; ***** Convert RC to bcd in M[RF] *****
; **************************************
              proc    tobcd16

              ghi     rf
              stxd
              glo     rf
              stxd
              ldi     5
              plo     re
tobcdlp1:     ldi     0
              str     rf
              inc     rf
              dec     re
              glo     re
              lbnz    tobcdlp1
              irx
              ldxa
              plo     rf
              ldx
              phi     rf
              ldi     16
              plo     r9
tobcdlp2:     ldi     5
              plo     re
              ghi     rf
              stxd
              glo     rf
              stxd
tobcdlp3:     ldn     rf
              smi     5
              lbnf    tobcdlp3a
              adi     8
              str     rf
tobcdlp3a:    inc     rf
              dec     re
              glo     re
              lbnz    tobcdlp3
              glo     rc
              shl
              plo     rc
              ghi     rc
              shlc
              phi     rc
              shlc
              shl
              shl
              shl
              str     rf
              irx
              ldxa
              plo     rf
              ldx
              phi     rf
              ghi     rf
              stxd
              glo     rf
              stxd
              ldi     5
              plo     re
tobcdlp4:     lda     rf
              str     r2
              ldn     rf
              shr
              shr
              shr
              shr
              ldn     r2
              shlc
              ani     0fh
              dec     rf
              str     rf
              inc     rf
              dec     re
              glo     re
              lbnz    tobcdlp4
              irx
              ldxa
              plo     rf
              ldx
              phi     rf
              dec     r9
              glo     r9
              lbnz    tobcdlp2
              rtn

              endp
