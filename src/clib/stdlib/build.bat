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
..\elfc -L _env_read_line.c
..\elfc -L _env_split_line.c
..\elfc -L getenv.c
..\elfc -L setenv.c
..\elfc -L unsetenv.c
..\elfc -L _getstr.c
..\elfc -L _putstr.c
..\elfc -L _getch.c
..\elfc -L _putch.c
..\elfc -L _rename.c
..\elfc -L _systime.c

type _env_read_line.prg _env_split_line.prg _fdinit.prg _fildes.prg _getch.prg _getstr.prg > stdlib.lib
type _init.prg _putch.prg _putstr.prg _rename.prg _systime.prg abort.prg >> stdlib.lib
type atexit.prg atoi.prg bsearch.prg calloc.prg close.prg creat.prg >> stdlib.lib
type div.prg exit.prg free.prg getenv.prg itoa.prg itou.prg >> stdlib.lib
type itox.prg lseek.prg lseek32.prg malloc.prg open.prg qsort.prg >> stdlib.lib
type rand.prg read.prg realloc.prg setenv.prg unlink.prg unsetenv.prg >> stdlib.lib
type write.prg >> stdlib.lib

copy stdlib.lib ..\lib\stdlib.lib
