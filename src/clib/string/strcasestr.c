#define _ELFCLIB_
#include <string.h>

#pragma           extrn Cstrncasecmp
#pragma           extrn Cstrlen

char *strcasestr(const char *s1, const char *s2) {
  size_t len = strlen(s2);
	for (; *s1; s1++) if (!strncasecmp(s1, s2, len)) return (char *)s1;
	return NULL;
}
