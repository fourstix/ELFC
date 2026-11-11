..\elfc -L -i ..\include _kdiropen.c
..\elfc -L -i ..\include _kdirread.c
..\elfc -L -i ..\include _kdirrestore.c
..\elfc -L -i ..\include _kdirsave.c
..\elfc -L -i ..\include _kpathres.c
..\elfc -L -i ..\include _kstat.c
..\elfc -L -i ..\include closedir.c
..\elfc -L -i ..\include opendir.c
..\elfc -L -i ..\include readdir.c
..\elfc -L -i ..\include rewinddir.c

type _kdiropen.prg _kdirread.prg _kdirrestore.prg _kdirsave.prg > dirent.lib
type _kpathres.prg _kstat.prg closedir.prg opendir.prg >> dirent.lib
type readdir.prg rewinddir.prg >> dirent.lib

copy dirent.lib ..\lib\dirent.lib
