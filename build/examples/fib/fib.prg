.big
{fib
=Cfib 0000
/epush16 000a 00
\epush16 000b
/lpush16 000f 00
:0000 e2 9b 73 8b 73 87 ab 97 bb d4 00 00 00 00 d4 00
\lpush16 0010
/eq16 0014 00
\eq16 0015
/dget16 0017 00
\dget16 0018
:0010 00 00 00 d4 00 00 d4 00 00 9a 52 8a f1 ca 00 30
/dpop16 0021 00
\dpop16 0022
/epush16 0024 00
\epush16 0025
/lpush16 0029 00
\lpush16 002a
/eq16 002e 00
\eq16 002f
:0020 d4 00 00 d4 00 00 00 01 d4 00 00 00 00 d4 00 00
/dpop16 0031 00
\dpop16 0032
/lpush16 003b 00
\lpush16 003c
:0030 d4 00 00 9a 52 8a f1 c2 00 48 d4 00 00 00 00 d4
/dpop16 0040 00
\dpop16 0041
/lpush16 0049 00
\lpush16 004a
/epush16 004e 00
\epush16 004f
:0040 00 00 c0 00 87 c0 00 87 d4 00 00 00 00 d4 00 00
/sub16 0053 00
\sub16 0054
/esmove 0059 00
\esmove 005a
?auto_err 005e
:0050 00 01 d4 00 00 d4 00 00 d4 00 00 00 02 c3 00 00
/dpush16 0061 00
\dpush16 0062
/lpush16 0064 00
\lpush16 0065
/epush16 0069 00
\epush16 006a
/sub16 006e 00
\sub16 006f
:0060 d4 00 00 d4 00 00 00 00 d4 00 00 00 02 d4 00 00
/esmove 0074 00
\esmove 0075
?auto_err 0079
/dpush16 007c 00
\dpush16 007d
/add16 007f 00
:0070 d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00 d4 00
\add16 0080
/dpop16 0082 00
\dpop16 0083
/escheck 0089 00
\escheck 008a
:0080 00 d4 00 00 c0 00 87 e2 d4 00 00 60 72 ab f0 bb
=Cmain 0091
/esmove 009b 00
\esmove 009c
:0090 d5 e2 9b 73 8b 73 87 ab 97 bb d4 00 00 ff fc c3
?auto_err 00a0
:00a0 00 00 c0 00 c3 46 69 72 73 74 20 74 65 6e 20 46
:00b0 69 62 6f 6e 61 63 63 69 20 6e 75 6d 62 65 72 73
/epush16 00c4 00
\epush16 00c5
/Cprintf 00c9 00
\Cprintf 00ca
/esmove 00cc 00
\esmove 00cd
:00c0 3a 0a 00 d4 00 00 00 a5 d4 00 00 d4 00 00 00 02
?auto_err 00d1
/epush16 00d4 00
\epush16 00d5
/lstor16 00d9 00
\lstor16 00da
/dpop16 00de 00
\dpop16 00df
:00d0 c3 00 00 d4 00 00 00 00 d4 00 00 ff fe d4 00 00
/lpush16 00e1 00
\lpush16 00e2
/epush16 00e6 00
\epush16 00e7
/lt16 00eb 00
\lt16 00ec
/dpop16 00ee 00
\dpop16 00ef
:00e0 d4 00 00 ff fe d4 00 00 00 0a d4 00 00 d4 00 00
/lpush16 00fe 00
\lpush16 00ff
:00f0 9a 52 8a f1 ca 00 fa c0 01 8e c0 01 0d d4 00 00
/linc16 0103 00
\linc16 0104
/dpop16 0108 00
\dpop16 0109
/lpush16 010e 00
\lpush16 010f
:0100 ff fe d4 00 00 ff fe d4 00 00 c0 00 e0 d4 00 00
/esmove 0116 00
\esmove 0117
?auto_err 011b
/dpush16 011e 00
\dpush16 011f
:0110 ff fe d4 00 00 d4 00 00 00 02 c3 00 00 d4 00 00
/lstor16 0121 00
\lstor16 0122
/dpop16 0126 00
\dpop16 0127
/lpush16 012f 00
:0120 d4 00 00 ff fc d4 00 00 c0 01 2e 25 64 00 d4 00
\lpush16 0130
/epush16 0134 00
\epush16 0135
/Cprintf 0139 00
\Cprintf 013a
/esmove 013c 00
\esmove 013d
:0130 00 ff fc d4 00 00 01 2b d4 00 00 d4 00 00 00 04
?auto_err 0141
/epush16 0144 00
\epush16 0145
/lpush16 0149 00
\lpush16 014a
/eq16 014e 00
\eq16 014f
:0140 c3 00 00 d4 00 00 00 09 d4 00 00 ff fe d4 00 00
/dpop16 0151 00
\dpop16 0152
:0150 d4 00 00 9a 52 8a f1 ca 01 5d c0 01 75 c0 01 62
/epush16 0163 00
\epush16 0164
/Cprintf 0168 00
\Cprintf 0169
/esmove 016b 00
\esmove 016c
:0160 0a 00 d4 00 00 01 60 d4 00 00 d4 00 00 00 02 c3
?auto_err 0170
/epush16 017c 00
\epush16 017d
:0170 00 00 c0 01 8b c0 01 7b 2c 20 00 d4 00 00 01 78
/Cprintf 0181 00
\Cprintf 0182
/esmove 0184 00
\esmove 0185
?auto_err 0189
/lpush16 018f 00
:0180 d4 00 00 d4 00 00 00 02 c3 00 00 c0 00 fd d4 00
\lpush16 0190
/dpop16 0194 00
\dpop16 0195
/esmove 0197 00
\esmove 0198
?auto_err 019c
:0190 00 ff fc d4 00 00 d4 00 00 00 04 c3 00 00 e2 d4
/escheck 01a0 00
\escheck 01a1
:01a0 00 00 60 72 ab f0 bb d5
+001e
+0038
+0043
+0046
^0056
v0057
^0071
v0072
+0085
+00a3
+00c6
+00f5
+00f8
+00fb
+010b
^0113
v0114
+0129
+0136
+0158
+015b
+015e
+0165
+0173
+0176
+017e
+018c
}
