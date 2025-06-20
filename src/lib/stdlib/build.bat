..\elfc -L abort.c
..\elfc -L abs.c
..\elfc -L exit.c


type abs.prg abort.prg exit.prg > stdlib.lib

copy stdlib.lib ..\lib\stdlib.lib
