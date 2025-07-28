..\elfc -L va_start.c
..\elfc -L va_arg.c
..\elfc -L va_end.c

type va_start.prg va_arg.prg va_end.prg  > stdarg.lib

copy stdarg.lib ..\lib\stdarg.lib
