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

type memchr.prg memcmp.prg memcpy.prg memmove.prg memset.prg > string.lib
type reverse.prg strcat.prg strchr.prg strcmp.prg strcpy.prg >> string.lib
type strcspn.prg strdup.prg strerror.prg strlcpy.prg strlen.prg >> string.lib
type strncat.prg strncmp.prg strncpy.prg strpbrk.prg strrchr.prg >> string.lib
type strspn.prg strstr.prg strtok.prg >> string.lib

copy string.lib ..\lib\string.lib
