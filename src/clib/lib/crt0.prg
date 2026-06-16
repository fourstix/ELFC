.big
=es_min 2289
=auto_err 2369
=stk_err 239f
=Elfexit 2054
:2000 30 0d 86 10 07 ea 00 04
.ever               ; tell linker to update header
:2008 45 6c 66 43 00 96 73 86 73 d4 20 66 f8 e7 af f8
:2018 21 bf 92 5f 1f 82 5f f8 68 a2 f8 22 b2 f8 68 a7
/C_init 2036 00
\C_init 2037
:2028 f8 23 b7 87 ab 97 bb f8 01 a9 f8 21 b9 d4 00 00
:2038 f8 e9 ad f8 23 bd f8 ea af f8 23 bf e7 9f 73 8f
/Cmain 2050 00
\Cmain 2051
:2048 73 f8 00 73 0d 73 e2 d4 00 00 fc 00 f8 e7 af f8
:2058 21 bf 4f b2 0f a2 e2 60 72 a6 f0 b6 8a d5 f8 80
:2068 a8 f8 00 b8 88 a9 98 b9 f8 ea aa f8 23 ba f8 00
:2078 ac ad ae af 48 bc c2 23 d9 8d c2 20 9e 8c ca 20
:2088 97 8e fb 08 c2 23 d9 89 5a 1a 99 5a 1a 1e 1c 9c
:2098 59 19 2d c0 20 7c 9c fb 5c ca 20 a8 1d c0 20 7c
:20a8 8f c2 20 bd 9c 52 9d f7 ca 20 b7 2f c0 20 7c 9c
:20b8 59 19 c0 20 7c 9c fb 27 c2 20 c9 9c fb 22 ca 20
:20c8 e1 8c ca 20 db 8e fb 08 c2 23 d9 89 5a 1a 99 5a
:20d8 1a 1e 1c 9c bd 1f c0 20 7c 9c fb 20 c2 20 ed 9c
:20e8 fb 09 ca 23 c1 8c c2 20 7c f8 00 59 19 ac c0 20
:20f8 7c
?esmove 2104
?stkchk 2107
?dpop16 210a
?dpush16 210d
:2100 d3 43 a9 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0
?dget16 2110
?epush16 2113
?vpop16 2116
?vpush8 2119
?vpush16 211c
?vstor8 211f
:2110 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00
?vstor16 2122
?vinc8 2125
?vinc16 2128
?vdec8 212b
?vdec16 212e
:2120 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00
?vpinc16 2131
?vpdec16 2134
?linit16 2137
?lstor8 213a
?lstor16 213d
:2130 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0
?lpush8 2140
?lpush16 2143
?lget16 2146
?lset16 2149
?linc8 214c
?linc16 214f
:2140 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00
?ldec8 2152
?ldec16 2155
?lpinc16 2158
?lpdec16 215b
?psave 215e
:2150 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00
?pstor8 2161
?pstor16 2164
?pinc8 2167
?pinc16 216a
?pdec8 216d
:2160 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0
?pdec16 2170
?pincptr 2173
?pdecptr 2176
?laddr16 2179
?deref8 217c
?deref16 217f
:2170 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00
?swap16 2182
?add16 2185
?sub16 2188
?neg16 218b
?mdsgn16 218e
:2180 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00
?mul16 2191
?div16 2194
?mod16 2197
?bool16 219a
?true16 219d
:2190 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0
?false16 21a0
?and16 21a3
?or16 21a6
?xor16 21a9
?not16 21ac
?inv16 21af
:21a0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00
?shl16 21b2
?shr16 21b5
?eq16 21b8
?gt16 21bb
?gte16 21be
:21b0 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00
?lt16 21c1
?lte16 21c4
?ne16 21c7
?ugt16 21ca
?uge16 21cd
:21c0 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0
?ult16 21d0
?ule16 21d3
?scltos2n 21d6
?sclsos2n 21d9
?unscl2n 21dc
?mcopy 21df
:21d0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00 00 c0 00
?epush8 21e2
?derefm 21e5
:21e0 00 c0 00 00 c0 00 00 00 00
>007f
:2268 00
>0020
>00df
:2368 00 d4 03 4b 4f 75 74 20 6f 66 20 53 74 61 63 6b
:2378 20 53 70 61 63 65 20 66 6f 72 20 41 75 74 6f 20
:2388 56 61 72 69 61 62 6c 65 73 0a 0d 00 f8 ff aa f8
:2398 ff ba ff 00 c0 20 54 d4 03 4b 53 74 61 63 6b 20
:23a8 43 72 65 65 70 20 45 72 72 6f 72 0a 0d 00 f8 ff
:23b8 aa f8 ff ba ff 00 c0 20 54 8c ca 23 d3 8e fb 08
:23c8 c2 23 d9 89 5a 1a 99 5a 1a 1e 1c 9c 59 19 c0 20
:23d8 7c 8c c2 23 e0 f8 00 59 f8 e9 a9 f8 23 b9 8e 59
:23e8 d5 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
:23f8 00 00
@2000
