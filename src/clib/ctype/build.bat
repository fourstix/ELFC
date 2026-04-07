..\elfc -L isalnum.c
..\elfc -L isalpha.c
..\elfc -L isascii.c
..\elfc -L isblank.c
..\elfc -L iscntrl.c
..\elfc -L isdigit.c
..\elfc -L isgraph.c
..\elfc -L islower.c
..\elfc -L isprint.c
..\elfc -L ispunct.c
..\elfc -L isspace.c
..\elfc -L isupper.c
..\elfc -L isxdigit.c
..\elfc -L tolower.c
..\elfc -L toupper.c


type isalnum.prg isalpha.prg isascii.prg isblank.prg iscntrl.prg > ctype.lib
type isdigit.prg isgraph.prg islower.prg isprint.prg ispunct.prg >> ctype.lib
type isspace.prg isupper.prg isxdigit.prg tolower.prg  toupper.prg >> ctype.lib

copy ctype.lib ..\lib\ctype.lib
