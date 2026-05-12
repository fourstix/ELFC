..\elfc -L absi32.c
..\elfc -L addi32.c
..\elfc -L asri32.c
..\elfc -L atoi32.c
..\elfc -L cmpi32.c
..\elfc -L divi32.c
..\elfc -L i32toa.c
..\elfc -L muli32.c
..\elfc -L muli32x16.c
..\elfc -L negi32.c
..\elfc -L shli32.c
..\elfc -L shri32.c
..\elfc -L strtoi32.c
..\elfc -L subi32.c
..\elfc -L toi32.c

type absi32.prg addi32.prg asri32.prg atoi32.prg  > mathi32.lib
type cmpi32.prg divi32.prg i32toa.prg muli32.prg >> mathi32.lib
type muli32x16.prg negi32.prg shli32.prg shri32.prg >> mathi32.lib
type strtoi32.prg subi32.prg toi32.prg >> mathi32.lib
