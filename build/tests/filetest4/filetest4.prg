.big
{filetest4
.library string.lib
=CErrors 0000
=Cresult 0002
=Cs1 0004
:0000 00 00 00 00
>0050
=Cs2 0054
>0050
:00a4 30 2d 2d 2d 7c 2d 2d 2d 2d 31 2d 2d 2d 2d 7c 2d
:00b4 2d 2d 2d 32 2d 2d 2d 2d 7c 2d 2d 2d 2d 33 2d 2d
:00c4 2d 2d 7c 2d 2d 2d 2d 34 2d 2d 2d 2d 7c 2d 2d 2d
=Cstr1 00a4
:00d4 2d 35 0a 00 43 43 43 43 43 43 43 43 43 43 43 43
:00e4 43 43 43 43 43 43 43 43 43 43 43 43 43 43 43 43
:00f4 43 43 43 43 43 43 43 43 43 43 43 43 43 43 43 43
=Cstr2 00d8
:0104 43 43 43 43 43 43 0a 00 44 44 44 44 44 44 44 44
:0114 44 44 44 44 44 44 44 44 44 44 44 44 44 44 44 44
=Cstr3 010c
:0124 00 45 45 45 45 45 45 45 45 45 45 45 45 45 45 45
=Cstr4 0125
:0134 45 45 45 45 45 45 45 45 45 00 25 25 25 25 25 25
=Cstr5 013e
=Cfail 0153
:0144 25 25 25 25 25 25 25 25 25 25 25 25 25 25 00 e2
:0154 9b 73 8b 73 87 ab 97 bb c0 01 6a 25 73 20 66 61
/lpush16 016b 00
\lpush16 016c
/epush16 0170 00
\epush16 0171
:0164 69 6c 65 64 0a 00 d4 00 00 00 00 d4 00 00 01 5f
/Cprintf 0175 00
\Cprintf 0176
/esmove 0178 00
\esmove 0179
?auto_err 017d
/vpush16 0180 00
\vpush16 0181
:0174 d4 00 00 d4 00 00 00 04 c3 00 00 d4 00 00 00 00
/vinc16 0185 00
\vinc16 0186
/dpop16 018a 00
\dpop16 018b
/epush16 018d 00
\epush16 018e
/vstor16 0192 00
\vstor16 0193
:0184 d4 00 00 00 00 d4 00 00 d4 00 00 00 01 d4 00 00
/dpop16 0197 00
\dpop16 0198
/escheck 019b 00
\escheck 019c
=Cpr 01a3
:0194 00 02 d4 00 00 e2 d4 00 00 60 72 ab f0 bb d5 e2
:01a4 9b 73 8b 73 87 ab 97 bb c0 01 b3 25 73 0a 00 d4
/lpush16 01b4 00
\lpush16 01b5
/epush16 01b9 00
\epush16 01ba
/Cprintf 01be 00
\Cprintf 01bf
/esmove 01c1 00
\esmove 01c2
:01b4 00 00 00 00 d4 00 00 01 af d4 00 00 d4 00 00 00
?auto_err 01c6
/escheck 01ca 00
\escheck 01cb
=Ctest_sio4 01d2
:01c4 04 c3 00 00 e2 d4 00 00 60 72 ab f0 bb d5 e2 9b
/esmove 01dc 00
\esmove 01dd
?auto_err 01e1
:01d4 73 8b 73 87 ab 97 bb d4 00 00 ff f6 c3 00 00 d4
/epush16 01e4 00
\epush16 01e5
/lstor16 01e9 00
\lstor16 01ea
/lstor16 01ee 00
\lstor16 01ef
/dpop16 01f3 00
:01e4 00 00 00 00 d4 00 00 ff f8 d4 00 00 ff fa d4 00
\dpop16 01f4
/epush16 0201 00
\epush16 0202
:01f4 00 c0 02 00 66 70 72 69 6e 74 66 00 d4 00 00 01
/esmove 0209 00
\esmove 020a
?auto_err 020e
:0204 f8 d4 01 a3 d4 00 00 00 02 c3 00 00 c0 02 1f 66
:0214 70 72 69 6e 74 66 2e 6f 75 74 00 c0 02 24 77 00
/epush16 0225 00
\epush16 0226
/epush16 022a 00
\epush16 022b
/Cfopen 022f 00
\Cfopen 0230
/esmove 0232 00
\esmove 0233
:0224 d4 00 00 02 22 d4 00 00 02 13 d4 00 00 d4 00 00
?auto_err 0237
/dpush16 023a 00
\dpush16 023b
/lstor16 023d 00
\lstor16 023e
/epush16 0242 00
\epush16 0243
:0234 00 04 c3 00 00 d4 00 00 d4 00 00 ff fc d4 00 00
/eq16 0247 00
\eq16 0248
/dpop16 024a 00
\dpop16 024b
:0244 00 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 02 56 c0
/epush16 0262 00
\epush16 0263
:0254 02 74 c0 02 61 66 6f 70 65 6e 2d 31 00 d4 00 00
/esmove 026a 00
\esmove 026b
?auto_err 026f
:0264 02 59 d4 01 53 d4 00 00 00 02 c3 00 00 c0 09 13
:0274 c0 02 8e 57 72 69 74 69 6e 67 20 74 65 73 74 20
/epush16 028f 00
\epush16 0290
:0284 66 69 6c 65 2e 2e 2e 2e 0a 00 d4 00 00 02 77 d4
/Cprintf 0294 00
\Cprintf 0295
/esmove 0297 00
\esmove 0298
?auto_err 029c
/lpush16 029f 00
\lpush16 02a0
:0294 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 ff fc d4
/epush16 02a4 00
\epush16 02a5
/Cfputs 02a9 00
\Cfputs 02aa
/esmove 02ac 00
\esmove 02ad
?auto_err 02b1
:02a4 00 00 00 a4 d4 00 00 d4 00 00 00 04 c3 00 00 d4
/epush16 02b4 00
\epush16 02b5
/lstor16 02b9 00
\lstor16 02ba
/dpop16 02be 00
\dpop16 02bf
/lpush16 02c1 00
\lpush16 02c2
:02b4 00 00 00 00 d4 00 00 ff f6 d4 00 00 d4 00 00 ff
/epush16 02c6 00
\epush16 02c7
/lt16 02cb 00
\lt16 02cc
/dpop16 02ce 00
\dpop16 02cf
:02c4 f6 d4 00 00 00 32 d4 00 00 d4 00 00 9a 52 8a f1
/lpush16 02de 00
\lpush16 02df
/linc16 02e3 00
:02d4 ca 02 da c0 03 05 c0 02 ed d4 00 00 ff f6 d4 00
\linc16 02e4
/dpop16 02e8 00
\dpop16 02e9
/lpush16 02ee 00
\lpush16 02ef
/epush16 02f3 00
:02e4 00 ff f6 d4 00 00 c0 02 c0 d4 00 00 ff fc d4 00
\epush16 02f4
/Cfputc 02f8 00
\Cfputc 02f9
/esmove 02fb 00
\esmove 02fc
?auto_err 0300
:02f4 00 00 41 d4 00 00 d4 00 00 00 04 c3 00 00 c0 02
/lpush16 0306 00
\lpush16 0307
/epush16 030b 00
\epush16 030c
/Cfputc 0310 00
\Cfputc 0311
/esmove 0313 00
:0304 dd d4 00 00 ff fc d4 00 00 00 0a d4 00 00 d4 00
\esmove 0314
?auto_err 0318
/epush16 031b 00
\epush16 031c
/lstor16 0320 00
\lstor16 0321
:0314 00 00 04 c3 00 00 d4 00 00 00 00 d4 00 00 ff f6
/dpop16 0325 00
\dpop16 0326
/lpush16 0328 00
\lpush16 0329
/epush16 032d 00
\epush16 032e
/lt16 0332 00
\lt16 0333
:0324 d4 00 00 d4 00 00 ff f6 d4 00 00 00 32 d4 00 00
/dpop16 0335 00
\dpop16 0336
:0334 d4 00 00 9a 52 8a f1 ca 03 41 c0 03 6c c0 03 54
/lpush16 0345 00
\lpush16 0346
/linc16 034a 00
\linc16 034b
/dpop16 034f 00
\dpop16 0350
:0344 d4 00 00 ff f6 d4 00 00 ff f6 d4 00 00 c0 03 27
/lpush16 0355 00
\lpush16 0356
/epush16 035a 00
\epush16 035b
/Cfputc 035f 00
\Cfputc 0360
/esmove 0362 00
\esmove 0363
:0354 d4 00 00 ff fc d4 00 00 00 42 d4 00 00 d4 00 00
?auto_err 0367
/lpush16 036d 00
\lpush16 036e
/epush16 0372 00
\epush16 0373
:0364 00 04 c3 00 00 c0 03 44 d4 00 00 ff fc d4 00 00
/Cfputc 0377 00
\Cfputc 0378
/esmove 037a 00
\esmove 037b
?auto_err 037f
:0374 00 0a d4 00 00 d4 00 00 00 04 c3 00 00 c0 03 87
/epush16 0388 00
\epush16 0389
/epush16 038d 00
\epush16 038e
/lpush16 0392 00
\lpush16 0393
:0384 25 73 00 d4 00 00 00 d8 d4 00 00 03 84 d4 00 00
/Cfprintf 0397 00
\Cfprintf 0398
/esmove 039a 00
\esmove 039b
?auto_err 039f
:0394 ff fc d4 00 00 d4 00 00 00 06 c3 00 00 c0 03 ac
/epush16 03ad 00
\epush16 03ae
/epush16 03b2 00
\epush16 03b3
:03a4 7c 25 34 38 73 7c 0a 00 d4 00 00 01 0c d4 00 00
/lpush16 03b7 00
\lpush16 03b8
/Cfprintf 03bc 00
\Cfprintf 03bd
/esmove 03bf 00
\esmove 03c0
:03b4 03 a4 d4 00 00 ff fc d4 00 00 d4 00 00 00 06 c3
?auto_err 03c4
/epush16 03d3 00
:03c4 00 00 c0 03 d2 7c 25 2d 34 38 73 7c 0a 00 d4 00
\epush16 03d4
/epush16 03d8 00
\epush16 03d9
/lpush16 03dd 00
\lpush16 03de
/Cfprintf 03e2 00
\Cfprintf 03e3
:03d4 00 01 25 d4 00 00 03 c9 d4 00 00 ff fc d4 00 00
/esmove 03e5 00
\esmove 03e6
?auto_err 03ea
/epush16 03ed 00
\epush16 03ee
/lstor16 03f2 00
\lstor16 03f3
:03e4 d4 00 00 00 06 c3 00 00 d4 00 00 00 00 d4 00 00
/dpop16 03f7 00
\dpop16 03f8
/lpush16 03fa 00
\lpush16 03fb
/epush16 03ff 00
\epush16 0400
:03f4 ff f6 d4 00 00 d4 00 00 ff f6 d4 00 00 00 05 d4
/lt16 0404 00
\lt16 0405
/dpop16 0407 00
\dpop16 0408
:0404 00 00 d4 00 00 9a 52 8a f1 ca 04 13 c0 04 88 c0
/lpush16 0417 00
\lpush16 0418
/linc16 041c 00
\linc16 041d
/dpop16 0421 00
\dpop16 0422
:0414 04 26 d4 00 00 ff f6 d4 00 00 ff f6 d4 00 00 c0
:0424 03 f9 c0 04 3e 25 63 25 63 25 63 25 63 25 63 25
/epush16 043f 00
\epush16 0440
:0434 63 25 63 25 63 25 63 25 63 00 d4 00 00 00 30 d4
/epush16 0444 00
\epush16 0445
/epush16 0449 00
\epush16 044a
/epush16 044e 00
\epush16 044f
/epush16 0453 00
:0444 00 00 00 39 d4 00 00 00 38 d4 00 00 00 37 d4 00
\epush16 0454
/epush16 0458 00
\epush16 0459
/epush16 045d 00
\epush16 045e
/epush16 0462 00
\epush16 0463
:0454 00 00 36 d4 00 00 00 35 d4 00 00 00 34 d4 00 00
/epush16 0467 00
\epush16 0468
/epush16 046c 00
\epush16 046d
/epush16 0471 00
\epush16 0472
:0464 00 33 d4 00 00 00 32 d4 00 00 00 31 d4 00 00 04
/lpush16 0476 00
\lpush16 0477
/Cfprintf 047b 00
\Cfprintf 047c
/esmove 047e 00
\esmove 047f
?auto_err 0483
:0474 29 d4 00 00 ff fc d4 00 00 d4 00 00 00 18 c3 00
/lpush16 048e 00
\lpush16 048f
/epush16 0493 00
:0484 00 c0 04 16 c0 04 8d 0a 00 d4 00 00 ff fc d4 00
\epush16 0494
/Cfputs 0498 00
\Cfputs 0499
/esmove 049b 00
\esmove 049c
?auto_err 04a0
:0494 00 04 8b d4 00 00 d4 00 00 00 04 c3 00 00 c0 04
/epush16 04ac 00
\epush16 04ad
/epush16 04b1 00
\epush16 04b2
:04a4 ab 25 35 30 64 0a 00 d4 00 00 cf c7 d4 00 00 04
/lpush16 04b6 00
\lpush16 04b7
/Cfprintf 04bb 00
\Cfprintf 04bc
/esmove 04be 00
\esmove 04bf
?auto_err 04c3
:04b4 a5 d4 00 00 ff fc d4 00 00 d4 00 00 00 06 c3 00
/epush16 04d1 00
\epush16 04d2
:04c4 00 c0 04 d0 25 2d 34 39 64 7c 0a 00 d4 00 00 cf
/epush16 04d6 00
\epush16 04d7
/lpush16 04db 00
\lpush16 04dc
/Cfprintf 04e0 00
\Cfprintf 04e1
/esmove 04e3 00
:04d4 c7 d4 00 00 04 c8 d4 00 00 ff fc d4 00 00 d4 00
\esmove 04e4
?auto_err 04e8
:04e4 00 00 06 c3 00 00 c0 04 f4 25 30 35 30 64 0a 00
/epush16 04f5 00
\epush16 04f6
/epush16 04fa 00
\epush16 04fb
/lpush16 04ff 00
\lpush16 0500
:04f4 d4 00 00 30 39 d4 00 00 04 ed d4 00 00 ff fc d4
/Cfprintf 0504 00
\Cfprintf 0505
/esmove 0507 00
\esmove 0508
?auto_err 050c
:0504 00 00 d4 00 00 00 06 c3 00 00 c0 05 26 30 78 25
:0514 78 20 25 31 35 73 25 64 25 31 36 73 20 30 25 6f
/epush16 052f 00
\epush16 0530
:0524 0a 00 c0 05 2a 00 c0 05 2e 00 d4 00 00 7b cd d4
/epush16 0534 00
\epush16 0535
/epush16 0539 00
\epush16 053a
/epush16 053e 00
\epush16 053f
/epush16 0543 00
:0534 00 00 05 2d d4 00 00 7b cd d4 00 00 05 29 d4 00
\epush16 0544
/epush16 0548 00
\epush16 0549
/lpush16 054d 00
\lpush16 054e
/Cfprintf 0552 00
\Cfprintf 0553
:0544 00 7b cd d4 00 00 05 11 d4 00 00 ff fc d4 00 00
/esmove 0555 00
\esmove 0556
?auto_err 055a
/epush16 055d 00
\epush16 055e
/lstor16 0562 00
\lstor16 0563
:0554 d4 00 00 00 0e c3 00 00 d4 00 00 00 00 d4 00 00
/dpop16 0567 00
\dpop16 0568
/lpush16 056a 00
\lpush16 056b
/epush16 056f 00
\epush16 0570
:0564 ff f6 d4 00 00 d4 00 00 ff f6 d4 00 00 00 05 d4
/lt16 0574 00
\lt16 0575
/dpop16 0577 00
\dpop16 0578
:0574 00 00 d4 00 00 9a 52 8a f1 ca 05 83 c0 05 ae c0
/lpush16 0587 00
\lpush16 0588
/linc16 058c 00
\linc16 058d
/dpop16 0591 00
\dpop16 0592
:0584 05 96 d4 00 00 ff f6 d4 00 00 ff f6 d4 00 00 c0
/epush16 0597 00
\epush16 0598
/lpush16 059c 00
\lpush16 059d
/Cfprintf 05a1 00
\Cfprintf 05a2
:0594 05 69 d4 00 00 01 3e d4 00 00 ff fc d4 00 00 d4
/esmove 05a4 00
\esmove 05a5
?auto_err 05a9
:05a4 00 00 00 04 c3 00 00 c0 05 86 c0 05 b3 0a 00 d4
/lpush16 05b4 00
\lpush16 05b5
/epush16 05b9 00
\epush16 05ba
/Cfputs 05be 00
\Cfputs 05bf
/esmove 05c1 00
\esmove 05c2
:05b4 00 00 ff fc d4 00 00 05 b1 d4 00 00 d4 00 00 00
?auto_err 05c6
/lpush16 05c9 00
\lpush16 05ca
/epush16 05ce 00
\epush16 05cf
/Cfputs 05d3 00
:05c4 04 c3 00 00 d4 00 00 ff fc d4 00 00 00 a4 d4 00
\Cfputs 05d4
/esmove 05d6 00
\esmove 05d7
?auto_err 05db
/lpush16 05de 00
\lpush16 05df
/Cfclose 05e3 00
:05d4 00 d4 00 00 00 04 c3 00 00 d4 00 00 ff fc d4 00
\Cfclose 05e4
/esmove 05e6 00
\esmove 05e7
?auto_err 05eb
:05e4 00 d4 00 00 00 02 c3 00 00 c0 05 f9 73 74 64 69
/epush16 05ff 00
\epush16 0600
:05f4 6f 2e 6f 6b 00 c0 05 fe 72 00 d4 00 00 05 fc d4
/epush16 0604 00
\epush16 0605
/Cfopen 0609 00
\Cfopen 060a
/esmove 060c 00
\esmove 060d
?auto_err 0611
:0604 00 00 05 f0 d4 00 00 d4 00 00 00 04 c3 00 00 d4
/dpush16 0614 00
\dpush16 0615
/lstor16 0617 00
\lstor16 0618
/epush16 061c 00
\epush16 061d
/eq16 0621 00
\eq16 0622
:0614 00 00 d4 00 00 ff fc d4 00 00 00 00 d4 00 00 d4
/dpop16 0624 00
\dpop16 0625
:0624 00 00 9a 52 8a f1 ca 06 30 c0 06 70 c0 06 4b 6d
:0634 69 73 73 69 6e 67 20 66 69 6c 65 3a 20 73 74 64
/vpush16 064c 00
\vpush16 064d
?Cstdout 064e
/epush16 0651 00
\epush16 0652
:0644 69 6f 2e 6f 6b 0a 00 d4 00 00 00 00 d4 00 00 06
/Cfputs 0656 00
\Cfputs 0657
/esmove 0659 00
\esmove 065a
?auto_err 065e
/vpush16 0661 00
\vpush16 0662
:0654 33 d4 00 00 d4 00 00 00 04 c3 00 00 d4 00 00 00
/vinc16 0666 00
\vinc16 0667
/dpop16 066b 00
\dpop16 066c
:0664 00 d4 00 00 00 00 d4 00 00 c0 08 d9 c0 06 7f 66
:0674 70 72 69 6e 74 66 2e 6f 75 74 00 c0 06 84 72 00
/epush16 0685 00
\epush16 0686
/epush16 068a 00
\epush16 068b
/Cfopen 068f 00
\Cfopen 0690
/esmove 0692 00
\esmove 0693
:0684 d4 00 00 06 82 d4 00 00 06 73 d4 00 00 d4 00 00
?auto_err 0697
/dpush16 069a 00
\dpush16 069b
/lstor16 069d 00
\lstor16 069e
/epush16 06a2 00
\epush16 06a3
:0694 00 04 c3 00 00 d4 00 00 d4 00 00 ff fe d4 00 00
/eq16 06a7 00
\eq16 06a8
/dpop16 06aa 00
\dpop16 06ab
:06a4 00 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 06 b6 c0
:06b4 07 05 c0 06 e0 63 6f 75 6c 64 20 6e 6f 74 20 6f
:06c4 70 65 6e 20 74 65 73 74 20 66 69 6c 65 3a 20 66
/vpush16 06e1 00
\vpush16 06e2
?Cstdout 06e3
:06d4 70 72 69 6e 74 66 2e 6f 75 74 0a 00 d4 00 00 00
/epush16 06e6 00
\epush16 06e7
/Cfputs 06eb 00
\Cfputs 06ec
/esmove 06ee 00
\esmove 06ef
?auto_err 06f3
:06e4 00 d4 00 00 06 b9 d4 00 00 d4 00 00 00 04 c3 00
/vpush16 06f6 00
\vpush16 06f7
/vinc16 06fb 00
\vinc16 06fc
/dpop16 0700 00
\dpop16 0701
:06f4 00 d4 00 00 00 00 d4 00 00 00 00 d4 00 00 c0 08
:0704 d9 c0 07 18 63 6f 6d 70 61 72 69 6e 67 20 6c 69
/epush16 0719 00
\epush16 071a
/Cputs 071e 00
\Cputs 071f
/esmove 0721 00
\esmove 0722
:0714 6e 65 73 00 d4 00 00 07 08 d4 00 00 d4 00 00 00
?auto_err 0726
/lpush16 0729 00
\lpush16 072a
/epush16 072e 00
\epush16 072f
/epush16 0733 00
:0724 02 c3 00 00 d4 00 00 ff fe d4 00 00 00 50 d4 00
\epush16 0734
/Cfgets 0738 00
\Cfgets 0739
/esmove 073b 00
\esmove 073c
?auto_err 0740
:0734 00 00 04 d4 00 00 d4 00 00 00 06 c3 00 00 c0 07
/linc16 0749 00
\linc16 074a
/lpush16 074e 00
\lpush16 074f
/dpop16 0753 00
:0744 48 c0 07 42 d4 00 00 ff f8 d4 00 00 ff f8 d4 00
\dpop16 0754
/lpush16 0756 00
\lpush16 0757
/epush16 075b 00
\epush16 075c
/epush16 0760 00
\epush16 0761
:0754 00 d4 00 00 ff fc d4 00 00 00 50 d4 00 00 00 54
/Cfgets 0765 00
\Cfgets 0766
/esmove 0768 00
\esmove 0769
?auto_err 076d
/lpush16 0770 00
\lpush16 0771
:0764 d4 00 00 d4 00 00 00 06 c3 00 00 d4 00 00 ff fe
/Cfeof 0775 00
\Cfeof 0776
/esmove 0778 00
\esmove 0779
?auto_err 077d
/dpush16 0780 00
\dpush16 0781
/dpop16 0783 00
:0774 d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00
\dpop16 0784
/lpush16 0790 00
\lpush16 0791
:0784 00 9a 52 8a f1 c2 07 8f c0 08 4b d4 00 00 ff fc
/Cfeof 0795 00
\Cfeof 0796
/esmove 0798 00
\esmove 0799
?auto_err 079d
/dpush16 07a0 00
\dpush16 07a1
/dpop16 07a3 00
:0794 d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00
\dpop16 07a4
/epush16 07b0 00
\epush16 07b1
:07a4 00 9a 52 8a f1 c2 07 af c0 08 4b d4 00 00 00 32
/epush16 07b5 00
\epush16 07b6
/epush16 07ba 00
\epush16 07bb
/Cmemcmp 07bf 00
\Cmemcmp 07c0
/esmove 07c2 00
\esmove 07c3
:07b4 d4 00 00 00 54 d4 00 00 00 04 d4 00 00 d4 00 00
?auto_err 07c7
/dpush16 07ca 00
\dpush16 07cb
/dpop16 07cd 00
\dpop16 07ce
:07c4 00 06 c3 00 00 d4 00 00 d4 00 00 9a 52 8a f1 c2
/linc16 07d7 00
\linc16 07d8
/lpush16 07dc 00
\lpush16 07dd
/dpop16 07e1 00
\dpop16 07e2
:07d4 08 09 d4 00 00 ff fa d4 00 00 ff fa d4 00 00 c0
/lpush16 07f2 00
\lpush16 07f3
:07e4 07 f1 25 32 64 20 45 72 72 6f 72 0a 00 d4 00 00
/epush16 07f7 00
\epush16 07f8
/Cprintf 07fc 00
\Cprintf 07fd
/esmove 07ff 00
\esmove 0800
:07f4 ff f8 d4 00 00 07 e6 d4 00 00 d4 00 00 00 04 c3
?auto_err 0804
:0804 00 00 c0 08 2e c0 08 14 25 32 64 3a 20 25 73 00
/epush16 0815 00
\epush16 0816
/lpush16 081a 00
\lpush16 081b
/epush16 081f 00
\epush16 0820
:0814 d4 00 00 00 04 d4 00 00 ff f8 d4 00 00 08 0c d4
/Cprintf 0824 00
\Cprintf 0825
/esmove 0827 00
\esmove 0828
?auto_err 082c
/lpush16 082f 00
\lpush16 0830
:0824 00 00 d4 00 00 00 06 c3 00 00 d4 00 00 ff fe d4
/epush16 0834 00
\epush16 0835
/epush16 0839 00
\epush16 083a
/Cfgets 083e 00
\Cfgets 083f
/esmove 0841 00
\esmove 0842
:0834 00 00 00 50 d4 00 00 00 04 d4 00 00 d4 00 00 00
?auto_err 0846
/lpush16 084c 00
\lpush16 084d
/Cfeof 0851 00
\Cfeof 0852
:0844 06 c3 00 00 c0 07 45 d4 00 00 ff fe d4 00 00 d4
/esmove 0854 00
\esmove 0855
?auto_err 0859
/dpush16 085c 00
\dpush16 085d
/not16 085f 00
\not16 0860
/dget16 0862 00
\dget16 0863
:0854 00 00 00 02 c3 00 00 d4 00 00 d4 00 00 d4 00 00
/dpop16 086c 00
\dpop16 086d
/lpush16 086f 00
\lpush16 0870
:0864 9a 52 8a f1 ca 08 84 d4 00 00 d4 00 00 ff fc d4
/Cfeof 0874 00
\Cfeof 0875
/esmove 0877 00
\esmove 0878
?auto_err 087c
/dpush16 087f 00
\dpush16 0880
/not16 0882 00
\not16 0883
:0874 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00 00
/dpop16 0885 00
\dpop16 0886
:0884 d4 00 00 9a 52 8a f1 c2 08 c9 c0 08 ac 66 69 6c
:0894 65 73 20 68 61 76 65 20 64 69 66 66 65 72 65 6e
/epush16 08ad 00
\epush16 08ae
/Cputs 08b2 00
\Cputs 08b3
:08a4 74 20 73 69 7a 65 73 00 d4 00 00 08 91 d4 00 00
/esmove 08b5 00
\esmove 08b6
?auto_err 08ba
/linc16 08bd 00
\linc16 08be
/lpush16 08c2 00
\lpush16 08c3
:08b4 d4 00 00 00 02 c3 00 00 d4 00 00 ff fa d4 00 00
/dpop16 08c7 00
\dpop16 08c8
/lpush16 08ca 00
\lpush16 08cb
/Cfclose 08cf 00
\Cfclose 08d0
/esmove 08d2 00
\esmove 08d3
:08c4 ff fa d4 00 00 d4 00 00 ff fe d4 00 00 d4 00 00
?auto_err 08d7
/lpush16 08da 00
\lpush16 08db
/Cfclose 08df 00
\Cfclose 08e0
/esmove 08e2 00
\esmove 08e3
:08d4 00 02 c3 00 00 d4 00 00 ff fc d4 00 00 d4 00 00
?auto_err 08e7
/lpush16 08ea 00
\lpush16 08eb
/dpop16 08ef 00
\dpop16 08f0
:08e4 00 02 c3 00 00 d4 00 00 ff fa d4 00 00 9a 52 8a
:08f4 f1 c2 09 13 c0 09 03 66 70 72 69 6e 74 66 00 d4
/epush16 0904 00
\epush16 0905
/esmove 090c 00
\esmove 090d
?auto_err 0911
:0904 00 00 08 fb d4 01 53 d4 00 00 00 02 c3 00 00 d4
/esmove 0914 00
\esmove 0915
?auto_err 0919
/escheck 091d 00
\escheck 091e
:0914 00 00 00 0a c3 00 00 e2 d4 00 00 60 72 ab f0 bb
=Ctest_printf 0925
/esmove 092f 00
\esmove 0930
:0924 d5 e2 9b 73 8b 73 87 ab 97 bb d4 00 00 ff fe c3
?auto_err 0934
/epush16 0941 00
\epush16 0942
:0934 00 00 c0 09 40 70 72 69 6e 74 66 00 d4 00 00 09
/esmove 0949 00
\esmove 094a
?auto_err 094e
/epush16 0951 00
\epush16 0952
:0944 39 d4 01 a3 d4 00 00 00 02 c3 00 00 d4 00 00 00
/Cputs 0956 00
\Cputs 0957
/esmove 0959 00
\esmove 095a
?auto_err 095e
/epush16 0961 00
\epush16 0962
:0954 a4 d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 00
/lstor16 0966 00
\lstor16 0967
/dpop16 096b 00
\dpop16 096c
/lpush16 096e 00
\lpush16 096f
/epush16 0973 00
:0964 00 d4 00 00 ff fe d4 00 00 d4 00 00 ff fe d4 00
\epush16 0974
/lt16 0978 00
\lt16 0979
/dpop16 097b 00
\dpop16 097c
:0974 00 00 32 d4 00 00 d4 00 00 9a 52 8a f1 ca 09 87
/lpush16 098b 00
\lpush16 098c
/linc16 0990 00
\linc16 0991
:0984 c0 09 b2 c0 09 9a d4 00 00 ff fe d4 00 00 ff fe
/dpop16 0995 00
\dpop16 0996
/vpush16 099b 00
\vpush16 099c
?Cstdout 099d
/epush16 09a0 00
\epush16 09a1
:0994 d4 00 00 c0 09 6d d4 00 00 00 00 d4 00 00 00 41
/Cfputc 09a5 00
\Cfputc 09a6
/esmove 09a8 00
\esmove 09a9
?auto_err 09ad
:09a4 d4 00 00 d4 00 00 00 04 c3 00 00 c0 09 8a c0 09
/epush16 09b7 00
\epush16 09b8
/Cputs 09bc 00
\Cputs 09bd
/esmove 09bf 00
\esmove 09c0
:09b4 b6 00 d4 00 00 09 b5 d4 00 00 d4 00 00 00 02 c3
?auto_err 09c4
/epush16 09c7 00
\epush16 09c8
/lstor16 09cc 00
\lstor16 09cd
/dpop16 09d1 00
\dpop16 09d2
:09c4 00 00 d4 00 00 00 00 d4 00 00 ff fe d4 00 00 d4
/lpush16 09d4 00
\lpush16 09d5
/epush16 09d9 00
\epush16 09da
/lt16 09de 00
\lt16 09df
/dpop16 09e1 00
\dpop16 09e2
:09d4 00 00 ff fe d4 00 00 00 32 d4 00 00 d4 00 00 9a
/lpush16 09f1 00
\lpush16 09f2
:09e4 52 8a f1 ca 09 ed c0 0a 13 c0 0a 00 d4 00 00 ff
/linc16 09f6 00
\linc16 09f7
/dpop16 09fb 00
\dpop16 09fc
/epush16 0a01 00
\epush16 0a02
:09f4 fe d4 00 00 ff fe d4 00 00 c0 09 d3 d4 00 00 00
/Cputchar 0a06 00
\Cputchar 0a07
/esmove 0a09 00
\esmove 0a0a
?auto_err 0a0e
:0a04 42 d4 00 00 d4 00 00 00 02 c3 00 00 c0 09 f0 c0
/epush16 0a18 00
\epush16 0a19
/Cputs 0a1d 00
\Cputs 0a1e
/esmove 0a20 00
\esmove 0a21
:0a14 0a 17 00 d4 00 00 0a 16 d4 00 00 d4 00 00 00 02
?auto_err 0a25
/epush16 0a28 00
\epush16 0a29
/Cprintf 0a2d 00
\Cprintf 0a2e
/esmove 0a30 00
\esmove 0a31
:0a24 c3 00 00 d4 00 00 00 d8 d4 00 00 d4 00 00 00 02
?auto_err 0a35
/epush16 0a43 00
:0a34 c3 00 00 c0 0a 42 7c 25 34 38 73 7c 0a 00 d4 00
\epush16 0a44
/epush16 0a48 00
\epush16 0a49
/Cprintf 0a4d 00
\Cprintf 0a4e
/esmove 0a50 00
\esmove 0a51
:0a44 00 01 0c d4 00 00 0a 3a d4 00 00 d4 00 00 00 04
?auto_err 0a55
:0a54 c3 00 00 c0 0a 63 7c 25 2d 34 38 73 7c 0a 00 d4
/epush16 0a64 00
\epush16 0a65
/epush16 0a69 00
\epush16 0a6a
/Cprintf 0a6e 00
\Cprintf 0a6f
/esmove 0a71 00
\esmove 0a72
:0a64 00 00 01 25 d4 00 00 0a 5a d4 00 00 d4 00 00 00
?auto_err 0a76
/epush16 0a79 00
\epush16 0a7a
/lstor16 0a7e 00
\lstor16 0a7f
/dpop16 0a83 00
:0a74 04 c3 00 00 d4 00 00 00 00 d4 00 00 ff fe d4 00
\dpop16 0a84
/lpush16 0a86 00
\lpush16 0a87
/epush16 0a8b 00
\epush16 0a8c
/lt16 0a90 00
\lt16 0a91
/dpop16 0a93 00
:0a84 00 d4 00 00 ff fe d4 00 00 00 05 d4 00 00 d4 00
\dpop16 0a94
/lpush16 0aa3 00
:0a94 00 9a 52 8a f1 ca 0a 9f c0 0b 0f c0 0a b2 d4 00
\lpush16 0aa4
/linc16 0aa8 00
\linc16 0aa9
/dpop16 0aad 00
\dpop16 0aae
:0aa4 00 ff fe d4 00 00 ff fe d4 00 00 c0 0a 85 c0 0a
:0ab4 ca 25 63 25 63 25 63 25 63 25 63 25 63 25 63 25
/epush16 0acb 00
\epush16 0acc
/epush16 0ad0 00
\epush16 0ad1
:0ac4 63 25 63 25 63 00 d4 00 00 00 30 d4 00 00 00 39
/epush16 0ad5 00
\epush16 0ad6
/epush16 0ada 00
\epush16 0adb
/epush16 0adf 00
\epush16 0ae0
:0ad4 d4 00 00 00 38 d4 00 00 00 37 d4 00 00 00 36 d4
/epush16 0ae4 00
\epush16 0ae5
/epush16 0ae9 00
\epush16 0aea
/epush16 0aee 00
\epush16 0aef
/epush16 0af3 00
:0ae4 00 00 00 35 d4 00 00 00 34 d4 00 00 00 33 d4 00
\epush16 0af4
/epush16 0af8 00
\epush16 0af9
/epush16 0afd 00
\epush16 0afe
/Cprintf 0b02 00
\Cprintf 0b03
:0af4 00 00 32 d4 00 00 00 31 d4 00 00 0a b5 d4 00 00
/esmove 0b05 00
\esmove 0b06
?auto_err 0b0a
:0b04 d4 00 00 00 16 c3 00 00 c0 0a a2 c0 0b 13 00 d4
/epush16 0b14 00
\epush16 0b15
/Cputs 0b19 00
\Cputs 0b1a
/esmove 0b1c 00
\esmove 0b1d
?auto_err 0b21
:0b14 00 00 0b 12 d4 00 00 d4 00 00 00 02 c3 00 00 c0
/epush16 0b2d 00
\epush16 0b2e
/epush16 0b32 00
\epush16 0b33
:0b24 0b 2c 25 35 30 64 0a 00 d4 00 00 cf c7 d4 00 00
/Cprintf 0b37 00
\Cprintf 0b38
/esmove 0b3a 00
\esmove 0b3b
?auto_err 0b3f
:0b34 0b 26 d4 00 00 d4 00 00 00 04 c3 00 00 c0 0b 4c
/epush16 0b4d 00
\epush16 0b4e
/epush16 0b52 00
\epush16 0b53
:0b44 25 2d 34 39 64 7c 0a 00 d4 00 00 cf c7 d4 00 00
/Cprintf 0b57 00
\Cprintf 0b58
/esmove 0b5a 00
\esmove 0b5b
?auto_err 0b5f
:0b54 0b 44 d4 00 00 d4 00 00 00 04 c3 00 00 c0 0b 6b
/epush16 0b6c 00
\epush16 0b6d
/epush16 0b71 00
\epush16 0b72
:0b64 25 30 35 30 64 0a 00 d4 00 00 30 39 d4 00 00 0b
/Cprintf 0b76 00
\Cprintf 0b77
/esmove 0b79 00
\esmove 0b7a
?auto_err 0b7e
:0b74 64 d4 00 00 d4 00 00 00 04 c3 00 00 c0 0b 98 30
:0b84 78 25 78 20 25 31 35 73 25 64 25 31 36 73 20 30
/epush16 0ba1 00
\epush16 0ba2
:0b94 25 6f 0a 00 c0 0b 9c 00 c0 0b a0 00 d4 00 00 7b
/epush16 0ba6 00
\epush16 0ba7
/epush16 0bab 00
\epush16 0bac
/epush16 0bb0 00
\epush16 0bb1
:0ba4 cd d4 00 00 0b 9f d4 00 00 7b cd d4 00 00 0b 9b
/epush16 0bb5 00
\epush16 0bb6
/epush16 0bba 00
\epush16 0bbb
/Cprintf 0bbf 00
\Cprintf 0bc0
/esmove 0bc2 00
\esmove 0bc3
:0bb4 d4 00 00 7b cd d4 00 00 0b 83 d4 00 00 d4 00 00
?auto_err 0bc7
/epush16 0bca 00
\epush16 0bcb
/lstor16 0bcf 00
\lstor16 0bd0
:0bc4 00 0c c3 00 00 d4 00 00 00 00 d4 00 00 ff fe d4
/dpop16 0bd4 00
\dpop16 0bd5
/lpush16 0bd7 00
\lpush16 0bd8
/epush16 0bdc 00
\epush16 0bdd
/lt16 0be1 00
\lt16 0be2
:0bd4 00 00 d4 00 00 ff fe d4 00 00 00 05 d4 00 00 d4
/dpop16 0be4 00
\dpop16 0be5
:0be4 00 00 9a 52 8a f1 ca 0b f0 c0 0c 16 c0 0c 03 d4
/lpush16 0bf4 00
\lpush16 0bf5
/linc16 0bf9 00
\linc16 0bfa
/dpop16 0bfe 00
\dpop16 0bff
:0bf4 00 00 ff fe d4 00 00 ff fe d4 00 00 c0 0b d6 d4
/epush16 0c04 00
\epush16 0c05
/Cprintf 0c09 00
\Cprintf 0c0a
/esmove 0c0c 00
\esmove 0c0d
?auto_err 0c11
:0c04 00 00 01 3e d4 00 00 d4 00 00 00 02 c3 00 00 c0
/epush16 0c1b 00
\epush16 0c1c
/Cputs 0c20 00
\Cputs 0c21
/esmove 0c23 00
:0c14 0b f3 c0 0c 1a 00 d4 00 00 0c 19 d4 00 00 d4 00
\esmove 0c24
?auto_err 0c28
/epush16 0c2b 00
\epush16 0c2c
/Cputs 0c30 00
\Cputs 0c31
/esmove 0c33 00
:0c24 00 00 02 c3 00 00 d4 00 00 00 a4 d4 00 00 d4 00
\esmove 0c34
?auto_err 0c38
/esmove 0c3b 00
\esmove 0c3c
?auto_err 0c40
:0c34 00 00 02 c3 00 00 d4 00 00 00 02 c3 00 00 e2 d4
/escheck 0c44 00
\escheck 0c45
=Cmain 0c4c
:0c44 00 00 60 72 ab f0 bb d5 f8 00 a1 f8 f0 b1 e2 9b
/vpush16 0c62 00
\vpush16 0c63
:0c54 73 8b 73 87 ab 97 bb d4 09 25 d4 01 d2 d4 00 00
/dpop16 0c67 00
\dpop16 0c68
:0c64 00 00 d4 00 00 9a 52 8a f1 ca 0c 88 c0 0c 78 6f
/epush16 0c79 00
\epush16 0c7a
/esmove 0c81 00
\esmove 0c82
:0c74 6b 61 79 00 d4 00 00 0c 73 d4 01 a3 d4 00 00 00
?auto_err 0c86
/vpush16 0c89 00
\vpush16 0c8a
/dpop16 0c8e 00
\dpop16 0c8f
/escheck 0c92 00
\escheck 0c93
:0c84 02 c3 00 00 d4 00 00 00 02 d4 00 00 e2 d4 00 00
:0c94 60 72 ab f0 bb d5
+015d
+0172
+0182
+0187
+0194
+01ad
+01bb
+01f6
+0203
^0206 a3
v0207
+0211
+0220
+0227
+022c
+0251
+0254
+0257
+0264
^0267 53
v0268
+0272
+0275
+0291
+02a6
+02d5
+02d8
+02db
+02eb
+0303
+033c
+033f
+0342
+0352
+036a
+0382
+038a
+038f
+03a2
+03af
+03b4
+03c7
+03d5
+03da
+040e
+0411
+0414
+0424
+0427
+0473
+0486
+0489
+0495
+04a3
+04b3
+04c6
+04d8
+04eb
+04fc
+050f
+0527
+052b
+0536
+0540
+054a
+057e
+0581
+0584
+0594
+0599
+05ac
+05af
+05bb
+05d0
+05ee
+05fa
+0601
+0606
+062b
+062e
+0631
+0653
+0663
+0668
+066e
+0671
+0680
+0687
+068c
+06b1
+06b4
+06b7
+06e8
+06f8
+06fd
+0703
+0706
+071b
+0735
+0743
+0746
+0762
+078a
+078d
+07aa
+07ad
+07b7
+07bc
+07d4
+07e4
+07f9
+0807
+080a
+0817
+0821
+083b
+0849
+0869
+088c
+088f
+08af
+08f6
+08f9
+0906
^0909 53
v090a
+0937
+0943
^0946 a3
v0947
+0953
+0982
+0985
+0988
+0998
+09b0
+09b3
+09b9
+09e8
+09eb
+09ee
+09fe
+0a11
+0a14
+0a1a
+0a2a
+0a38
+0a45
+0a4a
+0a58
+0a66
+0a6b
+0a9a
+0a9d
+0aa0
+0ab0
+0ab3
+0aff
+0b0d
+0b10
+0b16
+0b24
+0b34
+0b42
+0b54
+0b62
+0b73
+0b81
+0b99
+0b9d
+0ba8
+0bb2
+0bbc
+0beb
+0bee
+0bf1
+0c01
+0c06
+0c14
+0c17
+0c1d
+0c2d
^0c5c 25
v0c5d
^0c5f d2
v0c60
+0c64
+0c6e
+0c71
+0c7b
^0c7e a3
v0c7f
+0c8b
}
