..\elfc -L -i ..\include _odiropen.c
..\elfc -L -i ..\include _oopendir.c
..\elfc -L -i ..\include closedir.c
..\elfc -L -i ..\include opendir.c
..\elfc -L -i ..\include readdir.c
..\elfc -L -i ..\include rewinddir.c

type _odiropen.prg _oopendir.prg closedir.prg opendir.prg > dirent.lib
type readdir.prg rewinddir.prg >> dirent.lib

copy dirent.lib ..\lib\dirent.lib
