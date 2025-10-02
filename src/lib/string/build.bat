..\elfc -L memchr.c
..\elfc -L memcmp.c
..\elfc -L memcpy.c
..\elfc -L memmove.c
..\elfc -L memset.c
..\elfc -L strcat.c
..\elfc -L strchr.c
..\elfc -L strcmp.c
..\elfc -L strcpy.c
..\elfc -L strcspn.c
..\elfc -L strdup.c
..\elfc -L strerror.c
..\elfc -L strlen.c
..\elfc -L strncat.c
..\elfc -L strncmp.c
..\elfc -L strncpy.c
..\elfc -L strlcpy.c
..\elfc -L strpbrk.c
..\elfc -L strrchr.c
..\elfc -L strspn.c
..\elfc -L strstr.c
..\elfc -L strtok.c
..\elfc -L reverse.c


type memchr.prg memcmp.prg memcpy.prg memmove.prg memset.prg  > string.lib
type strcat.prg strchr.prg strcmp.prg strcpy.prg strcspn.prg strdup.prg >> string.lib
type strerror.prg strlen.prg strncat.prg strncmp.prg strncpy.prg strlcpy.prg >> string.lib
type strpbrk.prg strrchr.prg strspn.prg strstr.prg strtok.prg reverse.prg >> string.lib

copy string.lib ..\lib\string.lib
