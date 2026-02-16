..\elfc -L _init.c
..\elfc -L _fdinit.c
..\elfc -L _fildes.c
..\elfc -L abort.c
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
..\elfc -L lseek32.c
..\elfc -L unlink.c
..\elfc -L realloc.c

type _fdinit.prg _fildes.prg _init.prg abort.prg atexit.prg > stdlib.lib
type atoi.prg bsearch.prg calloc.prg close.prg creat.prg >> stdlib.lib
type div.prg exit.prg free.prg itoa.prg itou.prg >> stdlib.lib
type itox.prg lseek.prg malloc.prg open.prg qsort.prg >> stdlib.lib
type rand.prg read.prg realloc.prg unlink.prg write.prg >> stdlib.lib

copy stdlib.lib ..\lib\stdlib.lib
