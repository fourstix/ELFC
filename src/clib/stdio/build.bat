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
..\elfc -L rename.c
..\elfc -L fgetpos.c
..\elfc -L fsetpos.c
..\elfc -L fseek.c
..\elfc -L ftell.c
..\elfc -L perror.c
..\elfc -L rewind.c
..\elfc -L tmpnam.c
..\elfc -L tmpfile.c
..\elfc -L fileno.c


type gets.prg puts.prg putstr.prg getch.prg putch.prg fdopen.prg fclose.prg > stdio.lib
type fopen.prg feof.prg ferror.prg clearerr.prg fputc.prg fgetc.prg >> stdio.lib
type fgets.prg fputs.prg fread.prg fwrite.prg ungetc.prg _vformat.prg _vscan.prg >> stdio.lib
type printf.prg fprintf.prg sprintf.prg vprintf.prg vfprintf.prg vsprintf.prg >> stdio.lib
type kprintf.prg fscanf.prg scanf.prg sscanf.prg fflush.prg remove.prg rename.prg >> stdio.lib
type fgetpos.prg fsetpos.prg fseek.prg ftell.prg perror.prg  rewind.prg tmpnam.prg >> stdio.lib
type tmpfile.prg fileno.prg >> stdio.lib

copy stdio.lib ..\lib\stdio.lib
