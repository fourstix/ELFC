..\elfc -L _dow.c
..\elfc -L _doy.c
..\elfc -L systime.c
..\elfc -L asctime.c
..\elfc -L cstime.c
..\elfc -L timezone.c
..\elfc -L utctime.c
..\elfc -L strftime.c

type _dow.prg _doy.prg asctime.prg cstime.prg > time.lib
type strftime.prg systime.prg timezone.prg utctime.prg >> time.lib

copy time.lib ..\lib\time.lib
