..\elfc -L add32.c
..\elfc -L atoi32.c
..\elfc -L cmp32.c
..\elfc -L div32.c
..\elfc -L itoa32.c
..\elfc -L mul32.c
..\elfc -L neg32.c
..\elfc -L shl32.c
..\elfc -L shr32.c
..\elfc -L strtoi32.c
..\elfc -L sub32.c
..\elfc -L to_int32.c

type add32.prg atoi32.prg cmp32.prg div32.prg itoa32.prg > math32.lib
type mul32.prg neg32.prg shl32.prg shr32.prg strtoi32.prg >> math32.lib
type sub32.prg to_int32.prg >> math32.lib

copy math32.lib ..\lib\math32.lib
