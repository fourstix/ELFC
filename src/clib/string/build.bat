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

type memchr.prg memcmp.prg memcpy.prg memmove.prg memset.prg strcasecmp.prg> string.lib
type strcasestr.prg strcat.prg strchr.prg strcmp.prg strcpy.prg strcspn.prg >> string.lib
type strdup.prg strerror.prg strim.prg strlcat.prg strlcpy.prg strlen.prg strlwr.prg >> string.lib
type strncasecmp.prg strncat.prg strncmp.prg strncpy.prg strndup.prg strnlen.prg >> string.lib
type strnstr.prg strpbrk.prg strrchr.prg strrev.prg strsep.prg strspn.prg strstr.prg >> string.lib
type strtok.prg strupr.prg >> string.lib

copy string.lib ..\lib\string.lib
