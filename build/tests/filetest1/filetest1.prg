.big
{filetest1
.library string.lib
=Cbuf 0000
>0080
=Ctn1 0080
>0008
=Ctn2 0088
>0008
=CErrors 0090
=Cresult 0092
=Cfail 0094
:0090 00 00 00 00 e2 9b 73 8b 73 87 ab 97 bb c0 00 ab
/lpush16 00ac 00
\lpush16 00ad
:00a0 25 73 20 66 61 69 6c 65 64 0a 00 d4 00 00 00 00
/epush16 00b1 00
\epush16 00b2
/Cprintf 00b6 00
\Cprintf 00b7
/esmove 00b9 00
\esmove 00ba
?auto_err 00be
:00b0 d4 00 00 00 a0 d4 00 00 d4 00 00 00 04 c3 00 00
/vpush16 00c1 00
\vpush16 00c2
/vinc16 00c6 00
\vinc16 00c7
/dpop16 00cb 00
\dpop16 00cc
/epush16 00ce 00
\epush16 00cf
:00c0 d4 00 00 00 90 d4 00 00 00 90 d4 00 00 d4 00 00
/vstor16 00d3 00
\vstor16 00d4
/dpop16 00d8 00
\dpop16 00d9
/escheck 00dc 00
\escheck 00dd
:00d0 00 01 d4 00 00 00 92 d4 00 00 e2 d4 00 00 60 72
=Cpr 00e4
:00e0 ab f0 bb d5 e2 9b 73 8b 73 87 ab 97 bb c0 00 f4
/lpush16 00f5 00
\lpush16 00f6
/epush16 00fa 00
\epush16 00fb
/Cprintf 00ff 00
:00f0 25 73 0a 00 d4 00 00 00 00 d4 00 00 00 f0 d4 00
\Cprintf 0100
/esmove 0102 00
\esmove 0103
?auto_err 0107
/escheck 010b 00
\escheck 010c
:0100 00 d4 00 00 00 04 c3 00 00 e2 d4 00 00 60 72 ab
=Ctest_file 0113
/esmove 011d 00
\esmove 011e
:0110 f0 bb d5 e2 9b 73 8b 73 87 ab 97 bb d4 00 00 ff
?auto_err 0122
/epush16 012f 00
:0120 fe c3 00 00 c0 01 2e 72 65 6d 6f 76 65 00 d4 00
\epush16 0130
/esmove 0137 00
\esmove 0138
?auto_err 013c
:0130 00 01 27 d4 00 e4 d4 00 00 00 02 c3 00 00 c0 01
:0140 4b 66 74 65 73 74 2e 74 6d 70 00 c0 01 50 77 00
/epush16 0151 00
\epush16 0152
/epush16 0156 00
\epush16 0157
/Cfopen 015b 00
\Cfopen 015c
/esmove 015e 00
\esmove 015f
:0150 d4 00 00 01 4e d4 00 00 01 41 d4 00 00 d4 00 00
?auto_err 0163
/dpush16 0166 00
\dpush16 0167
/lstor16 0169 00
\lstor16 016a
/dpop16 016e 00
\dpop16 016f
:0160 00 04 c3 00 00 d4 00 00 d4 00 00 ff fe d4 00 00
/epush16 0171 00
\epush16 0172
/lpush16 0176 00
\lpush16 0177
/eq16 017b 00
\eq16 017c
/dpop16 017e 00
\dpop16 017f
:0170 d4 00 00 00 00 d4 00 00 ff fe d4 00 00 d4 00 00
:0180 9a 52 8a f1 ca 01 8a c0 01 bf c0 01 95 66 6f 70
/epush16 0196 00
\epush16 0197
/esmove 019e 00
\esmove 019f
:0190 65 6e 2d 31 00 d4 00 00 01 8d d4 00 94 d4 00 00
?auto_err 01a3
:01a0 00 02 c3 00 00 c0 01 af 72 65 6d 6f 76 65 00 d4
/epush16 01b0 00
\epush16 01b1
/Cperror 01b5 00
\Cperror 01b6
/esmove 01b8 00
\esmove 01b9
?auto_err 01bd
:01b0 00 00 01 a8 d4 00 00 d4 00 00 00 02 c3 00 00 d4
/lpush16 01c0 00
\lpush16 01c1
/Cfclose 01c5 00
\Cfclose 01c6
/esmove 01c8 00
\esmove 01c9
?auto_err 01cd
:01c0 00 00 ff fe d4 00 00 d4 00 00 00 02 c3 00 00 c0
/epush16 01dd 00
\epush16 01de
:01d0 01 dc 66 74 65 73 74 2e 74 6d 70 00 d4 00 00 01
/Cremove 01e2 00
\Cremove 01e3
/esmove 01e5 00
\esmove 01e6
?auto_err 01ea
/dpush16 01ed 00
\dpush16 01ee
:01e0 d2 d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4
/epush16 01f0 00
\epush16 01f1
/lt16 01f5 00
\lt16 01f6
/dpop16 01f8 00
\dpop16 01f9
:01f0 00 00 00 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 02
:0200 04 c0 02 20 c0 02 10 72 65 6d 6f 76 65 2d 31 00
/epush16 0211 00
\epush16 0212
/esmove 0219 00
\esmove 021a
?auto_err 021e
:0210 d4 00 00 02 07 d4 00 94 d4 00 00 00 02 c3 00 00
/epush16 022e 00
\epush16 022f
:0220 c0 02 2d 66 74 65 73 74 2e 74 6d 70 00 d4 00 00
/Cremove 0233 00
\Cremove 0234
/esmove 0236 00
\esmove 0237
?auto_err 023b
/dpush16 023e 00
\dpush16 023f
:0230 02 23 d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00
/epush16 0241 00
\epush16 0242
/gte16 0246 00
\gte16 0247
/dpop16 0249 00
\dpop16 024a
:0240 d4 00 00 00 00 d4 00 00 d4 00 00 9a 52 8a f1 ca
:0250 02 55 c0 02 71 c0 02 61 72 65 6d 6f 76 65 2d 32
/epush16 0262 00
\epush16 0263
/esmove 026a 00
\esmove 026b
?auto_err 026f
:0260 00 d4 00 00 02 58 d4 00 94 d4 00 00 00 02 c3 00
/epush16 027c 00
\epush16 027d
:0270 00 c0 02 7b 72 65 6e 61 6d 65 00 d4 00 00 02 74
/esmove 0284 00
\esmove 0285
?auto_err 0289
:0280 d4 00 e4 d4 00 00 00 02 c3 00 00 c0 02 98 66 74
:0290 65 73 74 2e 74 6d 70 00 c0 02 a6 66 74 65 73 74
/epush16 02a7 00
\epush16 02a8
/epush16 02ac 00
\epush16 02ad
:02a0 32 2e 74 6d 70 00 d4 00 00 02 9b d4 00 00 02 8e
/Crename 02b1 00
\Crename 02b2
/esmove 02b4 00
\esmove 02b5
?auto_err 02b9
/dpush16 02bc 00
\dpush16 02bd
/epush16 02bf 00
:02b0 d4 00 00 d4 00 00 00 04 c3 00 00 d4 00 00 d4 00
\epush16 02c0
/gte16 02c4 00
\gte16 02c5
/dpop16 02c7 00
\dpop16 02c8
:02c0 00 00 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 02 d3
:02d0 c0 02 ef c0 02 df 72 65 6e 61 6d 65 2d 31 00 d4
/epush16 02e0 00
\epush16 02e1
/esmove 02e8 00
\esmove 02e9
?auto_err 02ed
:02e0 00 00 02 d6 d4 00 94 d4 00 00 00 02 c3 00 00 c0
:02f0 02 fc 66 74 65 73 74 2e 74 6d 70 00 c0 03 01 77
/epush16 0302 00
\epush16 0303
/epush16 0307 00
\epush16 0308
/Cfopen 030c 00
\Cfopen 030d
/esmove 030f 00
:0300 00 d4 00 00 02 ff d4 00 00 02 f2 d4 00 00 d4 00
\esmove 0310
?auto_err 0314
/dpush16 0317 00
\dpush16 0318
/lstor16 031a 00
\lstor16 031b
/dpop16 031f 00
:0310 00 00 04 c3 00 00 d4 00 00 d4 00 00 ff fe d4 00
\dpop16 0320
/epush16 0322 00
\epush16 0323
/lpush16 0327 00
\lpush16 0328
/eq16 032c 00
\eq16 032d
/dpop16 032f 00
:0320 00 d4 00 00 00 00 d4 00 00 ff fe d4 00 00 d4 00
\dpop16 0330
:0330 00 9a 52 8a f1 ca 03 3b c0 03 70 c0 03 46 66 6f
/epush16 0347 00
\epush16 0348
/esmove 034f 00
:0340 70 65 6e 2d 32 00 d4 00 00 03 3e d4 00 94 d4 00
\esmove 0350
?auto_err 0354
:0350 00 00 02 c3 00 00 c0 03 60 72 65 6e 61 6d 65 00
/epush16 0361 00
\epush16 0362
/Cperror 0366 00
\Cperror 0367
/esmove 0369 00
\esmove 036a
?auto_err 036e
:0360 d4 00 00 03 59 d4 00 00 d4 00 00 00 02 c3 00 00
/lpush16 0371 00
\lpush16 0372
/Cfclose 0376 00
\Cfclose 0377
/esmove 0379 00
\esmove 037a
?auto_err 037e
:0370 d4 00 00 ff fe d4 00 00 d4 00 00 00 02 c3 00 00
:0380 c0 03 8d 66 74 65 73 74 2e 74 6d 70 00 c0 03 9b
/epush16 039c 00
\epush16 039d
:0390 66 74 65 73 74 32 2e 74 6d 70 00 d4 00 00 03 90
/epush16 03a1 00
\epush16 03a2
/Crename 03a6 00
\Crename 03a7
/esmove 03a9 00
\esmove 03aa
?auto_err 03ae
:03a0 d4 00 00 03 83 d4 00 00 d4 00 00 00 04 c3 00 00
/dpush16 03b1 00
\dpush16 03b2
/epush16 03b4 00
\epush16 03b5
/lt16 03b9 00
\lt16 03ba
/dpop16 03bc 00
\dpop16 03bd
:03b0 d4 00 00 d4 00 00 00 00 d4 00 00 d4 00 00 9a 52
:03c0 8a f1 ca 03 c8 c0 03 e4 c0 03 d4 72 65 6e 61 6d
/epush16 03d5 00
\epush16 03d6
/esmove 03dd 00
\esmove 03de
:03d0 65 2d 32 00 d4 00 00 03 cb d4 00 94 d4 00 00 00
?auto_err 03e2
:03e0 02 c3 00 00 c0 03 f1 66 74 65 73 74 2e 74 6d 70
:03f0 00 c0 03 ff 66 74 65 73 74 32 2e 74 6d 70 00 d4
/epush16 0400 00
\epush16 0401
/epush16 0405 00
\epush16 0406
/Crename 040a 00
\Crename 040b
/esmove 040d 00
\esmove 040e
:0400 00 00 03 f4 d4 00 00 03 e7 d4 00 00 d4 00 00 00
?auto_err 0412
/dpush16 0415 00
\dpush16 0416
/epush16 0418 00
\epush16 0419
/gte16 041d 00
\gte16 041e
:0410 04 c3 00 00 d4 00 00 d4 00 00 00 00 d4 00 00 d4
/dpop16 0420 00
\dpop16 0421
:0420 00 00 9a 52 8a f1 ca 04 2c c0 04 48 c0 04 38 72
/epush16 0439 00
\epush16 043a
:0430 65 6e 61 6d 65 2d 33 00 d4 00 00 04 2f d4 00 94
/esmove 0441 00
\esmove 0442
?auto_err 0446
:0440 d4 00 00 00 02 c3 00 00 c0 04 56 66 74 65 73 74
/epush16 0457 00
\epush16 0458
/Cremove 045c 00
\Cremove 045d
/esmove 045f 00
:0450 32 2e 74 6d 70 00 d4 00 00 04 4b d4 00 00 d4 00
\esmove 0460
?auto_err 0464
:0460 00 00 02 c3 00 00 c0 04 71 74 6d 70 66 69 6c 65
/epush16 0472 00
\epush16 0473
/esmove 047a 00
\esmove 047b
?auto_err 047f
:0470 00 d4 00 00 04 69 d4 00 e4 d4 00 00 00 02 c3 00
/Ctmpfile 0482 00
\Ctmpfile 0483
/dpush16 0485 00
\dpush16 0486
/lstor16 0488 00
\lstor16 0489
/epush16 048d 00
\epush16 048e
:0480 00 d4 00 00 d4 00 00 d4 00 00 ff fe d4 00 00 00
/eq16 0492 00
\eq16 0493
/dpop16 0495 00
\dpop16 0496
:0490 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 04 a1 c0 04
/epush16 04af 00
:04a0 dc c0 04 ae 74 6d 70 66 69 6c 65 2d 31 00 d4 00
\epush16 04b0
/esmove 04b7 00
\esmove 04b8
?auto_err 04bc
:04b0 00 04 a4 d4 00 94 d4 00 00 00 02 c3 00 00 c0 04
/epush16 04ca 00
\epush16 04cb
/Cperror 04cf 00
:04c0 c9 74 6d 70 66 69 6c 65 00 d4 00 00 04 c1 d4 00
\Cperror 04d0
/esmove 04d2 00
\esmove 04d3
?auto_err 04d7
/epush16 04dd 00
\epush16 04de
:04d0 00 d4 00 00 00 02 c3 00 00 c0 06 74 d4 00 00 00
/epush16 04e2 00
\epush16 04e3
/epush16 04e7 00
\epush16 04e8
/Cmemset 04ec 00
\Cmemset 04ed
/esmove 04ef 00
:04e0 80 d4 00 00 00 a5 d4 00 00 00 00 d4 00 00 d4 00
\esmove 04f0
?auto_err 04f4
/lpush16 04f7 00
\lpush16 04f8
/epush16 04fc 00
\epush16 04fd
:04f0 00 00 06 c3 00 00 d4 00 00 ff fe d4 00 00 00 80
/epush16 0501 00
\epush16 0502
/epush16 0506 00
\epush16 0507
/Cfwrite 050b 00
\Cfwrite 050c
/esmove 050e 00
\esmove 050f
:0500 d4 00 00 00 01 d4 00 00 00 00 d4 00 00 d4 00 00
?auto_err 0513
/dpush16 0516 00
\dpush16 0517
/epush16 0519 00
\epush16 051a
/ne16 051e 00
\ne16 051f
:0510 00 08 c3 00 00 d4 00 00 d4 00 00 00 80 d4 00 00
/dpop16 0521 00
\dpop16 0522
:0520 d4 00 00 9a 52 8a f1 ca 05 2d c0 05 4a c0 05 3a
/epush16 053b 00
\epush16 053c
:0530 74 6d 70 66 69 6c 65 2d 32 00 d4 00 00 05 30 d4
/esmove 0543 00
\esmove 0544
?auto_err 0548
/lpush16 054b 00
\lpush16 054c
:0540 00 94 d4 00 00 00 02 c3 00 00 d4 00 00 ff fe d4
/Crewind 0550 00
\Crewind 0551
/esmove 0553 00
\esmove 0554
?auto_err 0558
/lpush16 055b 00
\lpush16 055c
:0550 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 ff fe d4
/epush16 0560 00
\epush16 0561
/epush16 0565 00
\epush16 0566
/epush16 056a 00
\epush16 056b
/Cfread 056f 00
:0560 00 00 00 80 d4 00 00 00 01 d4 00 00 00 00 d4 00
\Cfread 0570
/esmove 0572 00
\esmove 0573
?auto_err 0577
/dpush16 057a 00
\dpush16 057b
/epush16 057d 00
\epush16 057e
:0570 00 d4 00 00 00 08 c3 00 00 d4 00 00 d4 00 00 00
/ne16 0582 00
\ne16 0583
/dpop16 0585 00
\dpop16 0586
:0580 80 d4 00 00 d4 00 00 9a 52 8a f1 ca 05 91 c0 05
/epush16 059f 00
:0590 ae c0 05 9e 74 6d 70 66 69 6c 65 2d 33 00 d4 00
\epush16 05a0
/esmove 05a7 00
\esmove 05a8
?auto_err 05ac
:05a0 00 05 94 d4 00 94 d4 00 00 00 02 c3 00 00 c0 05
/epush16 05bc 00
\epush16 05bd
:05b0 bb 74 65 6d 70 2e 25 30 32 64 00 d4 00 00 00 0a
/lpush16 05c1 00
\lpush16 05c2
/add16 05c6 00
\add16 05c7
/deref16 05c9 00
\deref16 05ca
/epush16 05cc 00
\epush16 05cd
:05c0 d4 00 00 ff fe d4 00 00 d4 00 00 d4 00 00 05 b1
/epush16 05d1 00
\epush16 05d2
/Csprintf 05d6 00
\Csprintf 05d7
/esmove 05d9 00
\esmove 05da
?auto_err 05de
:05d0 d4 00 00 00 80 d4 00 00 d4 00 00 00 06 c3 00 00
/lpush16 05e1 00
\lpush16 05e2
/Cfclose 05e6 00
\Cfclose 05e7
/esmove 05e9 00
\esmove 05ea
?auto_err 05ee
:05e0 d4 00 00 ff fe d4 00 00 d4 00 00 00 02 c3 00 00
/dpush16 05f1 00
\dpush16 05f2
/epush16 05f4 00
\epush16 05f5
/eq16 05f9 00
\eq16 05fa
/dpop16 05fc 00
\dpop16 05fd
:05f0 d4 00 00 d4 00 00 ff ff d4 00 00 d4 00 00 9a 52
:0600 8a f1 ca 06 08 c0 06 25 c0 06 15 74 6d 70 66 69
/epush16 0616 00
\epush16 0617
/esmove 061e 00
\esmove 061f
:0610 6c 65 2d 34 00 d4 00 00 06 0b d4 00 94 d4 00 00
?auto_err 0623
/epush16 062b 00
\epush16 062c
:0620 00 02 c3 00 00 c0 06 2a 72 00 d4 00 00 06 28 d4
/epush16 0630 00
\epush16 0631
/Cfopen 0635 00
\Cfopen 0636
/esmove 0638 00
\esmove 0639
?auto_err 063d
:0630 00 00 00 80 d4 00 00 d4 00 00 00 04 c3 00 00 d4
/dpush16 0640 00
\dpush16 0641
/epush16 0643 00
\epush16 0644
/ne16 0648 00
\ne16 0649
/dpop16 064b 00
\dpop16 064c
:0640 00 00 d4 00 00 00 00 d4 00 00 d4 00 00 9a 52 8a
:0650 f1 ca 06 57 c0 06 74 c0 06 64 74 6d 70 66 69 6c
/epush16 0665 00
\epush16 0666
/esmove 066d 00
\esmove 066e
:0660 65 2d 35 00 d4 00 00 06 5a d4 00 94 d4 00 00 00
?auto_err 0672
/epush16 067f 00
:0670 02 c3 00 00 c0 06 7e 74 6d 70 6e 61 6d 00 d4 00
\epush16 0680
/esmove 0687 00
\esmove 0688
?auto_err 068c
/epush16 068f 00
:0680 00 06 77 d4 00 e4 d4 00 00 00 02 c3 00 00 d4 00
\epush16 0690
/Ctmpnam 0694 00
\Ctmpnam 0695
/esmove 0697 00
\esmove 0698
?auto_err 069c
/dpush16 069f 00
:0690 00 00 80 d4 00 00 d4 00 00 00 02 c3 00 00 d4 00
\dpush16 06a0
/epush16 06a2 00
\epush16 06a3
/eq16 06a7 00
\eq16 06a8
/dpop16 06aa 00
\dpop16 06ab
:06a0 00 d4 00 00 00 00 d4 00 00 d4 00 00 9a 52 8a f1
:06b0 ca 06 b6 c0 06 d2 c0 06 c2 74 6d 70 6e 61 6d 2d
/epush16 06c3 00
\epush16 06c4
/esmove 06cb 00
\esmove 06cc
:06c0 31 00 d4 00 00 06 b9 d4 00 94 d4 00 00 00 02 c3
?auto_err 06d0
/epush16 06d8 00
\epush16 06d9
/epush16 06dd 00
\epush16 06de
:06d0 00 00 c0 06 d7 77 00 d4 00 00 06 d5 d4 00 00 00
/Cfopen 06e2 00
\Cfopen 06e3
/esmove 06e5 00
\esmove 06e6
?auto_err 06ea
/dpush16 06ed 00
\dpush16 06ee
:06e0 80 d4 00 00 d4 00 00 00 04 c3 00 00 d4 00 00 d4
/lstor16 06f0 00
\lstor16 06f1
/dpop16 06f5 00
\dpop16 06f6
/epush16 06f8 00
\epush16 06f9
/lpush16 06fd 00
\lpush16 06fe
:06f0 00 00 ff fe d4 00 00 d4 00 00 00 00 d4 00 00 ff
/eq16 0702 00
\eq16 0703
/dpop16 0705 00
\dpop16 0706
:0700 fe d4 00 00 d4 00 00 9a 52 8a f1 ca 07 11 c0 07
/epush16 071d 00
\epush16 071e
:0710 46 c0 07 1c 66 6f 70 65 6e 2d 33 00 d4 00 00 07
/esmove 0725 00
\esmove 0726
?auto_err 072a
:0720 14 d4 00 94 d4 00 00 00 02 c3 00 00 c0 07 36 74
/epush16 0737 00
\epush16 0738
/Cperror 073c 00
\Cperror 073d
/esmove 073f 00
:0730 6d 70 6e 61 6d 00 d4 00 00 07 2f d4 00 00 d4 00
\esmove 0740
?auto_err 0744
/lpush16 0747 00
\lpush16 0748
/Cfclose 074c 00
\Cfclose 074d
/esmove 074f 00
:0740 00 00 02 c3 00 00 d4 00 00 ff fe d4 00 00 d4 00
\esmove 0750
?auto_err 0754
/epush16 0757 00
\epush16 0758
/Ctmpnam 075c 00
\Ctmpnam 075d
/esmove 075f 00
:0750 00 00 02 c3 00 00 d4 00 00 00 88 d4 00 00 d4 00
\esmove 0760
?auto_err 0764
/dpush16 0767 00
\dpush16 0768
/epush16 076a 00
\epush16 076b
/eq16 076f 00
:0760 00 00 02 c3 00 00 d4 00 00 d4 00 00 00 00 d4 00
\eq16 0770
/dpop16 0772 00
\dpop16 0773
:0770 00 d4 00 00 9a 52 8a f1 ca 07 7e c0 07 9a c0 07
/epush16 078b 00
\epush16 078c
:0780 8a 74 6d 70 6e 61 6d 2d 32 00 d4 00 00 07 81 d4
/esmove 0793 00
\esmove 0794
?auto_err 0798
/epush16 079b 00
\epush16 079c
:0790 00 94 d4 00 00 00 02 c3 00 00 d4 00 00 00 88 d4
/epush16 07a0 00
\epush16 07a1
/Cstrcmp 07a5 00
\Cstrcmp 07a6
/esmove 07a8 00
\esmove 07a9
?auto_err 07ad
:07a0 00 00 00 80 d4 00 00 d4 00 00 00 04 c3 00 00 d4
/dpush16 07b0 00
\dpush16 07b1
/dpop16 07b3 00
\dpop16 07b4
:07b0 00 00 d4 00 00 9a 52 8a f1 ca 07 d8 c0 07 c8 74
/epush16 07c9 00
\epush16 07ca
:07c0 6d 70 6e 61 6d 2d 33 00 d4 00 00 07 bf d4 00 94
/esmove 07d1 00
\esmove 07d2
?auto_err 07d6
/epush16 07d9 00
\epush16 07da
/Cremove 07de 00
\Cremove 07df
:07d0 d4 00 00 00 02 c3 00 00 d4 00 00 00 80 d4 00 00
/esmove 07e1 00
\esmove 07e2
?auto_err 07e6
/esmove 07e9 00
\esmove 07ea
?auto_err 07ee
:07e0 d4 00 00 00 02 c3 00 00 d4 00 00 00 02 c3 00 00
/escheck 07f2 00
\escheck 07f3
=Ctest_stdio 07fa
:07f0 e2 d4 00 00 60 72 ab f0 bb d5 e2 9b 73 8b 73 87
/esmove 0804 00
\esmove 0805
?auto_err 0809
:0800 ab 97 bb d4 00 00 ff f6 c3 00 00 c0 08 14 66 6f
/epush16 0815 00
\epush16 0816
/esmove 081d 00
\esmove 081e
:0810 70 65 6e 00 d4 00 00 08 0e d4 00 e4 d4 00 00 00
?auto_err 0822
:0820 02 c3 00 00 c0 08 32 66 74 65 73 74 33 2e 74 6d
/epush16 0839 00
\epush16 083a
/epush16 083e 00
\epush16 083f
:0830 70 00 c0 08 38 77 2b 00 d4 00 00 08 35 d4 00 00
/Cfopen 0843 00
\Cfopen 0844
/esmove 0846 00
\esmove 0847
?auto_err 084b
/dpush16 084e 00
\dpush16 084f
:0840 08 27 d4 00 00 d4 00 00 00 04 c3 00 00 d4 00 00
/lstor16 0851 00
\lstor16 0852
/epush16 0856 00
\epush16 0857
/eq16 085b 00
\eq16 085c
/dpop16 085e 00
\dpop16 085f
:0850 d4 00 00 ff fe d4 00 00 00 00 d4 00 00 d4 00 00
:0860 9a 52 8a f1 ca 08 6a c0 08 a3 c0 08 75 73 74 64
/epush16 0876 00
\epush16 0877
/Cperror 087b 00
\Cperror 087c
/esmove 087e 00
\esmove 087f
:0870 69 6f 2d 31 00 d4 00 00 08 6d d4 00 00 d4 00 00
?auto_err 0883
:0880 00 02 c3 00 00 c0 08 90 66 6f 70 65 6e 2d 31 00
/epush16 0891 00
\epush16 0892
/esmove 0899 00
\esmove 089a
?auto_err 089e
:0890 d4 00 00 08 88 d4 00 94 d4 00 00 00 02 c3 00 00
/epush16 08ac 00
\epush16 08ad
:08a0 c0 09 12 c0 08 ab 66 65 6f 66 00 d4 00 00 08 a6
/esmove 08b4 00
\esmove 08b5
?auto_err 08b9
/lpush16 08bc 00
\lpush16 08bd
:08b0 d4 00 e4 d4 00 00 00 02 c3 00 00 d4 00 00 ff fe
/Cfgetc 08c1 00
\Cfgetc 08c2
/esmove 08c4 00
\esmove 08c5
?auto_err 08c9
/lpush16 08cc 00
\lpush16 08cd
:08c0 d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 ff fe
/Cfeof 08d1 00
\Cfeof 08d2
/esmove 08d4 00
\esmove 08d5
?auto_err 08d9
/dpush16 08dc 00
\dpush16 08dd
/dpop16 08df 00
:08d0 d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00
\dpop16 08e0
:08e0 00 9a 52 8a f1 ca 09 02 c0 08 f2 66 65 6f 66 2d
/epush16 08f3 00
\epush16 08f4
/esmove 08fb 00
\esmove 08fc
:08f0 31 00 d4 00 00 08 eb d4 00 94 d4 00 00 00 02 c3
?auto_err 0900
/lpush16 0903 00
\lpush16 0904
/Cfclose 0908 00
\Cfclose 0909
/esmove 090b 00
\esmove 090c
:0900 00 00 d4 00 00 ff fe d4 00 00 d4 00 00 00 02 c3
?auto_err 0910
:0910 00 00 c0 09 20 66 74 65 73 74 33 2e 74 6d 70 00
/epush16 0926 00
\epush16 0927
/epush16 092b 00
\epush16 092c
:0920 c0 09 25 77 00 d4 00 00 09 23 d4 00 00 09 15 d4
/Cfopen 0930 00
\Cfopen 0931
/esmove 0933 00
\esmove 0934
?auto_err 0938
/dpush16 093b 00
\dpush16 093c
/lstor16 093e 00
\lstor16 093f
:0930 00 00 d4 00 00 00 04 c3 00 00 d4 00 00 d4 00 00
/epush16 0943 00
\epush16 0944
/eq16 0948 00
\eq16 0949
/dpop16 094b 00
\dpop16 094c
:0940 ff fe d4 00 00 00 00 d4 00 00 d4 00 00 9a 52 8a
:0950 f1 ca 09 57 c0 09 90 c0 09 62 73 74 64 69 6f 2d
/epush16 0963 00
\epush16 0964
/Cperror 0968 00
\Cperror 0969
/esmove 096b 00
\esmove 096c
:0960 32 00 d4 00 00 09 5a d4 00 00 d4 00 00 00 02 c3
?auto_err 0970
/epush16 097e 00
\epush16 097f
:0970 00 00 c0 09 7d 66 6f 70 65 6e 2d 32 00 d4 00 00
/esmove 0986 00
\esmove 0987
?auto_err 098b
:0980 09 75 d4 00 94 d4 00 00 00 02 c3 00 00 c0 0e 5a
/epush16 099a 00
\epush16 099b
:0990 c0 09 99 66 70 75 74 73 00 d4 00 00 09 93 d4 00
/esmove 09a2 00
\esmove 09a3
?auto_err 09a7
:09a0 e4 d4 00 00 00 02 c3 00 00 c0 09 b8 31 31 31 31
/lpush16 09b9 00
\lpush16 09ba
/epush16 09be 00
\epush16 09bf
:09b0 31 31 31 31 31 31 0a 00 d4 00 00 ff fe d4 00 00
/Cfputs 09c3 00
\Cfputs 09c4
/esmove 09c6 00
\esmove 09c7
?auto_err 09cb
/dpush16 09ce 00
\dpush16 09cf
:09c0 09 ac d4 00 00 d4 00 00 00 04 c3 00 00 d4 00 00
/epush16 09d1 00
\epush16 09d2
/eq16 09d6 00
\eq16 09d7
/dpop16 09d9 00
\dpop16 09da
:09d0 d4 00 00 ff ff d4 00 00 d4 00 00 9a 52 8a f1 ca
:09e0 09 e5 c0 0a 00 c0 09 f0 66 70 75 74 73 2d 31 00
/epush16 09f1 00
\epush16 09f2
/esmove 09f9 00
\esmove 09fa
?auto_err 09fe
:09f0 d4 00 00 09 e8 d4 00 94 d4 00 00 00 02 c3 00 00
:0a00 c0 0a 0f 32 32 32 32 32 32 32 32 32 32 0a 00 d4
/lpush16 0a10 00
\lpush16 0a11
/epush16 0a15 00
\epush16 0a16
/Cfputs 0a1a 00
\Cfputs 0a1b
/esmove 0a1d 00
\esmove 0a1e
:0a10 00 00 ff fe d4 00 00 0a 03 d4 00 00 d4 00 00 00
?auto_err 0a22
/dpush16 0a25 00
\dpush16 0a26
/epush16 0a28 00
\epush16 0a29
/eq16 0a2d 00
\eq16 0a2e
:0a20 04 c3 00 00 d4 00 00 d4 00 00 ff ff d4 00 00 d4
/dpop16 0a30 00
\dpop16 0a31
:0a30 00 00 9a 52 8a f1 ca 0a 3c c0 0a 57 c0 0a 47 66
/epush16 0a48 00
\epush16 0a49
:0a40 70 75 74 73 2d 32 00 d4 00 00 0a 3f d4 00 94 d4
/esmove 0a50 00
\esmove 0a51
?auto_err 0a55
:0a50 00 00 00 02 c3 00 00 c0 0a 66 33 33 33 33 33 33
/lpush16 0a67 00
\lpush16 0a68
/epush16 0a6c 00
\epush16 0a6d
:0a60 33 33 33 33 0a 00 d4 00 00 ff fe d4 00 00 0a 5a
/Cfputs 0a71 00
\Cfputs 0a72
/esmove 0a74 00
\esmove 0a75
?auto_err 0a79
/dpush16 0a7c 00
\dpush16 0a7d
/epush16 0a7f 00
:0a70 d4 00 00 d4 00 00 00 04 c3 00 00 d4 00 00 d4 00
\epush16 0a80
/eq16 0a84 00
\eq16 0a85
/dpop16 0a87 00
\dpop16 0a88
:0a80 00 ff ff d4 00 00 d4 00 00 9a 52 8a f1 ca 0a 93
/epush16 0a9f 00
:0a90 c0 0a ae c0 0a 9e 66 70 75 74 73 2d 33 00 d4 00
\epush16 0aa0
/esmove 0aa7 00
\esmove 0aa8
?auto_err 0aac
:0aa0 00 0a 96 d4 00 94 d4 00 00 00 02 c3 00 00 c0 0a
/lpush16 0abe 00
\lpush16 0abf
:0ab0 bd 34 34 34 34 34 34 34 34 34 34 0a 00 d4 00 00
/epush16 0ac3 00
\epush16 0ac4
/Cfputs 0ac8 00
\Cfputs 0ac9
/esmove 0acb 00
\esmove 0acc
:0ac0 ff fe d4 00 00 0a b1 d4 00 00 d4 00 00 00 04 c3
?auto_err 0ad0
/dpush16 0ad3 00
\dpush16 0ad4
/epush16 0ad6 00
\epush16 0ad7
/eq16 0adb 00
\eq16 0adc
/dpop16 0ade 00
\dpop16 0adf
:0ad0 00 00 d4 00 00 d4 00 00 ff ff d4 00 00 d4 00 00
:0ae0 9a 52 8a f1 ca 0a ea c0 0b 05 c0 0a f5 66 70 75
/epush16 0af6 00
\epush16 0af7
/esmove 0afe 00
\esmove 0aff
:0af0 74 73 2d 34 00 d4 00 00 0a ed d4 00 94 d4 00 00
?auto_err 0b03
:0b00 00 02 c3 00 00 c0 0b 14 35 35 35 35 35 35 35 35
/lpush16 0b15 00
\lpush16 0b16
/epush16 0b1a 00
\epush16 0b1b
/Cfputs 0b1f 00
:0b10 35 35 0a 00 d4 00 00 ff fe d4 00 00 0b 08 d4 00
\Cfputs 0b20
/esmove 0b22 00
\esmove 0b23
?auto_err 0b27
/dpush16 0b2a 00
\dpush16 0b2b
/epush16 0b2d 00
\epush16 0b2e
:0b20 00 d4 00 00 00 04 c3 00 00 d4 00 00 d4 00 00 ff
/eq16 0b32 00
\eq16 0b33
/dpop16 0b35 00
\dpop16 0b36
:0b30 ff d4 00 00 d4 00 00 9a 52 8a f1 ca 0b 41 c0 0b
/epush16 0b4d 00
\epush16 0b4e
:0b40 5c c0 0b 4c 66 70 75 74 73 2d 35 00 d4 00 00 0b
/esmove 0b55 00
\esmove 0b56
?auto_err 0b5a
/lpush16 0b5d 00
\lpush16 0b5e
:0b50 44 d4 00 94 d4 00 00 00 02 c3 00 00 d4 00 00 ff
/Cfileno 0b62 00
\Cfileno 0b63
/esmove 0b65 00
\esmove 0b66
?auto_err 0b6a
/dpush16 0b6d 00
\dpush16 0b6e
:0b60 fe d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4
/lstor16 0b70 00
\lstor16 0b71
/dpop16 0b75 00
\dpop16 0b76
:0b70 00 00 ff f6 d4 00 00 c0 0b 81 66 63 6c 6f 73 65
/epush16 0b82 00
\epush16 0b83
/esmove 0b8a 00
\esmove 0b8b
?auto_err 0b8f
:0b80 00 d4 00 00 0b 7a d4 00 e4 d4 00 00 00 02 c3 00
/lpush16 0b92 00
\lpush16 0b93
/Cfclose 0b97 00
\Cfclose 0b98
/esmove 0b9a 00
\esmove 0b9b
?auto_err 0b9f
:0b90 00 d4 00 00 ff fe d4 00 00 d4 00 00 00 02 c3 00
/dpush16 0ba2 00
\dpush16 0ba3
/dpop16 0ba5 00
\dpop16 0ba6
:0ba0 00 d4 00 00 d4 00 00 9a 52 8a f1 c2 0b ca c0 0b
/epush16 0bbb 00
\epush16 0bbc
:0bb0 ba 66 63 6c 6f 73 65 2d 31 00 d4 00 00 0b b1 d4
/esmove 0bc3 00
\esmove 0bc4
?auto_err 0bc8
/lpush16 0bcb 00
\lpush16 0bcc
:0bc0 00 94 d4 00 00 00 02 c3 00 00 d4 00 00 ff f6 d4
/Cclose 0bd0 00
\Cclose 0bd1
/esmove 0bd3 00
\esmove 0bd4
?auto_err 0bd8
/dpush16 0bdb 00
\dpush16 0bdc
/epush16 0bde 00
\epush16 0bdf
:0bd0 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00 00
/eq16 0be3 00
\eq16 0be4
/dpop16 0be6 00
\dpop16 0be7
:0be0 00 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 0b f2 c0
/epush16 0bff 00
:0bf0 0c 0e c0 0b fe 66 63 6c 6f 73 65 2d 32 00 d4 00
\epush16 0c00
/esmove 0c07 00
\esmove 0c08
?auto_err 0c0c
:0c00 00 0b f5 d4 00 94 d4 00 00 00 02 c3 00 00 c0 0c
:0c10 1c 66 74 65 73 74 33 2e 74 6d 70 00 c0 0c 21 72
/epush16 0c22 00
\epush16 0c23
/epush16 0c27 00
\epush16 0c28
/Cfopen 0c2c 00
\Cfopen 0c2d
/esmove 0c2f 00
:0c20 00 d4 00 00 0c 1f d4 00 00 0c 11 d4 00 00 d4 00
\esmove 0c30
?auto_err 0c34
/dpush16 0c37 00
\dpush16 0c38
/lstor16 0c3a 00
\lstor16 0c3b
/epush16 0c3f 00
:0c30 00 00 04 c3 00 00 d4 00 00 d4 00 00 ff fe d4 00
\epush16 0c40
/eq16 0c44 00
\eq16 0c45
/dpop16 0c47 00
\dpop16 0c48
:0c40 00 00 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 0c 53
/epush16 0c5f 00
:0c50 c0 0c 8c c0 0c 5e 73 74 64 69 6f 2d 33 00 d4 00
\epush16 0c60
/Cperror 0c64 00
\Cperror 0c65
/esmove 0c67 00
\esmove 0c68
?auto_err 0c6c
:0c60 00 0c 56 d4 00 00 d4 00 00 00 02 c3 00 00 c0 0c
/epush16 0c7a 00
\epush16 0c7b
:0c70 79 66 6f 70 65 6e 2d 33 00 d4 00 00 0c 71 d4 00
/esmove 0c82 00
\esmove 0c83
?auto_err 0c87
:0c80 94 d4 00 00 00 02 c3 00 00 c0 0e 5a c0 0c 95 66
/epush16 0c96 00
\epush16 0c97
/esmove 0c9e 00
\esmove 0c9f
:0c90 67 65 74 73 00 d4 00 00 0c 8f d4 00 e4 d4 00 00
?auto_err 0ca3
/lpush16 0ca6 00
\lpush16 0ca7
/epush16 0cab 00
\epush16 0cac
:0ca0 00 02 c3 00 00 d4 00 00 ff fe d4 00 00 00 50 d4
/epush16 0cb0 00
\epush16 0cb1
/Cfgets 0cb5 00
\Cfgets 0cb6
/esmove 0cb8 00
\esmove 0cb9
?auto_err 0cbd
:0cb0 00 00 00 00 d4 00 00 d4 00 00 00 06 c3 00 00 d4
/epush16 0cc0 00
\epush16 0cc1
/lstor16 0cc5 00
\lstor16 0cc6
/dpop16 0cca 00
\dpop16 0ccb
/epush16 0ccd 00
\epush16 0cce
:0cc0 00 00 00 31 d4 00 00 ff fc d4 00 00 d4 00 00 00
/lstor16 0cd2 00
\lstor16 0cd3
/dpop16 0cd7 00
\dpop16 0cd8
/lpush16 0cda 00
\lpush16 0cdb
/Cfeof 0cdf 00
:0cd0 01 d4 00 00 ff f8 d4 00 00 d4 00 00 ff fe d4 00
\Cfeof 0ce0
/esmove 0ce2 00
\esmove 0ce3
?auto_err 0ce7
/dpush16 0cea 00
\dpush16 0ceb
/not16 0ced 00
\not16 0cee
:0ce0 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00 00 d4
/dget16 0cf0 00
\dget16 0cf1
/dpop16 0cfa 00
\dpop16 0cfb
/lpush16 0cfd 00
\lpush16 0cfe
:0cf0 00 00 9a 52 8a f1 c2 0d 01 d4 00 00 d4 00 00 ff
/dpop16 0d02 00
\dpop16 0d03
/epush16 0d0c 00
\epush16 0d0d
:0d00 f8 d4 00 00 9a 52 8a f1 c2 0d c2 d4 00 00 00 00
/lstor16 0d11 00
\lstor16 0d12
/dpop16 0d16 00
\dpop16 0d17
/lpush16 0d19 00
\lpush16 0d1a
/epush16 0d1e 00
\epush16 0d1f
:0d10 d4 00 00 ff fa d4 00 00 d4 00 00 ff fa d4 00 00
/lt16 0d23 00
\lt16 0d24
/dpop16 0d26 00
\dpop16 0d27
:0d20 00 0a d4 00 00 d4 00 00 9a 52 8a f1 ca 0d 32 c0
/lpush16 0d36 00
\lpush16 0d37
/linc16 0d3b 00
\linc16 0d3c
:0d30 0d 98 c0 0d 45 d4 00 00 ff fa d4 00 00 ff fa d4
/dpop16 0d40 00
\dpop16 0d41
/epush16 0d46 00
\epush16 0d47
/lpush16 0d4b 00
\lpush16 0d4c
:0d40 00 00 c0 0d 18 d4 00 00 00 00 d4 00 00 ff fa d4
/add16 0d50 00
\add16 0d51
/deref8 0d53 00
\deref8 0d54
/lpush16 0d56 00
\lpush16 0d57
/ne16 0d5b 00
\ne16 0d5c
/dpop16 0d5e 00
\dpop16 0d5f
:0d50 00 00 d4 00 00 d4 00 00 ff fc d4 00 00 d4 00 00
:0d60 9a 52 8a f1 ca 0d 6a c0 0d 95 c0 0d 75 66 67 65
/epush16 0d76 00
\epush16 0d77
/esmove 0d7e 00
\esmove 0d7f
:0d70 74 73 2d 31 00 d4 00 00 0d 6d d4 00 94 d4 00 00
?auto_err 0d83
/epush16 0d86 00
\epush16 0d87
/lstor16 0d8b 00
\lstor16 0d8c
:0d80 00 02 c3 00 00 d4 00 00 00 00 d4 00 00 ff f8 d4
/dpop16 0d90 00
\dpop16 0d91
/lpush16 0d99 00
\lpush16 0d9a
/linc16 0d9e 00
\linc16 0d9f
:0d90 00 00 c0 0d 98 c0 0d 35 d4 00 00 ff fc d4 00 00
/dpop16 0da3 00
\dpop16 0da4
/lpush16 0da6 00
\lpush16 0da7
/epush16 0dab 00
\epush16 0dac
:0da0 ff fc d4 00 00 d4 00 00 ff fe d4 00 00 00 50 d4
/epush16 0db0 00
\epush16 0db1
/Cfgets 0db5 00
\Cfgets 0db6
/esmove 0db8 00
\esmove 0db9
?auto_err 0dbd
:0db0 00 00 00 00 d4 00 00 d4 00 00 00 06 c3 00 00 c0
/lpush16 0dc3 00
\lpush16 0dc4
/Cfileno 0dc8 00
\Cfileno 0dc9
/esmove 0dcb 00
\esmove 0dcc
:0dc0 0c d9 d4 00 00 ff fe d4 00 00 d4 00 00 00 02 c3
?auto_err 0dd0
/dpush16 0dd3 00
\dpush16 0dd4
/lstor16 0dd6 00
\lstor16 0dd7
/dpop16 0ddb 00
\dpop16 0ddc
/lpush16 0dde 00
\lpush16 0ddf
:0dd0 00 00 d4 00 00 d4 00 00 ff f6 d4 00 00 d4 00 00
/Cfclose 0de3 00
\Cfclose 0de4
/esmove 0de6 00
\esmove 0de7
?auto_err 0deb
/dpush16 0dee 00
\dpush16 0def
:0de0 ff fe d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00
/dpop16 0df1 00
\dpop16 0df2
:0df0 d4 00 00 9a 52 8a f1 c2 0e 16 c0 0e 06 66 63 6c
/epush16 0e07 00
\epush16 0e08
/esmove 0e0f 00
:0e00 6f 73 65 2d 33 00 d4 00 00 0d fd d4 00 94 d4 00
\esmove 0e10
?auto_err 0e14
/lpush16 0e17 00
\lpush16 0e18
/Cclose 0e1c 00
\Cclose 0e1d
/esmove 0e1f 00
:0e10 00 00 02 c3 00 00 d4 00 00 ff f6 d4 00 00 d4 00
\esmove 0e20
?auto_err 0e24
/dpush16 0e27 00
\dpush16 0e28
/epush16 0e2a 00
\epush16 0e2b
/eq16 0e2f 00
:0e20 00 00 02 c3 00 00 d4 00 00 d4 00 00 00 00 d4 00
\eq16 0e30
/dpop16 0e32 00
\dpop16 0e33
:0e30 00 d4 00 00 9a 52 8a f1 ca 0e 3e c0 0e 5a c0 0e
/epush16 0e4b 00
\epush16 0e4c
:0e40 4a 66 63 6c 6f 73 65 2d 34 00 d4 00 00 0e 41 d4
/esmove 0e53 00
\esmove 0e54
?auto_err 0e58
:0e50 00 94 d4 00 00 00 02 c3 00 00 c0 0e 68 66 74 65
/epush16 0e69 00
\epush16 0e6a
/Cunlink 0e6e 00
\Cunlink 0e6f
:0e60 73 74 33 2e 74 6d 70 00 d4 00 00 0e 5d d4 00 00
/esmove 0e71 00
\esmove 0e72
?auto_err 0e76
/esmove 0e79 00
\esmove 0e7a
?auto_err 0e7e
:0e70 d4 00 00 00 02 c3 00 00 d4 00 00 00 0a c3 00 00
/escheck 0e82 00
\escheck 0e83
=Cmain 0e8a
:0e80 e2 d4 00 00 60 72 ab f0 bb d5 e2 9b 73 8b 73 87
/vpush16 0e9a 00
\vpush16 0e9b
/dpop16 0e9f 00
:0e90 ab 97 bb d4 01 13 d4 07 fa d4 00 00 00 92 d4 00
\dpop16 0ea0
/escheck 0ea3 00
\escheck 0ea4
:0ea0 00 e2 d4 00 00 60 72 ab f0 bb d5
+009e
+00b3
+00c3
+00c8
+00d5
+00ee
+00fc
+0125
+0131
^0134 e4
v0135
+013f
+014c
+0153
+0158
+0185
+0188
+018b
+0198
^019b 94
v019c
+01a6
+01b2
+01d0
+01df
+01ff
+0202
+0205
+0213
^0216 94
v0217
+0221
+0230
+0250
+0253
+0256
+0264
^0267 94
v0268
+0272
+027e
^0281 e4
v0282
+028c
+0299
+02a9
+02ae
+02ce
+02d1
+02d4
+02e2
^02e5 94
v02e6
+02f0
+02fd
+0304
+0309
+0336
+0339
+033c
+0349
^034c 94
v034d
+0357
+0363
+0381
+038e
+039e
+03a3
+03c3
+03c6
+03c9
+03d7
^03da 94
v03db
+03e5
+03f2
+0402
+0407
+0427
+042a
+042d
+043b
^043e 94
v043f
+0449
+0459
+0467
+0474
^0477 e4
v0478
+049c
+049f
+04a2
+04b1
^04b4 94
v04b5
+04bf
+04cc
+04da
+04e9
+0508
+0528
+052b
+052e
+053d
^0540 94
v0541
+056c
+058c
+058f
+0592
+05a1
^05a4 94
v05a5
+05af
+05ce
+05d3
+0603
+0606
+0609
+0618
^061b 94
v061c
+0626
+062d
+0632
+0652
+0655
+0658
+0667
^066a 94
v066b
+0675
+0681
^0684 e4
v0685
+0691
+06b1
+06b4
+06b7
+06c5
^06c8 94
v06c9
+06d3
+06da
+06df
+070c
+070f
+0712
+071f
^0722 94
v0723
+072d
+0739
+0759
+0779
+077c
+077f
+078d
^0790 94
v0791
+079d
+07a2
+07ba
+07bd
+07cb
^07ce 94
v07cf
+07db
+080c
+0817
^081a e4
v081b
+0825
+0833
+083b
+0840
+0865
+0868
+086b
+0878
+0886
+0893
^0896 94
v0897
+08a1
+08a4
+08ae
^08b1 e4
v08b2
+08e6
+08e9
+08f5
^08f8 94
v08f9
+0913
+0921
+0928
+092d
+0952
+0955
+0958
+0965
+0973
+0980
^0983 94
v0984
+098e
+0991
+099c
^099f e4
v09a0
+09aa
+09c0
+09e0
+09e3
+09e6
+09f3
^09f6 94
v09f7
+0a01
+0a17
+0a37
+0a3a
+0a3d
+0a4a
^0a4d 94
v0a4e
+0a58
+0a6e
+0a8e
+0a91
+0a94
+0aa1
^0aa4 94
v0aa5
+0aaf
+0ac5
+0ae5
+0ae8
+0aeb
+0af8
^0afb 94
v0afc
+0b06
+0b1c
+0b3c
+0b3f
+0b42
+0b4f
^0b52 94
v0b53
+0b78
+0b84
^0b87 e4
v0b88
+0bac
+0baf
+0bbd
^0bc0 94
v0bc1
+0bed
+0bf0
+0bf3
+0c01
^0c04 94
v0c05
+0c0f
+0c1d
+0c24
+0c29
+0c4e
+0c51
+0c54
+0c61
+0c6f
+0c7c
^0c7f 94
v0c80
+0c8a
+0c8d
+0c98
^0c9b e4
v0c9c
+0cb2
+0cf7
+0d09
+0d2d
+0d30
+0d33
+0d43
+0d48
+0d65
+0d68
+0d6b
+0d78
^0d7b 94
v0d7c
+0d93
+0d96
+0db2
+0dc0
+0df8
+0dfb
+0e09
^0e0c 94
v0e0d
+0e39
+0e3c
+0e3f
+0e4d
^0e50 94
v0e51
+0e5b
+0e6b
^0e94 13
v0e95
^0e97 fa
v0e98
+0e9c
}
