..\elfc -L gets.c
..\elfc -L puts.c
..\elfc -L putstr.c
..\elfc -L getch.c
..\elfc -L putch.c
..\elfc -L fdopen.c
..\elfc -L fclose.c
..\elfc -L fopen.c
..\elfc -L feof.c
..\elfc -L ferror.c
..\elfc -L clrerror.c
..\elfc -L fputc.c
..\elfc -L putchar.c
..\elfc -L fgetc.c
..\elfc -L getchar.c
..\elfc -L fgets.c
..\elfc -L fputs.c
..\elfc -L fread.c
..\elfc -L fwrite.c
..\elfc -L ungetc.c
..\elfc -L _vformat.c
..\elfc -L _vscan.c
..\elfc -L printf.c
..\elfc -L fprintf.c
..\elfc -L sprintf.c
..\elfc -L vprintf.c
..\elfc -L vfprintf.c
..\elfc -L vsprintf.c
..\elfc -L kprintf.c
..\elfc -L fscanf.c
..\elfc -L scanf.c
..\elfc -L sscanf.c
..\elfc -L fflush.c
..\elfc -L remove.c
..\elfc -L rename.c
..\elfc -L fgetpos.c
..\elfc -L fsetpos.c
..\elfc -L fseek.c
..\elfc -L ftell.c


type gets.prg puts.prg putstr.prg getch.prg putch.prg fdopen.prg fclose.prg fopen.prg > stdio.lib
type feof.prg ferror.prg clrerror.prg fputc.prg putchar.prg fgetc.prg getchar.prg >> stdio.lib
type fgets.prg fputs.prg fread.prg fwrite.prg ungetc.prg _vformat.prg _vscan.prg >> stdio.lib
type printf.prg fprintf.prg sprintf.prg vprintf.prg vfprintf.prg vsprintf.prg >> stdio.lib
type kprintf.prg fscanf.prg scanf.prg sscanf.prg fflush.prg remove.prg rename.prg >> stdio.lib
type fgetpos.prg fsetpos.prg fseek.prg ftell.prg >> stdio.lib

copy stdio.lib ..\lib\stdio.lib
