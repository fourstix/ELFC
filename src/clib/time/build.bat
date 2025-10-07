..\elfc -L _dow.c
..\elfc -L _doy.c
..\elfc -L systime.c
..\elfc -L asctime.c
..\elfc -L cstime.c
..\elfc -L timezone.c
..\elfc -L utctime.c
..\elfc -L strftime.c

type _dow.prg _doy.prg systime.prg asctime.prg cstime.prg > time.lib
type timezone.prg utctime.prg strftime.prg >> time.lib

copy time.lib ..\lib\time.lib
