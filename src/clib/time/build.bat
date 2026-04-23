..\elfc -L _asctime.c
..\elfc -L _asctime2.c
..\elfc -L _cstime.c
..\elfc -L _cstime2.c
..\elfc -L _dow.c
..\elfc -L _doy.c
..\elfc -L _strftime.c
..\elfc -L _strftime2.c
..\elfc -L systime.c
..\elfc -L timezone.c
..\elfc -L utctime.c

type _asctime.prg _asctime2.prg _cstime.prg _cstime2.prg _dow.prg _doy.prg  > time.lib
type _strftime.prg _strftime2.prg systime.prg timezone.prg utctime.prg >> time.lib

copy time.lib ..\lib\time.lib
