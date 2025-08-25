.big
{libtest1
.library string.lib
=CErrors 0000
=Cv1 0002
:0000 00 00
>0040
=Csegp 0042
>0014
=Cnum 0056
>0040
=Cresult 0096
=Cfail 0098
:0096 00 00 e2 9b 73 8b 73 87 ab 97 bb c0 00 af 25 73
/lpush16 00b0 00
\lpush16 00b1
/epush16 00b5 00
:00a6 20 66 61 69 6c 65 64 0a 00 d4 00 00 00 00 d4 00
\epush16 00b6
/Cprintf 00ba 00
\Cprintf 00bb
/esmove 00bd 00
\esmove 00be
?auto_err 00c2
/vpush16 00c5 00
:00b6 00 00 a4 d4 00 00 d4 00 00 00 04 c3 00 00 d4 00
\vpush16 00c6
/vinc16 00ca 00
\vinc16 00cb
/dpop16 00cf 00
\dpop16 00d0
/epush16 00d2 00
\epush16 00d3
:00c6 00 00 00 d4 00 00 00 00 d4 00 00 d4 00 00 00 01
/vstor16 00d7 00
\vstor16 00d8
/dpop16 00dc 00
\dpop16 00dd
/escheck 00e0 00
\escheck 00e1
:00d6 d4 00 00 00 96 d4 00 00 e2 d4 00 00 60 72 ab f0
=Cpr 00e8
:00e6 bb d5 e2 9b 73 8b 73 87 ab 97 bb c0 00 f8 25 73
/lpush16 00f9 00
\lpush16 00fa
/epush16 00fe 00
\epush16 00ff
/Cprintf 0103 00
\Cprintf 0104
:00f6 0a 00 d4 00 00 00 00 d4 00 00 00 f4 d4 00 00 d4
/esmove 0106 00
\esmove 0107
?auto_err 010b
/escheck 010f 00
\escheck 0110
:0106 00 00 00 04 c3 00 00 e2 d4 00 00 60 72 ab f0 bb
=Ctest_memfn 0117
/esmove 0121 00
\esmove 0122
:0116 d5 e2 9b 73 8b 73 87 ab 97 bb d4 00 00 ff f8 c3
?auto_err 0126
/epush16 0133 00
\epush16 0134
:0126 00 00 c0 01 32 6d 65 6d 63 6d 70 00 d4 00 00 01
/esmove 013b 00
\esmove 013c
?auto_err 0140
:0136 2b d4 00 e8 d4 00 00 00 02 c3 00 00 c0 01 4c 74
/epush16 014d 00
\epush16 014e
/lstor16 0152 00
\lstor16 0153
:0146 65 73 74 30 31 00 d4 00 00 01 45 d4 00 00 ff fe
/dpop16 0157 00
\dpop16 0158
/epush16 0164 00
\epush16 0165
:0156 d4 00 00 c0 01 63 74 65 73 74 30 33 00 d4 00 00
/lstor16 0169 00
\lstor16 016a
/dpop16 016e 00
\dpop16 016f
/epush16 0171 00
\epush16 0172
:0166 01 5c d4 00 00 ff fc d4 00 00 d4 00 00 00 05 d4
/lpush16 0176 00
\lpush16 0177
/lpush16 017b 00
\lpush16 017c
/Cmemcmp 0180 00
\Cmemcmp 0181
/esmove 0183 00
\esmove 0184
:0176 00 00 ff fc d4 00 00 ff fe d4 00 00 d4 00 00 00
?auto_err 0188
/dpush16 018b 00
\dpush16 018c
/dpop16 018e 00
\dpop16 018f
:0186 06 c3 00 00 d4 00 00 d4 00 00 9a 52 8a f1 c2 01
/epush16 01a4 00
\epush16 01a5
:0196 b3 c0 01 a3 6d 65 6d 63 6d 70 2d 31 00 d4 00 00
/esmove 01ac 00
\esmove 01ad
?auto_err 01b1
/epush16 01b4 00
\epush16 01b5
:01a6 01 9a d4 00 98 d4 00 00 00 02 c3 00 00 d4 00 00
/lpush16 01b9 00
\lpush16 01ba
/lpush16 01be 00
\lpush16 01bf
/Cmemcmp 01c3 00
\Cmemcmp 01c4
:01b6 00 06 d4 00 00 ff fc d4 00 00 ff fe d4 00 00 d4
/esmove 01c6 00
\esmove 01c7
?auto_err 01cb
/dpush16 01ce 00
\dpush16 01cf
/dpop16 01d1 00
\dpop16 01d2
:01c6 00 00 00 06 c3 00 00 d4 00 00 d4 00 00 9a 52 8a
:01d6 f1 ca 01 f6 c0 01 e6 6d 65 6d 63 6d 70 2d 32 00
/epush16 01e7 00
\epush16 01e8
/esmove 01ef 00
\esmove 01f0
?auto_err 01f4
:01e6 d4 00 00 01 dd d4 00 98 d4 00 00 00 02 c3 00 00
/epush16 01f7 00
\epush16 01f8
/lpush16 01fc 00
\lpush16 01fd
/lpush16 0201 00
\lpush16 0202
:01f6 d4 00 00 00 06 d4 00 00 ff fc d4 00 00 ff fe d4
/Cmemcmp 0206 00
\Cmemcmp 0207
/esmove 0209 00
\esmove 020a
?auto_err 020e
/dpush16 0211 00
\dpush16 0212
/epush16 0214 00
\epush16 0215
:0206 00 00 d4 00 00 00 06 c3 00 00 d4 00 00 d4 00 00
/ne16 0219 00
\ne16 021a
/dpop16 021c 00
\dpop16 021d
:0216 ff fe d4 00 00 d4 00 00 9a 52 8a f1 ca 02 28 c0
/epush16 0235 00
:0226 02 44 c0 02 34 6d 65 6d 63 6d 70 2d 33 00 d4 00
\epush16 0236
/esmove 023d 00
\esmove 023e
?auto_err 0242
/epush16 0245 00
:0236 00 02 2b d4 00 98 d4 00 00 00 02 c3 00 00 d4 00
\epush16 0246
/lpush16 024a 00
\lpush16 024b
/lpush16 024f 00
\lpush16 0250
/Cmemcmp 0254 00
\Cmemcmp 0255
:0246 00 00 06 d4 00 00 ff fe d4 00 00 ff fc d4 00 00
/esmove 0257 00
\esmove 0258
?auto_err 025c
/dpush16 025f 00
\dpush16 0260
/epush16 0262 00
\epush16 0263
:0256 d4 00 00 00 06 c3 00 00 d4 00 00 d4 00 00 00 02
/ne16 0267 00
\ne16 0268
/dpop16 026a 00
\dpop16 026b
:0266 d4 00 00 d4 00 00 9a 52 8a f1 ca 02 76 c0 02 92
/epush16 0283 00
\epush16 0284
:0276 c0 02 82 6d 65 6d 63 6d 70 2d 34 00 d4 00 00 02
/esmove 028b 00
\esmove 028c
?auto_err 0290
:0286 79 d4 00 98 d4 00 00 00 02 c3 00 00 c0 02 9c 6d
/epush16 029d 00
\epush16 029e
/esmove 02a5 00
:0296 65 6d 63 70 79 00 d4 00 00 02 95 d4 00 e8 d4 00
\esmove 02a6
?auto_err 02aa
:02a6 00 00 02 c3 00 00 c0 02 d4 61 62 63 64 65 66 67
:02b6 68 69 6a 6b 6c 6d 6e 6f 70 71 72 73 74 75 76 77
/epush16 02d5 00
:02c6 78 79 7a 30 31 32 33 34 35 36 37 38 39 00 d4 00
\epush16 02d6
/lstor16 02da 00
\lstor16 02db
/dpop16 02df 00
\dpop16 02e0
/epush16 02e2 00
\epush16 02e3
:02d6 00 02 af d4 00 00 ff fe d4 00 00 d4 00 00 00 24
/lpush16 02e7 00
\lpush16 02e8
/epush16 02ec 00
\epush16 02ed
/Cmemcpy 02f1 00
\Cmemcpy 02f2
/esmove 02f4 00
\esmove 02f5
:02e6 d4 00 00 ff fe d4 00 00 00 02 d4 00 00 d4 00 00
?auto_err 02f9
/epush16 02fc 00
\epush16 02fd
/epush16 0301 00
\epush16 0302
:02f6 00 06 c3 00 00 d4 00 00 00 24 d4 00 00 00 02 d4
/lpush16 0306 00
\lpush16 0307
/Cmemcmp 030b 00
\Cmemcmp 030c
/esmove 030e 00
\esmove 030f
?auto_err 0313
:0306 00 00 ff fe d4 00 00 d4 00 00 00 06 c3 00 00 d4
/dpush16 0316 00
\dpush16 0317
/dpop16 0319 00
\dpop16 031a
:0316 00 00 d4 00 00 9a 52 8a f1 c2 03 3e c0 03 2e 6d
/epush16 032f 00
\epush16 0330
:0326 65 6d 63 70 79 2d 31 00 d4 00 00 03 25 d4 00 98
/esmove 0337 00
\esmove 0338
?auto_err 033c
/epush16 033f 00
\epush16 0340
/epush16 0344 00
\epush16 0345
:0336 d4 00 00 00 02 c3 00 00 d4 00 00 00 24 d4 00 00
/epush16 0349 00
\epush16 034a
/epush16 034e 00
\epush16 034f
/add16 0353 00
\add16 0354
:0346 00 02 d4 00 00 00 02 d4 00 00 00 12 d4 00 00 d4
/Cmemcpy 0356 00
\Cmemcpy 0357
/esmove 0359 00
\esmove 035a
?auto_err 035e
/epush16 0361 00
\epush16 0362
:0356 00 00 d4 00 00 00 06 c3 00 00 d4 00 00 00 12 d4
/epush16 0366 00
\epush16 0367
/epush16 036b 00
\epush16 036c
/add16 0370 00
\add16 0371
/lpush16 0373 00
\lpush16 0374
:0366 00 00 00 02 d4 00 00 00 12 d4 00 00 d4 00 00 ff
/Cmemcmp 0378 00
\Cmemcmp 0379
/esmove 037b 00
\esmove 037c
?auto_err 0380
/dpush16 0383 00
\dpush16 0384
:0376 fe d4 00 00 d4 00 00 00 06 c3 00 00 d4 00 00 d4
/dpop16 0386 00
\dpop16 0387
:0386 00 00 9a 52 8a f1 c2 03 ab c0 03 9b 6d 65 6d 63
/epush16 039c 00
\epush16 039d
/esmove 03a4 00
\esmove 03a5
:0396 70 79 2d 32 00 d4 00 00 03 92 d4 00 98 d4 00 00
?auto_err 03a9
/epush16 03ac 00
\epush16 03ad
/epush16 03b1 00
\epush16 03b2
:03a6 00 02 c3 00 00 d4 00 00 00 24 d4 00 00 00 02 d4
/epush16 03b6 00
\epush16 03b7
/add16 03bb 00
\add16 03bc
/epush16 03be 00
\epush16 03bf
/Cmemcpy 03c3 00
\Cmemcpy 03c4
:03b6 00 00 00 12 d4 00 00 d4 00 00 00 02 d4 00 00 d4
/esmove 03c6 00
\esmove 03c7
?auto_err 03cb
/epush16 03ce 00
\epush16 03cf
/epush16 03d3 00
\epush16 03d4
:03c6 00 00 00 06 c3 00 00 d4 00 00 00 12 d4 00 00 00
/lpush16 03d8 00
\lpush16 03d9
/Cmemcmp 03dd 00
\Cmemcmp 03de
/esmove 03e0 00
\esmove 03e1
?auto_err 03e5
:03d6 02 d4 00 00 ff fe d4 00 00 d4 00 00 00 06 c3 00
/dpush16 03e8 00
\dpush16 03e9
/dpop16 03eb 00
\dpop16 03ec
:03e6 00 d4 00 00 d4 00 00 9a 52 8a f1 c2 04 10 c0 04
/epush16 0401 00
\epush16 0402
:03f6 00 6d 65 6d 63 70 79 2d 33 00 d4 00 00 03 f7 d4
/esmove 0409 00
\esmove 040a
?auto_err 040e
:0406 00 98 d4 00 00 00 02 c3 00 00 c0 04 1b 6d 65 6d
/epush16 041c 00
\epush16 041d
/esmove 0424 00
\esmove 0425
:0416 6d 6f 76 65 00 d4 00 00 04 13 d4 00 e8 d4 00 00
?auto_err 0429
/epush16 042c 00
\epush16 042d
/lpush16 0431 00
\lpush16 0432
:0426 00 02 c3 00 00 d4 00 00 00 24 d4 00 00 ff fe d4
/epush16 0436 00
\epush16 0437
/Cmemcpy 043b 00
\Cmemcpy 043c
/esmove 043e 00
\esmove 043f
?auto_err 0443
:0436 00 00 00 02 d4 00 00 d4 00 00 00 06 c3 00 00 d4
/epush16 0446 00
\epush16 0447
/epush16 044b 00
\epush16 044c
/epush16 0450 00
\epush16 0451
/epush16 0455 00
:0446 00 00 00 23 d4 00 00 00 02 d4 00 00 00 02 d4 00
\epush16 0456
/add16 045a 00
\add16 045b
/Cmemmove 045d 00
\Cmemmove 045e
/esmove 0460 00
\esmove 0461
?auto_err 0465
:0456 00 00 01 d4 00 00 d4 00 00 d4 00 00 00 06 c3 00
/epush16 0468 00
\epush16 0469
/lpush16 046d 00
\lpush16 046e
/epush16 0472 00
\epush16 0473
:0466 00 d4 00 00 00 23 d4 00 00 ff fe d4 00 00 00 02
/epush16 0477 00
\epush16 0478
/add16 047c 00
\add16 047d
/Cmemcmp 047f 00
\Cmemcmp 0480
/esmove 0482 00
\esmove 0483
:0476 d4 00 00 00 01 d4 00 00 d4 00 00 d4 00 00 00 06
?auto_err 0487
/dpush16 048a 00
\dpush16 048b
/dget16 048d 00
\dget16 048e
:0486 c3 00 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 04 a9
/dpop16 0497 00
\dpop16 0498
/epush16 049a 00
\epush16 049b
/deref8 049f 00
\deref8 04a0
/epush16 04a2 00
\epush16 04a3
:0496 d4 00 00 d4 00 00 00 02 d4 00 00 d4 00 00 00 61
/ne16 04a7 00
\ne16 04a8
/dpop16 04aa 00
\dpop16 04ab
:04a6 d4 00 00 d4 00 00 9a 52 8a f1 c2 04 d0 c0 04 c0
/epush16 04c1 00
\epush16 04c2
:04b6 6d 65 6d 6d 6f 76 65 2d 31 00 d4 00 00 04 b6 d4
/esmove 04c9 00
\esmove 04ca
?auto_err 04ce
/epush16 04d1 00
\epush16 04d2
:04c6 00 98 d4 00 00 00 02 c3 00 00 d4 00 00 00 24 d4
/lpush16 04d6 00
\lpush16 04d7
/epush16 04db 00
\epush16 04dc
/Cmemcpy 04e0 00
\Cmemcpy 04e1
/esmove 04e3 00
\esmove 04e4
:04d6 00 00 ff fe d4 00 00 00 02 d4 00 00 d4 00 00 00
?auto_err 04e8
/epush16 04eb 00
\epush16 04ec
/epush16 04f0 00
\epush16 04f1
/epush16 04f5 00
:04e6 06 c3 00 00 d4 00 00 00 23 d4 00 00 00 02 d4 00
\epush16 04f6
/add16 04fa 00
\add16 04fb
/epush16 04fd 00
\epush16 04fe
/Cmemmove 0502 00
\Cmemmove 0503
/esmove 0505 00
:04f6 00 00 01 d4 00 00 d4 00 00 00 02 d4 00 00 d4 00
\esmove 0506
?auto_err 050a
/epush16 050d 00
\epush16 050e
/epush16 0512 00
\epush16 0513
:0506 00 00 06 c3 00 00 d4 00 00 00 23 d4 00 00 00 01
/lpush16 0517 00
\lpush16 0518
/add16 051c 00
\add16 051d
/epush16 051f 00
\epush16 0520
/Cmemcmp 0524 00
\Cmemcmp 0525
:0516 d4 00 00 ff fe d4 00 00 d4 00 00 00 02 d4 00 00
/esmove 0527 00
\esmove 0528
?auto_err 052c
/dpush16 052f 00
\dpush16 0530
/dget16 0532 00
\dget16 0533
:0526 d4 00 00 00 06 c3 00 00 d4 00 00 d4 00 00 9a 52
/dpop16 053c 00
\dpop16 053d
/epush16 053f 00
\epush16 0540
/epush16 0544 00
\epush16 0545
:0536 8a f1 ca 05 56 d4 00 00 d4 00 00 00 02 d4 00 00
/add16 0549 00
\add16 054a
/deref8 054c 00
\deref8 054d
/epush16 054f 00
\epush16 0550
/ne16 0554 00
\ne16 0555
:0546 00 23 d4 00 00 d4 00 00 d4 00 00 00 39 d4 00 00
/dpop16 0557 00
\dpop16 0558
:0556 d4 00 00 9a 52 8a f1 c2 05 7d c0 05 6d 6d 65 6d
/epush16 056e 00
\epush16 056f
:0566 6d 6f 76 65 2d 32 00 d4 00 00 05 63 d4 00 98 d4
/esmove 0576 00
\esmove 0577
?auto_err 057b
:0576 00 00 00 02 c3 00 00 c0 05 87 6d 65 6d 73 65 74
/epush16 0588 00
\epush16 0589
/esmove 0590 00
\esmove 0591
?auto_err 0595
:0586 00 d4 00 00 05 80 d4 00 e8 d4 00 00 00 02 c3 00
/epush16 0598 00
\epush16 0599
/lstor16 059d 00
\lstor16 059e
/dpop16 05a2 00
\dpop16 05a3
/lpush16 05a5 00
:0596 00 d4 00 00 00 00 d4 00 00 ff f8 d4 00 00 d4 00
\lpush16 05a6
/epush16 05aa 00
\epush16 05ab
/lt16 05af 00
\lt16 05b0
/dpop16 05b2 00
\dpop16 05b3
:05a6 00 ff f8 d4 00 00 00 40 d4 00 00 d4 00 00 9a 52
/lpush16 05c2 00
\lpush16 05c3
:05b6 8a f1 ca 05 be c0 05 f2 c0 05 d1 d4 00 00 ff f8
/linc16 05c7 00
\linc16 05c8
/dpop16 05cc 00
\dpop16 05cd
/epush16 05d2 00
\epush16 05d3
:05c6 d4 00 00 ff f8 d4 00 00 c0 05 a4 d4 00 00 00 02
/lpush16 05d7 00
\lpush16 05d8
/add16 05dc 00
\add16 05dd
/epush16 05df 00
\epush16 05e0
/swap16 05e4 00
\swap16 05e5
:05d6 d4 00 00 ff f8 d4 00 00 d4 00 00 ff ff d4 00 00
/dpop16 05e7 00
\dpop16 05e8
/pstor8 05ea 00
\pstor8 05eb
/dpop16 05ed 00
\dpop16 05ee
/epush16 05f3 00
\epush16 05f4
:05e6 d4 00 00 d4 00 00 d4 00 00 c0 05 c1 d4 00 00 00
/epush16 05f8 00
\epush16 05f9
/epush16 05fd 00
\epush16 05fe
/Cmemset 0602 00
\Cmemset 0603
/esmove 0605 00
:05f6 20 d4 00 00 00 00 d4 00 00 00 02 d4 00 00 d4 00
\esmove 0606
?auto_err 060a
/epush16 060d 00
\epush16 060e
/epush16 0612 00
\epush16 0613
:0606 00 00 06 c3 00 00 d4 00 00 00 02 d4 00 00 00 1f
/add16 0617 00
\add16 0618
/deref8 061a 00
\deref8 061b
/dpop16 061d 00
\dpop16 061e
:0616 d4 00 00 d4 00 00 d4 00 00 9a 52 8a f1 c2 06 42
/epush16 0633 00
\epush16 0634
:0626 c0 06 32 6d 65 6d 73 65 74 2d 31 00 d4 00 00 06
/esmove 063b 00
\esmove 063c
?auto_err 0640
/epush16 0643 00
\epush16 0644
:0636 29 d4 00 98 d4 00 00 00 02 c3 00 00 d4 00 00 00
/epush16 0648 00
\epush16 0649
/add16 064d 00
\add16 064e
/deref8 0650 00
\deref8 0651
/dpop16 0653 00
\dpop16 0654
:0646 02 d4 00 00 00 20 d4 00 00 d4 00 00 d4 00 00 9a
:0656 52 8a f1 ca 06 78 c0 06 68 6d 65 6d 73 65 74 2d
/epush16 0669 00
\epush16 066a
/esmove 0671 00
\esmove 0672
:0666 32 00 d4 00 00 06 5f d4 00 98 d4 00 00 00 02 c3
?auto_err 0676
/epush16 0679 00
\epush16 067a
/lstor16 067e 00
\lstor16 067f
/dpop16 0683 00
\dpop16 0684
:0676 00 00 d4 00 00 00 00 d4 00 00 ff f8 d4 00 00 d4
/lpush16 0686 00
\lpush16 0687
/epush16 068b 00
\epush16 068c
/lt16 0690 00
\lt16 0691
/dpop16 0693 00
\dpop16 0694
:0686 00 00 ff f8 d4 00 00 00 80 d4 00 00 d4 00 00 9a
/lpush16 06a3 00
\lpush16 06a4
:0696 52 8a f1 ca 06 9f c0 06 d3 c0 06 b2 d4 00 00 ff
/linc16 06a8 00
\linc16 06a9
/dpop16 06ad 00
\dpop16 06ae
/epush16 06b3 00
\epush16 06b4
:06a6 f8 d4 00 00 ff f8 d4 00 00 c0 06 85 d4 00 00 00
/lpush16 06b8 00
\lpush16 06b9
/add16 06bd 00
\add16 06be
/epush16 06c0 00
\epush16 06c1
/swap16 06c5 00
:06b6 02 d4 00 00 ff f8 d4 00 00 d4 00 00 ff ff d4 00
\swap16 06c6
/dpop16 06c8 00
\dpop16 06c9
/pstor8 06cb 00
\pstor8 06cc
/dpop16 06ce 00
\dpop16 06cf
/epush16 06d4 00
\epush16 06d5
:06c6 00 d4 00 00 d4 00 00 d4 00 00 c0 06 a2 d4 00 00
/epush16 06d9 00
\epush16 06da
/epush16 06de 00
\epush16 06df
/Cmemset 06e3 00
\Cmemset 06e4
:06d6 00 20 d4 00 00 00 7b d4 00 00 00 02 d4 00 00 d4
/esmove 06e6 00
\esmove 06e7
?auto_err 06eb
/epush16 06ee 00
\epush16 06ef
/epush16 06f3 00
\epush16 06f4
:06e6 00 00 00 06 c3 00 00 d4 00 00 00 02 d4 00 00 00
/add16 06f8 00
\add16 06f9
/deref8 06fb 00
\deref8 06fc
/epush16 06fe 00
\epush16 06ff
/ne16 0703 00
\ne16 0704
:06f6 1f d4 00 00 d4 00 00 d4 00 00 00 7b d4 00 00 d4
/dpop16 0706 00
\dpop16 0707
:0706 00 00 9a 52 8a f1 ca 07 12 c0 07 2e c0 07 1e 6d
/epush16 071f 00
\epush16 0720
:0716 65 6d 73 65 74 2d 33 00 d4 00 00 07 15 d4 00 98
/esmove 0727 00
\esmove 0728
?auto_err 072c
/epush16 072f 00
\epush16 0730
/epush16 0734 00
\epush16 0735
:0726 d4 00 00 00 02 c3 00 00 d4 00 00 00 02 d4 00 00
/add16 0739 00
\add16 073a
/deref8 073c 00
\deref8 073d
/epush16 073f 00
\epush16 0740
/eq16 0744 00
\eq16 0745
:0736 00 20 d4 00 00 d4 00 00 d4 00 00 00 7b d4 00 00
/dpop16 0747 00
\dpop16 0748
:0746 d4 00 00 9a 52 8a f1 ca 07 53 c0 07 6f c0 07 5f
/epush16 0760 00
\epush16 0761
:0756 6d 65 6d 73 65 74 2d 34 00 d4 00 00 07 56 d4 00
/esmove 0768 00
\esmove 0769
?auto_err 076d
:0766 98 d4 00 00 00 02 c3 00 00 c0 07 79 6d 65 6d 63
/epush16 077a 00
\epush16 077b
/esmove 0782 00
\esmove 0783
:0776 68 72 00 d4 00 00 07 72 d4 00 e8 d4 00 00 00 02
?auto_err 0787
:0786 c3 00 00 c0 07 9e 2e 2e 2e 2e 2e 2e 2e 2e 2e 2e
/epush16 079f 00
\epush16 07a0
/lstor16 07a4 00
\lstor16 07a5
:0796 2e 2e 2e 2e 2e 58 31 00 d4 00 00 07 8c d4 00 00
/dpop16 07a9 00
\dpop16 07aa
/epush16 07ac 00
\epush16 07ad
/epush16 07b1 00
\epush16 07b2
:07a6 ff fe d4 00 00 d4 00 00 00 10 d4 00 00 00 58 d4
/lpush16 07b6 00
\lpush16 07b7
/Cmemchr 07bb 00
\Cmemchr 07bc
/esmove 07be 00
\esmove 07bf
?auto_err 07c3
:07b6 00 00 ff fe d4 00 00 d4 00 00 00 06 c3 00 00 d4
/dpush16 07c6 00
\dpush16 07c7
/lstor16 07c9 00
\lstor16 07ca
/dpop16 07ce 00
\dpop16 07cf
/lpush16 07d1 00
\lpush16 07d2
:07c6 00 00 d4 00 00 ff fa d4 00 00 d4 00 00 ff fa d4
/not16 07d6 00
\not16 07d7
/dget16 07d9 00
\dget16 07da
/dpop16 07e3 00
\dpop16 07e4
:07d6 00 00 d4 00 00 9a 52 8a f1 ca 08 1a d4 00 00 d4
/lpush16 07e6 00
\lpush16 07e7
/deref8 07eb 00
\deref8 07ec
/epush16 07ee 00
\epush16 07ef
/ne16 07f3 00
\ne16 07f4
:07e6 00 00 ff fa d4 00 00 d4 00 00 00 58 d4 00 00 d4
/dget16 07f6 00
\dget16 07f7
/dpop16 0800 00
\dpop16 0801
/epush16 0803 00
\epush16 0804
:07f6 00 00 9a 52 8a f1 ca 08 1a d4 00 00 d4 00 00 00
/lpush16 0808 00
\lpush16 0809
/add16 080d 00
\add16 080e
/deref8 0810 00
\deref8 0811
/epush16 0813 00
\epush16 0814
:0806 01 d4 00 00 ff fa d4 00 00 d4 00 00 d4 00 00 00
/ne16 0818 00
\ne16 0819
/dpop16 081b 00
\dpop16 081c
:0816 31 d4 00 00 d4 00 00 9a 52 8a f1 c2 08 40 c0 08
/epush16 0831 00
\epush16 0832
:0826 30 6d 65 6d 63 68 72 2d 31 00 d4 00 00 08 27 d4
/esmove 0839 00
\esmove 083a
?auto_err 083e
/epush16 0841 00
\epush16 0842
:0836 00 98 d4 00 00 00 02 c3 00 00 d4 00 00 00 0f d4
/epush16 0846 00
\epush16 0847
/lpush16 084b 00
\lpush16 084c
/Cmemchr 0850 00
\Cmemchr 0851
/esmove 0853 00
\esmove 0854
:0846 00 00 00 58 d4 00 00 ff fe d4 00 00 d4 00 00 00
?auto_err 0858
/dpush16 085b 00
\dpush16 085c
/epush16 085e 00
\epush16 085f
/ne16 0863 00
\ne16 0864
:0856 06 c3 00 00 d4 00 00 d4 00 00 00 00 d4 00 00 d4
/dpop16 0866 00
\dpop16 0867
:0866 00 00 9a 52 8a f1 ca 08 72 c0 08 8e c0 08 7e 6d
/epush16 087f 00
\epush16 0880
:0876 65 6d 63 68 72 2d 32 00 d4 00 00 08 75 d4 00 98
/esmove 0887 00
\esmove 0888
?auto_err 088c
/esmove 088f 00
\esmove 0890
?auto_err 0894
:0886 d4 00 00 00 02 c3 00 00 d4 00 00 00 08 c3 00 00
/escheck 0898 00
\escheck 0899
=Ctest_dmem 08a0
:0896 e2 d4 00 00 60 72 ab f0 bb d5 e2 9b 73 8b 73 87
/esmove 08aa 00
\esmove 08ab
?auto_err 08af
:08a6 ab 97 bb d4 00 00 ff fa c3 00 00 c0 08 bb 6d 61
/epush16 08bc 00
\epush16 08bd
/esmove 08c4 00
\esmove 08c5
:08b6 6c 6c 6f 63 00 d4 00 00 08 b4 d4 00 e8 d4 00 00
?auto_err 08c9
/epush16 08cc 00
\epush16 08cd
/lstor16 08d1 00
\lstor16 08d2
:08c6 00 02 c3 00 00 d4 00 00 00 00 d4 00 00 ff fc d4
/dpop16 08d6 00
\dpop16 08d7
/lpush16 08d9 00
\lpush16 08da
/epush16 08de 00
\epush16 08df
/lt16 08e3 00
\lt16 08e4
:08d6 00 00 d4 00 00 ff fc d4 00 00 00 0a d4 00 00 d4
/dpop16 08e6 00
\dpop16 08e7
:08e6 00 00 9a 52 8a f1 ca 08 f2 c0 09 b5 c0 09 05 d4
/lpush16 08f6 00
\lpush16 08f7
/linc16 08fb 00
\linc16 08fc
/dpop16 0900 00
\dpop16 0901
:08f6 00 00 ff fc d4 00 00 ff fc d4 00 00 c0 08 d8 d4
/epush16 0906 00
\epush16 0907
/lpush16 090b 00
\lpush16 090c
/scltos2 0910 00
\scltos2 0911
/add16 0913 00
\add16 0914
:0906 00 00 00 42 d4 00 00 ff fc d4 00 00 d4 00 00 d4
/epush16 0916 00
\epush16 0917
/Cmalloc 091b 00
\Cmalloc 091c
/esmove 091e 00
\esmove 091f
?auto_err 0923
:0916 00 00 00 40 d4 00 00 d4 00 00 00 02 c3 00 00 d4
/dpush16 0926 00
\dpush16 0927
/swap16 0929 00
\swap16 092a
/dpop16 092c 00
\dpop16 092d
/pstor16 092f 00
\pstor16 0930
/epush16 0932 00
\epush16 0933
:0926 00 00 d4 00 00 d4 00 00 d4 00 00 d4 00 00 00 00
/eq16 0937 00
\eq16 0938
/dpop16 093a 00
\dpop16 093b
:0936 d4 00 00 d4 00 00 9a 52 8a f1 ca 09 46 c0 09 49
/epush16 094a 00
\epush16 094b
/lstor16 094f 00
\lstor16 0950
/dpop16 0954 00
\dpop16 0955
:0946 c0 09 b5 d4 00 00 00 00 d4 00 00 ff fa d4 00 00
/lpush16 0957 00
\lpush16 0958
/epush16 095c 00
\epush16 095d
/lt16 0961 00
\lt16 0962
/dpop16 0964 00
\dpop16 0965
:0956 d4 00 00 ff fa d4 00 00 00 40 d4 00 00 d4 00 00
/lpush16 0974 00
\lpush16 0975
:0966 9a 52 8a f1 ca 09 70 c0 09 b2 c0 09 83 d4 00 00
/linc16 0979 00
\linc16 097a
/dpop16 097e 00
\dpop16 097f
/epush16 0984 00
\epush16 0985
:0976 ff fa d4 00 00 ff fa d4 00 00 c0 09 56 d4 00 00
/lpush16 0989 00
\lpush16 098a
/scltos2 098e 00
\scltos2 098f
/add16 0991 00
\add16 0992
/deref16 0994 00
\deref16 0995
:0986 00 42 d4 00 00 ff fc d4 00 00 d4 00 00 d4 00 00
/lpush16 0997 00
\lpush16 0998
/add16 099c 00
\add16 099d
/lpush16 099f 00
\lpush16 09a0
/swap16 09a4 00
\swap16 09a5
:0996 d4 00 00 ff fa d4 00 00 d4 00 00 ff fc d4 00 00
/dpop16 09a7 00
\dpop16 09a8
/pstor8 09aa 00
\pstor8 09ab
/dpop16 09ad 00
\dpop16 09ae
:09a6 d4 00 00 d4 00 00 d4 00 00 c0 09 73 c0 08 f5 d4
/lpush16 09b6 00
\lpush16 09b7
/epush16 09bb 00
\epush16 09bc
/lt16 09c0 00
\lt16 09c1
/dpop16 09c3 00
\dpop16 09c4
:09b6 00 00 ff fc d4 00 00 00 0a d4 00 00 d4 00 00 9a
:09c6 52 8a f1 ca 09 cf c0 09 eb c0 09 db 6d 61 6c 6c
/epush16 09dc 00
\epush16 09dd
/esmove 09e4 00
\esmove 09e5
:09d6 6f 63 2d 31 00 d4 00 00 09 d2 d4 00 98 d4 00 00
?auto_err 09e9
/epush16 09ec 00
\epush16 09ed
/lstor16 09f1 00
\lstor16 09f2
:09e6 00 02 c3 00 00 d4 00 00 00 00 d4 00 00 ff fc d4
/dpop16 09f6 00
\dpop16 09f7
/lpush16 09f9 00
\lpush16 09fa
/epush16 09fe 00
\epush16 09ff
/lt16 0a03 00
\lt16 0a04
:09f6 00 00 d4 00 00 ff fc d4 00 00 00 0a d4 00 00 d4
/dpop16 0a06 00
\dpop16 0a07
:0a06 00 00 9a 52 8a f1 ca 0a 12 c0 0a b8 c0 0a 25 d4
/lpush16 0a16 00
\lpush16 0a17
/linc16 0a1b 00
\linc16 0a1c
/dpop16 0a20 00
\dpop16 0a21
:0a16 00 00 ff fc d4 00 00 ff fc d4 00 00 c0 09 f8 d4
/epush16 0a26 00
\epush16 0a27
/lstor16 0a2b 00
\lstor16 0a2c
/dpop16 0a30 00
\dpop16 0a31
/lpush16 0a33 00
\lpush16 0a34
:0a26 00 00 00 00 d4 00 00 ff fa d4 00 00 d4 00 00 ff
/epush16 0a38 00
\epush16 0a39
/lt16 0a3d 00
\lt16 0a3e
/dpop16 0a40 00
\dpop16 0a41
:0a36 fa d4 00 00 00 40 d4 00 00 d4 00 00 9a 52 8a f1
/lpush16 0a50 00
\lpush16 0a51
/linc16 0a55 00
:0a46 ca 0a 4c c0 0a 98 c0 0a 5f d4 00 00 ff fa d4 00
\linc16 0a56
/dpop16 0a5a 00
\dpop16 0a5b
/epush16 0a60 00
\epush16 0a61
/lpush16 0a65 00
:0a56 00 ff fa d4 00 00 c0 0a 32 d4 00 00 00 42 d4 00
\lpush16 0a66
/scltos2 0a6a 00
\scltos2 0a6b
/add16 0a6d 00
\add16 0a6e
/deref16 0a70 00
\deref16 0a71
/lpush16 0a73 00
\lpush16 0a74
:0a66 00 ff fc d4 00 00 d4 00 00 d4 00 00 d4 00 00 ff
/add16 0a78 00
\add16 0a79
/deref8 0a7b 00
\deref8 0a7c
/lpush16 0a7e 00
\lpush16 0a7f
/ne16 0a83 00
\ne16 0a84
:0a76 fa d4 00 00 d4 00 00 d4 00 00 ff fc d4 00 00 d4
/dpop16 0a86 00
\dpop16 0a87
:0a86 00 00 9a 52 8a f1 ca 0a 92 c0 0a 95 c0 0a 98 c0
/epush16 0a99 00
\epush16 0a9a
/lpush16 0a9e 00
\lpush16 0a9f
/ne16 0aa3 00
\ne16 0aa4
:0a96 0a 4f d4 00 00 00 40 d4 00 00 ff fa d4 00 00 d4
/dpop16 0aa6 00
\dpop16 0aa7
:0aa6 00 00 9a 52 8a f1 ca 0a b2 c0 0a b5 c0 0a b8 c0
/lpush16 0ab9 00
\lpush16 0aba
/epush16 0abe 00
\epush16 0abf
/lt16 0ac3 00
\lt16 0ac4
:0ab6 0a 15 d4 00 00 ff fc d4 00 00 00 0a d4 00 00 d4
/dpop16 0ac6 00
\dpop16 0ac7
:0ac6 00 00 9a 52 8a f1 ca 0a d2 c0 0a ee c0 0a de 6d
/epush16 0adf 00
\epush16 0ae0
:0ad6 61 6c 6c 6f 63 2d 32 00 d4 00 00 0a d5 d4 00 98
/esmove 0ae7 00
\esmove 0ae8
?auto_err 0aec
:0ae6 d4 00 00 00 02 c3 00 00 c0 0a f6 66 72 65 65 00
/epush16 0af7 00
\epush16 0af8
/esmove 0aff 00
\esmove 0b00
?auto_err 0b04
:0af6 d4 00 00 0a f1 d4 00 e8 d4 00 00 00 02 c3 00 00
/epush16 0b07 00
\epush16 0b08
/lstor16 0b0c 00
\lstor16 0b0d
/dpop16 0b11 00
\dpop16 0b12
/lpush16 0b14 00
\lpush16 0b15
:0b06 d4 00 00 00 00 d4 00 00 ff fa d4 00 00 d4 00 00
/lpush16 0b19 00
\lpush16 0b1a
/lt16 0b1e 00
\lt16 0b1f
/dpop16 0b21 00
\dpop16 0b22
:0b16 ff fa d4 00 00 ff fc d4 00 00 d4 00 00 9a 52 8a
/lpush16 0b31 00
\lpush16 0b32
:0b26 f1 ca 0b 2d c0 0b 61 c0 0b 40 d4 00 00 ff fa d4
/linc16 0b36 00
\linc16 0b37
/dpop16 0b3b 00
\dpop16 0b3c
/epush16 0b41 00
\epush16 0b42
:0b36 00 00 ff fa d4 00 00 c0 0b 13 d4 00 00 00 42 d4
/lpush16 0b46 00
\lpush16 0b47
/scltos2 0b4b 00
\scltos2 0b4c
/add16 0b4e 00
\add16 0b4f
/deref16 0b51 00
\deref16 0b52
/Cfree 0b54 00
\Cfree 0b55
:0b46 00 00 ff fa d4 00 00 d4 00 00 d4 00 00 d4 00 00
/esmove 0b57 00
\esmove 0b58
?auto_err 0b5c
:0b56 d4 00 00 00 02 c3 00 00 c0 0b 30 c0 0b 6b 63 61
/epush16 0b6c 00
\epush16 0b6d
/esmove 0b74 00
\esmove 0b75
:0b66 6c 6c 6f 63 00 d4 00 00 0b 64 d4 00 e8 d4 00 00
?auto_err 0b79
/epush16 0b7c 00
\epush16 0b7d
/lpush16 0b81 00
\lpush16 0b82
:0b76 00 02 c3 00 00 d4 00 00 00 40 d4 00 00 ff fc d4
/Ccalloc 0b86 00
\Ccalloc 0b87
/esmove 0b89 00
\esmove 0b8a
?auto_err 0b8e
/dpush16 0b91 00
\dpush16 0b92
/lstor16 0b94 00
\lstor16 0b95
:0b86 00 00 d4 00 00 00 04 c3 00 00 d4 00 00 d4 00 00
/epush16 0b99 00
\epush16 0b9a
/eq16 0b9e 00
\eq16 0b9f
/dpop16 0ba1 00
\dpop16 0ba2
:0b96 ff fe d4 00 00 00 00 d4 00 00 d4 00 00 9a 52 8a
:0ba6 f1 ca 0b ad c0 0b c9 c0 0b b9 63 61 6c 6c 6f 63
/epush16 0bba 00
\epush16 0bbb
/esmove 0bc2 00
\esmove 0bc3
:0bb6 2d 31 00 d4 00 00 0b b0 d4 00 98 d4 00 00 00 02
?auto_err 0bc7
/epush16 0bca 00
\epush16 0bcb
/lstor16 0bcf 00
\lstor16 0bd0
/dpop16 0bd4 00
\dpop16 0bd5
:0bc6 c3 00 00 d4 00 00 00 00 d4 00 00 ff fc d4 00 00
/lpush16 0bd7 00
\lpush16 0bd8
/epush16 0bdc 00
\epush16 0bdd
/lt16 0be1 00
\lt16 0be2
/dpop16 0be4 00
\dpop16 0be5
:0bd6 d4 00 00 ff fc d4 00 00 00 40 d4 00 00 d4 00 00
/lpush16 0bf4 00
\lpush16 0bf5
:0be6 9a 52 8a f1 ca 0b f0 c0 0c 23 c0 0c 03 d4 00 00
/linc16 0bf9 00
\linc16 0bfa
/dpop16 0bfe 00
\dpop16 0bff
/lpush16 0c04 00
\lpush16 0c05
:0bf6 ff fc d4 00 00 ff fc d4 00 00 c0 0b d6 d4 00 00
/lpush16 0c09 00
\lpush16 0c0a
/add16 0c0e 00
\add16 0c0f
/deref8 0c11 00
\deref8 0c12
/dpop16 0c14 00
\dpop16 0c15
:0c06 ff fc d4 00 00 ff fe d4 00 00 d4 00 00 d4 00 00
/lpush16 0c24 00
\lpush16 0c25
:0c16 9a 52 8a f1 c2 0c 20 c0 0c 23 c0 0b f3 d4 00 00
/epush16 0c29 00
\epush16 0c2a
/lt16 0c2e 00
\lt16 0c2f
/dpop16 0c31 00
\dpop16 0c32
:0c26 ff fc d4 00 00 00 40 d4 00 00 d4 00 00 9a 52 8a
:0c36 f1 ca 0c 3d c0 0c 59 c0 0c 49 63 61 6c 6c 6f 63
/epush16 0c4a 00
\epush16 0c4b
/esmove 0c52 00
\esmove 0c53
:0c46 2d 32 00 d4 00 00 0c 40 d4 00 98 d4 00 00 00 02
?auto_err 0c57
/lpush16 0c5a 00
\lpush16 0c5b
/Cfree 0c5f 00
\Cfree 0c60
/esmove 0c62 00
\esmove 0c63
:0c56 c3 00 00 d4 00 00 ff fe d4 00 00 d4 00 00 00 02
?auto_err 0c67
/epush16 0c75 00
:0c66 c3 00 00 c0 0c 74 72 65 61 6c 6c 6f 63 00 d4 00
\epush16 0c76
/esmove 0c7d 00
\esmove 0c7e
?auto_err 0c82
/epush16 0c85 00
:0c76 00 0c 6c d4 00 e8 d4 00 00 00 02 c3 00 00 d4 00
\epush16 0c86
/Cmalloc 0c8a 00
\Cmalloc 0c8b
/esmove 0c8d 00
\esmove 0c8e
?auto_err 0c92
/dpush16 0c95 00
:0c86 00 00 7b d4 00 00 d4 00 00 00 02 c3 00 00 d4 00
\dpush16 0c96
/lstor16 0c98 00
\lstor16 0c99
/epush16 0c9d 00
\epush16 0c9e
/eq16 0ca2 00
\eq16 0ca3
/dpop16 0ca5 00
:0c96 00 d4 00 00 ff fe d4 00 00 00 00 d4 00 00 d4 00
\dpop16 0ca6
:0ca6 00 9a 52 8a f1 ca 0c b1 c0 0c cd c0 0c bd 6d 61
/epush16 0cbe 00
\epush16 0cbf
:0cb6 6c 6c 6f 63 2d 33 00 d4 00 00 0c b4 d4 00 98 d4
/esmove 0cc6 00
\esmove 0cc7
?auto_err 0ccb
/epush16 0cce 00
\epush16 0ccf
/lstor16 0cd3 00
\lstor16 0cd4
:0cc6 00 00 00 02 c3 00 00 d4 00 00 00 00 d4 00 00 ff
/dpop16 0cd8 00
\dpop16 0cd9
/lpush16 0cdb 00
\lpush16 0cdc
/epush16 0ce0 00
\epush16 0ce1
/lt16 0ce5 00
:0cd6 fc d4 00 00 d4 00 00 ff fc d4 00 00 00 7b d4 00
\lt16 0ce6
/dpop16 0ce8 00
\dpop16 0ce9
:0ce6 00 d4 00 00 9a 52 8a f1 ca 0c f4 c0 0d 28 c0 0d
/lpush16 0cf8 00
\lpush16 0cf9
/linc16 0cfd 00
\linc16 0cfe
/dpop16 0d02 00
\dpop16 0d03
:0cf6 07 d4 00 00 ff fc d4 00 00 ff fc d4 00 00 c0 0c
/lpush16 0d08 00
\lpush16 0d09
/lpush16 0d0d 00
\lpush16 0d0e
/add16 0d12 00
\add16 0d13
/lpush16 0d15 00
:0d06 da d4 00 00 ff fc d4 00 00 ff fe d4 00 00 d4 00
\lpush16 0d16
/swap16 0d1a 00
\swap16 0d1b
/dpop16 0d1d 00
\dpop16 0d1e
/pstor8 0d20 00
\pstor8 0d21
/dpop16 0d23 00
\dpop16 0d24
:0d16 00 ff fc d4 00 00 d4 00 00 d4 00 00 d4 00 00 c0
/epush16 0d29 00
\epush16 0d2a
/lpush16 0d2e 00
\lpush16 0d2f
/Crealloc 0d33 00
\Crealloc 0d34
:0d26 0c f7 d4 00 00 01 01 d4 00 00 ff fe d4 00 00 d4
/esmove 0d36 00
\esmove 0d37
?auto_err 0d3b
/dpush16 0d3e 00
\dpush16 0d3f
/lstor16 0d41 00
\lstor16 0d42
:0d36 00 00 00 04 c3 00 00 d4 00 00 d4 00 00 ff fe d4
/epush16 0d46 00
\epush16 0d47
/eq16 0d4b 00
\eq16 0d4c
/dpop16 0d4e 00
\dpop16 0d4f
:0d46 00 00 00 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 0d
:0d56 5a c0 0d 77 c0 0d 67 72 65 61 6c 6c 6f 63 2d 31
/epush16 0d68 00
\epush16 0d69
/esmove 0d70 00
\esmove 0d71
?auto_err 0d75
:0d66 00 d4 00 00 0d 5d d4 00 98 d4 00 00 00 02 c3 00
/epush16 0d78 00
\epush16 0d79
/lstor16 0d7d 00
\lstor16 0d7e
/dpop16 0d82 00
\dpop16 0d83
/lpush16 0d85 00
:0d76 00 d4 00 00 00 00 d4 00 00 ff fc d4 00 00 d4 00
\lpush16 0d86
/epush16 0d8a 00
\epush16 0d8b
/lt16 0d8f 00
\lt16 0d90
/dpop16 0d92 00
\dpop16 0d93
:0d86 00 ff fc d4 00 00 00 7b d4 00 00 d4 00 00 9a 52
/lpush16 0da2 00
\lpush16 0da3
:0d96 8a f1 ca 0d 9e c0 0d dc c0 0d b1 d4 00 00 ff fc
/linc16 0da7 00
\linc16 0da8
/dpop16 0dac 00
\dpop16 0dad
/lpush16 0db2 00
\lpush16 0db3
:0da6 d4 00 00 ff fc d4 00 00 c0 0d 84 d4 00 00 ff fc
/lpush16 0db7 00
\lpush16 0db8
/add16 0dbc 00
\add16 0dbd
/deref8 0dbf 00
\deref8 0dc0
/lpush16 0dc2 00
\lpush16 0dc3
:0db6 d4 00 00 ff fe d4 00 00 d4 00 00 d4 00 00 ff fc
/ne16 0dc7 00
\ne16 0dc8
/dpop16 0dca 00
\dpop16 0dcb
:0dc6 d4 00 00 d4 00 00 9a 52 8a f1 ca 0d d6 c0 0d d9
/lpush16 0ddd 00
\lpush16 0dde
/epush16 0de2 00
\epush16 0de3
:0dd6 c0 0d dc c0 0d a1 d4 00 00 ff fc d4 00 00 00 7b
/lt16 0de7 00
\lt16 0de8
/dpop16 0dea 00
\dpop16 0deb
:0de6 d4 00 00 d4 00 00 9a 52 8a f1 ca 0d f6 c0 0e 13
/epush16 0e04 00
\epush16 0e05
:0df6 c0 0e 03 72 65 61 6c 6c 6f 63 2d 32 00 d4 00 00
/esmove 0e0c 00
\esmove 0e0d
?auto_err 0e11
/epush16 0e14 00
\epush16 0e15
:0e06 0d f9 d4 00 98 d4 00 00 00 02 c3 00 00 d4 00 00
/lpush16 0e19 00
\lpush16 0e1a
/Crealloc 0e1e 00
\Crealloc 0e1f
/esmove 0e21 00
\esmove 0e22
:0e16 00 61 d4 00 00 ff fe d4 00 00 d4 00 00 00 04 c3
?auto_err 0e26
/dpush16 0e29 00
\dpush16 0e2a
/lstor16 0e2c 00
\lstor16 0e2d
/epush16 0e31 00
\epush16 0e32
:0e26 00 00 d4 00 00 d4 00 00 ff fe d4 00 00 00 00 d4
/eq16 0e36 00
\eq16 0e37
/dpop16 0e39 00
\dpop16 0e3a
:0e36 00 00 d4 00 00 9a 52 8a f1 ca 0e 45 c0 0e 62 c0
/epush16 0e53 00
\epush16 0e54
:0e46 0e 52 72 65 61 6c 6c 6f 63 2d 33 00 d4 00 00 0e
/esmove 0e5b 00
\esmove 0e5c
?auto_err 0e60
/epush16 0e63 00
\epush16 0e64
:0e56 48 d4 00 98 d4 00 00 00 02 c3 00 00 d4 00 00 00
/lstor16 0e68 00
\lstor16 0e69
/dpop16 0e6d 00
\dpop16 0e6e
/lpush16 0e70 00
\lpush16 0e71
/epush16 0e75 00
:0e66 00 d4 00 00 ff fc d4 00 00 d4 00 00 ff fc d4 00
\epush16 0e76
/lt16 0e7a 00
\lt16 0e7b
/dpop16 0e7d 00
\dpop16 0e7e
:0e76 00 00 61 d4 00 00 d4 00 00 9a 52 8a f1 ca 0e 89
/lpush16 0e8d 00
\lpush16 0e8e
/linc16 0e92 00
\linc16 0e93
:0e86 c0 0e c7 c0 0e 9c d4 00 00 ff fc d4 00 00 ff fc
/dpop16 0e97 00
\dpop16 0e98
/lpush16 0e9d 00
\lpush16 0e9e
/lpush16 0ea2 00
\lpush16 0ea3
:0e96 d4 00 00 c0 0e 6f d4 00 00 ff fc d4 00 00 ff fe
/add16 0ea7 00
\add16 0ea8
/deref8 0eaa 00
\deref8 0eab
/lpush16 0ead 00
\lpush16 0eae
/ne16 0eb2 00
\ne16 0eb3
/dpop16 0eb5 00
:0ea6 d4 00 00 d4 00 00 d4 00 00 ff fc d4 00 00 d4 00
\dpop16 0eb6
:0eb6 00 9a 52 8a f1 ca 0e c1 c0 0e c4 c0 0e c7 c0 0e
/lpush16 0ec8 00
\lpush16 0ec9
/epush16 0ecd 00
\epush16 0ece
/lt16 0ed2 00
\lt16 0ed3
/dpop16 0ed5 00
:0ec6 8c d4 00 00 ff fc d4 00 00 00 61 d4 00 00 d4 00
\dpop16 0ed6
:0ed6 00 9a 52 8a f1 ca 0e e1 c0 0e fe c0 0e ee 72 65
/epush16 0eef 00
\epush16 0ef0
:0ee6 61 6c 6c 6f 63 2d 34 00 d4 00 00 0e e4 d4 00 98
/esmove 0ef7 00
\esmove 0ef8
?auto_err 0efc
/lpush16 0eff 00
\lpush16 0f00
/Cfree 0f04 00
\Cfree 0f05
:0ef6 d4 00 00 00 02 c3 00 00 d4 00 00 ff fe d4 00 00
/esmove 0f07 00
\esmove 0f08
?auto_err 0f0c
/esmove 0f0f 00
\esmove 0f10
?auto_err 0f14
:0f06 d4 00 00 00 02 c3 00 00 d4 00 00 00 06 c3 00 00
/escheck 0f18 00
\escheck 0f19
=Cqcmp 0f20
:0f16 e2 d4 00 00 60 72 ab f0 bb d5 e2 9b 73 8b 73 87
/lpush16 0f2a 00
\lpush16 0f2b
/deref16 0f2f 00
\deref16 0f30
/lpush16 0f32 00
\lpush16 0f33
:0f26 ab 97 bb d4 00 00 00 00 d4 00 00 d4 00 00 00 02
/deref16 0f37 00
\deref16 0f38
/lt16 0f3a 00
\lt16 0f3b
/dpop16 0f3d 00
\dpop16 0f3e
:0f36 d4 00 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 0f 49
/epush16 0f4a 00
\epush16 0f4b
/lpush16 0f52 00
\lpush16 0f53
:0f46 c0 0f 51 d4 00 00 ff ff c0 0f 7e d4 00 00 00 00
/deref16 0f57 00
\deref16 0f58
/lpush16 0f5a 00
\lpush16 0f5b
/deref16 0f5f 00
\deref16 0f60
/gt16 0f62 00
\gt16 0f63
/dpop16 0f65 00
:0f56 d4 00 00 d4 00 00 00 02 d4 00 00 d4 00 00 d4 00
\dpop16 0f66
/epush16 0f72 00
\epush16 0f73
:0f66 00 9a 52 8a f1 ca 0f 71 c0 0f 79 d4 00 00 00 01
/epush16 0f7a 00
\epush16 0f7b
/dpop16 0f7f 00
\dpop16 0f80
/escheck 0f83 00
\escheck 0f84
:0f76 c0 0f 7e d4 00 00 00 00 d4 00 00 e2 d4 00 00 60
=Ctest_sort 0f8b
/esmove 0f95 00
:0f86 72 ab f0 bb d5 e2 9b 73 8b 73 87 ab 97 bb d4 00
\esmove 0f96
?auto_err 0f9a
:0f96 00 ff fc c3 00 00 c0 0f a5 71 73 6f 72 74 00 d4
/epush16 0fa6 00
\epush16 0fa7
/esmove 0fae 00
\esmove 0faf
?auto_err 0fb3
:0fa6 00 00 0f 9f d4 00 e8 d4 00 00 00 02 c3 00 00 d4
/epush16 0fb6 00
\epush16 0fb7
/lstor16 0fbb 00
\lstor16 0fbc
/dpop16 0fc0 00
\dpop16 0fc1
/lpush16 0fc3 00
\lpush16 0fc4
:0fb6 00 00 00 00 d4 00 00 ff fe d4 00 00 d4 00 00 ff
/epush16 0fc8 00
\epush16 0fc9
/lt16 0fcd 00
\lt16 0fce
/dpop16 0fd0 00
\dpop16 0fd1
:0fc6 fe d4 00 00 00 20 d4 00 00 d4 00 00 9a 52 8a f1
/lpush16 0fe0 00
\lpush16 0fe1
/linc16 0fe5 00
:0fd6 ca 0f dc c0 10 1b c0 0f ef d4 00 00 ff fe d4 00
\linc16 0fe6
/dpop16 0fea 00
\dpop16 0feb
/epush16 0ff0 00
\epush16 0ff1
/lpush16 0ff5 00
:0fe6 00 ff fe d4 00 00 c0 0f c2 d4 00 00 00 56 d4 00
\lpush16 0ff6
/scltos2 0ffa 00
\scltos2 0ffb
/add16 0ffd 00
\add16 0ffe
/epush16 1000 00
\epush16 1001
/lpush16 1005 00
:0ff6 00 ff fe d4 00 00 d4 00 00 d4 00 00 00 20 d4 00
\lpush16 1006
/sub16 100a 00
\sub16 100b
/swap16 100d 00
\swap16 100e
/dpop16 1010 00
\dpop16 1011
/pstor16 1013 00
\pstor16 1014
:1006 00 ff fe d4 00 00 d4 00 00 d4 00 00 d4 00 00 d4
/dpop16 1016 00
\dpop16 1017
/epush16 101c 00
\epush16 101d
/epush16 1021 00
\epush16 1022
:1016 00 00 c0 0f df d4 00 00 0f 20 d4 00 00 00 02 d4
/epush16 1026 00
\epush16 1027
/epush16 102b 00
\epush16 102c
/Cqsort 1030 00
\Cqsort 1031
/esmove 1033 00
\esmove 1034
:1026 00 00 00 20 d4 00 00 00 56 d4 00 00 d4 00 00 00
?auto_err 1038
/epush16 103b 00
\epush16 103c
/lstor16 1040 00
\lstor16 1041
/lstor16 1045 00
:1036 08 c3 00 00 d4 00 00 00 00 d4 00 00 ff fe d4 00
\lstor16 1046
/dpop16 104a 00
\dpop16 104b
/lpush16 104d 00
\lpush16 104e
/epush16 1052 00
\epush16 1053
:1046 00 ff fc d4 00 00 d4 00 00 ff fe d4 00 00 00 20
/lt16 1057 00
\lt16 1058
/dpop16 105a 00
\dpop16 105b
:1056 d4 00 00 d4 00 00 9a 52 8a f1 ca 10 66 c0 10 dd
/lpush16 106a 00
\lpush16 106b
/linc16 106f 00
\linc16 1070
/dpop16 1074 00
\dpop16 1075
:1066 c0 10 79 d4 00 00 ff fe d4 00 00 ff fe d4 00 00
/epush16 107a 00
\epush16 107b
/lpush16 107f 00
\lpush16 1080
/scltos2 1084 00
\scltos2 1085
:1076 c0 10 4c d4 00 00 00 56 d4 00 00 ff fe d4 00 00
/add16 1087 00
\add16 1088
/deref16 108a 00
\deref16 108b
/lpush16 108d 00
\lpush16 108e
/lt16 1092 00
\lt16 1093
/dpop16 1095 00
:1086 d4 00 00 d4 00 00 d4 00 00 ff fc d4 00 00 d4 00
\dpop16 1096
:1096 00 9a 52 8a f1 ca 10 a1 c0 10 bf c0 10 ac 71 73
/epush16 10ad 00
\epush16 10ae
/esmove 10b5 00
:10a6 6f 72 74 2d 31 00 d4 00 00 10 a4 d4 00 98 d4 00
\esmove 10b6
?auto_err 10ba
/epush16 10c0 00
\epush16 10c1
/lpush16 10c5 00
:10b6 00 00 02 c3 00 00 c0 10 dd d4 00 00 00 56 d4 00
\lpush16 10c6
/scltos2 10ca 00
\scltos2 10cb
/add16 10cd 00
\add16 10ce
/deref16 10d0 00
\deref16 10d1
/lstor16 10d3 00
\lstor16 10d4
:10c6 00 ff fe d4 00 00 d4 00 00 d4 00 00 d4 00 00 ff
/dpop16 10d8 00
\dpop16 10d9
/esmove 10de 00
\esmove 10df
?auto_err 10e3
:10d6 fc d4 00 00 c0 10 69 d4 00 00 00 04 c3 00 00 e2
/escheck 10e7 00
\escheck 10e8
:10e6 d4 00 00 60 72 ab f0 bb d5 02 00 03 00 05 00 07
=Ctest_array 10ef
=Ctest_search 1103
:10f6 00 0b 00 0d 00 11 00 13 00 17 00 1b 00 e2 9b 73
/esmove 110d 00
\esmove 110e
?auto_err 1112
:1106 8b 73 87 ab 97 bb d4 00 00 ff fc c3 00 00 c0 11
/epush16 1120 00
\epush16 1121
:1116 1f 62 73 65 61 72 63 68 00 d4 00 00 11 17 d4 00
/esmove 1128 00
\esmove 1129
?auto_err 112d
/epush16 1130 00
\epush16 1131
/lstor16 1135 00
:1126 e8 d4 00 00 00 02 c3 00 00 d4 00 00 00 0d d4 00
\lstor16 1136
/dpop16 113a 00
\dpop16 113b
/epush16 113d 00
\epush16 113e
/epush16 1142 00
\epush16 1143
:1136 00 ff fe d4 00 00 d4 00 00 0f 20 d4 00 00 00 02
/epush16 1147 00
\epush16 1148
/epush16 114c 00
\epush16 114d
/laddr16 1151 00
\laddr16 1152
:1146 d4 00 00 00 0a d4 00 00 10 ef d4 00 00 ff fe d4
/Cbsearch 1156 00
\Cbsearch 1157
/esmove 1159 00
\esmove 115a
?auto_err 115e
/dpush16 1161 00
\dpush16 1162
/lstor16 1164 00
\lstor16 1165
:1156 00 00 d4 00 00 00 0a c3 00 00 d4 00 00 d4 00 00
/epush16 1169 00
\epush16 116a
/eq16 116e 00
\eq16 116f
/dpop16 1171 00
\dpop16 1172
:1166 ff fc d4 00 00 00 00 d4 00 00 d4 00 00 9a 52 8a
:1176 f1 ca 11 7d c0 11 9a c0 11 8a 62 73 65 61 72 63
/epush16 118b 00
\epush16 118c
/esmove 1193 00
\esmove 1194
:1186 68 2d 31 00 d4 00 00 11 80 d4 00 98 d4 00 00 00
?auto_err 1198
/lpush16 119b 00
\lpush16 119c
/deref16 11a0 00
\deref16 11a1
/epush16 11a3 00
\epush16 11a4
:1196 02 c3 00 00 d4 00 00 ff fc d4 00 00 d4 00 00 00
/ne16 11a8 00
\ne16 11a9
/dpop16 11ab 00
\dpop16 11ac
:11a6 0d d4 00 00 d4 00 00 9a 52 8a f1 ca 11 b7 c0 11
/epush16 11c5 00
:11b6 d4 c0 11 c4 62 73 65 61 72 63 68 2d 32 00 d4 00
\epush16 11c6
/esmove 11cd 00
\esmove 11ce
?auto_err 11d2
/epush16 11d5 00
:11c6 00 11 ba d4 00 98 d4 00 00 00 02 c3 00 00 d4 00
\epush16 11d6
/lstor16 11da 00
\lstor16 11db
/dpop16 11df 00
\dpop16 11e0
/epush16 11e2 00
\epush16 11e3
:11d6 00 00 0f d4 00 00 ff fe d4 00 00 d4 00 00 0f 20
/epush16 11e7 00
\epush16 11e8
/epush16 11ec 00
\epush16 11ed
/epush16 11f1 00
\epush16 11f2
:11e6 d4 00 00 00 02 d4 00 00 00 0a d4 00 00 10 ef d4
/laddr16 11f6 00
\laddr16 11f7
/Cbsearch 11fb 00
\Cbsearch 11fc
/esmove 11fe 00
\esmove 11ff
?auto_err 1203
:11f6 00 00 ff fe d4 00 00 d4 00 00 00 0a c3 00 00 d4
/dpush16 1206 00
\dpush16 1207
/epush16 1209 00
\epush16 120a
/ne16 120e 00
\ne16 120f
/dpop16 1211 00
\dpop16 1212
:1206 00 00 d4 00 00 00 00 d4 00 00 d4 00 00 9a 52 8a
:1216 f1 ca 12 1d c0 12 3a c0 12 2a 62 73 65 61 72 63
/epush16 122b 00
\epush16 122c
/esmove 1233 00
\esmove 1234
:1226 68 2d 33 00 d4 00 00 12 20 d4 00 98 d4 00 00 00
?auto_err 1238
/esmove 123b 00
\esmove 123c
?auto_err 1240
/escheck 1244 00
\escheck 1245
:1236 02 c3 00 00 d4 00 00 00 04 c3 00 00 e2 d4 00 00
=Cmain 124c
:1246 60 72 ab f0 bb d5 e2 9b 73 8b 73 87 ab 97 bb d4
/vpush16 1262 00
\vpush16 1263
:1256 01 17 d4 08 a0 d4 0f 8b d4 11 03 d4 00 00 00 96
/dpop16 1267 00
\dpop16 1268
/escheck 126b 00
\escheck 126c
:1266 d4 00 00 e2 d4 00 00 60 72 ab f0 bb d5
+00a2
+00b7
+00c7
+00cc
+00d9
+00f2
+0100
+0129
+0135
^0138 e8
v0139
+0143
+014f
+015a
+0166
+0195
+0198
+01a6
^01a9 98
v01aa
+01d8
+01db
+01e9
^01ec 98
v01ed
+0223
+0226
+0229
+0237
^023a 98
v023b
+0271
+0274
+0277
+0285
^0288 98
v0289
+0293
+029f
^02a2 e8
v02a3
+02ad
+02d7
+02ee
+0303
+0320
+0323
+0331
^0334 98
v0335
+0346
+034b
+0368
+038d
+0390
+039e
^03a1 98
v03a2
+03b3
+03c0
+03d5
+03f2
+03f5
+0403
^0406 98
v0407
+0411
+041e
^0421 e8
v0422
+0438
+044d
+0452
+0474
+0494
+049c
+04b1
+04b4
+04c3
^04c6 98
v04c7
+04dd
+04f2
+04ff
+0521
+0539
+0541
+055e
+0561
+0570
^0573 98
v0574
+057e
+058a
^058d e8
v058e
+05b9
+05bc
+05bf
+05cf
+05d4
+05f0
+05ff
+060f
+0624
+0627
+0635
^0638 98
v0639
+0645
+065a
+065d
+066b
^066e 98
v066f
+069a
+069d
+06a0
+06b0
+06b5
+06d1
+06e0
+06f0
+070d
+0710
+0713
+0721
^0724 98
v0725
+0731
+074e
+0751
+0754
+0762
^0765 98
v0766
+0770
+077c
^077f e8
v0780
+078a
+07a1
+07e0
+07fd
+0822
+0825
+0833
^0836 98
v0837
+086d
+0870
+0873
+0881
^0884 98
v0885
+08b2
+08be
^08c1 e8
v08c2
+08ed
+08f0
+08f3
+0903
+0908
+0941
+0944
+0947
+096b
+096e
+0971
+0981
+0986
+09b0
+09b3
+09ca
+09cd
+09d0
+09de
^09e1 98
v09e2
+0a0d
+0a10
+0a13
+0a23
+0a47
+0a4a
+0a4d
+0a5d
+0a62
+0a8d
+0a90
+0a93
+0a96
+0aad
+0ab0
+0ab3
+0ab6
+0acd
+0ad0
+0ad3
+0ae1
^0ae4 98
v0ae5
+0aef
+0af9
^0afc e8
v0afd
+0b28
+0b2b
+0b2e
+0b3e
+0b43
+0b5f
+0b62
+0b6e
^0b71 e8
v0b72
+0ba8
+0bab
+0bae
+0bbc
^0bbf 98
v0bc0
+0beb
+0bee
+0bf1
+0c01
+0c1b
+0c1e
+0c21
+0c38
+0c3b
+0c3e
+0c4c
^0c4f 98
v0c50
+0c6a
+0c77
^0c7a e8
v0c7b
+0cac
+0caf
+0cb2
+0cc0
^0cc3 98
v0cc4
+0cef
+0cf2
+0cf5
+0d05
+0d26
+0d55
+0d58
+0d5b
+0d6a
^0d6d 98
v0d6e
+0d99
+0d9c
+0d9f
+0daf
+0dd1
+0dd4
+0dd7
+0dda
+0df1
+0df4
+0df7
+0e06
^0e09 98
v0e0a
+0e40
+0e43
+0e46
+0e55
^0e58 98
v0e59
+0e84
+0e87
+0e8a
+0e9a
+0ebc
+0ebf
+0ec2
+0ec5
+0edc
+0edf
+0ee2
+0ef1
^0ef4 98
v0ef5
+0f44
+0f47
+0f4f
+0f6c
+0f6f
+0f77
+0f9d
+0fa8
^0fab e8
v0fac
+0fd7
+0fda
+0fdd
+0fed
+0ff2
+1019
+101e
+102d
+1061
+1064
+1067
+1077
+107c
+109c
+109f
+10a2
+10af
^10b2 98
v10b3
+10bd
+10c2
+10db
+1115
+1122
^1125 e8
v1126
+113f
+114e
+1178
+117b
+117e
+118d
^1190 98
v1191
+11b2
+11b5
+11b8
+11c7
^11ca 98
v11cb
+11e4
+11f3
+1218
+121b
+121e
+122d
^1230 98
v1231
^1256 17
v1257
^1259 a0
v125a
^125c 8b
v125d
^125f 03
v1260
+1264
}
