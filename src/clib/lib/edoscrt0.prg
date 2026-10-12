.big
=es_min 0f92
=auto_err 0d82
=stk_err 0db6
=Elfexit 0d70
:0d00 45 44 46 01 00 00 96 73 86 73 8c ff 11 cb 0d 13
:0d10 f8 10 ac f8 72 af f8 10 bf 8c 5f f8 73 af f8 10
:0d20 bf 8c c2 0d 32 4a ae 4a 5f 1f 8e 5f 1f 2c 8c ca
:0d30 0d 25 f8 f0 af f8 0e bf 92 5f 1f 82 5f f8 71 a2
:0d40 f8 0f b2 f8 71 a7 f8 10 b7 87 ab 97 bb f8 01 a9
/C_init 0d54 00
\C_init 0d55
:0d50 f8 0e b9 d4 00 00 f8 72 ad f8 10 bd f8 73 af f8
/Cmain 0d6e 00
\Cmain 0d6f
:0d60 10 bf e7 9f 73 8f 73 f8 00 73 0d 73 e2 d4 00 00
:0d70 f8 f0 af f8 0e bf 4f b2 0f a2 e2 60 72 a6 f0 b6
:0d80 8a d5 d4 01 24 4f 75 74 20 6f 66 20 53 74 61 63
:0d90 6b 20 53 70 61 63 65 20 66 6f 72 20 41 75 74 6f
:0da0 20 56 61 72 69 61 62 6c 65 73 0a 0d 00 f8 ff aa
:0db0 f8 ff ba c0 0d 70 d4 01 24 53 74 61 63 6b 20 43
:0dc0 72 65 65 70 20 45 72 72 6f 72 0a 0d 00 f8 ff aa
:0dd0 f8 ff ba c0 0d 70
?esmove 0e04
?stkchk 0e07
?dpop16 0e0a
?dpush16 0e0d
:0e00 d3 43 a9 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0
?dget16 0e10
?epush16 0e13
?vpop16 0e16
?vpush8 0e19
?vpush16 0e1c
?vstor8 0e1f
:0e10 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00
?vstor16 0e22
?vinc8 0e25
?vinc16 0e28
?vdec8 0e2b
?vdec16 0e2e
:0e20 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00
?vpinc16 0e31
?vpdec16 0e34
?linit16 0e37
?lstor8 0e3a
?lstor16 0e3d
:0e30 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0
?lpush8 0e40
?lpush16 0e43
?lget16 0e46
?lset16 0e49
?linc8 0e4c
?linc16 0e4f
:0e40 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00
?ldec8 0e52
?ldec16 0e55
?lpinc16 0e58
?lpdec16 0e5b
?psave 0e5e
:0e50 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00
?pstor8 0e61
?pstor16 0e64
?pinc8 0e67
?pinc16 0e6a
?pdec8 0e6d
:0e60 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0
?pdec16 0e70
?pincptr 0e73
?pdecptr 0e76
?laddr16 0e79
?deref8 0e7c
?deref16 0e7f
:0e70 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00
?swap16 0e82
?add16 0e85
?sub16 0e88
?neg16 0e8b
?mdsgn16 0e8e
:0e80 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00
?mul16 0e91
?div16 0e94
?mod16 0e97
?bool16 0e9a
?true16 0e9d
:0e90 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0
?false16 0ea0
?and16 0ea3
?or16 0ea6
?xor16 0ea9
?not16 0eac
?inv16 0eaf
:0ea0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00
?shl16 0eb2
?shr16 0eb5
?eq16 0eb8
?gt16 0ebb
?gte16 0ebe
:0eb0 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00
?lt16 0ec1
?lte16 0ec4
?ne16 0ec7
?ugt16 0eca
?uge16 0ecd
:0ec0 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0
?ult16 0ed0
?ule16 0ed3
?scltos2n 0ed6
?sclsos2n 0ed9
?unscl2n 0edc
?mcopy 0edf
:0ed0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00
?epush8 0ee2
?derefm 0ee5
?fp2args 0ee8
?dpop32 0eeb
?fp1arg 0eee
:0ee0 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00
:0ef0 00 00
>007f
:0f71 00
>0020
>00df
:1071 00 00
>0020
