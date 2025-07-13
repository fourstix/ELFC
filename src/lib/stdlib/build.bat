..\elfc -L _init.c
..\elfc -L _fdinit.c
..\elfc -L abort.c
..\elfc -L abs.c
..\elfc -L atexit.c
..\elfc -L atoi.c
..\elfc -L bsearch.c
..\elfc -L calloc.c
..\elfc -L div.c
..\elfc -L exit.c
..\elfc -L free.c
..\elfc -L itoa.c
..\elfc -L itox.c
..\elfc -L malloc.c
..\elfc -L qsort.c
..\elfc -L rand.c
..\elfc -L creat.c
..\elfc -L open.c
..\elfc -L close.c
..\elfc -L read.c
..\elfc -L write.c
..\elfc -L lseek.c

type _init.prg _fdinit.prg abs.prg abort.prg atexit.prg atoi.prg bsearch.prg > stdlib.lib
type calloc.prg div.prg exit.prg free.prg itoa.prg itox.prg malloc.prg qsort.prg >> stdlib.lib
type rand.prg creat.prg open.prg close.prg read.prg write.prg lseek.prg >> stdlib.lib

copy stdlib.lib ..\lib\stdlib.lib
