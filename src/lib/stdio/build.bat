..\elfc -L gets.c
..\elfc -L puts.c


type gets.prg puts.prg > stdio.lib

copy stdio.lib ..\lib\stdio.lib
