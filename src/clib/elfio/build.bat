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
..\elfc -L clearerr.c
..\elfc -L fputc.c
..\elfc -L fgetc.c
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
..\elfc -L _rename.c
..\elfc -L rename.c
..\elfc -L fgetpos.c
..\elfc -L fsetpos.c
..\elfc -L fseek.c
..\elfc -L fseek32.c
..\elfc -L ftell.c
..\elfc -L perror.c
..\elfc -L rewind.c
..\elfc -L tmpnam.c
..\elfc -L tmpfile.c
..\elfc -L fileno.c

type clearerr.prg fclose.prg fdopen.prg feof.prg ferror.prg fflush.prg > elfio.lib
type fgetc.prg fgetpos.prg fgets.prg fileno.prg fopen.prg fprintf.prg >> elfio.lib
type fputc.prg fputs.prg fread.prg fscanf.prg fseek32.prg fseek.prg >> elfio.lib
type fsetpos.prg ftell.prg fwrite.prg getch.prg gets.prg kprintf.prg >> elfio.lib
type perror.prg printf.prg putch.prg puts.prg putstr.prg remove.prg >> elfio.lib
type _rename.prg rename.prg rewind.prg scanf.prg sprintf.prg sscanf.prg >> elfio.lib
type tmpfile.prg tmpnam.prg ungetc.prg _vformat.prg vfprintf.prg >> elfio.lib
type vprintf.prg _vscan.prg vsprintf.prg >> elfio.lib

copy elfio.lib ..\lib\elfio.lib
