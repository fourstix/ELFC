..\elfc -L absi32.c
..\elfc -L addi32.c
..\elfc -L addu32.c
..\elfc -L asri32.c
..\elfc -L atoi32.c
..\elfc -L atou32.c
..\elfc -L cmpi32.c
..\elfc -L cmpu32.c
..\elfc -L divi32.c
..\elfc -L divu32.c
..\elfc -L i32_from_int.c
..\elfc -L i32_from_u32.c
..\elfc -L i32toa.c
..\elfc -L int_from_i32.c
..\elfc -L make_i32.c
..\elfc -L make_u32.c
..\elfc -L muli32.c
..\elfc -L muli32x16.c
..\elfc -L mulu32.c
..\elfc -L mulu32x16.c
..\elfc -L negi32.c
..\elfc -L shli32.c
..\elfc -L shlu32.c
..\elfc -L shri32.c
..\elfc -L shru32.c
..\elfc -L strtoi32.c
..\elfc -L strtou32.c
..\elfc -L subi32.c
..\elfc -L subu32.c
..\elfc -L u32_from_i32.c
..\elfc -L u32_from_uint.c
..\elfc -L u32toa.c
..\elfc -L uint_from_u32.c

type absi32.prg addi32.prg addu32.prg asri32.prg atoi32.prg  > math32.lib
type atou32.prg cmpi32.prg cmpu32.prg divi32.prg divu32.prg >> math32.lib
type i32_from_int.prg i32_from_u32.prg i32toa.prg int_from_i32.prg >> math32.lib
type make_i32.prg make_u32.prg muli32.prg muli32x16.prg >> math32.lib
type mulu32.prg mulu32x16.prg negi32.prg shli32.prg shlu32.prg >> math32.lib
type shri32.prg shru32.prg strtoi32.prg strtou32.prg subi32.prg >> math32.lib
type subu32.prg u32_from_i32.prg u32_from_uint.prg u32toa.prg uint_from_u32.prg >> math32.lib

copy math32.lib ..\lib\math32.lib
