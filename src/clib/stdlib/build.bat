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

type abort.prg atexit.prg atoi.prg bsearch.prg calloc.prg close.prg > stdlib.lib
type creat.prg div.prg _env_read_line.prg _env_split_line.prg >> stdlib.lib
type exit.prg _fdinit.prg _fildes.prg free.prg _getch.prg >> stdlib.lib
type getenv.prg _getstr.prg _putch.prg _putstr.prg _init.prg >> stdlib.lib
type open.prg itoa.prg itou.prg itox.prg lseek32.prg lseek.prg >> stdlib.lib
type malloc.prg qsort.prg rand.prg read.prg realloc.prg _rename.prg >> stdlib.lib
type setenv.prg _systime.prg unlink.prg unsetenv.prg write.prg >> stdlib.lib

copy stdlib.lib ..\lib\stdlib.lib
