.big
{filetest2
.library string.lib
=CErrors 0000
=Cresult 0002
=Cfilpos 0004
:0000 00 00 00 00
>0004
=Cfail 0008
:0008 e2 9b 73 8b 73 87 ab 97 bb c0 00 1f 25 73 20 66
/lpush16 0020 00
\lpush16 0021
/epush16 0025 00
\epush16 0026
:0018 61 69 6c 65 64 0a 00 d4 00 00 00 00 d4 00 00 00
/Cprintf 002a 00
\Cprintf 002b
/esmove 002d 00
\esmove 002e
?auto_err 0032
/vpush16 0035 00
\vpush16 0036
:0028 14 d4 00 00 d4 00 00 00 04 c3 00 00 d4 00 00 00
/vinc16 003a 00
\vinc16 003b
/dpop16 003f 00
\dpop16 0040
/epush16 0042 00
\epush16 0043
/vstor16 0047 00
:0038 00 d4 00 00 00 00 d4 00 00 d4 00 00 00 01 d4 00
\vstor16 0048
/dpop16 004c 00
\dpop16 004d
/escheck 0050 00
\escheck 0051
:0048 00 00 02 d4 00 00 e2 d4 00 00 60 72 ab f0 bb d5
=Cpr 0058
:0058 e2 9b 73 8b 73 87 ab 97 bb c0 00 68 25 73 0a 00
/lpush16 0069 00
\lpush16 006a
/epush16 006e 00
\epush16 006f
/Cprintf 0073 00
\Cprintf 0074
/esmove 0076 00
\esmove 0077
:0068 d4 00 00 00 00 d4 00 00 00 64 d4 00 00 d4 00 00
?auto_err 007b
/escheck 007f 00
\escheck 0080
=Ctest_stdio2 0087
:0078 00 04 c3 00 00 e2 d4 00 00 60 72 ab f0 bb d5 e2
/esmove 0091 00
\esmove 0092
?auto_err 0096
:0088 9b 73 8b 73 87 ab 97 bb d4 00 00 ff f6 c3 00 00
/epush16 00a3 00
\epush16 00a4
:0098 c0 00 a2 66 69 6c 65 6e 6f 00 d4 00 00 00 9b d4
/esmove 00ab 00
\esmove 00ac
?auto_err 00b0
/vpush16 00b3 00
\vpush16 00b4
?Cstdin 00b5
:00a8 00 58 d4 00 00 00 02 c3 00 00 d4 00 00 00 00 d4
/Cfileno 00b8 00
\Cfileno 00b9
/esmove 00bb 00
\esmove 00bc
?auto_err 00c0
/dpush16 00c3 00
\dpush16 00c4
/epush16 00c6 00
\epush16 00c7
:00b8 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00 00
/ne16 00cb 00
\ne16 00cc
/dpop16 00ce 00
\dpop16 00cf
:00c8 00 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 00 da c0
/epush16 00e7 00
:00d8 00 f6 c0 00 e6 66 69 6c 65 6e 6f 2d 31 00 d4 00
\epush16 00e8
/esmove 00ef 00
\esmove 00f0
?auto_err 00f4
/vpush16 00f7 00
:00e8 00 00 dd d4 00 08 d4 00 00 00 02 c3 00 00 d4 00
\vpush16 00f8
?Cstdout 00f9
/Cfileno 00fc 00
\Cfileno 00fd
/esmove 00ff 00
\esmove 0100
?auto_err 0104
/dpush16 0107 00
:00f8 00 00 00 d4 00 00 d4 00 00 00 02 c3 00 00 d4 00
\dpush16 0108
/epush16 010a 00
\epush16 010b
/ne16 010f 00
\ne16 0110
/dpop16 0112 00
\dpop16 0113
:0108 00 d4 00 00 00 01 d4 00 00 d4 00 00 9a 52 8a f1
:0118 ca 01 1e c0 01 3a c0 01 2a 66 69 6c 65 6e 6f 2d
/epush16 012b 00
\epush16 012c
/esmove 0133 00
\esmove 0134
:0128 32 00 d4 00 00 01 21 d4 00 08 d4 00 00 00 02 c3
?auto_err 0138
/vpush16 013b 00
\vpush16 013c
?Cstderr 013d
/Cfileno 0140 00
\Cfileno 0141
/esmove 0143 00
\esmove 0144
:0138 00 00 d4 00 00 00 00 d4 00 00 d4 00 00 00 02 c3
?auto_err 0148
/dpush16 014b 00
\dpush16 014c
/epush16 014e 00
\epush16 014f
/ne16 0153 00
\ne16 0154
/dpop16 0156 00
\dpop16 0157
:0148 00 00 d4 00 00 d4 00 00 00 02 d4 00 00 d4 00 00
:0158 9a 52 8a f1 ca 01 62 c0 01 7e c0 01 6e 66 69 6c
/epush16 016f 00
\epush16 0170
/esmove 0177 00
:0168 65 6e 6f 2d 33 00 d4 00 00 01 65 d4 00 08 d4 00
\esmove 0178
?auto_err 017c
:0178 00 00 02 c3 00 00 c0 01 8c 66 74 65 73 74 34 2e
/epush16 0193 00
\epush16 0194
:0188 74 6d 70 00 c0 01 92 77 2b 00 d4 00 00 01 8f d4
/epush16 0198 00
\epush16 0199
/Cfopen 019d 00
\Cfopen 019e
/esmove 01a0 00
\esmove 01a1
?auto_err 01a5
:0198 00 00 01 81 d4 00 00 d4 00 00 00 04 c3 00 00 d4
/dpush16 01a8 00
\dpush16 01a9
/lstor16 01ab 00
\lstor16 01ac
/epush16 01b0 00
\epush16 01b1
/eq16 01b5 00
\eq16 01b6
:01a8 00 00 d4 00 00 ff fe d4 00 00 00 00 d4 00 00 d4
/dpop16 01b8 00
\dpop16 01b9
:01b8 00 00 9a 52 8a f1 ca 01 c4 c0 01 e2 c0 01 cf 66
/epush16 01d0 00
\epush16 01d1
:01c8 6f 70 65 6e 2d 31 00 d4 00 00 01 c7 d4 00 08 d4
/esmove 01d8 00
\esmove 01d9
?auto_err 01dd
:01d8 00 00 00 02 c3 00 00 c0 0b 99 c0 01 eb 66 70 75
/epush16 01ec 00
\epush16 01ed
/esmove 01f4 00
\esmove 01f5
:01e8 74 63 00 d4 00 00 01 e5 d4 00 58 d4 00 00 00 02
?auto_err 01f9
/epush16 01fc 00
\epush16 01fd
/lstor16 0201 00
\lstor16 0202
/dpop16 0206 00
\dpop16 0207
:01f8 c3 00 00 d4 00 00 00 41 d4 00 00 ff fc d4 00 00
/lpush16 0209 00
\lpush16 020a
/epush16 020e 00
\epush16 020f
/lte16 0213 00
\lte16 0214
/dpop16 0216 00
\dpop16 0217
:0208 d4 00 00 ff fc d4 00 00 00 5a d4 00 00 d4 00 00
/lpush16 0226 00
\lpush16 0227
:0218 9a 52 8a f1 ca 02 22 c0 02 80 c0 02 35 d4 00 00
/linc16 022b 00
\linc16 022c
/dpop16 0230 00
\dpop16 0231
/lpush16 0236 00
\lpush16 0237
:0228 ff fc d4 00 00 ff fc d4 00 00 c0 02 08 d4 00 00
/lpush16 023b 00
\lpush16 023c
/Cfputc 0240 00
\Cfputc 0241
/esmove 0243 00
\esmove 0244
:0238 ff fe d4 00 00 ff fc d4 00 00 d4 00 00 00 04 c3
?auto_err 0248
/lpush16 024b 00
\lpush16 024c
/dpush16 0250 00
\dpush16 0251
/ne16 0253 00
\ne16 0254
/dpop16 0256 00
\dpop16 0257
:0248 00 00 d4 00 00 ff fc d4 00 00 d4 00 00 d4 00 00
:0258 9a 52 8a f1 ca 02 62 c0 02 7d c0 02 6d 66 70 75
/epush16 026e 00
\epush16 026f
/esmove 0276 00
\esmove 0277
:0268 74 63 2d 31 00 d4 00 00 02 65 d4 00 08 d4 00 00
?auto_err 027b
:0278 00 02 c3 00 00 c0 02 25 c0 02 8a 66 66 6c 75 73
/epush16 028b 00
\epush16 028c
/esmove 0293 00
\esmove 0294
:0288 68 00 d4 00 00 02 83 d4 00 58 d4 00 00 00 02 c3
?auto_err 0298
/lpush16 029b 00
\lpush16 029c
/Cfflush 02a0 00
\Cfflush 02a1
/esmove 02a3 00
\esmove 02a4
:0298 00 00 d4 00 00 ff fe d4 00 00 d4 00 00 00 02 c3
?auto_err 02a8
/dpush16 02ab 00
\dpush16 02ac
/epush16 02ae 00
\epush16 02af
/lt16 02b3 00
\lt16 02b4
/dpop16 02b6 00
\dpop16 02b7
:02a8 00 00 d4 00 00 d4 00 00 00 00 d4 00 00 d4 00 00
:02b8 9a 52 8a f1 ca 02 c2 c0 02 de c0 02 ce 66 66 6c
/epush16 02cf 00
\epush16 02d0
/esmove 02d7 00
:02c8 75 73 68 2d 31 00 d4 00 00 02 c5 d4 00 08 d4 00
\esmove 02d8
?auto_err 02dc
/lpush16 02df 00
\lpush16 02e0
/Cfclose 02e4 00
\Cfclose 02e5
/esmove 02e7 00
:02d8 00 00 02 c3 00 00 d4 00 00 ff fe d4 00 00 d4 00
\esmove 02e8
?auto_err 02ec
:02e8 00 00 02 c3 00 00 c0 02 fc 66 74 65 73 74 34 2e
/epush16 0302 00
\epush16 0303
/epush16 0307 00
:02f8 74 6d 70 00 c0 03 01 72 00 d4 00 00 02 ff d4 00
\epush16 0308
/Cfopen 030c 00
\Cfopen 030d
/esmove 030f 00
\esmove 0310
?auto_err 0314
/dpush16 0317 00
:0308 00 02 f1 d4 00 00 d4 00 00 00 04 c3 00 00 d4 00
\dpush16 0318
/lstor16 031a 00
\lstor16 031b
/epush16 031f 00
\epush16 0320
/eq16 0324 00
\eq16 0325
/dpop16 0327 00
:0318 00 d4 00 00 ff fe d4 00 00 00 00 d4 00 00 d4 00
\dpop16 0328
:0328 00 9a 52 8a f1 ca 03 33 c0 03 51 c0 03 3e 66 6f
/epush16 033f 00
\epush16 0340
/esmove 0347 00
:0338 70 65 6e 2d 32 00 d4 00 00 03 36 d4 00 08 d4 00
\esmove 0348
?auto_err 034c
:0348 00 00 02 c3 00 00 c0 0b 99 c0 03 5a 6c 73 65 65
/epush16 035b 00
\epush16 035c
/esmove 0363 00
\esmove 0364
:0358 6b 00 d4 00 00 03 54 d4 00 58 d4 00 00 00 02 c3
?auto_err 0368
/lpush16 036b 00
\lpush16 036c
/Cfileno 0370 00
\Cfileno 0371
/esmove 0373 00
\esmove 0374
:0368 00 00 d4 00 00 ff fe d4 00 00 d4 00 00 00 02 c3
?auto_err 0378
/dpush16 037b 00
\dpush16 037c
/lstor16 037e 00
\lstor16 037f
/dpop16 0383 00
\dpop16 0384
/epush16 0386 00
\epush16 0387
:0378 00 00 d4 00 00 d4 00 00 ff fa d4 00 00 d4 00 00
/epush16 038b 00
\epush16 038c
/epush16 0390 00
\epush16 0391
/lpush16 0395 00
\lpush16 0396
:0388 00 02 d4 00 00 ff ff d4 00 00 ff ff d4 00 00 ff
/Clseek 039a 00
\Clseek 039b
/esmove 039d 00
\esmove 039e
?auto_err 03a2
/dpush16 03a5 00
\dpush16 03a6
:0398 fa d4 00 00 d4 00 00 00 08 c3 00 00 d4 00 00 d4
/epush16 03a8 00
\epush16 03a9
/lt16 03ad 00
\lt16 03ae
/dpop16 03b0 00
\dpop16 03b1
:03a8 00 00 00 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 03
:03b8 bc c0 03 da c0 03 c7 6c 73 65 65 6b 2d 31 00 d4
/epush16 03c8 00
\epush16 03c9
/esmove 03d0 00
\esmove 03d1
?auto_err 03d5
:03c8 00 00 03 bf d4 00 08 d4 00 00 00 02 c3 00 00 c0
/lpush16 03db 00
\lpush16 03dc
/Cfgetc 03e0 00
\Cfgetc 03e1
/esmove 03e3 00
\esmove 03e4
:03d8 04 3d d4 00 00 ff fe d4 00 00 d4 00 00 00 02 c3
?auto_err 03e8
/dpush16 03eb 00
\dpush16 03ec
/lstor8 03ee 00
\lstor8 03ef
/dpop16 03f3 00
\dpop16 03f4
/epush16 03f6 00
\epush16 03f7
:03e8 00 00 d4 00 00 d4 00 00 ff f6 d4 00 00 d4 00 00
/lpush8 03fb 00
\lpush8 03fc
/ne16 0400 00
\ne16 0401
/dpop16 0403 00
\dpop16 0404
:03f8 00 5a d4 00 00 ff f6 d4 00 00 d4 00 00 9a 52 8a
:0408 f1 ca 04 0f c0 04 3d c0 04 1a 6c 73 65 65 6b 2d
/epush16 041b 00
\epush16 041c
/esmove 0423 00
\esmove 0424
:0418 32 00 d4 00 00 04 12 d4 00 08 d4 00 00 00 02 c3
?auto_err 0428
/lpush16 042b 00
\lpush16 042c
/Cfclose 0430 00
\Cfclose 0431
/esmove 0433 00
\esmove 0434
:0428 00 00 d4 00 00 ff fe d4 00 00 d4 00 00 00 02 c3
?auto_err 0438
/epush16 043e 00
\epush16 043f
/epush16 0443 00
\epush16 0444
:0438 00 00 c0 0b 99 d4 00 00 00 00 d4 00 00 00 00 d4
/epush16 0448 00
\epush16 0449
/lpush16 044d 00
\lpush16 044e
/Clseek 0452 00
\Clseek 0453
/esmove 0455 00
\esmove 0456
:0448 00 00 00 00 d4 00 00 ff fa d4 00 00 d4 00 00 00
?auto_err 045a
/dpush16 045d 00
\dpush16 045e
/epush16 0460 00
\epush16 0461
/lt16 0465 00
\lt16 0466
:0458 08 c3 00 00 d4 00 00 d4 00 00 00 00 d4 00 00 d4
/dpop16 0468 00
\dpop16 0469
:0468 00 00 9a 52 8a f1 ca 04 74 c0 04 92 c0 04 7f 6c
/epush16 0480 00
\epush16 0481
:0478 73 65 65 6b 2d 33 00 d4 00 00 04 77 d4 00 08 d4
/esmove 0488 00
\esmove 0489
?auto_err 048d
/lpush16 0493 00
\lpush16 0494
:0488 00 00 00 02 c3 00 00 c0 04 e2 d4 00 00 ff fe d4
/Cfgetc 0498 00
\Cfgetc 0499
/esmove 049b 00
\esmove 049c
?auto_err 04a0
/dpush16 04a3 00
\dpush16 04a4
/lstor8 04a6 00
\lstor8 04a7
:0498 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00 00
/dpop16 04ab 00
\dpop16 04ac
/epush16 04ae 00
\epush16 04af
/lpush8 04b3 00
\lpush8 04b4
:04a8 ff f6 d4 00 00 d4 00 00 00 41 d4 00 00 ff f6 d4
/ne16 04b8 00
\ne16 04b9
/dpop16 04bb 00
\dpop16 04bc
:04b8 00 00 d4 00 00 9a 52 8a f1 ca 04 c7 c0 04 e2 c0
/epush16 04d3 00
\epush16 04d4
:04c8 04 d2 6c 73 65 65 6b 2d 34 00 d4 00 00 04 ca d4
/esmove 04db 00
\esmove 04dc
?auto_err 04e0
/epush16 04e3 00
\epush16 04e4
:04d8 00 08 d4 00 00 00 02 c3 00 00 d4 00 00 00 01 d4
/epush16 04e8 00
\epush16 04e9
/epush16 04ed 00
\epush16 04ee
/lpush16 04f2 00
\lpush16 04f3
/Clseek 04f7 00
:04e8 00 00 00 0c d4 00 00 00 00 d4 00 00 ff fa d4 00
\Clseek 04f8
/esmove 04fa 00
\esmove 04fb
?auto_err 04ff
/dpush16 0502 00
\dpush16 0503
/epush16 0505 00
\epush16 0506
:04f8 00 d4 00 00 00 08 c3 00 00 d4 00 00 d4 00 00 00
/lt16 050a 00
\lt16 050b
/dpop16 050d 00
\dpop16 050e
:0508 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 05 19 c0 05
/epush16 0525 00
\epush16 0526
:0518 37 c0 05 24 6c 73 65 65 6b 2d 35 00 d4 00 00 05
/esmove 052d 00
\esmove 052e
?auto_err 0532
:0528 1c d4 00 08 d4 00 00 00 02 c3 00 00 c0 05 87 d4
/lpush16 0538 00
\lpush16 0539
/Cfgetc 053d 00
\Cfgetc 053e
/esmove 0540 00
\esmove 0541
?auto_err 0545
:0538 00 00 ff fe d4 00 00 d4 00 00 00 02 c3 00 00 d4
/dpush16 0548 00
\dpush16 0549
/lstor8 054b 00
\lstor8 054c
/dpop16 0550 00
\dpop16 0551
/epush16 0553 00
\epush16 0554
:0548 00 00 d4 00 00 ff f6 d4 00 00 d4 00 00 00 4e d4
/lpush8 0558 00
\lpush8 0559
/ne16 055d 00
\ne16 055e
/dpop16 0560 00
\dpop16 0561
:0558 00 00 ff f6 d4 00 00 d4 00 00 9a 52 8a f1 ca 05
:0568 6c c0 05 87 c0 05 77 6c 73 65 65 6b 2d 36 00 d4
/epush16 0578 00
\epush16 0579
/esmove 0580 00
\esmove 0581
?auto_err 0585
:0578 00 00 05 6f d4 00 08 d4 00 00 00 02 c3 00 00 d4
/epush16 0588 00
\epush16 0589
/lstor16 058d 00
\lstor16 058e
/dpop16 0592 00
\dpop16 0593
:0588 00 00 00 04 d4 00 00 ff f8 d4 00 00 c0 05 9f 66
/epush16 05a0 00
\epush16 05a1
:0598 67 65 74 70 6f 73 00 d4 00 00 05 97 d4 00 58 d4
/esmove 05a8 00
\esmove 05a9
?auto_err 05ad
/lpush16 05b0 00
\lpush16 05b1
/lpush16 05b5 00
\lpush16 05b6
:05a8 00 00 00 02 c3 00 00 d4 00 00 ff f8 d4 00 00 ff
/Cfgetpos 05ba 00
\Cfgetpos 05bb
/esmove 05bd 00
\esmove 05be
?auto_err 05c2
/dpush16 05c5 00
\dpush16 05c6
:05b8 fe d4 00 00 d4 00 00 00 04 c3 00 00 d4 00 00 d4
/epush16 05c8 00
\epush16 05c9
/lt16 05cd 00
\lt16 05ce
/dpop16 05d0 00
\dpop16 05d1
:05c8 00 00 00 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 05
:05d8 dc c0 05 f9 c0 05 e9 66 67 65 74 70 6f 73 2d 31
/epush16 05ea 00
\epush16 05eb
/esmove 05f2 00
\esmove 05f3
?auto_err 05f7
:05e8 00 d4 00 00 05 df d4 00 08 d4 00 00 00 02 c3 00
/lpush16 05fa 00
\lpush16 05fb
/deref16 05ff 00
\deref16 0600
/epush16 0602 00
\epush16 0603
/ne16 0607 00
:05f8 00 d4 00 00 ff f8 d4 00 00 d4 00 00 00 00 d4 00
\ne16 0608
/dpop16 060a 00
\dpop16 060b
:0608 00 d4 00 00 9a 52 8a f1 ca 06 16 c0 06 33 c0 06
/epush16 0624 00
\epush16 0625
:0618 23 66 67 65 74 70 6f 73 2d 32 00 d4 00 00 06 19
/esmove 062c 00
\esmove 062d
?auto_err 0631
/epush16 0634 00
\epush16 0635
:0628 d4 00 08 d4 00 00 00 02 c3 00 00 d4 00 00 00 02
/lpush16 0639 00
\lpush16 063a
/add16 063e 00
\add16 063f
/deref16 0641 00
\deref16 0642
/epush16 0644 00
\epush16 0645
:0638 d4 00 00 ff f8 d4 00 00 d4 00 00 d4 00 00 00 0e
/ne16 0649 00
\ne16 064a
/dpop16 064c 00
\dpop16 064d
:0648 d4 00 00 d4 00 00 9a 52 8a f1 ca 06 58 c0 06 75
/epush16 0666 00
\epush16 0667
:0658 c0 06 65 66 67 65 74 70 6f 73 2d 33 00 d4 00 00
/esmove 066e 00
\esmove 066f
?auto_err 0673
:0668 06 5b d4 00 08 d4 00 00 00 02 c3 00 00 c0 06 7e
/epush16 067f 00
\epush16 0680
/esmove 0687 00
:0678 66 74 65 6c 6c 00 d4 00 00 06 78 d4 00 58 d4 00
\esmove 0688
?auto_err 068c
/lpush16 068f 00
\lpush16 0690
/Cftell 0694 00
\Cftell 0695
/esmove 0697 00
:0688 00 00 02 c3 00 00 d4 00 00 ff fe d4 00 00 d4 00
\esmove 0698
?auto_err 069c
/dpush16 069f 00
\dpush16 06a0
/epush16 06a2 00
\epush16 06a3
/ne16 06a7 00
:0698 00 00 02 c3 00 00 d4 00 00 d4 00 00 00 0e d4 00
\ne16 06a8
/dpop16 06aa 00
\dpop16 06ab
:06a8 00 d4 00 00 9a 52 8a f1 ca 06 b6 c0 06 d1 c0 06
/epush16 06c2 00
\epush16 06c3
:06b8 c1 66 74 65 6c 6c 2d 31 00 d4 00 00 06 b9 d4 00
/esmove 06ca 00
\esmove 06cb
?auto_err 06cf
:06c8 08 d4 00 00 00 02 c3 00 00 c0 06 dc 66 73 65 74
/epush16 06dd 00
\epush16 06de
/esmove 06e5 00
\esmove 06e6
:06d8 70 6f 73 00 d4 00 00 06 d4 d4 00 58 d4 00 00 00
?auto_err 06ea
/epush16 06ed 00
\epush16 06ee
/lpush16 06f2 00
\lpush16 06f3
/add16 06f7 00
:06e8 02 c3 00 00 d4 00 00 00 02 d4 00 00 ff f8 d4 00
\add16 06f8
/epush16 06fa 00
\epush16 06fb
/swap16 06ff 00
\swap16 0700
/dpop16 0702 00
\dpop16 0703
/pstor16 0705 00
\pstor16 0706
:06f8 00 d4 00 00 00 14 d4 00 00 d4 00 00 d4 00 00 d4
/dpop16 0708 00
\dpop16 0709
/lpush16 070b 00
\lpush16 070c
/epush16 0710 00
\epush16 0711
/swap16 0715 00
\swap16 0716
:0708 00 00 d4 00 00 ff f8 d4 00 00 00 00 d4 00 00 d4
/dpop16 0718 00
\dpop16 0719
/pstor16 071b 00
\pstor16 071c
/dpop16 071e 00
\dpop16 071f
/lpush16 0721 00
\lpush16 0722
/lpush16 0726 00
\lpush16 0727
:0718 00 00 d4 00 00 d4 00 00 d4 00 00 ff f8 d4 00 00
/Cfsetpos 072b 00
\Cfsetpos 072c
/esmove 072e 00
\esmove 072f
?auto_err 0733
/dpush16 0736 00
\dpush16 0737
:0728 ff fe d4 00 00 d4 00 00 00 04 c3 00 00 d4 00 00
/epush16 0739 00
\epush16 073a
/lt16 073e 00
\lt16 073f
/dpop16 0741 00
\dpop16 0742
:0738 d4 00 00 00 00 d4 00 00 d4 00 00 9a 52 8a f1 ca
:0748 07 4d c0 07 6a c0 07 5a 66 73 65 74 70 6f 73 2d
/epush16 075b 00
\epush16 075c
/esmove 0763 00
\esmove 0764
:0758 31 00 d4 00 00 07 50 d4 00 08 d4 00 00 00 02 c3
?auto_err 0768
/lpush16 076b 00
\lpush16 076c
/Cftell 0770 00
\Cftell 0771
/esmove 0773 00
\esmove 0774
:0768 00 00 d4 00 00 ff fe d4 00 00 d4 00 00 00 02 c3
?auto_err 0778
/dpush16 077b 00
\dpush16 077c
/epush16 077e 00
\epush16 077f
/ne16 0783 00
\ne16 0784
/dpop16 0786 00
\dpop16 0787
:0778 00 00 d4 00 00 d4 00 00 00 14 d4 00 00 d4 00 00
:0788 9a 52 8a f1 ca 07 92 c0 07 af c0 07 9f 66 73 65
/epush16 07a0 00
\epush16 07a1
:0798 74 70 6f 73 2d 32 00 d4 00 00 07 95 d4 00 08 d4
/esmove 07a8 00
\esmove 07a9
?auto_err 07ad
:07a8 00 00 00 02 c3 00 00 c0 07 b8 66 73 65 65 6b 00
/epush16 07b9 00
\epush16 07ba
/esmove 07c1 00
\esmove 07c2
?auto_err 07c6
:07b8 d4 00 00 07 b2 d4 00 58 d4 00 00 00 02 c3 00 00
/epush16 07c9 00
\epush16 07ca
/epush16 07ce 00
\epush16 07cf
/lpush16 07d3 00
\lpush16 07d4
:07c8 d4 00 00 00 01 d4 00 00 00 02 d4 00 00 ff fe d4
/Cfseek 07d8 00
\Cfseek 07d9
/esmove 07db 00
\esmove 07dc
?auto_err 07e0
/dpush16 07e3 00
\dpush16 07e4
/epush16 07e6 00
\epush16 07e7
:07d8 00 00 d4 00 00 00 06 c3 00 00 d4 00 00 d4 00 00
/lt16 07eb 00
\lt16 07ec
/dpop16 07ee 00
\dpop16 07ef
:07e8 00 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 07 fa c0
/epush16 0806 00
\epush16 0807
:07f8 08 15 c0 08 05 66 73 65 65 6b 2d 31 00 d4 00 00
/esmove 080e 00
\esmove 080f
?auto_err 0813
/lpush16 0816 00
\lpush16 0817
:0808 07 fd d4 00 08 d4 00 00 00 02 c3 00 00 d4 00 00
/Cftell 081b 00
\Cftell 081c
/esmove 081e 00
\esmove 081f
?auto_err 0823
/dpush16 0826 00
\dpush16 0827
:0818 ff fe d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00
/epush16 0829 00
\epush16 082a
/ne16 082e 00
\ne16 082f
/dpop16 0831 00
\dpop16 0832
:0828 d4 00 00 00 16 d4 00 00 d4 00 00 9a 52 8a f1 ca
:0838 08 3d c0 08 58 c0 08 48 66 73 65 65 6b 2d 32 00
/epush16 0849 00
\epush16 084a
/esmove 0851 00
\esmove 0852
?auto_err 0856
:0848 d4 00 00 08 40 d4 00 08 d4 00 00 00 02 c3 00 00
/epush16 0863 00
\epush16 0864
:0858 c0 08 62 72 65 77 69 6e 64 00 d4 00 00 08 5b d4
/esmove 086b 00
\esmove 086c
?auto_err 0870
/lpush16 0873 00
\lpush16 0874
:0868 00 58 d4 00 00 00 02 c3 00 00 d4 00 00 ff fe d4
/Crewind 0878 00
\Crewind 0879
/esmove 087b 00
\esmove 087c
?auto_err 0880
/lpush16 0883 00
\lpush16 0884
:0878 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 ff fe d4
/Cftell 0888 00
\Cftell 0889
/esmove 088b 00
\esmove 088c
?auto_err 0890
/dpush16 0893 00
\dpush16 0894
/epush16 0896 00
\epush16 0897
:0888 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00 00
/ne16 089b 00
\ne16 089c
/dpop16 089e 00
\dpop16 089f
:0898 00 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 08 aa c0
/epush16 08b7 00
:08a8 08 c6 c0 08 b6 72 65 77 69 6e 64 2d 31 00 d4 00
\epush16 08b8
/esmove 08bf 00
\esmove 08c0
?auto_err 08c4
:08b8 00 08 ad d4 00 08 d4 00 00 00 02 c3 00 00 c0 08
/epush16 08d0 00
\epush16 08d1
:08c8 cf 66 67 65 74 73 00 d4 00 00 08 c9 d4 00 58 d4
/esmove 08d8 00
\esmove 08d9
?auto_err 08dd
/epush16 08e0 00
\epush16 08e1
/lstor16 08e5 00
\lstor16 08e6
:08d8 00 00 00 02 c3 00 00 d4 00 00 00 41 d4 00 00 ff
/dpop16 08ea 00
\dpop16 08eb
/lpush16 08ed 00
\lpush16 08ee
/epush16 08f2 00
\epush16 08f3
/lte16 08f7 00
:08e8 fc d4 00 00 d4 00 00 ff fc d4 00 00 00 5a d4 00
\lte16 08f8
/dpop16 08fa 00
\dpop16 08fb
:08f8 00 d4 00 00 9a 52 8a f1 ca 09 06 c0 09 62 c0 09
/lpush16 090a 00
\lpush16 090b
/linc16 090f 00
\linc16 0910
/dpop16 0914 00
\dpop16 0915
:0908 19 d4 00 00 ff fc d4 00 00 ff fc d4 00 00 c0 08
/lpush16 091a 00
\lpush16 091b
/Cfgetc 091f 00
\Cfgetc 0920
/esmove 0922 00
\esmove 0923
?auto_err 0927
:0918 ec d4 00 00 ff fe d4 00 00 d4 00 00 00 02 c3 00
/lpush16 092a 00
\lpush16 092b
/dpush16 092f 00
\dpush16 0930
/ne16 0932 00
\ne16 0933
/dpop16 0935 00
\dpop16 0936
:0928 00 d4 00 00 ff fc d4 00 00 d4 00 00 d4 00 00 9a
:0938 52 8a f1 ca 09 41 c0 09 5f c0 09 4c 66 67 65 74
/epush16 094d 00
\epush16 094e
/esmove 0955 00
\esmove 0956
:0948 63 2d 31 00 d4 00 00 09 44 d4 00 08 d4 00 00 00
?auto_err 095a
/lpush16 0963 00
\lpush16 0964
:0958 02 c3 00 00 c0 09 62 c0 09 09 d4 00 00 ff fe d4
/Cfgetc 0968 00
\Cfgetc 0969
/esmove 096b 00
\esmove 096c
?auto_err 0970
/dpush16 0973 00
\dpush16 0974
/epush16 0976 00
\epush16 0977
:0968 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00 00
/ne16 097b 00
\ne16 097c
/dpop16 097e 00
\dpop16 097f
:0978 ff ff d4 00 00 d4 00 00 9a 52 8a f1 ca 09 8a c0
/epush16 0996 00
\epush16 0997
:0988 09 a5 c0 09 95 66 67 65 74 63 2d 32 00 d4 00 00
/esmove 099e 00
\esmove 099f
?auto_err 09a3
:0998 09 8d d4 00 08 d4 00 00 00 02 c3 00 00 c0 09 af
/epush16 09b0 00
\epush16 09b1
:09a8 75 6e 67 65 74 63 00 d4 00 00 09 a8 d4 00 58 d4
/esmove 09b8 00
\esmove 09b9
?auto_err 09bd
/lpush16 09c0 00
\lpush16 09c1
/Cclearerr 09c5 00
\Cclearerr 09c6
:09b8 00 00 00 02 c3 00 00 d4 00 00 ff fe d4 00 00 d4
/esmove 09c8 00
\esmove 09c9
?auto_err 09cd
/lpush16 09d0 00
\lpush16 09d1
/epush16 09d5 00
\epush16 09d6
:09c8 00 00 00 02 c3 00 00 d4 00 00 ff fe d4 00 00 00
/Cungetc 09da 00
\Cungetc 09db
/esmove 09dd 00
\esmove 09de
?auto_err 09e2
/dpush16 09e5 00
\dpush16 09e6
:09d8 58 d4 00 00 d4 00 00 00 04 c3 00 00 d4 00 00 d4
/epush16 09e8 00
\epush16 09e9
/ne16 09ed 00
\ne16 09ee
/dpop16 09f0 00
\dpop16 09f1
:09e8 00 00 00 58 d4 00 00 d4 00 00 9a 52 8a f1 ca 09
:09f8 fc c0 0a 18 c0 0a 08 75 6e 67 65 74 63 2d 31 00
/epush16 0a09 00
\epush16 0a0a
/esmove 0a11 00
\esmove 0a12
?auto_err 0a16
:0a08 d4 00 00 09 ff d4 00 08 d4 00 00 00 02 c3 00 00
/lpush16 0a19 00
\lpush16 0a1a
/Cfgetc 0a1e 00
\Cfgetc 0a1f
/esmove 0a21 00
\esmove 0a22
?auto_err 0a26
:0a18 d4 00 00 ff fe d4 00 00 d4 00 00 00 02 c3 00 00
/dpush16 0a29 00
\dpush16 0a2a
/epush16 0a2c 00
\epush16 0a2d
/ne16 0a31 00
\ne16 0a32
/dpop16 0a34 00
\dpop16 0a35
:0a28 d4 00 00 d4 00 00 00 58 d4 00 00 d4 00 00 9a 52
:0a38 8a f1 ca 0a 40 c0 0a 5c c0 0a 4c 75 6e 67 65 74
/epush16 0a4d 00
\epush16 0a4e
/esmove 0a55 00
\esmove 0a56
:0a48 63 2d 32 00 d4 00 00 0a 43 d4 00 08 d4 00 00 00
?auto_err 0a5a
/lpush16 0a5d 00
\lpush16 0a5e
/epush16 0a62 00
\epush16 0a63
/Cungetc 0a67 00
:0a58 02 c3 00 00 d4 00 00 ff fe d4 00 00 00 58 d4 00
\Cungetc 0a68
/esmove 0a6a 00
\esmove 0a6b
?auto_err 0a6f
/dpush16 0a72 00
\dpush16 0a73
/epush16 0a75 00
\epush16 0a76
:0a68 00 d4 00 00 00 04 c3 00 00 d4 00 00 d4 00 00 00
/ne16 0a7a 00
\ne16 0a7b
/dpop16 0a7d 00
\dpop16 0a7e
:0a78 58 d4 00 00 d4 00 00 9a 52 8a f1 ca 0a 89 c0 0a
/epush16 0a96 00
\epush16 0a97
:0a88 a5 c0 0a 95 75 6e 67 65 74 63 2d 33 00 d4 00 00
/esmove 0a9e 00
\esmove 0a9f
?auto_err 0aa3
/lpush16 0aa6 00
\lpush16 0aa7
:0a98 0a 8c d4 00 08 d4 00 00 00 02 c3 00 00 d4 00 00
/epush16 0aab 00
\epush16 0aac
/Cungetc 0ab0 00
\Cungetc 0ab1
/esmove 0ab3 00
\esmove 0ab4
:0aa8 ff fe d4 00 00 00 58 d4 00 00 d4 00 00 00 04 c3
?auto_err 0ab8
/dpush16 0abb 00
\dpush16 0abc
/epush16 0abe 00
\epush16 0abf
/ne16 0ac3 00
\ne16 0ac4
/dpop16 0ac6 00
\dpop16 0ac7
:0ab8 00 00 d4 00 00 d4 00 00 ff ff d4 00 00 d4 00 00
:0ac8 9a 52 8a f1 ca 0a d2 c0 0a ee c0 0a de 75 6e 67
/epush16 0adf 00
\epush16 0ae0
/esmove 0ae7 00
:0ad8 65 74 63 2d 34 00 d4 00 00 0a d5 d4 00 08 d4 00
\esmove 0ae8
?auto_err 0aec
/lpush16 0aef 00
\lpush16 0af0
/Cfgetc 0af4 00
\Cfgetc 0af5
/esmove 0af7 00
:0ae8 00 00 02 c3 00 00 d4 00 00 ff fe d4 00 00 d4 00
\esmove 0af8
?auto_err 0afc
/dpush16 0aff 00
\dpush16 0b00
/epush16 0b02 00
\epush16 0b03
/ne16 0b07 00
:0af8 00 00 02 c3 00 00 d4 00 00 d4 00 00 00 58 d4 00
\ne16 0b08
/dpop16 0b0a 00
\dpop16 0b0b
:0b08 00 d4 00 00 9a 52 8a f1 ca 0b 16 c0 0b 32 c0 0b
/epush16 0b23 00
\epush16 0b24
:0b18 22 75 6e 67 65 74 63 2d 35 00 d4 00 00 0b 19 d4
/esmove 0b2b 00
\esmove 0b2c
?auto_err 0b30
/lpush16 0b33 00
\lpush16 0b34
:0b28 00 08 d4 00 00 00 02 c3 00 00 d4 00 00 ff fe d4
/Cclearerr 0b38 00
\Cclearerr 0b39
/esmove 0b3b 00
\esmove 0b3c
?auto_err 0b40
/lpush16 0b43 00
\lpush16 0b44
:0b38 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 ff fe d4
/Cfclose 0b48 00
\Cfclose 0b49
/esmove 0b4b 00
\esmove 0b4c
?auto_err 0b50
/dpush16 0b53 00
\dpush16 0b54
/dpop16 0b56 00
\dpop16 0b57
:0b48 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00 00
:0b58 9a 52 8a f1 c2 0b 7b c0 0b 6b 66 63 6c 6f 73 65
/epush16 0b6c 00
\epush16 0b6d
/esmove 0b74 00
\esmove 0b75
:0b68 2d 35 00 d4 00 00 0b 62 d4 00 08 d4 00 00 00 02
?auto_err 0b79
:0b78 c3 00 00 c0 0b 89 66 74 65 73 74 34 2e 74 6d 70
/epush16 0b8a 00
\epush16 0b8b
/Cunlink 0b8f 00
\Cunlink 0b90
/esmove 0b92 00
\esmove 0b93
?auto_err 0b97
:0b88 00 d4 00 00 0b 7e d4 00 00 d4 00 00 00 02 c3 00
/esmove 0b9a 00
\esmove 0b9b
?auto_err 0b9f
/escheck 0ba3 00
\escheck 0ba4
:0b98 00 d4 00 00 00 0a c3 00 00 e2 d4 00 00 60 72 ab
=Cmain 0bab
:0ba8 f0 bb d5 e2 9b 73 8b 73 87 ab 97 bb d4 00 87 d4
/vpush16 0bb8 00
\vpush16 0bb9
/dpop16 0bbd 00
\dpop16 0bbe
/escheck 0bc1 00
\escheck 0bc2
:0bb8 00 00 00 02 d4 00 00 e2 d4 00 00 60 72 ab f0 bb
:0bc8 d5
+0012
+0027
+0037
+003c
+0049
+0062
+0070
+0099
+00a5
^00a8 58
v00a9
+00d5
+00d8
+00db
+00e9
^00ec 08
v00ed
+0119
+011c
+011f
+012d
^0130 08
v0131
+015d
+0160
+0163
+0171
^0174 08
v0175
+017f
+018d
+0195
+019a
+01bf
+01c2
+01c5
+01d2
^01d5 08
v01d6
+01e0
+01e3
+01ee
^01f1 58
v01f2
+021d
+0220
+0223
+0233
+025d
+0260
+0263
+0270
^0273 08
v0274
+027e
+0281
+028d
^0290 58
v0291
+02bd
+02c0
+02c3
+02d1
^02d4 08
v02d5
+02ef
+02fd
+0304
+0309
+032e
+0331
+0334
+0341
^0344 08
v0345
+034f
+0352
+035d
^0360 58
v0361
+03b7
+03ba
+03bd
+03ca
^03cd 08
v03ce
+03d8
+040a
+040d
+0410
+041d
^0420 08
v0421
+043b
+046f
+0472
+0475
+0482
^0485 08
v0486
+0490
+04c2
+04c5
+04c8
+04d5
^04d8 08
v04d9
+0514
+0517
+051a
+0527
^052a 08
v052b
+0535
+0567
+056a
+056d
+057a
^057d 08
v057e
+058a
+0595
+05a2
^05a5 58
v05a6
+05d7
+05da
+05dd
+05ec
^05ef 08
v05f0
+0611
+0614
+0617
+0626
^0629 08
v062a
+0653
+0656
+0659
+0668
^066b 08
v066c
+0676
+0681
^0684 58
v0685
+06b1
+06b4
+06b7
+06c4
^06c7 08
v06c8
+06d2
+06df
^06e2 58
v06e3
+0748
+074b
+074e
+075d
^0760 08
v0761
+078d
+0790
+0793
+07a2
^07a5 08
v07a6
+07b0
+07bb
^07be 58
v07bf
+07f5
+07f8
+07fb
+0808
^080b 08
v080c
+0838
+083b
+083e
+084b
^084e 08
v084f
+0859
+0865
^0868 58
v0869
+08a5
+08a8
+08ab
+08b9
^08bc 08
v08bd
+08c7
+08d2
^08d5 58
v08d6
+0901
+0904
+0907
+0917
+093c
+093f
+0942
+094f
^0952 08
v0953
+095d
+0960
+0985
+0988
+098b
+0998
^099b 08
v099c
+09a6
+09b2
^09b5 58
v09b6
+09f7
+09fa
+09fd
+0a0b
^0a0e 08
v0a0f
+0a3b
+0a3e
+0a41
+0a4f
^0a52 08
v0a53
+0a84
+0a87
+0a8a
+0a98
^0a9b 08
v0a9c
+0acd
+0ad0
+0ad3
+0ae1
^0ae4 08
v0ae5
+0b11
+0b14
+0b17
+0b25
^0b28 08
v0b29
+0b5d
+0b60
+0b6e
^0b71 08
v0b72
+0b7c
+0b8c
^0bb5 87
v0bb6
+0bba
}
