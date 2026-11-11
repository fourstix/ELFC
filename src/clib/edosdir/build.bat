..\elfc -L -i ..\include _kfill.c
..\elfc -L -i ..\include _kpathres.c
..\elfc -L -i ..\include _kstat.c
..\elfc -L -i ..\include closedir.c
..\elfc -L -i ..\include opendir.c
..\elfc -L -i ..\include readdir.c
..\elfc -L -i ..\include rewinddir.c

type _kfill.prg _kpathres.prg _kstat.prg closedir.prg opendir.prg > edosdir.lib
type readdir.prg rewinddir.prg >> edosdir.lib

copy edosdir.lib ..\lib\edosdir.lib
