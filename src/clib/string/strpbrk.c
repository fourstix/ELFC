#define _ELFCLIB_
#include <string.h>

#pragma           extrn Cstrchr


char *strpbrk(const char *s, const char *set) {
	while (*s && !strchr(set, *s))
		s++;
	return *s ? s: NULL;
}
