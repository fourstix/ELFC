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
..\elfc -L strrev.c
..\elfc -L strnlen.c
..\elfc -L strlcat.c
..\elfc -L strndup.c
..\elfc -L strcasecmp.c
..\elfc -L strncasecmp.c
..\elfc -L strcasestr.c
..\elfc -L strsep.c
..\elfc -L strlwr.c
..\elfc -L strupr.c
..\elfc -L strim.c
..\elfc -L strnstr.c

type memchr.prg memcmp.prg memcpy.prg memmove.prg memset.prg strcasecmp.prg > string.lib
type strcasestr.prg strcat.prg strchr.prg strcmp.prg strcpy.prg >> string.lib
type strcspn.prg strdup.prg strerror.prg strim.prg strlcat.prg >> string.lib
type strlcpy.prg strlen.prg strlwr.prg strncasecmp.prg strncat.prg >> string.lib
type strncmp.prg strncpy.prg strndup.prg strnlen.prg strnstr.prg >> string.lib
type strpbrk.prg strrchr.prg strrev.prg strsep.prg strspn.prg >> string.lib
type strstr.prg strtok.prg strupr.prg >> string.lib

copy string.lib ..\lib\string.lib
