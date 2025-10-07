..\elfc -L _init.c
..\elfc -L _fdinit.c
..\elfc -L _fildes.c
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
..\elfc -L itou.c
..\elfc -L malloc.c
..\elfc -L qsort.c
..\elfc -L rand.c
..\elfc -L creat.c
..\elfc -L open.c
..\elfc -L close.c
..\elfc -L read.c
..\elfc -L write.c
..\elfc -L lseek.c
..\elfc -L unlink.c
..\elfc -L realloc.c
..\elfc -L min.c
..\elfc -L max.c

type _init.prg _fdinit.prg _fildes.prg abort.prg exit.prg atexit.prg atoi.prg > stdlib.lib
type calloc.prg malloc.prg free.prg itoa.prg itox.prg itou.prg realloc.prg >> stdlib.lib
type creat.prg open.prg close.prg read.prg write.prg lseek.prg unlink.prg >> stdlib.lib
type bsearch.prg qsort.prg rand.prg div.prg abs.prg min.prg max.prg >> stdlib.lib

copy stdlib.lib ..\lib\stdlib.lib
