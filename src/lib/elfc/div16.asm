#include      ../include/ops_c.inc

              proc    div16

              extrn   mdnorm16

              sex     r7
              irx
              ldxa
              plo     rd
              ldxa
              phi     rd
              ldxa
              plo     rc
              ldx
              phi     rc
              sex     r2
              call    mdnorm16
              plo     re
              glo     rd
              lbnz    div16_1
              ghi     rd
              lbnz    div16_1
              sex     r7
              ldi     0
              stxd
              stxd
              sex     r2
              rtn
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
              rtn
divgo:        glo     rc
              plo     r9
              ghi     rc
              phi     r9
              glo     rd
              str     r2
              glo     rc
              sm
              plo     rc
              ghi     rd
              str     r2
              ghi     rc
              smb
              phi     rc
              lbdf    divyes
              glo     r9
              plo     rc
              ghi     r9
              phi     rc
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
