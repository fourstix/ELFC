;-------------------------------------------------------------------------------
; crt0 - Elf/OS c start-up library - subroutine vectors
;-------------------------------------------------------------------------------
#define SUBTBL   $2100
s_return:  equ  SUBTBL

s_esmove:  equ  (SUBTBL + $03)
s_stkchk:  equ  (SUBTBL + $06)          
s_dpop16:  equ  (SUBTBL + $09)    
s_dpush16: equ  (SUBTBL + $0C)
s_dget16:  equ  (SUBTBL + $0F)  
s_epush16: equ  (SUBTBL + $12)
s_vpop16:  equ  (SUBTBL + $15)
s_vpush8:  equ  (SUBTBL + $18)
s_vpush16: equ  (SUBTBL + $1B)
s_vstor8:  equ  (SUBTBL + $1E)
s_vstor16: equ  (SUBTBL + $21)
s_vinc8:   equ  (SUBTBL + $24)
s_vinc16:  equ  (SUBTBL + $27)
s_vdec8:   equ  (SUBTBL + $2A)
s_vdec16:  equ  (SUBTBL + $2D)
s_vpinc16: equ  (SUBTBL + $30)
s_vpdec16: equ  (SUBTBL + $33)
s_linit16: equ  (SUBTBL + $36)
s_lstor8:  equ  (SUBTBL + $39)
s_lstor16: equ  (SUBTBL + $3C)
s_lpush8:  equ  (SUBTBL + $3F)  
s_lpush16: equ  (SUBTBL + $42) 
s_lget16:  equ  (SUBTBL + $45) 
s_lset16:  equ  (SUBTBL + $48)
s_linc8:   equ  (SUBTBL + $4B)
s_linc16:  equ  (SUBTBL + $4E)
s_ldec8:   equ  (SUBTBL + $51)
s_ldec16:  equ  (SUBTBL + $54)
s_lpinc16: equ  (SUBTBL + $57)
s_lpdec16: equ  (SUBTBL + $5A)
s_psave:   equ  (SUBTBL + $5D)
s_pstor8:  equ  (SUBTBL + $60)
s_pstor16: equ  (SUBTBL + $63)
s_pinc8:   equ  (SUBTBL + $66)
s_pinc16:  equ  (SUBTBL + $69)
s_pdec8:   equ  (SUBTBL + $6C)
s_pdec16:  equ  (SUBTBL + $6F)
s_pincptr: equ  (SUBTBL + $72)
s_pdecptr: equ  (SUBTBL + $75)
s_laddr16: equ  (SUBTBL + $78)
s_deref8:  equ  (SUBTBL + $7B) 
s_deref16: equ  (SUBTBL + $7E)  
s_swap16:  equ  (SUBTBL + $81)
s_add16:   equ  (SUBTBL + $84)
s_sub16:   equ  (SUBTBL + $87)
s_neg16:   equ  (SUBTBL + $8A)
s_mdsgn16: equ  (SUBTBL + $8D)
s_mul16:   equ  (SUBTBL + $90)
s_div16:   equ  (SUBTBL + $93)
s_mod16:   equ  (SUBTBL + $96)
s_bool16:  equ  (SUBTBL + $99)
s_true16:  equ  (SUBTBL + $9C)
s_false16: equ  (SUBTBL + $9F)
s_and16:   equ  (SUBTBL + $A2)
s_or16:    equ  (SUBTBL + $A5)
s_xor16:   equ  (SUBTBL + $A8)
s_not16:   equ  (SUBTBL + $AB)
s_inv16:   equ  (SUBTBL + $AE)
s_shl16:   equ  (SUBTBL + $B1)
s_shr16:   equ  (SUBTBL + $B4)
s_eq16:    equ  (SUBTBL + $B7)
s_gt16:    equ  (SUBTBL + $BA)
s_gte16:   equ  (SUBTBL + $BD)
s_lt16:    equ  (SUBTBL + $C0)
s_lte16:   equ  (SUBTBL + $C3)
s_ne16:    equ  (SUBTBL + $C6)
s_ugt16:   equ  (SUBTBL + $C9)
s_uge16:   equ  (SUBTBL + $CC)
s_ult16:   equ  (SUBTBL + $CF)
s_ule16:   equ  (SUBTBL + $D2)
s_scltos2: equ  (SUBTBL + $D5)
s_scltos4: equ  (SUBTBL + $D8)
s_sclsos2: equ  (SUBTBL + $DB)
s_sclsos4: equ  (SUBTBL + $DE)
s_unscl2:  equ  (SUBTBL + $E1)
s_unscl4:  equ  (SUBTBL + $E3)







;-------------------------------------------------------------------------------
; crt0 - Elf/OS c start-up library - error vectors
;-------------------------------------------------------------------------------
          extrn   auto_err
          extrn   stk_err
