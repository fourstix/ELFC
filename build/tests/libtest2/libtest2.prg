.big
{libtest2
.library string.lib
.library ctype.lib
.requires Cctype
=CErrors 0000
=Calpha 0002
:0000 00 00
>0040
=Calnum 0042
>0040
=Cxnum 0082
>0040
=Cresult 00c2
=Cfail 00c4
:00c2 00 00 e2 9b 73 8b 73 87 ab 97 bb c0 00 db 25 73
/lpush16 00dc 00
\lpush16 00dd
/epush16 00e1 00
:00d2 20 66 61 69 6c 65 64 0a 00 d4 00 00 00 00 d4 00
\epush16 00e2
/Cprintf 00e6 00
\Cprintf 00e7
/esmove 00e9 00
\esmove 00ea
?auto_err 00ee
/vpush16 00f1 00
:00e2 00 00 d0 d4 00 00 d4 00 00 00 04 c3 00 00 d4 00
\vpush16 00f2
/vinc16 00f6 00
\vinc16 00f7
/dpop16 00fb 00
\dpop16 00fc
/epush16 00fe 00
\epush16 00ff
:00f2 00 00 00 d4 00 00 00 00 d4 00 00 d4 00 00 00 01
/vstor16 0103 00
\vstor16 0104
/dpop16 0108 00
\dpop16 0109
/escheck 010c 00
\escheck 010d
:0102 d4 00 00 00 c2 d4 00 00 e2 d4 00 00 60 72 ab f0
=Cpr 0114
:0112 bb d5 e2 9b 73 8b 73 87 ab 97 bb c0 01 24 25 73
/lpush16 0125 00
\lpush16 0126
/epush16 012a 00
\epush16 012b
/Cprintf 012f 00
\Cprintf 0130
:0122 0a 00 d4 00 00 00 00 d4 00 00 01 20 d4 00 00 d4
/esmove 0132 00
\esmove 0133
?auto_err 0137
/escheck 013b 00
\escheck 013c
:0132 00 00 00 04 c3 00 00 e2 d4 00 00 60 72 ab f0 bb
=Cxstrchr 0143
/epush16 014d 00
\epush16 014e
:0142 d5 e2 9b 73 8b 73 87 ab 97 bb d4 00 00 00 00 d4
/lpush16 0152 00
\lpush16 0153
/eq16 0157 00
\eq16 0158
/dpop16 015a 00
\dpop16 015b
:0152 00 00 00 02 d4 00 00 d4 00 00 9a 52 8a f1 ca 01
/epush16 0167 00
\epush16 0168
/dpop16 016c 00
\dpop16 016d
:0162 66 c0 01 71 d4 00 00 00 00 d4 00 00 c0 01 86 d4
/lpush16 0172 00
\lpush16 0173
/lpush16 0177 00
\lpush16 0178
/Cstrchr 017c 00
\Cstrchr 017d
/esmove 017f 00
\esmove 0180
:0172 00 00 00 02 d4 00 00 00 00 d4 00 00 d4 00 00 00
?auto_err 0184
/escheck 0188 00
\escheck 0189
=Ctest_chrfn 0190
:0182 04 c3 00 00 e2 d4 00 00 60 72 ab f0 bb d5 e2 9b
/esmove 019a 00
\esmove 019b
?auto_err 019f
:0192 73 8b 73 87 ab 97 bb d4 00 00 ff f0 c3 00 00 c0
/epush16 01ac 00
\epush16 01ad
:01a2 01 ab 73 74 72 63 68 72 00 d4 00 00 01 a4 d4 01
/esmove 01b4 00
\esmove 01b5
?auto_err 01b9
:01b2 14 d4 00 00 00 02 c3 00 00 c0 01 e0 2e 2e 2e 2e
:01c2 2e 2e 2e 2e 2e 2e 2e 2e 2e 2e 2e 58 31 2e 2e 2e
/epush16 01e1 00
:01d2 2e 2e 2e 2e 2e 2e 2e 2e 2e 2e 2e 58 32 00 d4 00
\epush16 01e2
/lstor16 01e6 00
\lstor16 01e7
/dpop16 01eb 00
\dpop16 01ec
/epush16 01ee 00
\epush16 01ef
:01e2 00 01 be d4 00 00 ff fe d4 00 00 d4 00 00 00 58
/lpush16 01f3 00
\lpush16 01f4
/Cstrchr 01f8 00
\Cstrchr 01f9
/esmove 01fb 00
\esmove 01fc
?auto_err 0200
:01f2 d4 00 00 ff fe d4 00 00 d4 00 00 00 04 c3 00 00
/dpush16 0203 00
\dpush16 0204
/lstor16 0206 00
\lstor16 0207
/dpop16 020b 00
\dpop16 020c
/lpush16 020e 00
\lpush16 020f
:0202 d4 00 00 d4 00 00 ff fc d4 00 00 d4 00 00 ff fc
/not16 0213 00
\not16 0214
/dget16 0216 00
\dget16 0217
/dpop16 0220 00
\dpop16 0221
:0212 d4 00 00 d4 00 00 9a 52 8a f1 ca 02 57 d4 00 00
/lpush16 0223 00
\lpush16 0224
/deref8 0228 00
\deref8 0229
/epush16 022b 00
\epush16 022c
/ne16 0230 00
\ne16 0231
:0222 d4 00 00 ff fc d4 00 00 d4 00 00 00 58 d4 00 00
/dget16 0233 00
\dget16 0234
/dpop16 023d 00
\dpop16 023e
/epush16 0240 00
\epush16 0241
:0232 d4 00 00 9a 52 8a f1 ca 02 57 d4 00 00 d4 00 00
/lpush16 0245 00
\lpush16 0246
/add16 024a 00
\add16 024b
/deref8 024d 00
\deref8 024e
/epush16 0250 00
\epush16 0251
:0242 00 01 d4 00 00 ff fc d4 00 00 d4 00 00 d4 00 00
/ne16 0255 00
\ne16 0256
/dpop16 0258 00
\dpop16 0259
:0252 00 31 d4 00 00 d4 00 00 9a 52 8a f1 c2 02 7d c0
/epush16 026e 00
\epush16 026f
:0262 02 6d 73 74 72 63 68 72 2d 31 00 d4 00 00 02 64
/esmove 0276 00
\esmove 0277
?auto_err 027b
/epush16 027e 00
\epush16 027f
:0272 d4 00 c4 d4 00 00 00 02 c3 00 00 d4 00 00 00 5a
/lpush16 0283 00
\lpush16 0284
/Cstrchr 0288 00
\Cstrchr 0289
/esmove 028b 00
\esmove 028c
?auto_err 0290
:0282 d4 00 00 ff fe d4 00 00 d4 00 00 00 04 c3 00 00
/dpush16 0293 00
\dpush16 0294
/dpop16 0296 00
\dpop16 0297
:0292 d4 00 00 d4 00 00 9a 52 8a f1 c2 02 bb c0 02 ab
/epush16 02ac 00
\epush16 02ad
:02a2 73 74 72 63 68 72 2d 32 00 d4 00 00 02 a2 d4 00
/esmove 02b4 00
\esmove 02b5
?auto_err 02b9
:02b2 c4 d4 00 00 00 02 c3 00 00 c0 02 c6 73 74 72 72
/epush16 02c7 00
\epush16 02c8
/esmove 02cf 00
\esmove 02d0
:02c2 63 68 72 00 d4 00 00 02 be d4 01 14 d4 00 00 00
?auto_err 02d4
/epush16 02d7 00
\epush16 02d8
/lpush16 02dc 00
\lpush16 02dd
/Cstrrchr 02e1 00
:02d2 02 c3 00 00 d4 00 00 00 58 d4 00 00 ff fe d4 00
\Cstrrchr 02e2
/esmove 02e4 00
\esmove 02e5
?auto_err 02e9
/dpush16 02ec 00
\dpush16 02ed
/lstor16 02ef 00
\lstor16 02f0
:02e2 00 d4 00 00 00 04 c3 00 00 d4 00 00 d4 00 00 ff
/dpop16 02f4 00
\dpop16 02f5
/lpush16 02f7 00
\lpush16 02f8
/not16 02fc 00
\not16 02fd
/dget16 02ff 00
\dget16 0300
:02f2 fc d4 00 00 d4 00 00 ff fc d4 00 00 d4 00 00 9a
/dpop16 0309 00
\dpop16 030a
/lpush16 030c 00
\lpush16 030d
/deref8 0311 00
:0302 52 8a f1 ca 03 40 d4 00 00 d4 00 00 ff fc d4 00
\deref8 0312
/epush16 0314 00
\epush16 0315
/ne16 0319 00
\ne16 031a
/dget16 031c 00
\dget16 031d
:0312 00 d4 00 00 00 58 d4 00 00 d4 00 00 9a 52 8a f1
/dpop16 0326 00
\dpop16 0327
/epush16 0329 00
\epush16 032a
/lpush16 032e 00
\lpush16 032f
:0322 ca 03 40 d4 00 00 d4 00 00 00 01 d4 00 00 ff fc
/add16 0333 00
\add16 0334
/deref8 0336 00
\deref8 0337
/epush16 0339 00
\epush16 033a
/ne16 033e 00
\ne16 033f
/dpop16 0341 00
:0332 d4 00 00 d4 00 00 d4 00 00 00 32 d4 00 00 d4 00
\dpop16 0342
:0342 00 9a 52 8a f1 c2 03 67 c0 03 57 73 74 72 72 63
/epush16 0358 00
\epush16 0359
/esmove 0360 00
\esmove 0361
:0352 68 72 2d 31 00 d4 00 00 03 4d d4 00 c4 d4 00 00
?auto_err 0365
/epush16 0368 00
\epush16 0369
/lpush16 036d 00
\lpush16 036e
:0362 00 02 c3 00 00 d4 00 00 00 5a d4 00 00 ff fe d4
/Cstrrchr 0372 00
\Cstrrchr 0373
/esmove 0375 00
\esmove 0376
?auto_err 037a
/dpush16 037d 00
\dpush16 037e
/dpop16 0380 00
\dpop16 0381
:0372 00 00 d4 00 00 00 04 c3 00 00 d4 00 00 d4 00 00
:0382 9a 52 8a f1 c2 03 a5 c0 03 95 73 74 72 63 68 72
/epush16 0396 00
\epush16 0397
/esmove 039e 00
\esmove 039f
:0392 2d 32 00 d4 00 00 03 8c d4 00 c4 d4 00 00 00 02
?auto_err 03a3
/epush16 03ad 00
\epush16 03ae
:03a2 c3 00 00 c0 03 ac 69 73 2a 00 d4 00 00 03 a8 d4
/esmove 03b5 00
\esmove 03b6
?auto_err 03ba
:03b2 01 14 d4 00 00 00 02 c3 00 00 c0 03 ca 30 31 32
/epush16 03cb 00
\epush16 03cc
/lstor16 03d0 00
\lstor16 03d1
:03c2 33 34 35 36 37 38 39 00 d4 00 00 03 bf d4 00 00
/dpop16 03d5 00
\dpop16 03d6
:03d2 ff f8 d4 00 00 c0 03 f5 61 62 63 64 65 66 67 68
:03e2 69 6a 6b 6c 6d 6e 6f 70 71 72 73 74 75 76 77 78
/epush16 03f6 00
\epush16 03f7
/lstor16 03fb 00
\lstor16 03fc
/dpop16 0400 00
\dpop16 0401
:03f2 79 7a 00 d4 00 00 03 da d4 00 00 ff f6 d4 00 00
:0402 c0 04 20 41 42 43 44 45 46 47 48 49 4a 4b 4c 4d
/epush16 0421 00
:0412 4e 4f 50 51 52 53 54 55 56 57 58 59 5a 00 d4 00
\epush16 0422
/lstor16 0426 00
\lstor16 0427
/dpop16 042b 00
\dpop16 042c
:0422 00 04 05 d4 00 00 ff f4 d4 00 00 c0 04 37 09 0b
/epush16 0438 00
\epush16 0439
/lstor16 043d 00
\lstor16 043e
:0432 0c 0a 0d 20 00 d4 00 00 04 30 d4 00 00 ff f2 d4
/dpop16 0442 00
\dpop16 0443
:0442 00 00 c0 04 68 21 22 23 24 25 26 27 28 29 2a 2b
:0452 2c 2d 2e 2f 3a 3b 3c 3d 3e 3f 40 5b 5c 5d 5e 5f
/epush16 0469 00
\epush16 046a
/lstor16 046e 00
\lstor16 046f
:0462 60 7b 7c 7d 7e 00 d4 00 00 04 47 d4 00 00 ff f0
/dpop16 0473 00
\dpop16 0474
/lpush16 0476 00
\lpush16 0477
/epush16 047b 00
\epush16 047c
/Cstrcpy 0480 00
\Cstrcpy 0481
:0472 d4 00 00 d4 00 00 ff f6 d4 00 00 00 02 d4 00 00
/esmove 0483 00
\esmove 0484
?auto_err 0488
/lpush16 048b 00
\lpush16 048c
/epush16 0490 00
\epush16 0491
:0482 d4 00 00 00 04 c3 00 00 d4 00 00 ff f4 d4 00 00
/Cstrcat 0495 00
\Cstrcat 0496
/esmove 0498 00
\esmove 0499
?auto_err 049d
/epush16 04a0 00
\epush16 04a1
:0492 00 02 d4 00 00 d4 00 00 00 04 c3 00 00 d4 00 00
/epush16 04a5 00
\epush16 04a6
/Cstrcpy 04aa 00
\Cstrcpy 04ab
/esmove 04ad 00
\esmove 04ae
:04a2 00 02 d4 00 00 00 42 d4 00 00 d4 00 00 00 04 c3
?auto_err 04b2
/lpush16 04b5 00
\lpush16 04b6
/epush16 04ba 00
\epush16 04bb
/Cstrcat 04bf 00
\Cstrcat 04c0
:04b2 00 00 d4 00 00 ff f8 d4 00 00 00 42 d4 00 00 d4
/esmove 04c2 00
\esmove 04c3
?auto_err 04c7
/lpush16 04ca 00
\lpush16 04cb
/epush16 04cf 00
\epush16 04d0
:04c2 00 00 00 04 c3 00 00 d4 00 00 ff f8 d4 00 00 00
/Cstrcpy 04d4 00
\Cstrcpy 04d5
/esmove 04d7 00
\esmove 04d8
?auto_err 04dc
:04d2 82 d4 00 00 d4 00 00 00 04 c3 00 00 c0 04 ee 61
/epush16 04ef 00
\epush16 04f0
:04e2 62 63 64 65 66 41 42 43 44 45 46 00 d4 00 00 04
/epush16 04f4 00
\epush16 04f5
/Cstrcat 04f9 00
\Cstrcat 04fa
/esmove 04fc 00
\esmove 04fd
?auto_err 0501
:04f2 e1 d4 00 00 00 82 d4 00 00 d4 00 00 00 04 c3 00
/epush16 0504 00
\epush16 0505
/lstor16 0509 00
\lstor16 050a
/dpop16 050e 00
\dpop16 050f
/lpush16 0511 00
:0502 00 d4 00 00 00 00 d4 00 00 ff fa d4 00 00 d4 00
\lpush16 0512
/epush16 0516 00
\epush16 0517
/lt16 051b 00
\lt16 051c
/dpop16 051e 00
\dpop16 051f
:0512 00 ff fa d4 00 00 00 80 d4 00 00 d4 00 00 9a 52
/lpush16 052e 00
\lpush16 052f
:0522 8a f1 ca 05 2a c0 0f eb c0 05 3d d4 00 00 ff fa
/linc16 0533 00
\linc16 0534
/dpop16 0538 00
\dpop16 0539
:0532 d4 00 00 ff fa d4 00 00 c0 05 10 c0 05 58 69 73
:0542 43 68 61 72 20 54 65 73 74 73 3a 20 63 68 61 72
/lpush16 0559 00
\lpush16 055a
/epush16 055e 00
\epush16 055f
:0552 28 25 64 29 0a 00 d4 00 00 ff fa d4 00 00 05 40
/Cprintf 0563 00
\Cprintf 0564
/esmove 0566 00
\esmove 0567
?auto_err 056b
/lpush16 056e 00
\lpush16 056f
:0562 d4 00 00 d4 00 00 00 04 c3 00 00 d4 00 00 ff fa
/Cisalnum 0573 00
\Cisalnum 0574
/esmove 0576 00
\esmove 0577
?auto_err 057b
/dpush16 057e 00
\dpush16 057f
/dget16 0581 00
:0572 d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00
\dget16 0582
/dpop16 058b 00
\dpop16 058c
/lpush16 058e 00
\lpush16 058f
:0582 00 9a 52 8a f1 c2 05 a8 d4 00 00 d4 00 00 ff fa
/epush16 0593 00
\epush16 0594
/Cstrchr 0598 00
\Cstrchr 0599
/esmove 059b 00
\esmove 059c
?auto_err 05a0
:0592 d4 00 00 00 42 d4 00 00 d4 00 00 00 04 c3 00 00
/dpush16 05a3 00
\dpush16 05a4
/not16 05a6 00
\not16 05a7
/dpop16 05a9 00
\dpop16 05aa
:05a2 d4 00 00 d4 00 00 d4 00 00 9a 52 8a f1 c2 05 cf
/epush16 05c0 00
\epush16 05c1
:05b2 c0 05 bf 69 73 61 6c 6e 75 6d 2d 31 00 d4 00 00
/esmove 05c8 00
\esmove 05c9
?auto_err 05cd
/lpush16 05d0 00
\lpush16 05d1
:05c2 05 b5 d4 00 c4 d4 00 00 00 02 c3 00 00 d4 00 00
/Cisalpha 05d5 00
\Cisalpha 05d6
/esmove 05d8 00
\esmove 05d9
?auto_err 05dd
/dpush16 05e0 00
\dpush16 05e1
:05d2 ff fa d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00
/dget16 05e3 00
\dget16 05e4
/dpop16 05ed 00
\dpop16 05ee
/lpush16 05f0 00
\lpush16 05f1
:05e2 d4 00 00 9a 52 8a f1 c2 06 0a d4 00 00 d4 00 00
/epush16 05f5 00
\epush16 05f6
/Cstrchr 05fa 00
\Cstrchr 05fb
/esmove 05fd 00
\esmove 05fe
:05f2 ff fa d4 00 00 00 02 d4 00 00 d4 00 00 00 04 c3
?auto_err 0602
/dpush16 0605 00
\dpush16 0606
/not16 0608 00
\not16 0609
/dpop16 060b 00
\dpop16 060c
:0602 00 00 d4 00 00 d4 00 00 d4 00 00 9a 52 8a f1 c2
:0612 06 31 c0 06 21 69 73 61 6c 70 68 61 2d 31 00 d4
/epush16 0622 00
\epush16 0623
/esmove 062a 00
\esmove 062b
?auto_err 062f
:0622 00 00 06 17 d4 00 c4 d4 00 00 00 02 c3 00 00 d4
/lpush16 0632 00
\lpush16 0633
/Ciscntrl 0637 00
\Ciscntrl 0638
/esmove 063a 00
\esmove 063b
?auto_err 063f
:0632 00 00 ff fa d4 00 00 d4 00 00 00 02 c3 00 00 d4
/dpush16 0642 00
\dpush16 0643
/dget16 0645 00
\dget16 0646
/dpop16 064f 00
\dpop16 0650
:0642 00 00 d4 00 00 9a 52 8a f1 c2 06 78 d4 00 00 d4
/lpush16 0652 00
\lpush16 0653
/epush16 0657 00
\epush16 0658
/gt16 065c 00
\gt16 065d
/dget16 065f 00
\dget16 0660
:0652 00 00 ff fa d4 00 00 00 1f d4 00 00 d4 00 00 9a
/dpop16 0669 00
\dpop16 066a
/lpush16 066c 00
\lpush16 066d
/epush16 0671 00
:0662 52 8a f1 c2 06 78 d4 00 00 d4 00 00 ff fa d4 00
\epush16 0672
/lt16 0676 00
\lt16 0677
/dpop16 0679 00
\dpop16 067a
:0672 00 00 7f d4 00 00 d4 00 00 9a 52 8a f1 c2 06 9f
/epush16 0690 00
\epush16 0691
:0682 c0 06 8f 69 73 63 72 6e 74 6c 2d 31 00 d4 00 00
/esmove 0698 00
\esmove 0699
?auto_err 069d
/lpush16 06a0 00
\lpush16 06a1
:0692 06 85 d4 00 c4 d4 00 00 00 02 c3 00 00 d4 00 00
/Cisdigit 06a5 00
\Cisdigit 06a6
/esmove 06a8 00
\esmove 06a9
?auto_err 06ad
/dpush16 06b0 00
\dpush16 06b1
:06a2 ff fa d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00
/dget16 06b3 00
\dget16 06b4
/dpop16 06bd 00
\dpop16 06be
/lpush16 06c0 00
\lpush16 06c1
:06b2 d4 00 00 9a 52 8a f1 c2 06 da d4 00 00 d4 00 00
/lpush16 06c5 00
\lpush16 06c6
/Cstrchr 06ca 00
\Cstrchr 06cb
/esmove 06cd 00
\esmove 06ce
:06c2 ff fa d4 00 00 ff f8 d4 00 00 d4 00 00 00 04 c3
?auto_err 06d2
/dpush16 06d5 00
\dpush16 06d6
/not16 06d8 00
\not16 06d9
/dpop16 06db 00
\dpop16 06dc
:06d2 00 00 d4 00 00 d4 00 00 d4 00 00 9a 52 8a f1 c2
:06e2 07 01 c0 06 f1 69 73 64 69 67 69 74 2d 31 00 d4
/epush16 06f2 00
\epush16 06f3
/esmove 06fa 00
\esmove 06fb
?auto_err 06ff
:06f2 00 00 06 e7 d4 00 c4 d4 00 00 00 02 c3 00 00 d4
/lpush16 0702 00
\lpush16 0703
/Cisgraph 0707 00
\Cisgraph 0708
/esmove 070a 00
\esmove 070b
?auto_err 070f
:0702 00 00 ff fa d4 00 00 d4 00 00 00 02 c3 00 00 d4
/dpush16 0712 00
\dpush16 0713
/dget16 0715 00
\dget16 0716
/dpop16 071f 00
\dpop16 0720
:0712 00 00 d4 00 00 9a 52 8a f1 c2 07 48 d4 00 00 d4
/lpush16 0722 00
\lpush16 0723
/epush16 0727 00
\epush16 0728
/lt16 072c 00
\lt16 072d
/dget16 072f 00
\dget16 0730
:0722 00 00 ff fa d4 00 00 00 21 d4 00 00 d4 00 00 9a
/dpop16 0739 00
\dpop16 073a
/lpush16 073c 00
\lpush16 073d
/epush16 0741 00
:0732 52 8a f1 c2 07 48 d4 00 00 d4 00 00 ff fa d4 00
\epush16 0742
/gt16 0746 00
\gt16 0747
/dpop16 0749 00
\dpop16 074a
:0742 00 00 7e d4 00 00 d4 00 00 9a 52 8a f1 c2 07 6f
/epush16 0760 00
\epush16 0761
:0752 c0 07 5f 69 73 67 72 61 70 68 2d 31 00 d4 00 00
/esmove 0768 00
\esmove 0769
?auto_err 076d
/lpush16 0770 00
\lpush16 0771
:0762 07 55 d4 00 c4 d4 00 00 00 02 c3 00 00 d4 00 00
/Cislower 0775 00
\Cislower 0776
/esmove 0778 00
\esmove 0779
?auto_err 077d
/dpush16 0780 00
\dpush16 0781
:0772 ff fa d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00
/dget16 0783 00
\dget16 0784
/dpop16 078d 00
\dpop16 078e
/lpush16 0790 00
\lpush16 0791
:0782 d4 00 00 9a 52 8a f1 c2 07 aa d4 00 00 d4 00 00
/lpush16 0795 00
\lpush16 0796
/Cstrchr 079a 00
\Cstrchr 079b
/esmove 079d 00
\esmove 079e
:0792 ff fa d4 00 00 ff f6 d4 00 00 d4 00 00 00 04 c3
?auto_err 07a2
/dpush16 07a5 00
\dpush16 07a6
/not16 07a8 00
\not16 07a9
/dpop16 07ab 00
\dpop16 07ac
:07a2 00 00 d4 00 00 d4 00 00 d4 00 00 9a 52 8a f1 c2
:07b2 07 d1 c0 07 c1 69 73 6c 6f 77 65 72 2d 31 00 d4
/epush16 07c2 00
\epush16 07c3
/esmove 07ca 00
\esmove 07cb
?auto_err 07cf
:07c2 00 00 07 b7 d4 00 c4 d4 00 00 00 02 c3 00 00 d4
/lpush16 07d2 00
\lpush16 07d3
/Cisprint 07d7 00
\Cisprint 07d8
/esmove 07da 00
\esmove 07db
?auto_err 07df
:07d2 00 00 ff fa d4 00 00 d4 00 00 00 02 c3 00 00 d4
/dpush16 07e2 00
\dpush16 07e3
/dget16 07e5 00
\dget16 07e6
/dpop16 07ef 00
\dpop16 07f0
:07e2 00 00 d4 00 00 9a 52 8a f1 c2 08 1b d4 00 00 d4
/lpush16 07f2 00
\lpush16 07f3
/epush16 07f7 00
\epush16 07f8
/lt16 07fc 00
\lt16 07fd
/dget16 07ff 00
\dget16 0800
:07f2 00 00 ff fa d4 00 00 00 20 d4 00 00 d4 00 00 9a
/dpop16 0809 00
\dpop16 080a
/lpush16 080c 00
\lpush16 080d
/epush16 0811 00
:0802 52 8a f1 ca 08 18 d4 00 00 d4 00 00 ff fa d4 00
\epush16 0812
/gt16 0816 00
\gt16 0817
/bool16 0819 00
\bool16 081a
/dpop16 081c 00
\dpop16 081d
:0812 00 00 7e d4 00 00 d4 00 00 d4 00 00 9a 52 8a f1
:0822 c2 08 42 c0 08 32 69 73 70 72 69 6e 74 2d 31 00
/epush16 0833 00
\epush16 0834
/esmove 083b 00
\esmove 083c
?auto_err 0840
:0832 d4 00 00 08 28 d4 00 c4 d4 00 00 00 02 c3 00 00
/lpush16 0843 00
\lpush16 0844
/Cispunct 0848 00
\Cispunct 0849
/esmove 084b 00
\esmove 084c
?auto_err 0850
:0842 d4 00 00 ff fa d4 00 00 d4 00 00 00 02 c3 00 00
/dpush16 0853 00
\dpush16 0854
/dget16 0856 00
\dget16 0857
/dpop16 0860 00
\dpop16 0861
:0852 d4 00 00 d4 00 00 9a 52 8a f1 c2 08 7d d4 00 00
/lpush16 0863 00
\lpush16 0864
/lpush16 0868 00
\lpush16 0869
/Cstrchr 086d 00
\Cstrchr 086e
/esmove 0870 00
\esmove 0871
:0862 d4 00 00 ff fa d4 00 00 ff f0 d4 00 00 d4 00 00
?auto_err 0875
/dpush16 0878 00
\dpush16 0879
/not16 087b 00
\not16 087c
/dpop16 087e 00
\dpop16 087f
:0872 00 04 c3 00 00 d4 00 00 d4 00 00 d4 00 00 9a 52
:0882 8a f1 c2 08 a4 c0 08 94 69 73 70 75 6e 63 74 2d
/epush16 0895 00
\epush16 0896
/esmove 089d 00
\esmove 089e
:0892 31 00 d4 00 00 08 8a d4 00 c4 d4 00 00 00 02 c3
?auto_err 08a2
/lpush16 08a5 00
\lpush16 08a6
/Cisspace 08aa 00
\Cisspace 08ab
/esmove 08ad 00
\esmove 08ae
:08a2 00 00 d4 00 00 ff fa d4 00 00 d4 00 00 00 02 c3
?auto_err 08b2
/dpush16 08b5 00
\dpush16 08b6
/dget16 08b8 00
\dget16 08b9
:08b2 00 00 d4 00 00 d4 00 00 9a 52 8a f1 c2 08 df d4
/dpop16 08c2 00
\dpop16 08c3
/lpush16 08c5 00
\lpush16 08c6
/lpush16 08ca 00
\lpush16 08cb
/Cstrchr 08cf 00
\Cstrchr 08d0
:08c2 00 00 d4 00 00 ff fa d4 00 00 ff f2 d4 00 00 d4
/esmove 08d2 00
\esmove 08d3
?auto_err 08d7
/dpush16 08da 00
\dpush16 08db
/not16 08dd 00
\not16 08de
/dpop16 08e0 00
\dpop16 08e1
:08d2 00 00 00 04 c3 00 00 d4 00 00 d4 00 00 d4 00 00
:08e2 9a 52 8a f1 c2 09 06 c0 08 f6 69 73 73 70 61 63
/epush16 08f7 00
\epush16 08f8
/esmove 08ff 00
\esmove 0900
:08f2 65 2d 31 00 d4 00 00 08 ec d4 00 c4 d4 00 00 00
?auto_err 0904
/lpush16 0907 00
\lpush16 0908
/Cisupper 090c 00
\Cisupper 090d
/esmove 090f 00
\esmove 0910
:0902 02 c3 00 00 d4 00 00 ff fa d4 00 00 d4 00 00 00
?auto_err 0914
/dpush16 0917 00
\dpush16 0918
/dget16 091a 00
\dget16 091b
:0912 02 c3 00 00 d4 00 00 d4 00 00 9a 52 8a f1 c2 09
/dpop16 0924 00
\dpop16 0925
/lpush16 0927 00
\lpush16 0928
/lpush16 092c 00
\lpush16 092d
/Cstrchr 0931 00
:0922 41 d4 00 00 d4 00 00 ff fa d4 00 00 ff f4 d4 00
\Cstrchr 0932
/esmove 0934 00
\esmove 0935
?auto_err 0939
/dpush16 093c 00
\dpush16 093d
/not16 093f 00
\not16 0940
:0932 00 d4 00 00 00 04 c3 00 00 d4 00 00 d4 00 00 d4
/dpop16 0942 00
\dpop16 0943
:0942 00 00 9a 52 8a f1 c2 09 68 c0 09 58 69 73 75 70
/epush16 0959 00
\epush16 095a
/esmove 0961 00
:0952 70 65 72 2d 31 00 d4 00 00 09 4e d4 00 c4 d4 00
\esmove 0962
?auto_err 0966
/lpush16 0969 00
\lpush16 096a
/Cisxdigit 096e 00
\Cisxdigit 096f
/esmove 0971 00
:0962 00 00 02 c3 00 00 d4 00 00 ff fa d4 00 00 d4 00
\esmove 0972
?auto_err 0976
/dpush16 0979 00
\dpush16 097a
/dget16 097c 00
\dget16 097d
:0972 00 00 02 c3 00 00 d4 00 00 d4 00 00 9a 52 8a f1
/dpop16 0986 00
\dpop16 0987
/lpush16 0989 00
\lpush16 098a
/epush16 098e 00
\epush16 098f
:0982 c2 09 a3 d4 00 00 d4 00 00 ff fa d4 00 00 00 82
/Cstrchr 0993 00
\Cstrchr 0994
/esmove 0996 00
\esmove 0997
?auto_err 099b
/dpush16 099e 00
\dpush16 099f
/not16 09a1 00
:0992 d4 00 00 d4 00 00 00 04 c3 00 00 d4 00 00 d4 00
\not16 09a2
/dpop16 09a4 00
\dpop16 09a5
:09a2 00 d4 00 00 9a 52 8a f1 c2 09 cb c0 09 bb 69 73
/epush16 09bc 00
\epush16 09bd
:09b2 78 64 69 67 69 74 2d 31 00 d4 00 00 09 b0 d4 00
/esmove 09c4 00
\esmove 09c5
?auto_err 09c9
/lpush16 09cc 00
\lpush16 09cd
/Cisalnum 09d1 00
:09c2 c4 d4 00 00 00 02 c3 00 00 d4 00 00 ff fa d4 00
\Cisalnum 09d2
/esmove 09d4 00
\esmove 09d5
?auto_err 09d9
/dpush16 09dc 00
\dpush16 09dd
/not16 09df 00
\not16 09e0
:09d2 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00 00 d4
/dget16 09e2 00
\dget16 09e3
/dpop16 09ec 00
\dpop16 09ed
/lpush16 09ef 00
\lpush16 09f0
:09e2 00 00 9a 52 8a f1 c2 0a 06 d4 00 00 d4 00 00 ff
/epush16 09f4 00
\epush16 09f5
/esmove 09fc 00
\esmove 09fd
?auto_err 0a01
:09f2 fa d4 00 00 00 42 d4 01 43 d4 00 00 00 04 c3 00
/dpush16 0a04 00
\dpush16 0a05
/dpop16 0a07 00
\dpop16 0a08
:0a02 00 d4 00 00 d4 00 00 9a 52 8a f1 c2 0a 2d c0 0a
/epush16 0a1e 00
\epush16 0a1f
:0a12 1d 69 73 61 6c 6e 75 6d 2d 32 00 d4 00 00 0a 13
/esmove 0a26 00
\esmove 0a27
?auto_err 0a2b
/lpush16 0a2e 00
\lpush16 0a2f
:0a22 d4 00 c4 d4 00 00 00 02 c3 00 00 d4 00 00 ff fa
/Cisalpha 0a33 00
\Cisalpha 0a34
/esmove 0a36 00
\esmove 0a37
?auto_err 0a3b
/dpush16 0a3e 00
\dpush16 0a3f
/not16 0a41 00
:0a32 d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00
\not16 0a42
/dget16 0a44 00
\dget16 0a45
/dpop16 0a4e 00
\dpop16 0a4f
/lpush16 0a51 00
:0a42 00 d4 00 00 9a 52 8a f1 c2 0a 68 d4 00 00 d4 00
\lpush16 0a52
/epush16 0a56 00
\epush16 0a57
/esmove 0a5e 00
\esmove 0a5f
:0a52 00 ff fa d4 00 00 00 02 d4 01 43 d4 00 00 00 04
?auto_err 0a63
/dpush16 0a66 00
\dpush16 0a67
/dpop16 0a69 00
\dpop16 0a6a
:0a62 c3 00 00 d4 00 00 d4 00 00 9a 52 8a f1 c2 0a 8f
/epush16 0a80 00
\epush16 0a81
:0a72 c0 0a 7f 69 73 61 6c 70 68 61 2d 32 00 d4 00 00
/esmove 0a88 00
\esmove 0a89
?auto_err 0a8d
/lpush16 0a90 00
\lpush16 0a91
:0a82 0a 75 d4 00 c4 d4 00 00 00 02 c3 00 00 d4 00 00
/Ciscntrl 0a95 00
\Ciscntrl 0a96
/esmove 0a98 00
\esmove 0a99
?auto_err 0a9d
/dpush16 0aa0 00
\dpush16 0aa1
:0a92 ff fa d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00
/not16 0aa3 00
\not16 0aa4
/dget16 0aa6 00
\dget16 0aa7
/dpop16 0ab0 00
\dpop16 0ab1
:0aa2 d4 00 00 d4 00 00 9a 52 8a f1 c2 0a dc d4 00 00
/lpush16 0ab3 00
\lpush16 0ab4
/epush16 0ab8 00
\epush16 0ab9
/lt16 0abd 00
\lt16 0abe
/dget16 0ac0 00
\dget16 0ac1
:0ab2 d4 00 00 ff fa d4 00 00 00 20 d4 00 00 d4 00 00
/dpop16 0aca 00
\dpop16 0acb
/lpush16 0acd 00
\lpush16 0ace
:0ac2 9a 52 8a f1 ca 0a d9 d4 00 00 d4 00 00 ff fa d4
/epush16 0ad2 00
\epush16 0ad3
/gt16 0ad7 00
\gt16 0ad8
/bool16 0ada 00
\bool16 0adb
/dpop16 0add 00
\dpop16 0ade
:0ad2 00 00 00 7e d4 00 00 d4 00 00 d4 00 00 9a 52 8a
:0ae2 f1 c2 0b 03 c0 0a f3 69 73 63 72 6e 74 6c 2d 32
/epush16 0af4 00
\epush16 0af5
/esmove 0afc 00
\esmove 0afd
?auto_err 0b01
:0af2 00 d4 00 00 0a e9 d4 00 c4 d4 00 00 00 02 c3 00
/lpush16 0b04 00
\lpush16 0b05
/Cisdigit 0b09 00
\Cisdigit 0b0a
/esmove 0b0c 00
\esmove 0b0d
?auto_err 0b11
:0b02 00 d4 00 00 ff fa d4 00 00 d4 00 00 00 02 c3 00
/dpush16 0b14 00
\dpush16 0b15
/not16 0b17 00
\not16 0b18
/dget16 0b1a 00
\dget16 0b1b
:0b12 00 d4 00 00 d4 00 00 d4 00 00 9a 52 8a f1 c2 0b
/dpop16 0b24 00
\dpop16 0b25
/lpush16 0b27 00
\lpush16 0b28
/lpush16 0b2c 00
\lpush16 0b2d
:0b22 3e d4 00 00 d4 00 00 ff fa d4 00 00 ff f8 d4 01
/esmove 0b34 00
\esmove 0b35
?auto_err 0b39
/dpush16 0b3c 00
\dpush16 0b3d
/dpop16 0b3f 00
\dpop16 0b40
:0b32 43 d4 00 00 00 04 c3 00 00 d4 00 00 d4 00 00 9a
:0b42 52 8a f1 c2 0b 65 c0 0b 55 69 73 64 69 67 69 74
/epush16 0b56 00
\epush16 0b57
/esmove 0b5e 00
\esmove 0b5f
:0b52 2d 32 00 d4 00 00 0b 4b d4 00 c4 d4 00 00 00 02
?auto_err 0b63
/lpush16 0b66 00
\lpush16 0b67
/Cisgraph 0b6b 00
\Cisgraph 0b6c
/esmove 0b6e 00
\esmove 0b6f
:0b62 c3 00 00 d4 00 00 ff fa d4 00 00 d4 00 00 00 02
?auto_err 0b73
/dpush16 0b76 00
\dpush16 0b77
/not16 0b79 00
\not16 0b7a
/dget16 0b7c 00
\dget16 0b7d
:0b72 c3 00 00 d4 00 00 d4 00 00 d4 00 00 9a 52 8a f1
/dpop16 0b86 00
\dpop16 0b87
/lpush16 0b89 00
\lpush16 0b8a
/epush16 0b8e 00
\epush16 0b8f
:0b82 c2 0b af d4 00 00 d4 00 00 ff fa d4 00 00 00 20
/gt16 0b93 00
\gt16 0b94
/dget16 0b96 00
\dget16 0b97
/dpop16 0ba0 00
\dpop16 0ba1
:0b92 d4 00 00 d4 00 00 9a 52 8a f1 c2 0b af d4 00 00
/lpush16 0ba3 00
\lpush16 0ba4
/epush16 0ba8 00
\epush16 0ba9
/lt16 0bad 00
\lt16 0bae
/dpop16 0bb0 00
\dpop16 0bb1
:0ba2 d4 00 00 ff fa d4 00 00 00 7f d4 00 00 d4 00 00
:0bb2 9a 52 8a f1 c2 0b d6 c0 0b c6 69 73 67 72 61 70
/epush16 0bc7 00
\epush16 0bc8
/esmove 0bcf 00
\esmove 0bd0
:0bc2 68 2d 32 00 d4 00 00 0b bc d4 00 c4 d4 00 00 00
?auto_err 0bd4
/lpush16 0bd7 00
\lpush16 0bd8
/Cislower 0bdc 00
\Cislower 0bdd
/esmove 0bdf 00
\esmove 0be0
:0bd2 02 c3 00 00 d4 00 00 ff fa d4 00 00 d4 00 00 00
?auto_err 0be4
/dpush16 0be7 00
\dpush16 0be8
/not16 0bea 00
\not16 0beb
/dget16 0bed 00
\dget16 0bee
:0be2 02 c3 00 00 d4 00 00 d4 00 00 d4 00 00 9a 52 8a
/dpop16 0bf7 00
\dpop16 0bf8
/lpush16 0bfa 00
\lpush16 0bfb
/lpush16 0bff 00
\lpush16 0c00
:0bf2 f1 c2 0c 11 d4 00 00 d4 00 00 ff fa d4 00 00 ff
/esmove 0c07 00
\esmove 0c08
?auto_err 0c0c
/dpush16 0c0f 00
\dpush16 0c10
:0c02 f6 d4 01 43 d4 00 00 00 04 c3 00 00 d4 00 00 d4
/dpop16 0c12 00
\dpop16 0c13
:0c12 00 00 9a 52 8a f1 c2 0c 38 c0 0c 28 69 73 6c 6f
/epush16 0c29 00
\epush16 0c2a
/esmove 0c31 00
:0c22 77 65 72 2d 32 00 d4 00 00 0c 1e d4 00 c4 d4 00
\esmove 0c32
?auto_err 0c36
/lpush16 0c39 00
\lpush16 0c3a
/Cisprint 0c3e 00
\Cisprint 0c3f
/esmove 0c41 00
:0c32 00 00 02 c3 00 00 d4 00 00 ff fa d4 00 00 d4 00
\esmove 0c42
?auto_err 0c46
/dpush16 0c49 00
\dpush16 0c4a
/not16 0c4c 00
\not16 0c4d
/dget16 0c4f 00
\dget16 0c50
:0c42 00 00 02 c3 00 00 d4 00 00 d4 00 00 d4 00 00 9a
/dpop16 0c59 00
\dpop16 0c5a
/lpush16 0c5c 00
\lpush16 0c5d
/epush16 0c61 00
:0c52 52 8a f1 c2 0c 82 d4 00 00 d4 00 00 ff fa d4 00
\epush16 0c62
/gt16 0c66 00
\gt16 0c67
/dget16 0c69 00
\dget16 0c6a
:0c62 00 00 1f d4 00 00 d4 00 00 9a 52 8a f1 c2 0c 82
/dpop16 0c73 00
\dpop16 0c74
/lpush16 0c76 00
\lpush16 0c77
/epush16 0c7b 00
\epush16 0c7c
/lt16 0c80 00
\lt16 0c81
:0c72 d4 00 00 d4 00 00 ff fa d4 00 00 00 7f d4 00 00
/dpop16 0c83 00
\dpop16 0c84
:0c82 d4 00 00 9a 52 8a f1 c2 0c a9 c0 0c 99 69 73 70
/epush16 0c9a 00
\epush16 0c9b
:0c92 72 69 6e 74 2d 32 00 d4 00 00 0c 8f d4 00 c4 d4
/esmove 0ca2 00
\esmove 0ca3
?auto_err 0ca7
/lpush16 0caa 00
\lpush16 0cab
/Cispunct 0caf 00
\Cispunct 0cb0
:0ca2 00 00 00 02 c3 00 00 d4 00 00 ff fa d4 00 00 d4
/esmove 0cb2 00
\esmove 0cb3
?auto_err 0cb7
/dpush16 0cba 00
\dpush16 0cbb
/not16 0cbd 00
\not16 0cbe
/dget16 0cc0 00
\dget16 0cc1
:0cb2 00 00 00 02 c3 00 00 d4 00 00 d4 00 00 d4 00 00
/dpop16 0cca 00
\dpop16 0ccb
/lpush16 0ccd 00
\lpush16 0cce
:0cc2 9a 52 8a f1 c2 0c e4 d4 00 00 d4 00 00 ff fa d4
/lpush16 0cd2 00
\lpush16 0cd3
/esmove 0cda 00
\esmove 0cdb
?auto_err 0cdf
:0cd2 00 00 ff f0 d4 01 43 d4 00 00 00 04 c3 00 00 d4
/dpush16 0ce2 00
\dpush16 0ce3
/dpop16 0ce5 00
\dpop16 0ce6
:0ce2 00 00 d4 00 00 9a 52 8a f1 c2 0d 0b c0 0c fb 69
/epush16 0cfc 00
\epush16 0cfd
:0cf2 73 70 75 6e 63 74 2d 32 00 d4 00 00 0c f1 d4 00
/esmove 0d04 00
\esmove 0d05
?auto_err 0d09
/lpush16 0d0c 00
\lpush16 0d0d
/Cisspace 0d11 00
:0d02 c4 d4 00 00 00 02 c3 00 00 d4 00 00 ff fa d4 00
\Cisspace 0d12
/esmove 0d14 00
\esmove 0d15
?auto_err 0d19
/dpush16 0d1c 00
\dpush16 0d1d
/not16 0d1f 00
\not16 0d20
:0d12 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00 00 d4
/dget16 0d22 00
\dget16 0d23
/dpop16 0d2c 00
\dpop16 0d2d
/lpush16 0d2f 00
\lpush16 0d30
:0d22 00 00 9a 52 8a f1 c2 0d 46 d4 00 00 d4 00 00 ff
/lpush16 0d34 00
\lpush16 0d35
/esmove 0d3c 00
\esmove 0d3d
?auto_err 0d41
:0d32 fa d4 00 00 ff f2 d4 01 43 d4 00 00 00 04 c3 00
/dpush16 0d44 00
\dpush16 0d45
/dpop16 0d47 00
\dpop16 0d48
:0d42 00 d4 00 00 d4 00 00 9a 52 8a f1 c2 0d 6d c0 0d
/epush16 0d5e 00
\epush16 0d5f
:0d52 5d 69 73 73 70 61 63 65 2d 32 00 d4 00 00 0d 53
/esmove 0d66 00
\esmove 0d67
?auto_err 0d6b
/lpush16 0d6e 00
\lpush16 0d6f
:0d62 d4 00 c4 d4 00 00 00 02 c3 00 00 d4 00 00 ff fa
/Cisupper 0d73 00
\Cisupper 0d74
/esmove 0d76 00
\esmove 0d77
?auto_err 0d7b
/dpush16 0d7e 00
\dpush16 0d7f
/not16 0d81 00
:0d72 d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00
\not16 0d82
/dget16 0d84 00
\dget16 0d85
/dpop16 0d8e 00
\dpop16 0d8f
/lpush16 0d91 00
:0d82 00 d4 00 00 9a 52 8a f1 c2 0d a8 d4 00 00 d4 00
\lpush16 0d92
/lpush16 0d96 00
\lpush16 0d97
/esmove 0d9e 00
\esmove 0d9f
:0d92 00 ff fa d4 00 00 ff f4 d4 01 43 d4 00 00 00 04
?auto_err 0da3
/dpush16 0da6 00
\dpush16 0da7
/dpop16 0da9 00
\dpop16 0daa
:0da2 c3 00 00 d4 00 00 d4 00 00 9a 52 8a f1 c2 0d cf
/epush16 0dc0 00
\epush16 0dc1
:0db2 c0 0d bf 69 73 75 70 70 65 72 2d 32 00 d4 00 00
/esmove 0dc8 00
\esmove 0dc9
?auto_err 0dcd
/lpush16 0dd0 00
\lpush16 0dd1
:0dc2 0d b5 d4 00 c4 d4 00 00 00 02 c3 00 00 d4 00 00
/Cisxdigit 0dd5 00
\Cisxdigit 0dd6
/esmove 0dd8 00
\esmove 0dd9
?auto_err 0ddd
/dpush16 0de0 00
\dpush16 0de1
:0dd2 ff fa d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00
/not16 0de3 00
\not16 0de4
/dget16 0de6 00
\dget16 0de7
/dpop16 0df0 00
\dpop16 0df1
:0de2 d4 00 00 d4 00 00 9a 52 8a f1 c2 0e 0a d4 00 00
/lpush16 0df3 00
\lpush16 0df4
/epush16 0df8 00
\epush16 0df9
/esmove 0e00 00
\esmove 0e01
:0df2 d4 00 00 ff fa d4 00 00 00 82 d4 01 43 d4 00 00
?auto_err 0e05
/dpush16 0e08 00
\dpush16 0e09
/dpop16 0e0b 00
\dpop16 0e0c
:0e02 00 04 c3 00 00 d4 00 00 d4 00 00 9a 52 8a f1 c2
:0e12 0e 32 c0 0e 22 69 73 78 64 69 67 69 74 2d 32 00
/epush16 0e23 00
\epush16 0e24
/esmove 0e2b 00
\esmove 0e2c
?auto_err 0e30
:0e22 d4 00 00 0e 17 d4 00 c4 d4 00 00 00 02 c3 00 00
/lpush16 0e33 00
\lpush16 0e34
/Cisupper 0e38 00
\Cisupper 0e39
/esmove 0e3b 00
\esmove 0e3c
?auto_err 0e40
:0e32 d4 00 00 ff fa d4 00 00 d4 00 00 00 02 c3 00 00
/dpush16 0e43 00
\dpush16 0e44
/dget16 0e46 00
\dget16 0e47
/dpop16 0e50 00
\dpop16 0e51
:0e42 d4 00 00 d4 00 00 9a 52 8a f1 c2 0e 76 d4 00 00
/lpush16 0e53 00
\lpush16 0e54
/Ctolower 0e58 00
\Ctolower 0e59
/esmove 0e5b 00
\esmove 0e5c
?auto_err 0e60
:0e52 d4 00 00 ff fa d4 00 00 d4 00 00 00 02 c3 00 00
/dpush16 0e63 00
\dpush16 0e64
/Cislower 0e66 00
\Cislower 0e67
/esmove 0e69 00
\esmove 0e6a
?auto_err 0e6e
/dpush16 0e71 00
:0e62 d4 00 00 d4 00 00 d4 00 00 00 02 c3 00 00 d4 00
\dpush16 0e72
/not16 0e74 00
\not16 0e75
/dpop16 0e77 00
\dpop16 0e78
:0e72 00 d4 00 00 d4 00 00 9a 52 8a f1 c2 0e 9d c0 0e
/epush16 0e8e 00
\epush16 0e8f
:0e82 8d 74 6f 6c 6f 77 65 72 2d 31 00 d4 00 00 0e 83
/esmove 0e96 00
\esmove 0e97
?auto_err 0e9b
/lpush16 0e9e 00
\lpush16 0e9f
:0e92 d4 00 c4 d4 00 00 00 02 c3 00 00 d4 00 00 ff fa
/Cislower 0ea3 00
\Cislower 0ea4
/esmove 0ea6 00
\esmove 0ea7
?auto_err 0eab
/dpush16 0eae 00
\dpush16 0eaf
/dget16 0eb1 00
:0ea2 d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00
\dget16 0eb2
/dpop16 0ebb 00
\dpop16 0ebc
/lpush16 0ebe 00
\lpush16 0ebf
:0eb2 00 9a 52 8a f1 c2 0e e6 d4 00 00 d4 00 00 ff fa
/Ctoupper 0ec3 00
\Ctoupper 0ec4
/esmove 0ec6 00
\esmove 0ec7
?auto_err 0ecb
/dpush16 0ece 00
\dpush16 0ecf
/Ctolower 0ed1 00
:0ec2 d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00
\Ctolower 0ed2
/esmove 0ed4 00
\esmove 0ed5
?auto_err 0ed9
/lpush16 0edc 00
\lpush16 0edd
/dpush16 0ee1 00
:0ed2 00 d4 00 00 00 02 c3 00 00 d4 00 00 ff fa d4 00
\dpush16 0ee2
/ne16 0ee4 00
\ne16 0ee5
/dpop16 0ee7 00
\dpop16 0ee8
:0ee2 00 d4 00 00 d4 00 00 9a 52 8a f1 c2 0f 0d c0 0e
/epush16 0efe 00
\epush16 0eff
:0ef2 fd 74 6f 6c 6f 77 65 72 2d 32 00 d4 00 00 0e f3
/esmove 0f06 00
\esmove 0f07
?auto_err 0f0b
/lpush16 0f0e 00
\lpush16 0f0f
:0f02 d4 00 c4 d4 00 00 00 02 c3 00 00 d4 00 00 ff fa
/Cislower 0f13 00
\Cislower 0f14
/esmove 0f16 00
\esmove 0f17
?auto_err 0f1b
/dpush16 0f1e 00
\dpush16 0f1f
/dget16 0f21 00
:0f12 d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00
\dget16 0f22
/dpop16 0f2b 00
\dpop16 0f2c
/lpush16 0f2e 00
\lpush16 0f2f
:0f22 00 9a 52 8a f1 c2 0f 51 d4 00 00 d4 00 00 ff fa
/Ctoupper 0f33 00
\Ctoupper 0f34
/esmove 0f36 00
\esmove 0f37
?auto_err 0f3b
/dpush16 0f3e 00
\dpush16 0f3f
/Cisupper 0f41 00
:0f32 d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00
\Cisupper 0f42
/esmove 0f44 00
\esmove 0f45
?auto_err 0f49
/dpush16 0f4c 00
\dpush16 0f4d
/not16 0f4f 00
\not16 0f50
:0f42 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00 00 d4
/dpop16 0f52 00
\dpop16 0f53
:0f52 00 00 9a 52 8a f1 c2 0f 78 c0 0f 68 74 6f 75 70
/epush16 0f69 00
\epush16 0f6a
/esmove 0f71 00
:0f62 70 65 72 2d 31 00 d4 00 00 0f 5e d4 00 c4 d4 00
\esmove 0f72
?auto_err 0f76
/lpush16 0f79 00
\lpush16 0f7a
/Cisupper 0f7e 00
\Cisupper 0f7f
/esmove 0f81 00
:0f72 00 00 02 c3 00 00 d4 00 00 ff fa d4 00 00 d4 00
\esmove 0f82
?auto_err 0f86
/dpush16 0f89 00
\dpush16 0f8a
/dget16 0f8c 00
\dget16 0f8d
:0f82 00 00 02 c3 00 00 d4 00 00 d4 00 00 9a 52 8a f1
/dpop16 0f96 00
\dpop16 0f97
/lpush16 0f99 00
\lpush16 0f9a
/Ctolower 0f9e 00
\Ctolower 0f9f
/esmove 0fa1 00
:0f92 c2 0f c1 d4 00 00 d4 00 00 ff fa d4 00 00 d4 00
\esmove 0fa2
?auto_err 0fa6
/dpush16 0fa9 00
\dpush16 0faa
/Ctoupper 0fac 00
\Ctoupper 0fad
/esmove 0faf 00
\esmove 0fb0
:0fa2 00 00 02 c3 00 00 d4 00 00 d4 00 00 d4 00 00 00
?auto_err 0fb4
/lpush16 0fb7 00
\lpush16 0fb8
/dpush16 0fbc 00
\dpush16 0fbd
/ne16 0fbf 00
\ne16 0fc0
:0fb2 02 c3 00 00 d4 00 00 ff fa d4 00 00 d4 00 00 d4
/dpop16 0fc2 00
\dpop16 0fc3
:0fc2 00 00 9a 52 8a f1 c2 0f e8 c0 0f d8 74 6f 75 70
/epush16 0fd9 00
\epush16 0fda
/esmove 0fe1 00
:0fd2 70 65 72 2d 32 00 d4 00 00 0f ce d4 00 c4 d4 00
\esmove 0fe2
?auto_err 0fe6
/esmove 0fec 00
\esmove 0fed
?auto_err 0ff1
:0fe2 00 00 02 c3 00 00 c0 05 2d d4 00 00 00 10 c3 00
/escheck 0ff5 00
\escheck 0ff6
=Cmain 0ffd
:0ff2 00 e2 d4 00 00 60 72 ab f0 bb d5 e2 9b 73 8b 73
/vpush16 100a 00
\vpush16 100b
/dpop16 100f 00
\dpop16 1010
:1002 87 ab 97 bb d4 01 90 d4 00 00 00 c2 d4 00 00 e2
/escheck 1013 00
\escheck 1014
:1012 d4 00 00 60 72 ab f0 bb d5
+00ce
+00e3
+00f3
+00f8
+0105
+011e
+012c
+0161
+0164
+016f
+01a2
+01ae
^01b1 14
v01b2
+01bc
+01e3
+021d
+023a
+025f
+0262
+0270
^0273 c4
v0274
+029d
+02a0
+02ae
^02b1 c4
v02b2
+02bc
+02c9
^02cc 14
v02cd
+0306
+0323
+0348
+034b
+035a
^035d c4
v035e
+0387
+038a
+0398
^039b c4
v039c
+03a6
+03af
^03b2 14
v03b3
+03bd
+03cd
+03d8
+03f8
+0403
+0423
+042e
+043a
+0445
+046b
+047d
+0492
+04a2
+04a7
+04bc
+04d1
+04df
+04f1
+04f6
+0525
+0528
+052b
+053b
+053e
+0560
+0588
+0595
+05b0
+05b3
+05c2
^05c5 c4
v05c6
+05ea
+05f7
+0612
+0615
+0624
^0627 c4
v0628
+064c
+0666
+0680
+0683
+0692
^0695 c4
v0696
+06ba
+06e2
+06e5
+06f4
^06f7 c4
v06f8
+071c
+0736
+0750
+0753
+0762
^0765 c4
v0766
+078a
+07b2
+07b5
+07c4
^07c7 c4
v07c8
+07ec
+0806
+0823
+0826
+0835
^0838 c4
v0839
+085d
+0885
+0888
+0897
^089a c4
v089b
+08bf
+08e7
+08ea
+08f9
^08fc c4
v08fd
+0921
+0949
+094c
+095b
^095e c4
v095f
+0983
+0990
+09ab
+09ae
+09be
^09c1 c4
v09c2
+09e9
+09f6
^09f9 43
v09fa
+0a0e
+0a11
+0a20
^0a23 c4
v0a24
+0a4b
+0a58
^0a5b 43
v0a5c
+0a70
+0a73
+0a82
^0a85 c4
v0a86
+0aad
+0ac7
+0ae4
+0ae7
+0af6
^0af9 c4
v0afa
+0b21
^0b31 43
v0b32
+0b46
+0b49
+0b58
^0b5b c4
v0b5c
+0b83
+0b9d
+0bb7
+0bba
+0bc9
^0bcc c4
v0bcd
+0bf4
^0c04 43
v0c05
+0c19
+0c1c
+0c2b
^0c2e c4
v0c2f
+0c56
+0c70
+0c8a
+0c8d
+0c9c
^0c9f c4
v0ca0
+0cc7
^0cd7 43
v0cd8
+0cec
+0cef
+0cfe
^0d01 c4
v0d02
+0d29
^0d39 43
v0d3a
+0d4e
+0d51
+0d60
^0d63 c4
v0d64
+0d8b
^0d9b 43
v0d9c
+0db0
+0db3
+0dc2
^0dc5 c4
v0dc6
+0ded
+0dfa
^0dfd 43
v0dfe
+0e12
+0e15
+0e25
^0e28 c4
v0e29
+0e4d
+0e7e
+0e81
+0e90
^0e93 c4
v0e94
+0eb8
+0eee
+0ef1
+0f00
^0f03 c4
v0f04
+0f28
+0f59
+0f5c
+0f6b
^0f6e c4
v0f6f
+0f93
+0fc9
+0fcc
+0fdb
^0fde c4
v0fdf
+0fe9
^1007 90
v1008
+100c
}
