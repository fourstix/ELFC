..\elfc -L _init.c
..\elfc -L _heapinit.c
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
..\elfc -L _conin.c
..\elfc -L _conecho.c

type _conecho.prg _conin.prg _env_read_line.prg _env_split_line.prg _fdinit.prg _fildes.prg > edosstd.lib
type _getch.prg _getstr.prg _heapinit.prg _init.prg _putch.prg _putstr.prg >> edosstd.lib
type _rename.prg _systime.prg abort.prg atexit.prg atoi.prg bsearch.prg >> edosstd.lib
type calloc.prg close.prg creat.prg div.prg exit.prg free.prg >> edosstd.lib
type getenv.prg itoa.prg itou.prg itox.prg lseek.prg lseek32.prg >> edosstd.lib
type malloc.prg open.prg qsort.prg rand.prg read.prg realloc.prg >> edosstd.lib
type setenv.prg unlink.prg unsetenv.prg write.prg >> edosstd.lib

rem modules from the ELF-DOS SDK that are part of this library
cd ..\elfdos-sdk\lib
..\..\asm02 -q -r -L -C -I .. heap_malloc.asm
..\..\asm02 -q -r -L -C -I .. env.asm
..\..\asm02 -q -r -L -C -I .. drives.asm
cd ..\..\edosstd
type ..\elfdos-sdk\lib\heap_malloc.prg ..\elfdos-sdk\lib\env.prg ..\elfdos-sdk\lib\drives.prg >> edosstd.lib

copy edosstd.lib ..\lib\edosstd.lib
