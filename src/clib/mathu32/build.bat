..\elfc -L addu32.c
..\elfc -L atou32.c
..\elfc -L cmpu32.c
..\elfc -L divu32.c
..\elfc -L u32toa.c
..\elfc -L mulu32.c
..\elfc -L mulu32x16.c
..\elfc -L shlu32.c
..\elfc -L shru32.c
..\elfc -L strtou32.c
..\elfc -L subu32.c
..\elfc -L tou32.c

type addu32.prg atou32.prg cmpu32.prg divu32.prg > mathu32.lib
type u32toa.prg mulu32.prg >> mathu32.lib
type mulu32x16.prg shlu32.prg shru32.prg >> mathu32.lib
type strtou32.prg subu32.prg tou32.prg >> mathu32.lib

copy mathu32.lib ..\lib\mathu32.lib
