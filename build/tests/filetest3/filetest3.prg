.big
{filetest3
.library string.lib
=CErrors 0000
=Cresult 0002
=Cs1 0004
:0000 00 00 00 00
>0050
=Cs2 0054
>0050
=Cfail 00a4
:00a4 e2 9b 73 8b 73 87 ab 97 bb c0 00 bb 25 73 20 66
/lpush16 00bc 00
\lpush16 00bd
/epush16 00c1 00
\epush16 00c2
:00b4 61 69 6c 65 64 0a 00 d4 00 00 00 00 d4 00 00 00
/Cprintf 00c6 00
\Cprintf 00c7
/esmove 00c9 00
\esmove 00ca
?auto_err 00ce
/vpush16 00d1 00
\vpush16 00d2
:00c4 b0 d4 00 00 d4 00 00 00 04 c3 00 00 d4 00 00 00
/vinc16 00d6 00
\vinc16 00d7
/dpop16 00db 00
\dpop16 00dc
/epush16 00de 00
\epush16 00df
/vstor16 00e3 00
:00d4 00 d4 00 00 00 00 d4 00 00 d4 00 00 00 01 d4 00
\vstor16 00e4
/dpop16 00e8 00
\dpop16 00e9
/escheck 00ec 00
\escheck 00ed
:00e4 00 00 02 d4 00 00 e2 d4 00 00 60 72 ab f0 bb d5
=Cpr 00f4
:00f4 e2 9b 73 8b 73 87 ab 97 bb c0 01 04 25 73 0a 00
/lpush16 0105 00
\lpush16 0106
/epush16 010a 00
\epush16 010b
/Cprintf 010f 00
\Cprintf 0110
/esmove 0112 00
\esmove 0113
:0104 d4 00 00 00 00 d4 00 00 01 00 d4 00 00 d4 00 00
?auto_err 0117
/escheck 011b 00
\escheck 011c
:0114 00 04 c3 00 00 e2 d4 00 00 60 72 ab f0 bb d5
>0100
=Ctest_sio3 0223
/esmove 022d 00
\esmove 022e
?auto_err 0232
:0223 e2 9b 73 8b 73 87 ab 97 bb d4 00 00 ff fa c3 00
:0233 00 c0 02 42 66 74 65 73 74 35 2e 74 6d 70 00 c0
/epush16 0249 00
\epush16 024a
/epush16 024e 00
\epush16 024f
:0243 02 48 77 2b 00 d4 00 00 02 45 d4 00 00 02 37 d4
/Cfopen 0253 00
\Cfopen 0254
/esmove 0256 00
\esmove 0257
?auto_err 025b
/dpush16 025e 00
\dpush16 025f
/lstor16 0261 00
\lstor16 0262
:0253 00 00 d4 00 00 00 04 c3 00 00 d4 00 00 d4 00 00
/epush16 0266 00
\epush16 0267
/eq16 026b 00
\eq16 026c
/dpop16 026e 00
\dpop16 026f
:0263 ff fe d4 00 00 00 00 d4 00 00 d4 00 00 9a 52 8a
:0273 f1 ca 02 7a c0 02 98 c0 02 85 66 6f 70 65 6e 2d
/epush16 0286 00
\epush16 0287
/esmove 028e 00
\esmove 028f
:0283 31 00 d4 00 00 02 7d d4 00 a4 d4 00 00 00 02 c3
?auto_err 0293
:0293 00 00 c0 0b 6c c0 02 a2 66 77 72 69 74 65 00 d4
/epush16 02a3 00
\epush16 02a4
/esmove 02ab 00
\esmove 02ac
?auto_err 02b0
:02a3 00 00 02 9b d4 00 f4 d4 00 00 00 02 c3 00 00 d4
/epush16 02b3 00
\epush16 02b4
/lstor16 02b8 00
\lstor16 02b9
/dpop16 02bd 00
\dpop16 02be
/lpush16 02c0 00
\lpush16 02c1
:02b3 00 00 00 1f d4 00 00 ff fc d4 00 00 d4 00 00 ff
/epush16 02c5 00
\epush16 02c6
/lte16 02ca 00
\lte16 02cb
/dpop16 02cd 00
\dpop16 02ce
:02c3 fc d4 00 00 00 83 d4 00 00 d4 00 00 9a 52 8a f1
/epush16 02dd 00
\epush16 02de
/lpush16 02e2 00
:02d3 ca 02 d9 c0 03 64 c0 02 f4 d4 00 00 00 1f d4 00
\lpush16 02e3
/add16 02e7 00
\add16 02e8
/lstor16 02ea 00
\lstor16 02eb
/dpop16 02ef 00
\dpop16 02f0
:02e3 00 ff fc d4 00 00 d4 00 00 ff fc d4 00 00 c0 02
/lpush16 02f5 00
\lpush16 02f6
/lpush16 02fa 00
\lpush16 02fb
/epush16 02ff 00
\epush16 0300
:02f3 bf d4 00 00 ff fc d4 00 00 ff fc d4 00 00 01 23
/Cmemset 0304 00
\Cmemset 0305
/esmove 0307 00
\esmove 0308
?auto_err 030c
/lpush16 030f 00
\lpush16 0310
:0303 d4 00 00 d4 00 00 00 06 c3 00 00 d4 00 00 ff fe
/lpush16 0314 00
\lpush16 0315
/epush16 0319 00
\epush16 031a
/epush16 031e 00
\epush16 031f
:0313 d4 00 00 ff fc d4 00 00 00 01 d4 00 00 01 23 d4
/Cfwrite 0323 00
\Cfwrite 0324
/esmove 0326 00
\esmove 0327
?auto_err 032b
/lpush16 032e 00
\lpush16 032f
:0323 00 00 d4 00 00 00 08 c3 00 00 d4 00 00 ff fc d4
/dpush16 0333 00
\dpush16 0334
/ne16 0336 00
\ne16 0337
/dpop16 0339 00
\dpop16 033a
:0333 00 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 03 45 c0
/epush16 0352 00
:0343 03 61 c0 03 51 66 77 72 69 74 65 2d 31 00 d4 00
\epush16 0353
/esmove 035a 00
\esmove 035b
?auto_err 035f
:0353 00 03 48 d4 00 a4 d4 00 00 00 02 c3 00 00 c0 02
/lpush16 0365 00
\lpush16 0366
/Crewind 036a 00
\Crewind 036b
/esmove 036d 00
\esmove 036e
?auto_err 0372
:0363 dc d4 00 00 ff fe d4 00 00 d4 00 00 00 02 c3 00
/epush16 037e 00
\epush16 037f
:0373 00 c0 03 7d 66 72 65 61 64 00 d4 00 00 03 77 d4
/esmove 0386 00
\esmove 0387
?auto_err 038b
/epush16 038e 00
\epush16 038f
:0383 00 f4 d4 00 00 00 02 c3 00 00 d4 00 00 00 1f d4
/lstor16 0393 00
\lstor16 0394
/dpop16 0398 00
\dpop16 0399
/lpush16 039b 00
\lpush16 039c
/epush16 03a0 00
\epush16 03a1
:0393 00 00 ff fc d4 00 00 d4 00 00 ff fc d4 00 00 00
/lte16 03a5 00
\lte16 03a6
/dpop16 03a8 00
\dpop16 03a9
:03a3 83 d4 00 00 d4 00 00 9a 52 8a f1 ca 03 b4 c0 04
/epush16 03b8 00
\epush16 03b9
/lpush16 03bd 00
\lpush16 03be
/add16 03c2 00
:03b3 e3 c0 03 cf d4 00 00 00 1f d4 00 00 ff fc d4 00
\add16 03c3
/lstor16 03c5 00
\lstor16 03c6
/dpop16 03ca 00
\dpop16 03cb
/lpush16 03d0 00
\lpush16 03d1
:03c3 00 d4 00 00 ff fc d4 00 00 c0 03 9a d4 00 00 ff
/lpush16 03d5 00
\lpush16 03d6
/epush16 03da 00
\epush16 03db
/Cmemset 03df 00
\Cmemset 03e0
/esmove 03e2 00
:03d3 fc d4 00 00 ff fc d4 00 00 01 23 d4 00 00 d4 00
\esmove 03e3
?auto_err 03e7
/lpush16 03ea 00
\lpush16 03eb
/lpush16 03ef 00
\lpush16 03f0
:03e3 00 00 06 c3 00 00 d4 00 00 ff fe d4 00 00 ff fc
/epush16 03f4 00
\epush16 03f5
/epush16 03f9 00
\epush16 03fa
/Cfread 03fe 00
\Cfread 03ff
/esmove 0401 00
\esmove 0402
:03f3 d4 00 00 00 01 d4 00 00 01 23 d4 00 00 d4 00 00
?auto_err 0406
/lpush16 0409 00
\lpush16 040a
/dpush16 040e 00
\dpush16 040f
/ne16 0411 00
\ne16 0412
:0403 00 08 c3 00 00 d4 00 00 ff fc d4 00 00 d4 00 00
/dpop16 0414 00
\dpop16 0415
:0413 d4 00 00 9a 52 8a f1 ca 04 20 c0 04 3b c0 04 2b
/epush16 042c 00
\epush16 042d
:0423 66 72 65 61 64 2d 31 00 d4 00 00 04 23 d4 00 a4
/esmove 0434 00
\esmove 0435
?auto_err 0439
/epush16 043c 00
\epush16 043d
/lstor16 0441 00
\lstor16 0442
:0433 d4 00 00 00 02 c3 00 00 d4 00 00 00 00 d4 00 00
/dpop16 0446 00
\dpop16 0447
/lpush16 0449 00
\lpush16 044a
/lpush16 044e 00
\lpush16 044f
:0443 ff fa d4 00 00 d4 00 00 ff fa d4 00 00 ff fc d4
/lt16 0453 00
\lt16 0454
/dpop16 0456 00
\dpop16 0457
:0453 00 00 d4 00 00 9a 52 8a f1 ca 04 62 c0 04 a8 c0
/lpush16 0466 00
\lpush16 0467
/linc16 046b 00
\linc16 046c
/dpop16 0470 00
\dpop16 0471
:0463 04 75 d4 00 00 ff fa d4 00 00 ff fa d4 00 00 c0
/epush16 0476 00
\epush16 0477
/lpush16 047b 00
\lpush16 047c
/add16 0480 00
\add16 0481
:0473 04 48 d4 00 00 01 23 d4 00 00 ff fa d4 00 00 d4
/deref8 0483 00
\deref8 0484
/lpush16 0486 00
\lpush16 0487
/epush16 048b 00
\epush16 048c
/mod16 0490 00
\mod16 0491
:0483 00 00 d4 00 00 ff fc d4 00 00 01 00 d4 00 00 d4
/ne16 0493 00
\ne16 0494
/dpop16 0496 00
\dpop16 0497
:0493 00 00 d4 00 00 9a 52 8a f1 ca 04 a2 c0 04 a5 c0
/lpush16 04a9 00
\lpush16 04aa
/lpush16 04ae 00
\lpush16 04af
:04a3 04 a8 c0 04 65 d4 00 00 ff fa d4 00 00 ff fc d4
/lt16 04b3 00
\lt16 04b4
/dpop16 04b6 00
\dpop16 04b7
:04b3 00 00 d4 00 00 9a 52 8a f1 ca 04 c2 c0 04 e0 c0
/epush16 04ce 00
\epush16 04cf
:04c3 04 cd 66 72 65 61 64 2d 32 00 d4 00 00 04 c5 d4
/esmove 04d6 00
\esmove 04d7
?auto_err 04db
:04d3 00 a4 d4 00 00 00 02 c3 00 00 c0 04 e3 c0 03 b7
/epush16 04ee 00
\epush16 04ef
:04e3 c0 04 ed 66 63 6c 6f 73 65 00 d4 00 00 04 e6 d4
/esmove 04f6 00
\esmove 04f7
?auto_err 04fb
/lpush16 04fe 00
\lpush16 04ff
:04f3 00 f4 d4 00 00 00 02 c3 00 00 d4 00 00 ff fe d4
/Cfclose 0503 00
\Cfclose 0504
/esmove 0506 00
\esmove 0507
?auto_err 050b
/dpush16 050e 00
\dpush16 050f
/dpop16 0511 00
\dpop16 0512
:0503 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00 00
:0513 9a 52 8a f1 c2 05 36 c0 05 26 66 63 6c 6f 73 65
/epush16 0527 00
\epush16 0528
/esmove 052f 00
\esmove 0530
:0523 2d 31 00 d4 00 00 05 1d d4 00 a4 d4 00 00 00 02
?auto_err 0534
/epush16 0540 00
\epush16 0541
:0533 c3 00 00 c0 05 3f 66 6f 70 65 6e 00 d4 00 00 05
/esmove 0548 00
\esmove 0549
?auto_err 054d
:0543 39 d4 00 f4 d4 00 00 00 02 c3 00 00 c0 05 5d 66
:0553 74 65 73 74 35 2e 74 6d 70 00 c0 05 63 77 2b 00
/epush16 0564 00
\epush16 0565
/epush16 0569 00
\epush16 056a
/Cfopen 056e 00
\Cfopen 056f
/esmove 0571 00
\esmove 0572
:0563 d4 00 00 05 60 d4 00 00 05 52 d4 00 00 d4 00 00
?auto_err 0576
/dpush16 0579 00
\dpush16 057a
/lstor16 057c 00
\lstor16 057d
/epush16 0581 00
\epush16 0582
:0573 00 04 c3 00 00 d4 00 00 d4 00 00 ff fe d4 00 00
/eq16 0586 00
\eq16 0587
/dpop16 0589 00
\dpop16 058a
:0583 00 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 05 95 c0
/epush16 05a1 00
\epush16 05a2
:0593 05 b3 c0 05 a0 66 6f 70 65 6e 2d 32 00 d4 00 00
/esmove 05a9 00
\esmove 05aa
?auto_err 05ae
:05a3 05 98 d4 00 a4 d4 00 00 00 02 c3 00 00 c0 0b 6c
/epush16 05b4 00
\epush16 05b5
/lstor16 05b9 00
\lstor16 05ba
/dpop16 05be 00
\dpop16 05bf
/lpush16 05c1 00
\lpush16 05c2
:05b3 d4 00 00 00 00 d4 00 00 ff fc d4 00 00 d4 00 00
/epush16 05c6 00
\epush16 05c7
/lt16 05cb 00
\lt16 05cc
/dpop16 05ce 00
\dpop16 05cf
:05c3 ff fc d4 00 00 01 00 d4 00 00 d4 00 00 9a 52 8a
/lpush16 05de 00
\lpush16 05df
:05d3 f1 ca 05 da c0 06 0e c0 05 ed d4 00 00 ff fc d4
/linc16 05e3 00
\linc16 05e4
/dpop16 05e8 00
\dpop16 05e9
/epush16 05ee 00
\epush16 05ef
:05e3 00 00 ff fc d4 00 00 c0 05 c0 d4 00 00 01 23 d4
/lpush16 05f3 00
\lpush16 05f4
/add16 05f8 00
\add16 05f9
/epush16 05fb 00
\epush16 05fc
/swap16 0600 00
\swap16 0601
:05f3 00 00 ff fc d4 00 00 d4 00 00 00 35 d4 00 00 d4
/dpop16 0603 00
\dpop16 0604
/pstor8 0606 00
\pstor8 0607
/dpop16 0609 00
\dpop16 060a
:0603 00 00 d4 00 00 d4 00 00 c0 05 dd c0 06 18 66 77
/epush16 0619 00
\epush16 061a
/esmove 0621 00
\esmove 0622
:0613 72 69 74 65 00 d4 00 00 06 11 d4 00 f4 d4 00 00
?auto_err 0626
/epush16 0629 00
\epush16 062a
/lstor16 062e 00
\lstor16 062f
:0623 00 02 c3 00 00 d4 00 00 00 00 d4 00 00 ff fc d4
/dpop16 0633 00
\dpop16 0634
/lpush16 0636 00
\lpush16 0637
/epush16 063b 00
\epush16 063c
/lt16 0640 00
\lt16 0641
:0633 00 00 d4 00 00 ff fc d4 00 00 00 10 d4 00 00 d4
/dpop16 0643 00
\dpop16 0644
:0643 00 00 9a 52 8a f1 ca 06 4f c0 06 bb c0 06 62 d4
/lpush16 0653 00
\lpush16 0654
/linc16 0658 00
\linc16 0659
/dpop16 065d 00
\dpop16 065e
:0653 00 00 ff fc d4 00 00 ff fc d4 00 00 c0 06 35 d4
/lpush16 0663 00
\lpush16 0664
/epush16 0668 00
\epush16 0669
/epush16 066d 00
\epush16 066e
/epush16 0672 00
:0663 00 00 ff fe d4 00 00 01 00 d4 00 00 00 01 d4 00
\epush16 0673
/Cfwrite 0677 00
\Cfwrite 0678
/esmove 067a 00
\esmove 067b
?auto_err 067f
/dpush16 0682 00
:0673 00 01 23 d4 00 00 d4 00 00 00 08 c3 00 00 d4 00
\dpush16 0683
/epush16 0685 00
\epush16 0686
/ne16 068a 00
\ne16 068b
/dpop16 068d 00
\dpop16 068e
:0683 00 d4 00 00 01 00 d4 00 00 d4 00 00 9a 52 8a f1
:0693 ca 06 99 c0 06 b8 c0 06 a5 66 77 72 69 74 65 2d
/epush16 06a6 00
\epush16 06a7
/esmove 06ae 00
\esmove 06af
:06a3 32 00 d4 00 00 06 9c d4 00 a4 d4 00 00 00 02 c3
?auto_err 06b3
:06b3 00 00 c0 06 bb c0 06 52 c0 06 c5 72 65 77 69 6e
/epush16 06c6 00
\epush16 06c7
/esmove 06ce 00
\esmove 06cf
:06c3 64 00 d4 00 00 06 be d4 00 f4 d4 00 00 00 02 c3
?auto_err 06d3
/lpush16 06d6 00
\lpush16 06d7
/Crewind 06db 00
\Crewind 06dc
/esmove 06de 00
\esmove 06df
:06d3 00 00 d4 00 00 ff fe d4 00 00 d4 00 00 00 02 c3
?auto_err 06e3
/epush16 06ef 00
\epush16 06f0
:06e3 00 00 c0 06 ee 66 72 65 61 64 00 d4 00 00 06 e8
/esmove 06f7 00
\esmove 06f8
?auto_err 06fc
/epush16 06ff 00
\epush16 0700
:06f3 d4 00 f4 d4 00 00 00 02 c3 00 00 d4 00 00 00 00
/lstor16 0704 00
\lstor16 0705
/dpop16 0709 00
\dpop16 070a
/lpush16 070c 00
\lpush16 070d
/epush16 0711 00
\epush16 0712
:0703 d4 00 00 ff fc d4 00 00 d4 00 00 ff fc d4 00 00
/lt16 0716 00
\lt16 0717
/dpop16 0719 00
\dpop16 071a
:0713 00 10 d4 00 00 d4 00 00 9a 52 8a f1 ca 07 25 c0
/lpush16 0729 00
\lpush16 072a
/linc16 072e 00
\linc16 072f
:0723 07 90 c0 07 38 d4 00 00 ff fc d4 00 00 ff fc d4
/dpop16 0733 00
\dpop16 0734
/lpush16 0739 00
\lpush16 073a
/epush16 073e 00
\epush16 073f
:0733 00 00 c0 07 0b d4 00 00 ff fe d4 00 00 01 00 d4
/epush16 0743 00
\epush16 0744
/epush16 0748 00
\epush16 0749
/Cfread 074d 00
\Cfread 074e
/esmove 0750 00
\esmove 0751
:0743 00 00 00 01 d4 00 00 01 23 d4 00 00 d4 00 00 00
?auto_err 0755
/dpush16 0758 00
\dpush16 0759
/epush16 075b 00
\epush16 075c
/ne16 0760 00
\ne16 0761
:0753 08 c3 00 00 d4 00 00 d4 00 00 01 00 d4 00 00 d4
/dpop16 0763 00
\dpop16 0764
:0763 00 00 9a 52 8a f1 ca 07 6f c0 07 8d c0 07 7a 66
/epush16 077b 00
\epush16 077c
:0773 72 65 61 64 2d 33 00 d4 00 00 07 72 d4 00 a4 d4
/esmove 0783 00
\esmove 0784
?auto_err 0788
:0783 00 00 00 02 c3 00 00 c0 07 90 c0 07 28 c0 07 9e
/epush16 079f 00
\epush16 07a0
:0793 66 67 65 74 63 28 65 6f 66 29 00 d4 00 00 07 93
/esmove 07a7 00
\esmove 07a8
?auto_err 07ac
/lpush16 07af 00
\lpush16 07b0
:07a3 d4 00 f4 d4 00 00 00 02 c3 00 00 d4 00 00 ff fe
/Cfgetc 07b4 00
\Cfgetc 07b5
/esmove 07b7 00
\esmove 07b8
?auto_err 07bc
/dpush16 07bf 00
\dpush16 07c0
/epush16 07c2 00
:07b3 d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00
\epush16 07c3
/ne16 07c7 00
\ne16 07c8
/dpop16 07ca 00
\dpop16 07cb
:07c3 00 ff ff d4 00 00 d4 00 00 9a 52 8a f1 ca 07 d6
/epush16 07df 00
\epush16 07e0
:07d3 c0 07 ee c0 07 de 66 65 6f 66 00 d4 00 00 07 d9
/esmove 07e7 00
\esmove 07e8
?auto_err 07ec
/lpush16 07ef 00
\lpush16 07f0
:07e3 d4 00 a4 d4 00 00 00 02 c3 00 00 d4 00 00 ff fe
/Cclearerr 07f4 00
\Cclearerr 07f5
/esmove 07f7 00
\esmove 07f8
?auto_err 07fc
:07f3 d4 00 00 d4 00 00 00 02 c3 00 00 c0 08 08 66 63
/epush16 0809 00
\epush16 080a
/esmove 0811 00
\esmove 0812
:0803 6c 6f 73 65 00 d4 00 00 08 01 d4 00 f4 d4 00 00
?auto_err 0816
/lpush16 0819 00
\lpush16 081a
/Cfclose 081e 00
\Cfclose 081f
/esmove 0821 00
\esmove 0822
:0813 00 02 c3 00 00 d4 00 00 ff fe d4 00 00 d4 00 00
?auto_err 0826
/dpush16 0829 00
\dpush16 082a
/dpop16 082c 00
\dpop16 082d
:0823 00 02 c3 00 00 d4 00 00 d4 00 00 9a 52 8a f1 c2
/epush16 0842 00
:0833 08 51 c0 08 41 66 63 6c 6f 73 65 2d 32 00 d4 00
\epush16 0843
/esmove 084a 00
\esmove 084b
?auto_err 084f
:0843 00 08 38 d4 00 a4 d4 00 00 00 02 c3 00 00 c0 08
/epush16 085b 00
\epush16 085c
:0853 5a 66 6f 70 65 6e 00 d4 00 00 08 54 d4 00 f4 d4
/esmove 0863 00
\esmove 0864
?auto_err 0868
:0863 00 00 00 02 c3 00 00 c0 08 78 66 74 65 73 74 35
/epush16 087e 00
\epush16 087f
:0873 2e 74 6d 70 00 c0 08 7d 72 00 d4 00 00 08 7b d4
/epush16 0883 00
\epush16 0884
/Cfopen 0888 00
\Cfopen 0889
/esmove 088b 00
\esmove 088c
?auto_err 0890
:0883 00 00 08 6d d4 00 00 d4 00 00 00 04 c3 00 00 d4
/dpush16 0893 00
\dpush16 0894
/lstor16 0896 00
\lstor16 0897
/epush16 089b 00
\epush16 089c
/eq16 08a0 00
\eq16 08a1
:0893 00 00 d4 00 00 ff fe d4 00 00 00 00 d4 00 00 d4
/dpop16 08a3 00
\dpop16 08a4
:08a3 00 00 9a 52 8a f1 ca 08 af c0 08 cd c0 08 ba 66
/epush16 08bb 00
\epush16 08bc
:08b3 6f 70 65 6e 2d 33 00 d4 00 00 08 b2 d4 00 a4 d4
/esmove 08c3 00
\esmove 08c4
?auto_err 08c8
:08c3 00 00 00 02 c3 00 00 c0 0b 6c c0 08 d6 66 74 65
/epush16 08d7 00
\epush16 08d8
/esmove 08df 00
\esmove 08e0
:08d3 6c 6c 00 d4 00 00 08 d0 d4 00 f4 d4 00 00 00 02
?auto_err 08e4
/lpush16 08e7 00
\lpush16 08e8
/Cftell 08ec 00
\Cftell 08ed
/esmove 08ef 00
\esmove 08f0
:08e3 c3 00 00 d4 00 00 ff fe d4 00 00 d4 00 00 00 02
?auto_err 08f4
/dpush16 08f7 00
\dpush16 08f8
/epush16 08fa 00
\epush16 08fb
/ne16 08ff 00
\ne16 0900
/dpop16 0902 00
:08f3 c3 00 00 d4 00 00 d4 00 00 00 00 d4 00 00 d4 00
\dpop16 0903
:0903 00 9a 52 8a f1 ca 09 0e c0 09 29 c0 09 19 66 74
/epush16 091a 00
\epush16 091b
/esmove 0922 00
:0913 65 6c 6c 2d 31 00 d4 00 00 09 11 d4 00 a4 d4 00
\esmove 0923
?auto_err 0927
:0923 00 00 02 c3 00 00 c0 09 32 66 73 65 65 6b 00 d4
/epush16 0933 00
\epush16 0934
/esmove 093b 00
\esmove 093c
?auto_err 0940
:0933 00 00 09 2c d4 00 f4 d4 00 00 00 02 c3 00 00 d4
/epush16 0943 00
\epush16 0944
/epush16 0948 00
\epush16 0949
/lpush16 094d 00
\lpush16 094e
/Cfseek 0952 00
:0943 00 00 00 02 d4 00 00 00 00 d4 00 00 ff fe d4 00
\Cfseek 0953
/esmove 0955 00
\esmove 0956
?auto_err 095a
/dpush16 095d 00
\dpush16 095e
/epush16 0960 00
\epush16 0961
:0953 00 d4 00 00 00 06 c3 00 00 d4 00 00 d4 00 00 00
/ne16 0965 00
\ne16 0966
/dpop16 0968 00
\dpop16 0969
:0963 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 09 74 c0 09
/epush16 0980 00
\epush16 0981
:0973 8f c0 09 7f 66 73 65 65 6b 2d 31 00 d4 00 00 09
/esmove 0988 00
\esmove 0989
?auto_err 098d
/lpush16 0990 00
\lpush16 0991
:0983 77 d4 00 a4 d4 00 00 00 02 c3 00 00 d4 00 00 ff
/Cftell 0995 00
\Cftell 0996
/esmove 0998 00
\esmove 0999
?auto_err 099d
/dpush16 09a0 00
\dpush16 09a1
:0993 fe d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4
/epush16 09a3 00
\epush16 09a4
/ne16 09a8 00
\ne16 09a9
/dpop16 09ab 00
\dpop16 09ac
:09a3 00 00 10 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 09
:09b3 b7 c0 09 d2 c0 09 c2 66 74 65 6c 6c 2d 32 00 d4
/epush16 09c3 00
\epush16 09c4
/esmove 09cb 00
\esmove 09cc
?auto_err 09d0
:09c3 00 00 09 ba d4 00 a4 d4 00 00 00 02 c3 00 00 c0
/epush16 09dc 00
\epush16 09dd
:09d3 09 db 66 73 65 65 6b 00 d4 00 00 09 d5 d4 00 f4
/esmove 09e4 00
\esmove 09e5
?auto_err 09e9
/epush16 09ec 00
\epush16 09ed
/epush16 09f1 00
\epush16 09f2
:09e3 d4 00 00 00 02 c3 00 00 d4 00 00 00 00 d4 00 00
/lpush16 09f6 00
\lpush16 09f7
/Cfseek 09fb 00
\Cfseek 09fc
/esmove 09fe 00
\esmove 09ff
:09f3 07 e9 d4 00 00 ff fe d4 00 00 d4 00 00 00 06 c3
?auto_err 0a03
/dpush16 0a06 00
\dpush16 0a07
/epush16 0a09 00
\epush16 0a0a
/ne16 0a0e 00
\ne16 0a0f
/dpop16 0a11 00
\dpop16 0a12
:0a03 00 00 d4 00 00 d4 00 00 00 00 d4 00 00 d4 00 00
:0a13 9a 52 8a f1 ca 0a 1d c0 0a 38 c0 0a 28 66 73 65
/epush16 0a29 00
\epush16 0a2a
/esmove 0a31 00
\esmove 0a32
:0a23 65 6b 2d 32 00 d4 00 00 0a 20 d4 00 a4 d4 00 00
?auto_err 0a36
/lpush16 0a39 00
\lpush16 0a3a
/Cftell 0a3e 00
\Cftell 0a3f
/esmove 0a41 00
\esmove 0a42
:0a33 00 02 c3 00 00 d4 00 00 ff fe d4 00 00 d4 00 00
?auto_err 0a46
/dpush16 0a49 00
\dpush16 0a4a
/epush16 0a4c 00
\epush16 0a4d
/ne16 0a51 00
\ne16 0a52
:0a43 00 02 c3 00 00 d4 00 00 d4 00 00 07 e9 d4 00 00
/dpop16 0a54 00
\dpop16 0a55
:0a53 d4 00 00 9a 52 8a f1 ca 0a 60 c0 0a 7b c0 0a 6b
/epush16 0a6c 00
\epush16 0a6d
:0a63 66 73 65 65 6b 2d 33 00 d4 00 00 0a 63 d4 00 a4
/esmove 0a74 00
\esmove 0a75
?auto_err 0a79
:0a73 d4 00 00 00 02 c3 00 00 c0 0a 84 66 73 65 65 6b
/epush16 0a85 00
\epush16 0a86
/esmove 0a8d 00
\esmove 0a8e
?auto_err 0a92
:0a83 00 d4 00 00 0a 7e d4 00 f4 d4 00 00 00 02 c3 00
/epush16 0a95 00
\epush16 0a96
/epush16 0a9a 00
\epush16 0a9b
/lpush16 0a9f 00
\lpush16 0aa0
:0a93 00 d4 00 00 00 01 d4 00 00 01 db d4 00 00 ff fe
/Cfseek 0aa4 00
\Cfseek 0aa5
/esmove 0aa7 00
\esmove 0aa8
?auto_err 0aac
/dpush16 0aaf 00
\dpush16 0ab0
/epush16 0ab2 00
:0aa3 d4 00 00 d4 00 00 00 06 c3 00 00 d4 00 00 d4 00
\epush16 0ab3
/ne16 0ab7 00
\ne16 0ab8
/dpop16 0aba 00
\dpop16 0abb
:0ab3 00 00 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 0a c6
/epush16 0ad2 00
:0ac3 c0 0a e1 c0 0a d1 66 73 65 65 6b 2d 34 00 d4 00
\epush16 0ad3
/esmove 0ada 00
\esmove 0adb
?auto_err 0adf
/lpush16 0ae2 00
:0ad3 00 0a c9 d4 00 a4 d4 00 00 00 02 c3 00 00 d4 00
\lpush16 0ae3
/Cftell 0ae7 00
\Cftell 0ae8
/esmove 0aea 00
\esmove 0aeb
?auto_err 0aef
/dpush16 0af2 00
:0ae3 00 ff fe d4 00 00 d4 00 00 00 02 c3 00 00 d4 00
\dpush16 0af3
/epush16 0af5 00
\epush16 0af6
/ne16 0afa 00
\ne16 0afb
/dpop16 0afd 00
\dpop16 0afe
:0af3 00 d4 00 00 09 c4 d4 00 00 d4 00 00 9a 52 8a f1
:0b03 ca 0b 09 c0 0b 24 c0 0b 14 66 73 65 65 6b 2d 35
/epush16 0b15 00
\epush16 0b16
/esmove 0b1d 00
\esmove 0b1e
?auto_err 0b22
:0b13 00 d4 00 00 0b 0c d4 00 a4 d4 00 00 00 02 c3 00
/epush16 0b2f 00
\epush16 0b30
:0b23 00 c0 0b 2e 66 63 6c 6f 73 65 00 d4 00 00 0b 27
/esmove 0b37 00
\esmove 0b38
?auto_err 0b3c
/lpush16 0b3f 00
\lpush16 0b40
:0b33 d4 00 f4 d4 00 00 00 02 c3 00 00 d4 00 00 ff fe
/Cfclose 0b44 00
\Cfclose 0b45
/esmove 0b47 00
\esmove 0b48
?auto_err 0b4c
:0b43 d4 00 00 d4 00 00 00 02 c3 00 00 c0 0b 5c 66 74
/epush16 0b5d 00
\epush16 0b5e
/Cunlink 0b62 00
:0b53 65 73 74 35 2e 74 6d 70 00 d4 00 00 0b 51 d4 00
\Cunlink 0b63
/esmove 0b65 00
\esmove 0b66
?auto_err 0b6a
/esmove 0b6d 00
\esmove 0b6e
?auto_err 0b72
:0b63 00 d4 00 00 00 02 c3 00 00 d4 00 00 00 06 c3 00
/escheck 0b76 00
\escheck 0b77
=Cmain 0b7e
:0b73 00 e2 d4 00 00 60 72 ab f0 bb d5 f8 00 a1 f8 f0
/vpush16 0b91 00
\vpush16 0b92
:0b83 b1 e2 9b 73 8b 73 87 ab 97 bb d4 02 23 d4 00 00
/dpop16 0b96 00
\dpop16 0b97
/escheck 0b9a 00
\escheck 0b9b
:0b93 00 02 d4 00 00 e2 d4 00 00 60 72 ab f0 bb d5
+00ae
+00c3
+00d3
+00d8
+00e5
+00fe
+010c
+0235
+0243
+024b
+0250
+0275
+0278
+027b
+0288
^028b a4
v028c
+0296
+0299
+02a5
^02a8 f4
v02a9
+02d4
+02d7
+02da
+02f2
+0301
+0320
+0340
+0343
+0346
+0354
^0357 a4
v0358
+0362
+0375
+0380
^0383 f4
v0384
+03af
+03b2
+03b5
+03cd
+03dc
+03fb
+041b
+041e
+0421
+042e
^0431 a4
v0432
+045d
+0460
+0463
+0473
+0478
+049d
+04a0
+04a3
+04a6
+04bd
+04c0
+04c3
+04d0
^04d3 a4
v04d4
+04de
+04e1
+04e4
+04f0
^04f3 f4
v04f4
+0518
+051b
+0529
^052c a4
v052d
+0537
+0542
^0545 f4
v0546
+0550
+055e
+0566
+056b
+0590
+0593
+0596
+05a3
^05a6 a4
v05a7
+05b1
+05d5
+05d8
+05db
+05eb
+05f0
+060c
+060f
+061b
^061e f4
v061f
+064a
+064d
+0650
+0660
+0674
+0694
+0697
+069a
+06a8
^06ab a4
v06ac
+06b6
+06b9
+06bc
+06c8
^06cb f4
v06cc
+06e6
+06f1
^06f4 f4
v06f5
+0720
+0723
+0726
+0736
+074a
+076a
+076d
+0770
+077d
^0780 a4
v0781
+078b
+078e
+0791
+07a1
^07a4 f4
v07a5
+07d1
+07d4
+07d7
+07e1
^07e4 a4
v07e5
+07ff
+080b
^080e f4
v080f
+0833
+0836
+0844
^0847 a4
v0848
+0852
+085d
^0860 f4
v0861
+086b
+0879
+0880
+0885
+08aa
+08ad
+08b0
+08bd
^08c0 a4
v08c1
+08cb
+08ce
+08d9
^08dc f4
v08dd
+0909
+090c
+090f
+091c
^091f a4
v0920
+092a
+0935
^0938 f4
v0939
+096f
+0972
+0975
+0982
^0985 a4
v0986
+09b2
+09b5
+09b8
+09c5
^09c8 a4
v09c9
+09d3
+09de
^09e1 f4
v09e2
+0a18
+0a1b
+0a1e
+0a2b
^0a2e a4
v0a2f
+0a5b
+0a5e
+0a61
+0a6e
^0a71 a4
v0a72
+0a7c
+0a87
^0a8a f4
v0a8b
+0ac1
+0ac4
+0ac7
+0ad4
^0ad7 a4
v0ad8
+0b04
+0b07
+0b0a
+0b17
^0b1a a4
v0b1b
+0b25
+0b31
^0b34 f4
v0b35
+0b4f
+0b5f
^0b8e 23
v0b8f
+0b93
}
